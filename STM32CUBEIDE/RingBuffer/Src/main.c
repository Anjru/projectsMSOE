/**
 ******************************************************************************
 * @file    main.c
 * @author  Auto-generated by STM32CubeIDE
 * @version V1.0
 * @brief   Default main function.
 ******************************************************************************
 */

#include <stdio.h>
#include "uart_driver.h"
#include "ringbuffer.h"

#define F_CPU 16000000UL

// main
int main(void){
	init_usart2(19200,F_CPU);

	//infinite loop
	printf("%s", "Type \"help\" to assist you input correctly \n\r");
	//infinite loop
	while (1 != 0) {
		char user_input[50];
		fgets(user_input, sizeof(user_input), stdin);
		char* input = strtok(user_input, "\n");

		//splits input by spaces
		//retrieves command
		char* token = strtok(input, " ");
		char command[3];
		sprintf(command, "%s", token);

		//retrieves address
		token = strtok(NULL, " ");
		char address[33];
		sprintf(address, "%s", token);
		uint32_t address_convert = (uint32_t)strtoll(address, NULL, 16);

		//retrives value
		//wm, value is to be written in selected address
		//dm, value is for number of bytes to be dumped
		token = strtok(NULL, " ");
		char value[10];
		int default_bytes = 16;
		sprintf(value, "%s", token);
		uint32_t value_converted = (uint32_t)strtoll(value, NULL, 16);
		uint32_t *address_data = (uint32_t) address_convert;

		if((command[0] == 'r')&& (command[1] == 'm')) {
			printf("Hex:%X, Dec:%d \n\r", *address_data, *address_data);

		} else if ((command[0] == 'w')&&(command[1] == 'm')) {
			*address_data = value_converted;

		} else if ((command[0] == 'd')&&(command[1] == 'm')) {
			if (value_converted == 0){
				value_converted = default_bytes;
			}
			int word_per_line = 4;
			printf("%X: ", address_data);
			//repeats while there are more bytes to be read or
			//the line needs to be filled with 16 bytes
			while ((value_converted > 0) || (word_per_line != 0)){
				if (word_per_line == 0) {
					printf("\n\r%\X: ", address_data);
					word_per_line = 4;
				}
				printf("%08X ", *address_data);
				address_data ++;
				//decreases by 4 because there are 4 bytes per word
				value_converted -= 4;
				word_per_line --;
			}
			printf("\n\r");

		} else if ((command[0] == 'h')&&(command[1] == 'e')&&
				(command[2] == 'l')&& (command[3] == 'p')) {
			printf("There are 3 commands, rm, wm, and dm.\r\n");
			printf("rm is to read memory from a given address.\n\r");
			printf("wm is to write memory in hex to a given address.\n\r");
			printf("dm is to dump memory from a given address.\n\r");
			printf("Type the command, then press space and enter an address.\n\r");
			printf("The address should be enterd in hex form and can add/exclude 0x\n\r");
			printf("Lastly, press space again and choose a value.\n\r");
			printf("If command wm is chosen, the value will be placed into the given address.\n\r");
			printf("If command dm is chosen, the value is the number of bytes to dump.\n\r");
			printf("The value has no usefulness for the rm command.\n\r");
		} else {
			printf("Error, retype\n\r");
		}
	}
	//for(;;){}

	return 0;
}

////////////////////////////////////////////////////////////
/*
 * uart_driver.c
 *
 *  Created on: Nov 8, 2016
 *      Author: barnekow
 */
#include "uart_driver.h"
#include <inttypes.h>
#include <stdio.h>
#include "ringbuffer.h"

static RingBuffer receivebuffer = {0,0};
static RingBuffer transmitbuffer = {0,0};

// These will override _read and _write in syscalls.c, which are
// prototyped as weak
int _read(int file, char *ptr, int len)
{
	int DataIdx;
	// Modified the for loop in order to get the correct behavior for fgets
	int byteCnt = 0;
	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		//*ptr++ = __io_getchar();
		byteCnt++;
		//*ptr++ = usart2_getch();
		*ptr = usart2_getch();
		if(*ptr == '\n') break;
		ptr++;
	}

	//return len;
	return byteCnt; // Return byte count
}

int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		usart2_putch(*ptr++);
	}
	return len;
}


char usart2_getch(){
	char c;
	while(!hasElement(&receivebuffer)){
	}
	c = get(&receivebuffer);
	//echo to transmit buffer
	put(&transmitbuffer, c);
	uint32_t *txe_int = (uint32_t)(USART_CR1);
	*txe_int |= (USART_CR1_TXEIE);
	if (c == '\r'){  // If character is CR
		usart2_putch('\n');  // send it
		c = '\n';   // Return LF. fgets is terminated by LF
	}

	return c;
}

void usart2_putch(char c){
	while((*(USART_SR)&(1<<TXE)) != (1<<TXE));
	*(USART_DR) = c;
}

void init_usart2(uint32_t baud, uint32_t sysclk){
	// Enable clocks for GPIOA and USART2
	*(RCC_AHB1ENR) |= (1<<GPIOAEN);
	*(RCC_APB1ENR) |= (1<<USART2EN);

	// Function 7 of PORTA pins is USART
	*(GPIOA_AFRL) &= (0xFFFF00FF); // Clear the bits associated with PA3 and PA2
	*(GPIOA_AFRL) |= (0b01110111<<8);  // Choose function 7 for both PA3 and PA2
	*(GPIOA_MODER) &= (0xFFFFFF0F);  // Clear mode bits for PA3 and PA2
	*(GPIOA_MODER) |= (0b1010<<4);  // Both PA3 and PA2 in alt function mode

	// Set up USART2
	//USART2_init();  //8n1 no flow control
	// over8 = 0..oversample by 16
	// M = 0..1 start bit, data size is 8, 1 stop bit
	// PCE= 0..Parity check not enabled
	// no interrupts... using polling
	*(USART_CR1) = (1<<UE)|(1<<TE)|(1<<RE); // Enable UART, Tx and Rx
	*(USART_CR2) = 0;  // This is the default, but do it anyway
	*(USART_CR3) = 0;  // This is the default, but do it anyway
	*(USART_BRR) = sysclk/baud;

	//enable interrupt
	uint32_t *nvic = (uint32_t) (NVIC_BASE + NVIC_ISER1);
	*nvic |= (1 << 6);

	//enable RXNE bit
	uint32_t *rxne_int = (uint32_t)(USART_CR1);
	*rxne_int |= (USART_CR1_RXNE);

	/* I'm not sure if this is needed for standard IO*/
	 //setvbuf(stderr, NULL, _IONBF, 0);
	 //setvbuf(stdin, NULL, _IONBF, 0);
	 setvbuf(stdout, NULL, _IONBF, 0);
}

void USART2_IRQHandler() {
	//RXNE
	if((*(USART_SR)&(1<<RXNE)) == (1<<RXNE)) {
	put(&receivebuffer, (*(USART_DR)));
	}

	//TXE
	if(hasElement(&transmitbuffer)) {
		*(USART_DR) = get(&transmitbuffer);

	} else {
		//disable_txe_interrupt
		uint32_t *txe_int = (uint32_t)(USART_CR1);
		*txe_int &= ~(USART_CR1_TXEIE);
	}
}


////////////////////////////////////////////////////////////
/*
 * ringbuffer.c
 *
 *  Created on: Jan 21, 2020
 *      Author: yanga
 */

#include <stdio.h>
#include "ringbuffer.h"

//add element to buffer
void put(RingBuffer* buffer, char element) {
	buffer->buffer[buffer->put] = element;
	buffer->put++;;
	//put overwrites get so get must increment
	if(buffer->put == buffer->get) {
		buffer->get++;
	}
	if (buffer->put >= BUF_SIZE) {
		buffer->put = 0;
	}
}

//recieve char
char get(RingBuffer* buffer) {
	//blocks if buffer is empty
	//if get is 1 less than 1, get doesnt increment
	char returned = buffer->buffer[buffer->get];
	if(buffer->get == (buffer->put)) {
		char returned = buffer->buffer[buffer->get];
	} else {
	char returned = buffer->buffer[buffer->get];
	buffer->get++;
	//if get is greater than or equal to buffer size-1, restart to 0
	if (buffer->get >= (BUF_SIZE)) {
		buffer->get = 0;
	}
	}
	return returned;
}

int hasSpace(RingBuffer* buffer) {
	if(buffer->put==((buffer->get)-1)){
		return 0;
	} else {
		return 1;
	}
}

int hasElement(RingBuffer* buffer) {
	if(buffer->get == buffer->put) {
		return 0;
	} else {
		return 1;
	}
}



////////////////////////////////////////////////////////////
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


