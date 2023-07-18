#include "gpio.h"
#include "nvic.h"

void gpio_init(GPIO_Type *port, unsigned int pin, GPIO_MODE_Type direction) {
	// Enable clock
	if (port == GPIOA) {
		RCC->AHB1ENR |= 0x01U;
	} else if (port == GPIOB) {
		RCC->AHB1ENR |= 0x02U;
	} else if (port == GPIOC) {
		RCC->AHB1ENR |= 0x04U;
	} else if (port == GPIOD) {
		RCC->AHB1ENR |= 0x08U;
	} else if (port == GPIOE) {
		RCC->AHB1ENR |= 0x10U;
	} else if (port == GPIOF) {
		RCC->AHB1ENR |= 0x20U;
	} else if (port == GPIOG) {
		RCC->AHB1ENR |= 0x40U;
	} else if (port == GPIOH) {
		RCC->AHB1ENR |= 0x80U;
	} else {
		return;
	}
	// Set pin direction
	port->MODER &= ~(0x3U << (2 * pin));
	port->MODER |= direction << (2 * pin);
}

//extern inline void gpio_write(GPIO_Type *port, unsigned int pin, GPIO_LOGIC_Type output) {
//	if (output == HIGH) {
//		port->BSRR |= 0x1U << pin;
//
//	} else if (output == LOW) {
//		port->BSRR |= 0x1U << (pin + 16U);
//	}
//}
//
//extern inline GPIO_LOGIC_Type gpio_read(GPIO_Type *port, unsigned int pin) {
//	return (port->IDR >> pin) & 0x0001U;
//}
