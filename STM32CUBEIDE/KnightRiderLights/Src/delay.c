/*
 * delay.c
 *
 *  Created on: Dec 10, 2019
 *      Author: yanga
 */

#include <stdint.h>

#define STK_CTRL 0xE000E010;
#define STK_LOAD 0xE000E014;
#define STK_VAL 0xE000E018;
#define COUNTFLAG (0b01<<16)


void delay_ms(int theDelay)
{
	//insert reload value
	uint32_t *reload = (uint32_t*) STK_LOAD; //reload value
	*reload = theDelay;

	//enable stk
	uint32_t *countenable = (uint32_t*) STK_CTRL;
	int enable = 1;
	*countenable = (*countenable|enable);

	volatile uint32_t *countflag = (uint32_t*) STK_CTRL; //countflag
	while(!(*countflag&COUNTFLAG)) {
	}
}
