#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/gpio/consumer.h>
#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/sysfs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include "gpio_lcd_driver.h"
#include "lcd.h"

static struct class *class_lcd;

static ssize_t lcdxy_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct lcddev_private_data *lcd_data = dev_get_drvdata(dev); 
	int ret, x, y;
	long value;
	ret = kstrtol(buf, 10, &value);
	if(ret)
		return ret;
	x = value / 10;
	y = value % 10;
	ret = sprintf(lcd_data->lcdxy, "(%d, %d)", x, y);
	return ret;	
}

static ssize_t lcdxy_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret;
	struct lcddev_private_data *dev_data = dev_get_drvdata(dev);
	ret = sprintf(buf, "%s\n", dev_data->lcdxy);
	return ret;
}

static DEVICE_ATTR_RW(lcdxy);

static struct attribute *lcd_attrs[] = 
{
	&dev_attr_lcdxy.attr
};

static struct attribute_group lcd_attr_group = 
{
	.attrs = lcd_attrs
};

static const struct attribute_group *lcd_attr_groups[] = 
{
	&lcd_attr_group,
	NULL
};

static int lcd_open(struct inode *inode, struct file *filp)
{
	struct lcddev_private_data *lcd_data;
	lcd_data = container_of(inode->i_cdev, struct lcddev_private_data, lcd_cdev);
	filp->private_data = lcd_data; 
	pr_info("Open was successful\n");
	return 0;
}

static int lcd_release(struct inode *inode, struct file *filp)
{
	pr_info("Release was successful\n");
	return 0;
}

static ssize_t lcd_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	return -EINVAL;
}

static ssize_t lcd_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct lcddev_private_data *lcd_data = (struct lcddev_private_data*) filp->private_data;
	char kbuf[64];
	if(count > 64)
	{
		pr_info("Only 64 characters are allowed\n");
		return -EINVAL;
	}
	if(copy_from_user(&kbuf, buf, count))
	{
		return -EFAULT;
	}
	lcd_print_string(lcd_data->dev, kbuf);
	return 0;
}


static struct file_operations fops = 
{
	.open = lcd_open,
	.release = lcd_release,
	.read = lcd_read,
	.write = lcd_write,
	.owner = THIS_MODULE
};

static int gpio_lcd_driver_probe(struct platform_device *pdev)
{
	int ret;
	struct lcddev_private_data *lcd_data;
	struct device *dev = &pdev->dev;

	/* Allocating memory and resources for struct and GPIOs */
	lcd_data = devm_kzalloc(dev, sizeof(*lcd_data), GFP_KERNEL);
	if(!lcd_data)
		return -ENOMEM;	
	lcd_data->gpio[LCD_RS] = devm_gpiod_get(dev, "rs", GPIOD_OUT_LOW);
	lcd_data->gpio[LCD_EN] = devm_gpiod_get(dev, "en", GPIOD_OUT_LOW);
	lcd_data->gpio[LCD_RW] = devm_gpiod_get(dev, "rw", GPIOD_OUT_LOW);
	lcd_data->gpio[LCD_D4] = devm_gpiod_get(dev, "d4", GPIOD_OUT_LOW);
	lcd_data->gpio[LCD_D5] = devm_gpiod_get(dev, "d5", GPIOD_OUT_LOW);
	lcd_data->gpio[LCD_D6] = devm_gpiod_get(dev, "d6", GPIOD_OUT_LOW);
	lcd_data->gpio[LCD_D7] = devm_gpiod_get(dev, "d7", GPIOD_OUT_LOW);

	if(IS_ERR(lcd_data->gpio[LCD_RS]) || \
		IS_ERR(lcd_data->gpio[LCD_EN]) || \
		IS_ERR(lcd_data->gpio[LCD_RW]) || \
		IS_ERR(lcd_data->gpio[LCD_D4]) || \
		IS_ERR(lcd_data->gpio[LCD_D5]) || \
		IS_ERR(lcd_data->gpio[LCD_D6]) || \
		IS_ERR(lcd_data->gpio[LCD_D7]))
	{ 
		dev_err(dev, "GPIO assignment error\n");
		return -EINVAL;
	}

	/* Bind device data to pdev */
	dev_set_drvdata(dev, lcd_data);
	
	lcd_init(dev);

	/* Creating character device interface */
	ret = alloc_chrdev_region(&lcd_data->device_number, 0, 1, "lcddev");
	if(ret < 0)
	{
		dev_err(dev, "Device number allocation failed\n");
		return ret;
	}
	cdev_init(&lcd_data->lcd_cdev, &fops);
      	ret = cdev_add(&lcd_data->lcd_cdev, lcd_data->device_number, 1);	
	if(ret < 0)
	{
		dev_err(dev, "cdev_add failed\n");
		unregister_chrdev_region(lcd_data->device_number, 1);
		return ret;
	} 

	/* Creating /dev and sysfs attributes */
	struct device *char_dev = device_create_with_groups(class_lcd, &pdev->dev, lcd_data->device_number, lcd_data, lcd_attr_groups, "LCD");
	if(IS_ERR(lcd_data->dev))
	{
		dev_err(dev, "Error creating class entry\n");
		return PTR_ERR(lcd_data->dev);
	}
	dev_info(dev, "Probe was successful\n");	
	return 0;
}

static void gpio_lcd_driver_remove(struct platform_device *pdev)
{
	struct lcddev_private_data *lcd = dev_get_drvdata(&pdev->dev);
	device_destroy(class_lcd, lcd->device_number);
	cdev_del(&lcd->lcd_cdev);
	unregister_chrdev_region(lcd->device_number, 1);
	lcd_deinit(&pdev->dev);
}

struct of_device_id gpio_lcd_device_match[] = 
{
	{.compatible = "org, gpio-lcd"},
	{ }
};

struct platform_driver gpio_lcd_driver =
{
	.probe = gpio_lcd_driver_probe,
	.remove = gpio_lcd_driver_remove,
	.driver = 
	{
		.name = "gpio-lcd",
		.of_match_table = of_match_ptr(gpio_lcd_device_match)
	}
};

static int __init gpio_lcd_driver_init(void)
{	
	class_lcd = class_create("lcd");
	platform_driver_register(&gpio_lcd_driver);
	pr_info("Module loaded successfully\n");
	return 0;
}

static void __exit gpio_lcd_driver_exit(void)
{
	platform_driver_unregister(&gpio_lcd_driver);
	class_destroy(class_lcd);
	pr_info("Module unloaded successfully\n");
}

module_init(gpio_lcd_driver_init);
module_exit(gpio_lcd_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PPD");
MODULE_DESCRIPTION("A device driver interfacing with LCD");
