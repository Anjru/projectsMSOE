/*
 * lcd.c
 *
 *  Created on: Jan 13, 2020
 *      Author: yanga
 */

#include <stdio.h>
#include "uart_driver.h"
#include <stdint.h>
#include "lcd.h"

#define F_CPU 16000000UL

void lcd_init(void) {
	//enable clock register (gpio A)
	uint32_t *rcc = (uint32_t*) AHB1ENR;
	*rcc = (*rcc|(1<<LCD_DATA_GPIO_PORT));

	//enable gpio C
	*rcc = (*rcc|(1<<GPIO_PORT_C));

	//For GPIO MODER A, set mode to output for P8-11
	uint32_t *gpioModeA = (uint32_t*) GPIO_MODER_A;
	*gpioModeA = (*gpioModeA|(OUTPUT<<(PA8*2)));
	*gpioModeA = (*gpioModeA|(OUTPUT<<(PA9*2)));
	*gpioModeA = (*gpioModeA|(OUTPUT<<(PA10*2)));
	*gpioModeA = (*gpioModeA|(OUTPUT<<(PA11*2)));

	//gpio MODER for C set to output
	uint32_t *gpioModeC = (uint32_t*) GPIO_MODER_C;

	//RS_GPIO is resetted and set to output
	*gpioModeC &= ~(CLR_BITS<<(LCD_RS_GPIO*2));
	*gpioModeC = (*gpioModeC|(OUTPUT<<(LCD_RS_GPIO*2)));

	//RW_GPIO is resetted and set to output
	*gpioModeC &= ~(CLR_BITS<<(LCD_RW_GPIO*2));
	*gpioModeC = (*gpioModeC|(OUTPUT<<(LCD_RW_GPIO*2)));

	//E_GPIO is resetted and set to output
	*gpioModeC &= ~(CLR_BITS<<(LCD_E_GPIO*2));
	*gpioModeC = (*gpioModeC|(OUTPUT<<(LCD_E_GPIO*2)));

	//CONFIGURE DISPLAY
	//delay 41 miliseconds
	delay_ms(41);

	lcd_write_setup(LCD_RS_INSTR);

	lcd_write_half((LCD_INSTR_FUNCTION_SET|LCD_FUNCTION_DATALENGTH_4_BIT)>>4);

	//delay 38 microseconds
	delay_us(38);

	lcd_write(LCD_RS_INSTR, LCD_INSTR_FUNCTION_SET|
			LCD_FUNCTION_DATALENGTH_4_BIT|
			LCD_FUNCTION_DISPLAY_LINES_2|
			LCD_FUNCTION_FONT_5X11);

	//delay 38 microseconds
	delay_us(38);

	lcd_write(LCD_RS_INSTR, LCD_INSTR_FUNCTION_SET|
				LCD_FUNCTION_DATALENGTH_4_BIT|
				LCD_FUNCTION_DISPLAY_LINES_2|
				LCD_FUNCTION_FONT_5X11);

	//delay 80 us
	delay_us(80);

	//turn on display
	lcd_write(LCD_RS_INSTR, LCD_INSTR_DISPLAY_ON_OFF|LCD_DISPLAY_DISPLAY_ON|
			LCD_DISPLAY_CURSOR_ON|LCD_DISPLAY_BLINK_ON);

	lcd_clear();

	lcd_home();
}

//clears lcd
void lcd_clear() {
	//delay for 80 microseconds
	delay_us(80);
	lcd_write(LCD_RS_INSTR, LCD_INSTR_CLEAR_DISPLAY);


}

//sets lcd to home
void lcd_home() {
	//delays for 80 microseconds
	delay_us(80);
	lcd_write(LCD_RS_INSTR, LCD_INSTR_RETURN_HOME);
}

void static lcd_write_setup(int rs) {
	uint32_t *gpioModeA = (uint32_t*) GPIO_MODER_A;
	//turn RS ODR on or off (rs)
	uint32_t *gpioODRC = (uint32_t*) GPIO_ODR_C;
	//clears ODR for RS
	*gpioODRC &= ~(1 << LCD_RS_GPIO);
	*gpioODRC |= (rs << LCD_RS_GPIO);

	//mask GPIOA moder P8-11
	*gpioModeA &= ~(0xFF<<(LCD_DATA_GPIO_BASE * 2));
	//sets P8-P11 to output mode
	*gpioModeA |= (0b01010101 << (LCD_DATA_GPIO_BASE * 2));

	//set RW to write mode
	*gpioODRC &= ~(1 << LCD_RW_GPIO);
	*gpioODRC |= (LCD_RW_WRITE << LCD_RW_GPIO);
}


void static lcd_write(int rs, int value) {
	uint32_t *gpioBSSRA = (uint32_t*) GPIO_BSSR_A;
	lcd_write_setup(rs);
	//writes the upper byte of value
	lcd_write_half(value >> 4);
	//writes the lower byte of value
	lcd_write_half(value&(0x0F));

	*gpioBSSRA |= (0b1111 << LCD_DATA_GPIO_BASE);
}

void static lcd_write_half (int bit) {
	uint32_t *gpioODRC = (uint32_t*) GPIO_ODR_C;
	uint32_t *gpioODRA = (uint32_t*)GPIO_ODR_A;

	//start E ODR
	*gpioODRC &= ~(1 << LCD_E_GPIO);
	*gpioODRC |= (LCD_E_START << LCD_E_GPIO);

	//delay 1 microsecond
	delay_us(1);

	//gpioA ODR
	//mask 8-11
	*gpioODRA &= ~(CLR_BYTE<<(LCD_DATA_GPIO_BASE));
	*gpioODRA |= (bit<<LCD_DATA_GPIO_BASE);

	//delay for 1 microseconds
	delay_us(1);

	//turn off E
	*gpioODRC &= ~(1 << LCD_E_GPIO);
	*gpioODRC |= (LCD_E_IDLE << LCD_E_GPIO);

	//delay 10 ns
	delay_ns(10);
}


//not being used
void lcd_set_position() {
	delay_us(80);
	lcd_write(LCD_RS_INSTR, LCD_INSTR_ENTRY_MODE_SET);
}


//Print a null terminated string to display
//Param: poninter to null-terminated string
//return number of characters written to display
int lcd_print_string(char *string) {
	//delay for 80 microseconds
	delay_us(80);

	int index = 0;
	while(string[index] != 0) {
	lcd_write(LCD_RS_DATA, string[index]);
	index++;
	}
	return index;
}

//prints decimal number to display
//Param: number printed
//return: number of char written to display
//send to pring string
int lcd_print_num(int num){
	//delay 80 microseconds
	delay_us(80);
	char buffer[50];
	snprintf(buffer, 50, "%d", num);

	return lcd_print_string(buffer);
}


