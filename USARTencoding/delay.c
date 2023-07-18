/**
 ******************************************************************************
 * @file    delay.c
 * @author  Kyle Esser
 * @version V1.0
 * @brief   API file that contains all of the delay functions
 ******************************************************************************
 */
#include "delay.h"
#include <stdio.h>
/*
 * Delay routine using the systick timer for a delay in ms
 */
void delay_ms(unsigned int theDelay) {
	volatile uint32_t *const systick_ctrl = STK_CTRL;
	volatile uint32_t *const systick_load = STK_LOAD;
	volatile uint32_t *const systick_val = STK_VAL;

	// set reload value
	*systick_load = F_CPU / 8000 * theDelay;

	// clear VAL
	*systick_val = 0;

	// enable counter
	*systick_ctrl = ENABLE;

	// poll count flag
	while (!(*systick_ctrl & CFLAG)) {
		// polling loop
	}

	*systick_ctrl = 0;

}

/*
 * Delay routine using the systick timer for a delay in us
 */
void delay_us(unsigned int theDelay) {
	volatile uint32_t *const systick_ctrl = STK_CTRL;
	volatile uint32_t *const systick_load = STK_LOAD;
	volatile uint32_t *const systick_val = STK_VAL;

	// set reload value
	*systick_load = F_CPU / 8000000 * theDelay;

	// clear VAL
	*systick_val = 0;

	// enable counter
	*systick_ctrl = ENABLE;

	// poll count flag
	while (!(*systick_ctrl & CFLAG)) {
		// polling loop
	}

	*systick_ctrl = 0;

}
