/*
 ============================================================================
 Name        : hello2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	setvbuf(stdout,NULL, _IONBF, 0);
	setvbuf(stdout,NULL, _IONBF, 0);

	char name[50];
	puts("Enter your name: ");

	fgets(name,50,stdin);


	printf("Hello %s!!!\n", name); /* prints !!!Hello World!!! */

	return EXIT_SUCCESS;
}
