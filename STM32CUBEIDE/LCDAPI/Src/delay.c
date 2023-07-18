/*
 * delay.c
 *
 *  Created on: Dec 10, 2019
 *      Author: yanga
 */

#include <stdint.h>
#include "delay.h"

void delay_s(int theDelay) {
	int reloadS = SEC*theDelay;
	uint32_t *reload = (uint32_t*) STK_LOAD; //reload value
	uint32_t *stk_ctrl = (uint32_t*) STK_CTRL;
	volatile uint32_t *countflag = (uint32_t*) STK_CTRL; //countflag

	//resets/insert reload value
	*reload &= ~CLR_RELOAD;
	*reload = reloadS;

	//enable stk
	*stk_ctrl = (ENABLE<<CLOCK_SRC);
	*stk_ctrl = (*stk_ctrl|ENABLE);

	while(!(*countflag&COUNTFLAG)) {
	}
	//disable stk
	*stk_ctrl &= ~(DISABLE);

}

void delay_ms(int theDelay) {
	int reloadMs = MS*theDelay;
	uint32_t *reload = (uint32_t*) STK_LOAD; //reload value
	uint32_t *stk_ctrl = (uint32_t*) STK_CTRL;
	volatile uint32_t *countflag = (uint32_t*) STK_CTRL; //countflag

	//resets/insert reload value
	*reload &= ~CLR_RELOAD;
	*reload = reloadMs;

	//enable stk
	*stk_ctrl = (ENABLE<<CLOCK_SRC);
	*stk_ctrl |= (ENABLE);

	while(!(*countflag&COUNTFLAG)) {
	}
	//disable stk
	*stk_ctrl &= ~(DISABLE);
}

void delay_us(int theDelay) {
	int reloadUs = US*theDelay;
	uint32_t *stk_ctrl = (uint32_t*) STK_CTRL;
	uint32_t *reload = (uint32_t*) STK_LOAD; //reload value
	volatile uint32_t *countflag = (uint32_t*) STK_CTRL; //countflag
	//reset/insert reload value
	*reload &= ~CLR_RELOAD;
	*reload = reloadUs;
	*stk_ctrl = (ENABLE<<CLOCK_SRC);
	*stk_ctrl |= (ENABLE);
	while(!(*countflag&COUNTFLAG)) {
	}

	//disable stk
	*stk_ctrl &= ~(DISABLE);
}

void delay_ns(int theDelay) {
	int reloadNs = NS*theDelay;
	//enable stk
	uint32_t *stk_ctrl = (uint32_t*) STK_CTRL;
	uint32_t *reload = (uint32_t*) STK_LOAD; //reload value
	volatile uint32_t *countflag = (uint32_t*) STK_CTRL; //countflag

	//reset/insert reload value
	*reload &= ~CLR_RELOAD;
	*reload = reloadNs;

	*stk_ctrl = (ENABLE<<CLOCK_SRC);
	*stk_ctrl |= ENABLE;

	while(!(*countflag&COUNTFLAG)) {
	}
	//disable stk
	*stk_ctrl &= ~(DISABLE);
}
