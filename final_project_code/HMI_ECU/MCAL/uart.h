/******************************************************************************
 *
 * Module: UART MODULE
 *
 * File Name: uart.h
 *
 * Description: UART driver  header file for AVR
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/

#ifndef MCAL_UART_H_
#define MCAL_UART_H_



/*******************************************************************************
 *                                Includes                                     *
 * ******************************************************************************/
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"


/*******************************************************************************
 *                                       ENUM                                  *
 *******************************************************************************/
typedef enum {
	one_bit, two_bit
}UART_Stop_Bit;

typedef enum {
	FIVE_BITS ,SIX_BITS, SEVEN_BITS , EIGHT_BITS , NINE_BITS =7
}UART_Data_Bit;

typedef enum {
	DISABLED ,EVEN_PARITY = 2, ODD_PARITY
}UART_Parity;



/*******************************************************************************
 *                             Structures and Unions                           *
 *******************************************************************************/

/*******************************************************************************
* [struct name] :uart_config
* [Description] : struct for configuration of uart
********************************************************************************/
typedef struct {
	UART_Parity Pr_mode ;
	UART_Data_Bit Bit_No;
	UART_Stop_Bit stp_bit;
	//UART_BAUD_PRESCALE Baud_Rate;
}uart_config;

/*******************************************************************************
 *                               Function Declarations                        *
 *******************************************************************************/
uint8 UART_init(uart_config * a_conf);
uint8 UART_sendByte(const uint8 data);
uint8 UART_recieveByte(uint8 * data );
uint8 UART_sendString(const uint8 *Str);
uint8 UART_receiveString(uint8 *Str);


#endif /* MCAL_UART_H_ */
