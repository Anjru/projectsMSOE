/******************************************************************************
 * Project: STM32F446xx Series HAL
 * File: nvic.c
 * Created: 6/10/21
 * Author: Cody Nettesheim
 * Description: This file implements functions for enabling interrupts using
 * 				the standard ARM Cortex-M4 NVIC.
 *****************************************************************************/
#include "nvic.h"

void set_register(IRQ_Type IRQn, uint32_t *base_reg);
void set_register_ipr(IRQ_Type IRQn, uint32_t *base_reg);

//Non-IPR registers:
//	register number = IRQ / 32
//	register bitfield location = IRQ mod 32
//IPR registers:
//	register number = IRQ / 4
//	register bitfield location = 8 * (IRQ mod 4) + 4

void NVIC_EnableIRQ(IRQ_Type IRQn) {
	set_register(IRQn, (uint32_t*) &NVIC->ISER);
}

void NVIC_DisableIRQ(IRQ_Type IRQn) {
	set_register(IRQn, (uint32_t*) &NVIC->ICER);
}

void NVIC_SetPendingIRQ(IRQ_Type IRQn) {
	set_register(IRQn, (uint32_t*) &NVIC->ISPR);
}

void NVIC_ClearPendingIRQ(IRQ_Type IRQn) {
	set_register(IRQn, (uint32_t*) &NVIC->ICPR);
}

uint32_t NVIC_GetPendingIRQ(IRQ_Type IRQn) {
	uint32_t reg = IRQn / 32U;
	uint32_t bitmask = 0x1U << (IRQn % 32U);
	return (NVIC->ISPR[reg] & bitmask);

}

void NVIC_SetPriority(IRQ_Type IRQn, uint32_t bitmask) {
	uint32_t reg = IRQn / 4U;
	NVIC->IPR[reg] |= bitmask;
}

uint32_t NVIC_GetPriority(IRQ_Type IRQn) {
	uint32_t reg = IRQn / 4U;
	uint32_t bitmask = 0x1U << (8U * (IRQn % 4U) + 4U);
	return (NVIC->IPR[reg] & bitmask);
}

//Non-IPR only
void set_register(IRQ_Type IRQn, uint32_t *base_reg) {
	uint32_t reg = IRQn / 32U;
	uint32_t bitmask = 0x1U << (IRQn % 32U);
	base_reg[reg] |= bitmask;
}
