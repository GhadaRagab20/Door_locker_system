/******************************************************************************
 *
 * Module: UART MODULE
 *
 * File Name: uart.h
 *
 * Description: UART driver header file for AVR
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/
#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"



#define DOUBLE_SPEED  1U
#define MODE_BIT  0U
#define BAUD_PRESCALE(RATE) (((F_CPU / ((RATE) * 8UL))) - 1)


typedef enum
{
	BIT_5, BIT_6, BIT_7, BIT_8, BIT_9 = 7
}number_of_data_bits;

typedef enum
{
	DISABLE, EVEN =2, ODD
}parity_type;

typedef enum
{
	STOP_BIT_1, STOP_BIT_2
}stop_bit_type;

typedef struct
{
	number_of_data_bits data_bits;
	parity_type parity;
	stop_bit_type stop_bit;
	uint16 rate;
}UART_config;


void uart_init(const UART_config * cofig_Ptr);
void uart_sendByte(uint8 data);
uint8 uart_recieveByte(void);
void uart_sendString(const uint8 *str);
void uart_recieveString(uint8 *str);


#endif /* UART_H_ */
