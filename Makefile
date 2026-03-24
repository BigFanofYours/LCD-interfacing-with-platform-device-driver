obj-m=gpio_lcd_driver.o
HOST_KERN_DIR=/lib/modules/6.17.0-14-generic/build/

host:
	make -C $(HOST_KERN_DIR) M=$(PWD) modules
clean:
	make -C $(HOST_KERN_DIR) M=$(PWD) clean
