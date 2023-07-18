#ifndef SPEAKER_H_
#define SPEAKER_H_

#include <inttypes.h>

// RCC_AHB1ENR & GPIOB position
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define GPIOB_EN 1

// RCC AHB3 & TIM3 position
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define TIM3 1

// GPIOB registers
#define GPIOB_BASE (volatile uint32_t*) 0x40020400
#define GPIOB_MODR (volatile uint32_t*) 0x40020400
#define GPIOB_AFRL (volatile uint32_t*) 0x40020420
#define GPIOB_ODR (volatile uint32_t*) 0x40020414
// TIM3 registers
#define TIM3_CCMR1  (volatile uint32_t*) 0x40000418
#define TIM3_CCER   (volatile uint32_t*) 0x40000420
#define TIM3_ARR (volatile uint32_t*) 0x4000042C
#define TIM3_CCR1 (volatile uint32_t*) 0x40000434
#define TIM3_CR1 (volatile uint32_t*) 0x40000400


// AFRL function mask
#define FUNC2 0b0010 << 16

// Speaker pin position
#define SPEAKER 8

// tones
#define Do 440
#define Re 493
#define Mi 554
#define Fa 587
#define Sol 659
#define La 739
#define Ti 830
#define Do1 880

typedef struct {
    uint16_t note;
    uint32_t dur;
} tone;

/*
* Speaker initiation function
*/
void init_speaker();
void speak(uint16_t frequency, uint32_t duration);
void play(tone tones[], int size);

#endif /* SPEAKER_H_ */
