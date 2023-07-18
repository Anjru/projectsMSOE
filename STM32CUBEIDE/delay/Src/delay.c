/*
 * delay.c
 *
 *  Created on: Dec 10, 2019
 *      Author: yanga
 */

//#define StK_CtrL = 0xE000E010;

void delay_ms(int theDelay)
{
	//enable stk
	uint32_t *stk_ctrl = (uint32_t*) 0xE000E010; //systick timer
	int enable = 1;
	*stck_ctrl = stck_ctrl|enable;

	//insert reload value
	//theDelay to binary?
	uint32_t *stk_load = (uint32_t*) 0xE000E014; //reload value
	*stk_load = theDelay;

	//stops counter
	*stck_ctrl = (stck_ctrl&~(enable));
}
