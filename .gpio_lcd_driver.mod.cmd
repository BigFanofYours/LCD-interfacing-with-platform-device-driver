savedcmd_gpio_lcd_driver.mod := printf '%s\n'   gpio_lcd_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > gpio_lcd_driver.mod
