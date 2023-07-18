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

