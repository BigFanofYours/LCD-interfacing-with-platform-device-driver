savedcmd_gpio_lcd.o := ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o gpio_lcd.o @gpio_lcd.mod 
