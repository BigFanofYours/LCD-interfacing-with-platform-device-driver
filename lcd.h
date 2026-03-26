#ifndef LCD_H
#define LCD_H

/*LCD commands */
#define LCD_CMD_4DL_2N_5X8F  		0x28
#define LCD_CMD_DON_CURON    		0x0E
#define LCD_CMD_INCADD       		0x06
#define LCD_CMD_DIS_CLEAR    		0X01
#define LCD_CMD_DIS_RETURN_HOME  	0x02

/*Sets CGRAM address. CGRAM data is sent and received after this setting. */
#define LCD_CMD_SET_CGRAM_ADDRESS  			0x40

/* Sets DDRAM address. DDRAM data is sent and received after this setting. */
#define LCD_CMD_SET_DDRAM_ADDRESS  			0x80

#define DDRAM_SECOND_LINE_BASE_ADDR         	(LCD_CMD_SET_DDRAM_ADDRESS | 0x40 )
#define DDRAM_FIRST_LINE_BASE_ADDR          	LCD_CMD_SET_DDRAM_ADDRESS


#define LCD_ENABLE 1
#define LCD_DISABLE 0


/* public function prototypes */
void lcd_deinit(struct device *dev);
int lcd_init(struct device *dev);
void lcd_display_clear(struct device *dev);
void lcd_display_return_home(struct device *dev);
void lcd_set_cursor(struct device *dev, u8 row, u8 column);
void lcd_enable(struct device *dev);
void lcd_print_char(struct device *dev, u8 data);
void lcd_print_string(struct device *dev, char *buf);
void lcd_send_command(struct device *dev, u8 command);

#endif
