/******************************************************************************
 *
 * Module: Timer MODULE
 *
 * File Name: timer.h
 *
 * Description: timer driver header file for AVR
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


typedef enum
{
	NO_CLK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}timer1_Clock_pre;


typedef struct
{
	timer1_Clock_pre clk;
	uint16 initial_value;
	uint16 compare_value;
}Timer1_config;

uint8 Timer1_init(const Timer1_config * config_Ptr);
uint8 Timer1_set_CallBack(void(*a_ptr)(void));

#endif /* TIMER_H_ */
