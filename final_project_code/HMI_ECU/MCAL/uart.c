/******************************************************************************
 *
 * Module: UART MODULE
 *
 * File Name: uart.c
 *
 * Description: UART driver source file for AVR
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/
#include "uart.h"


void uart_init(const UART_config * cofig_Ptr)
{

	UCSRB |= (1 << RXEN) | (1 << TXEN); // enable Tx, Rx
	UCSRC |= (1 << URSEL) ;

	/*double speed*/
	UCSRA = (UCSRA & 0xFD) | (DOUBLE_SPEED << 1);

	UCSRC = (UCSRC & 0xF9) | ((cofig_Ptr->data_bits & 0x03)<<1);
	UCSRB = (UCSRB & 0xFB) | (cofig_Ptr->data_bits & 0x04);

	/*parity*/
	UCSRC = (UCSRC & 0xCF) | (cofig_Ptr->parity << 4);

	/* stop_bit*/
	UCSRC = (UCSRC & 0xF7) | (cofig_Ptr->stop_bit << 3);

	/*mode*/
	UCSRC = (UCSRC & 0xBF) | (MODE_BIT << 6);

	UBRRL = BAUD_PRESCALE(cofig_Ptr->rate);
	UBRRH = BAUD_PRESCALE(cofig_Ptr->rate) >> 8;
}


void uart_sendByte(uint8 data)
{
	while (BIT_IS_CLEAR(UCSRA ,UDRE)){};
	UDR = data;
}

uint8 uart_recieveByte(void)
{
	while (BIT_IS_CLEAR(UCSRA ,RXC)){};
	return UDR;
}

void uart_sendString(const uint8 *str)
{
	uint8 i = 0;
	while (str[i] != '\0')
	{
		uart_sendByte(str[i]);
		i++;
	}
}

void uart_recieveString(uint8 *str)
{
	uint8 i = 0;
	str[i] = uart_recieveByte();
	while (str[i] != '#')
	{
		i++;
		str[i] = uart_recieveByte();
	}
	str[i] = '\0';
}
