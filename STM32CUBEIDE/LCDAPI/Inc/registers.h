#ifndef REGISTERS_H
#define REGISTERS_H

// RCC Peripheral
#define RCC_BASE 0x40023800

// AHB1ENR and bits
#define AHB1ENR  0x30

#define GPIOAEN	0
#define GPIOBEN	1
#define GPIOCEN	2
#define GPIODEN	3
#define GPIOEEN	4
#define GPIOFEN	5
#define GPIOGEN	6
#define GPIOHEN	7
#define CRCEN	12
#define BKPSRAMEN	18
#define DMA1EN	21
#define DMA2EN	22
#define OTGHSEN	29
#define OTGHSULPIEN	30

#define GPIOAENB	0x1
#define GPIOBENB	0x2
#define GPIOCENB	0x4
#define GPIODENB	0x8
#define GPIOEENB	0x10
#define GPIOFENB	0x20
#define GPIOGENB	0x40
#define GPIOHENB	0x80



// GPIO peripherals
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800

// GPIO registers
#define MODER 0
#define OTYPER 1
#define OSPEEDR 2
#define PUPDR 3
#define IDR 4
#define ODR 5
#define BSRR 6

// GPIO Bits
#define DR0 0
#define DR1 1
#define DR2 2
#define DR3 3
#define DR4 4
#define DR5 5
#define DR6 6
#define DR7 7
#define DR8 8
#define DR9 9
#define DR10 10
#define DR11 11
#define DR12 12
#define DR13 13
#define DR14 14
#define DR15 15

// GPIO MODER settings and bits
#define INPUT 0
#define OUTPUT 1
#define ALTERNATE 2
#define ANALOG 3

#define MODER0 0
#define MODER1 2
#define MODER2 4
#define MODER3 6
#define MODER4 8
#define MODER5 10
#define MODER6 12
#define MODER7 14
#define MODER8 16
#define MODER9 18
#define MODER10 20
#define MODER11 22
#define MODER12 24
#define MODER13 26
#define MODER14 28
#define MODER15 30

// GPIO PUPDR settings and bits
#define NO_PU_PD 0
#define PULL_UP 1
#define PULL_DOWN 2
#define RESERVED 3

#define PUPDR0 0
#define PUPDR1 2
#define PUPDR2 4
#define PUPDR3 6
#define PUPDR4 8
#define PUPDR5 10
#define PUPDR6 12
#define PUPDR7 14
#define PUPDR8 16
#define PUPDR9 18
#define PUPDR10 20
#define PUPDR11 22
#define PUPDR12 24
#define PUPDR13 26
#define PUPDR14 28
#define PUPDR15 30



#endif
