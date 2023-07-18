/*
 * delay.h
 *
 *  Created on: Dec 10, 2019
 *      Author: yanga
 */

#ifndef DELAY_H_
#define DELAY_H_

#define STK_CTRL 0xE000E010;
#define STK_LOAD 0xE000E014;
#define STK_VAL 0xE000E018;
#define COUNTFLAG (0b01<<16)
#define CLOCK_SRC (2)
#define CLR_RELOAD 0xFFFFFF
#define SEC 16000000
#define MS 16000
#define US 16
#define NS 1
#define ENABLE 1
#define DISABLE 1

void delay_ms(int);
void delay_us(int);
void delay_ns(int);
void delay_s(int);

#endif /* DELAY_H_ */
