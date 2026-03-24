#ifndef GPIO_LCD_DRIVER_H
#define GPIO_LCD_DRIVER_H

#define GPIO_LINES 3

enum
{
        LCD_RS,
        LCD_EN,
        LCD_DATA
};

struct lcddev_private_data
{
        struct device *dev;
	struct gpio_desc *gpio[GPIO_LINES];
	struct cdev lcd_cdev;
	dev_t device_number;
	char lcdxy[8];
};

#endif
