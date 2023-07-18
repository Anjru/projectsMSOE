/*
 * lcd.h
 *
 *  Created on: Jan 15, 2020
 *      Author: yanga
 */

#ifndef LCD_H_
#define LCD_H_
#define PERIPH_BASE 0x40000000
#define RCC_BASE (PERIPH_BASE + 0x23800)
#define AHB1ENR (RCC_BASE + 0x30)

#define GPIO_PORT_SPACING 0x400
#define GPIO_BASE (PERIPH_BASE + 0x20000)
#define GPIO_PINS_PER_PORT 16
#define GPIO_C (2 * GPIO_PINS_PER_PORT)
#define GPIO_PORT_C 2 //GPIO C
//
#define LED_NUCLEO_GPIO_PORT 1 // Port B
#define LED_NUCLEO_GPIO_PIN 5
#define LED_NUCLEO_GPIO_PORT_BASE (GPIO_BASE + LED_NUCLEO_GPIO_PORT * GPIO_PORT_SPACING)

#define GPIO_ODR (LED_NUCLEO_GPIO_PORT_BASE + 0x14)
#define GPIO_MODER (LED_NUCLEO_GPIO_PORT_BASE + 0x00)

//
#define LCD_DATA_GPIO_PORT 0 // GPIO A
#define LCD_DATA_GPIO_BASE 8
#define LCD_RS_GPIO (8)
#define LCD_RW_GPIO (9)
#define LCD_E_GPIO (10)
#define LCD_INSTR_FUNCTION_SET 0x20

#define PA8 8
#define PA9 9
#define PA10 10
#define PA11 11


//not sure what to call
#define LCD_DATA_PORT_BASE_A (GPIO_BASE +  LCD_DATA_GPIO_PORT * GPIO_PORT_SPACING)
#define LCD_GPIO_C (GPIO_BASE +  GPIO_PORT_C * GPIO_PORT_SPACING)

#define GPIO_MODER_A (LCD_DATA_PORT_BASE_A + 0x00)
#define GPIO_MODER_C (LCD_GPIO_C + 0x00)

#define GPIO_ODR_A (LCD_DATA_PORT_BASE_A + 0x14)
#define GPIO_ODR_C (LCD_GPIO_C + 0x14)

#define GPIO_BSSR_A (LCD_DATA_PORT_BASE_A + 0x18)

#define LCD_RW_WRITE 0
#define LCD_RW_READ 1
#define LCD_RS_INSTR 0
#define LCD_RS_DATA 1
#define LCD_E_START 1
#define LCD_E_IDLE 0
#define LCD_BUSY 0x80

#define LCD_INSTR_CLEAR_DISPLAY 0x01
#define LCD_INSTR_RETURN_HOME 0x02
#define LCD_INSTR_ENTRY_MODE_SET 0x04

#define LCD_FUNCTION_DATALENGTH_4_BIT 0x00
#define LCD_FUNCTION_DISPLAY_LINES_2 0x08
#define LCD_FUNCTION_FONT_5X11 0x04

#define LCD_DISPLAY_BLINK_ON 0x01
#define LCD_DISPLAY_BLINK_OFF 0x00
#define LCD_DISPLAY_CURSOR_ON 0x02
#define LCD_DISPLAY_CURSOR_OFF 0x00
#define LCD_DISPLAY_DISPLAY_ON 0x04
#define LCD_DISPLAY_DISPLAY_OFF 0x00
#define LCD_INSTR_DISPLAY_ON_OFF 0x08

#define CLR_BITS 0b11
#define CLR_BYTE 0b1111
#define INPUT 0b00
#define OUTPUT 0b01

//Fix prototypes
void lcd_init(void);
void lcd_clear(void);
void lcd_home(void);
void lcd_set_position(void);
int lcd_print_string(char *);
int lcd_print_num(int);


static void lcd_print_char(void);
static void lcd_data(void);
static void lcd_command(void);
static void lcd_write(int, int);
static void lcd_write_setup(int);
static void lcd_write_half (int);


#endif /* LCD_H_ */
