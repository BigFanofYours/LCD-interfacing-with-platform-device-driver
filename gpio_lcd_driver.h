#ifndef GPIO_LCD_DRIVER_H
#define GPIO_LCD_DRIVER_H

#include <linux/cdev.h>
#include <linux/device.h>

#define GPIO_LINES 7

enum
{
        LCD_RS,
        LCD_EN,
        LCD_RW,
	LCD_D4,
	LCD_D5,
	LCD_D6,
	LCD_D7
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
