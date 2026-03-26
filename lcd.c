#include <linux/device.h>
#include <linux/delay.h>
#include "gpio.h"
#include "lcd.h"
#include "gpio_lcd_driver.h"

static void write_4_bits(struct device *dev, u8 data)
{
        gpio_write_value(dev, LCD_D4, (data >> 0) & 0x1);
        gpio_write_value(dev, LCD_D5, (data >> 1) & 0x1);
        gpio_write_value(dev, LCD_D6, (data >> 2) & 0x1);
        gpio_write_value(dev, LCD_D7, (data >> 3) & 0x1);
}

void lcd_deinit(struct device *dev)
{
	lcd_display_clear(dev);      	
	lcd_display_return_home(dev);        
}


int lcd_init(struct device *dev)
{
	gpio_configure_dir(dev, LCD_RS, GPIO_DIR_OUT);
	gpio_configure_dir(dev, LCD_RW, GPIO_DIR_OUT);
	gpio_configure_dir(dev, LCD_EN, GPIO_DIR_OUT);
	gpio_configure_dir(dev, LCD_D4, GPIO_DIR_OUT);
	gpio_configure_dir(dev, LCD_D5, GPIO_DIR_OUT);
	gpio_configure_dir(dev, LCD_D6, GPIO_DIR_OUT);
	gpio_configure_dir(dev, LCD_D7, GPIO_DIR_OUT);

	gpio_write_value(dev, LCD_RS, GPIO_LOW_VALUE);
	gpio_write_value(dev, LCD_EN, GPIO_LOW_VALUE);

	gpio_write_value(dev, LCD_D4, GPIO_LOW_VALUE);
	gpio_write_value(dev, LCD_D5, GPIO_LOW_VALUE);
	gpio_write_value(dev, LCD_D6, GPIO_LOW_VALUE);
	gpio_write_value(dev, LCD_D7, GPIO_LOW_VALUE);

	mdelay(40);
	
	/* RS=0 for LCD command */
	gpio_write_value(dev, LCD_RS, LOW_VALUE);
	
	/*R/nW = 0, for write */
	gpio_write_value(dev, LCD_RW, LOW_VALUE);
	
	write_4_bits(dev, 0x03);
	mdelay(5);
	
	write_4_bits(dev, 0x03);
	udelay(150);
	
	write_4_bits(dev, 0x03);
	write_4_bits(dev, 0x02);

    	/*4 bit data mode, 2 lines selection , font size 5x8 */
	lcd_send_command(dev, LCD_CMD_4DL_2N_5X8F);
	
	/* Display ON, Cursor ON */
	lcd_send_command(dev, LCD_CMD_DON_CURON);
	
	lcd_display_clear(dev);
	
	/*Address auto increment*/
	lcd_send_command(dev, LCD_CMD_INCADD);

	return 0;

}

void lcd_display_clear(struct device *dev)
{
	lcd_send_command(dev, LCD_CMD_DIS_CLEAR);
	mdelay(2);
}

void lcd_display_return_home(struct device *dev)
{
	lcd_send_command(dev, LCD_CMD_DIS_RETURN_HOME);
	mdelay(2);
}

void lcd_set_cursor(struct device *dev, u8 row, u8 column)
{
	column--;
  	switch (row)
  	{
    		case 1:
      			lcd_send_command(dev, (column |= DDRAM_FIRST_LINE_BASE_ADDR));
      			break;
    		case 2:
        		lcd_send_command(dev, (column |= DDRAM_SECOND_LINE_BASE_ADDR));
     	 		break;
    		default:
      			break;
  	}
}

void lcd_enable(struct device *dev)
{ 
	gpio_write_value(dev, LCD_EN,LOW_VALUE);
	udelay(10);
	gpio_write_value(dev, LCD_EN,HIGH_VALUE);
	udelay(10);
	gpio_write_value(dev, LCD_EN,LOW_VALUE);
	udelay(100); /* execution time > 37 micro seconds */
}

void lcd_print_char(struct device *dev, u8 data)
{
	gpio_write_value(dev, LCD_RS, HIGH_VALUE);
	gpio_write_value(dev, LCD_RW, LOW_VALUE);
	write_4_bits(dev, (data >> 4));
	write_4_bits(dev, data);
}

void lcd_print_string(struct device *dev, char *buf)
{
	do
	{
		lcd_print_char(dev, (u8)*buf++);
	}while(*buf != '\0');
}

void lcd_send_command(struct device *dev, uint8_t command)
{
	/* RS=0 for LCD command */
	gpio_write_value(dev, LCD_RS,LOW_VALUE);
	
	/*R/nW = 0, for write */
	gpio_write_value(dev, LCD_RW,LOW_VALUE);
	
	write_4_bits(dev, (command >> 4)); /* higher nibble */
	write_4_bits(dev, command);     /* lower nibble */

}

