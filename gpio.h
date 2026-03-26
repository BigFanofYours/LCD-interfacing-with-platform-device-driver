#ifndef GPIO_H
#define GPIO_H

#include<linux/types.h>

#define HIGH_VALUE          1
#define LOW_VALUE           0

#define GPIO_DIR_OUT        HIGH_VALUE
#define GPIO_DIR_IN         LOW_VALUE

#define GPIO_LOW_VALUE      LOW_VALUE
#define GPIO_HIGH_VALUE     HIGH_VALUE

int gpio_configure_dir(struct device *dev, u8 desc_id , u8 dir_value);
int gpio_write_value(struct device *dev, u8 desc_id, u8 value);

#endif
