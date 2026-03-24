#include "gpio.h"
#include "gpio_lcd_driver.h"

int gpio_write_value(struct device *dev, u8 desc_id, u8 value)
{
	struct lcddev_private_data *lcd_data = dev_get_drvdata(dev); 
	gpiod_set_value(lcd_data->gpio[desc_id],value);
	return 0;
}
