/******************************************************************************
 *
 * Module: main
 *
 * File Name: main.c
 *
 * Description: source code for appliction in control ECU
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/


#include "eeprom.h"
#include "motor.h"
#include "timer.h"
#include "uart.h"
#include "buzzer.h"

#define PASSWORD_LEN  5
/* status of operation */
#define READY 0x10
#define MATCHING 0x20
#define UNMATCHING 0x30
#define THEIF 0x40

/* function to compare 2 passwords*/
uint8 cmp (uint8 password_1[], uint8 password_2[])
{
	for(uint8 i = 0; i < PASSWORD_LEN; i++)
	{
		if (password_1[i] != password_2[i]) return 0;
	}

	return 1;
}



int main(void)
{
	uint8 comp;  // to compare the two passwords
	uint8 read_password; // data read from EEPRM
	uint8 read_password_arr[PASSWORD_LEN];
	uint8 password[5]; // the received password using UART
	uint8 i ;
	uint8 rx_data; // rx_data->(option) = (-) or (+)

	/* Enable Global Interrupt */
	SREG |= (1 << 7); // I_bit

	/* output pin for BUZZER */
//	DDRC |= (1 << 7);
//	PORTC &= ~(1 << 7);

	UART_config config = {BIT_8, DISABLE, STOP_BIT_1,9600};
	uart_init(&config);
	TWI_config configt = {2};

	EEPROM_init(&configt);
    Buzzer_init();
    Motor_init();
	/* initial password */
	/* receive the new password by UART and store it in the EEPRM */
	while (uart_recieveByte() != READY){}; //pooling until the HMI be ready
	for ( i = 0; i < PASSWORD_LEN ; i++)
	{
		uart_sendByte(READY);
		password[i] = uart_recieveByte();
		/*write the password[i] in EEPROM address (0x000 | i) */
		EEPROM_writeByte((0x000 | i), password[i]);
		_delay_ms(10);
	}


	while(1)
	{

		while (uart_recieveByte() != READY){};


		 rx_data = uart_recieveByte();
		/* receive (-) for opening the door
		 *  receiving the password
		 *  read the existing password from EEPROM
		 *  compare the 2 passwords, check the password*/
		if (rx_data == '-')
		{
			for (uint8 i = 0; i < PASSWORD_LEN ; i++)
			{
				uart_sendByte(READY);
				password[i] = uart_recieveByte();
			}

			for (uint8 i = 0; i < PASSWORD_LEN ; i++)
			{
				EEPROM_readByte((0x000 | i), &read_password);
				read_password_arr[i] = read_password;
			}
			comp = cmp (password, read_password_arr);

			/* matching
             * send match to HMI by UART
             * motor on clock wise
             * wait 15 sec
             * motor on anti clock wise */
			if (comp)
			{
				while(uart_recieveByte() != READY);

				uart_sendByte(MATCHING);
				Motor_rotate_Clockwise();
				Timer1_set_CallBack(Motor_rotate_AntiClockwise);

				/*wait for 8 second*/
				Timer1_config timer_config1 = {F_CPU_1024, 0, 65535};
				Timer1_init(&timer_config1);
				Timer1_set_CallBack(Motor_rotate_AntiClockwise);
				//3 sec
				Timer1_config timer_config2 = {F_CPU_1024, 0, 23437};
				Timer1_init(&timer_config2);
				Timer1_set_CallBack(Motor_stop);

				/*wait for 15 second*/
				Timer1_config timer_config3 = {F_CPU_1024, 0, 65535};
				Timer1_init(&timer_config3);
			}
            /* unmatching
             *  Send unmatch to HMI by UART
             *  */
			else
			{
				while(uart_recieveByte() != READY){};
				uart_sendByte(UNMATCHING);

			}
		}

		/* when receive (+) for changing the password
		 * receiving the password
		 * read the existing password from EEPROM
		 * compare the 2 passwords,check the password
		 * */
		else if (rx_data == '+')
		{

			for ( i = 0; i < PASSWORD_LEN ; i++)
			{
				uart_sendByte(READY);
				password[i] = uart_recieveByte();
			}

			for ( i = 0; i < PASSWORD_LEN ; i++)
			{
					EEPROM_readByte((0x000 | i), &read_password);
					read_password_arr[i] = read_password;
			}
			comp = cmp (password, read_password_arr);

			/* matching :
			 * send match to HMI by UART
			 * receive the new password
			 * store it in the EEPRM
			 */
			if (comp)
			{
				while(uart_recieveByte() != READY);
				uart_sendByte(MATCHING);
				while (uart_recieveByte() != READY){};
				for (uint8 i = 0; i < PASSWORD_LEN ; i++)
				{
					uart_sendByte(READY);
					password[i] = uart_recieveByte();
					EEPROM_writeByte((0x000 | i), password[i]);
					_delay_ms(10);
				}
			}

			/* unmatching
			 *  Send unmatch to HMI by UART
			 *  */
			else
			{
				while(uart_recieveByte() != READY);
				uart_sendByte(UNMATCHING);

			}
		}

		/* buzzer */
		else
		{
			Buzzer_on();
			Timer1_set_CallBack(Buzzer_off);
			/* wait 1 m*/
			Timer1_config timer_config = {F_CPU_1024, 0 , 65535};
			Timer1_init(&timer_config);
		}

	}
}
