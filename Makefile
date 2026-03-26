obj-m=gpio_lcd.o
gpio_lcd-objs += gpio_lcd_driver.o lcd.o gpio.o
ARCH = arm
CROSS_COMPILE=arm-linux-gnueabihf-
HOST_KERN_DIR=/lib/modules/6.17.0-14-generic/build/

host:
	make -C $(HOST_KERN_DIR) M=$(PWD) modules
clean:
	make -C $(HOST_KERN_DIR) M=$(PWD) clean
