/*
 * tune.h
 *
 *  Created on: Feb 10, 2020
 *      Author: yanga
 */

#ifndef INC_TUNE_H_
#define INC_TUNE_H_

// TIM3 registers
#define TIM3_CCMR1  (volatile uint32_t*) 0x40000418
#define TIM3_CCER   (volatile uint32_t*) 0x40000420
#define TIM3_ARR (volatile uint32_t*) 0x4000042C
#define TIM3_CCR1 (volatile uint32_t*) 0x40000434
#define TIM3_CR1 (volatile uint32_t*) 0x40000400

//Notes
#define C
#define D
#define E
#define F
#define G
#define A
#define B

typedef struct {
	uint16_t note;
	uint32_t duration;
} Notes;


#endif /* INC_TUNE_H_ */
