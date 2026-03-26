savedcmd_gpio_lcd.mod := printf '%s\n'   gpio_lcd_driver.o lcd.o gpio.o | awk '!x[$$0]++ { print("./"$$0) }' > gpio_lcd.mod
