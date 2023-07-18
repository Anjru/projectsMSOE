/*
 * ringbuffer.h
 *
 *  Created on: Jan 21, 2020
 *      Author: yanga
 */


#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#define BUF_SIZE 50
#define NVIC_BASE 0xE000E100
#define NVIC_ISER0 0x000
#define NVIC_ISER1 0x004
#define NVIC_ISER2 0x008
#define UART_BASEA 0x40004000
#define UART_SPACINGA 0x400
#define USART2_BASEA (UART_BASEA + 1*UART_SPACINGA)
#define USART_CR1A 0x0C
#define USART_CR1_TXEIE (1<<7)
#define USART_CR1_RXNE (1<<5)

typedef struct{
	unsigned int put;
	unsigned int get;
	char buffer [BUF_SIZE];
} RingBuffer;

//add element to buffer
void put(RingBuffer*, char);

char get(RingBuffer*);

int hasSpace(RingBuffer*);

int hasElement(RingBuffer*);



#endif /* RINGBUFFER_H_ */

