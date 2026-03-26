#include <linux/gpio/consumer.h>
#include <linux/device.h>
#include <linux/cdev.h>

#include "gpio.h"
#include "gpio_lcd_driver.h"

int gpio_configure_dir(struct device *dev, u8 desc_id, u8 dir_value)
{
	int ret;
	struct lcddev_private_data *lcd_data = dev_get_drvdata(dev);
	if(dir_value)
		ret = gpiod_direction_output(lcd_data->gpio[desc_id], 0);
	else 
		ret = gpiod_direction_input(lcd_data->gpio[desc_id]);
	return ret;
}

int gpio_write_value(struct device *dev, u8 desc_id, u8 value)
{
	struct lcddev_private_data *lcd_data = dev_get_drvdata(dev); 
	gpiod_set_value(lcd_data->gpio[desc_id],value);
	return 0;
}
