/******************************************************************************
 *
 * Module: Timer MODULE
 *
 * File Name: timer.c
 *
 * Description: timer driver source file for AVR
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/


#include "timer.h"

/* global pointer to function for callback*/
static volatile void(*g_callBackPTr)(void) = NULL;
volatile uint8 g_init_flag=0;

ISR (TIMER1_COMPA_vect)
{   g_init_flag=0;
	if (g_callBackPTr != NULL)
	{
		(*g_callBackPTr)();
	}

}

uint8 Timer1_init(const Timer1_config * config_Ptr)
{
	while(g_init_flag);
	SREG |= (1 << 7); // I_bit

	/* non_PWM mode */
	TCCR1A |= (1 << FOC1A) | (1 << FOC1B);

	/* set initial value */
	TCNT1 = config_Ptr->initial_value;

	/* set compare value */
	OCR1A = config_Ptr->compare_value;

	/* enable timer interrupt  in compare mode */
	TIMSK = (TIMSK & 0xEF) | (1 << OCIE1A);

	/* TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12);
	 * pre_scalar = 8 MHZ / 1028 then interrupt every 0.128 secondS
	 */
	TCCR1B = (TCCR1B & 0xF8) | (config_Ptr->clk);
	TCCR1B = (TCCR1B & 0xF7) | (1 << WGM12);
	g_init_flag=1;
	return E_OK;

}

uint8 Timer1_set_CallBack(void(*a_ptr)(void))
{
	g_callBackPTr = a_ptr;
	return E_OK;

}
