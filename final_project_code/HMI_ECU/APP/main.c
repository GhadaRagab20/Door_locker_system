/******************************************************************************
 *
 * Module: main
 *
 * File Name: main.c
 *
 * Description: source code for application in HMI ECU
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/

#include "lcd.h"
#include "keypad.h"
#include "timer.h"
#include "uart.h"

#define PASSWORD_LEN  5

/* status of operation */
#define READY 0x10
#define MATCHING 0x20
#define DISMATCHING 0x30
#define THEIF 0x40


uint8 g_clear = 0;

void get_password(uint8 password[])
{
	uint8 i = 0;
	for (i = 0; i < PASSWORD_LEN ; i++)
	{
		password[i] = KeyPad_getPressedKey();
		_delay_ms(150);
		LCD_goToRowColumn(1,i);
		LCD_displayCharacter('*');
	}
	KeyPad_getPressedKey();
	LCD_clearScreen();
}

uint8 cmp (uint8 password_1[], uint8 password_2[])
{
	for(uint8 i = 0; i < PASSWORD_LEN; i++)
	{
		if (password_1[i] != password_2[i]) return 0;
	}

	return 1;
}


void LCD_clear(void)
{
	if (g_clear == 1)
	{
		LCD_clearScreen();
		g_clear = 0;
	}
	SREG &= ~(1 << 7);
}

int main(void)
{
	uint8 comp=1;
	uint8 new_password[PASSWORD_LEN];
	uint8 re_new_password[PASSWORD_LEN];
	uint8 i;
	uint8 s_flag = 0;
	uint8 no_of_tries = 0;

	LCD_init();
	UART_config config = {BIT_8, DISABLE, STOP_BIT_1,9600};
	uart_init(&config);



	/* step(1) initial the password
	 *  enter new password
	 *  re_enter the new password
	 *  check whether they are matching or no
	 *  */
	do
	{
		LCD_displayString("enter new pass: ");
		get_password(new_password);
		LCD_displayString("enter pass again: ");
		_delay_ms(50);
		get_password(re_new_password);
		comp = cmp (new_password, re_new_password);
	}while (!comp);

	/* send the new password by UART to the Control ECU
	 * the Control ECU receive it and store it in EEPROM */
	uart_sendByte(READY);
	for (i = 0; i < PASSWORD_LEN; i++)
	{
		while (uart_recieveByte() != READY){};
		uart_sendByte(new_password[i]);
	}


	while (1)
	{
		/* select an option (-) open door or (+) change password */
		while (g_clear != 0) {};
		LCD_displayString("select an option");
		uint8 option = KeyPad_getPressedKey();
		LCD_clearScreen();

		/* option(-) open door
		 * get password from user
		 * send the password by UART to control ECU
		 * receive the result from control ECU (matching or unmatching)
		 * */
		if (option == '-')
		{
			s_flag = 0;
			no_of_tries = 0;
			while(!(s_flag) && no_of_tries != 3)
			{

				LCD_displayString("enter the pass: ");
				_delay_ms(50);
				get_password(new_password);

				uart_sendByte(READY);
				uart_sendByte('-');
				for (uint8 i = 0; i < PASSWORD_LEN; i++)
				{
					while (uart_recieveByte() != READY){};
					uart_sendByte(new_password[i]);
				}

				uart_sendByte(READY);
				/* matching	*/
				if (uart_recieveByte() == MATCHING)
				{
					LCD_displayString("door unlocking");
					g_clear = 1;
					Timer1_set_CallBack(LCD_clear);
					//for 15 sec
					Timer1_config timer_config = {F_CPU_1024, 0, 117187};
					Timer1_init(&timer_config);
					while(g_clear == 1) {};
					LCD_displayString("door locking");
					g_clear = 1;
					Timer1_init(&timer_config);
					s_flag = 1;

				}
				// unmatching
				else
				{
					LCD_displayString("unmatching");
					_delay_ms(100);
					LCD_clearScreen();
					s_flag= 0; // return success to 0 if wrong password
					no_of_tries ++;
				}

			};
            /* if error tries exceed 3 he is thief
             * print Thief on lcd
             * and send it to the control ECU to set buzzer on
             * and wait for 1 min*/
			if (no_of_tries == 3)
			{
				Timer1_set_CallBack(LCD_clear);
				LCD_displayString("THIEF");
				uart_sendByte(READY);
				uart_sendByte(THEIF);
				g_clear = 1;
				//8 sec
				Timer1_config timer_config = {F_CPU_1024, 0, 65535};
				Timer1_init(&timer_config);

			}

		}


		/* option(+) change password
		 * get password from user
		 * send the password by UART
		 * receive the result from control ECU (matching or unmatching)
		 * */
		else if (option == '+')
		{
			s_flag = 0;
			no_of_tries = 0;
			while(!(s_flag) && no_of_tries != 3)
			{
				LCD_displayString("enter the pass: ");
				_delay_ms(50);
				get_password(new_password);
				uart_sendByte(READY);
				uart_sendByte('+');
				for (uint8 i = 0; i < PASSWORD_LEN; i++)
				{
					while (uart_recieveByte() != READY){};
					uart_sendByte(new_password[i]);
				}
				uart_sendByte(READY);
				/* matching:
				 * enter new password
				 * re_enter the new password
				 * check whether they are matching or no
				 * send the new password using uart to the control ECU
				 * */
				if (uart_recieveByte() == MATCHING)
				{
					LCD_displayString("matching");
					_delay_ms(100);
					LCD_clearScreen();
					s_flag = 1;
					comp=1;
					while (comp)
					{
						LCD_displayString("enter new pass: ");
						get_password(new_password);
						LCD_displayString("enter pass again: ");
						_delay_ms(50);
						get_password(re_new_password);
						comp = cmp (new_password, re_new_password);
					}
					uart_sendByte(READY);
					for ( i = 0; i < PASSWORD_LEN; i++)
					{
						while (uart_recieveByte() != READY){};
						uart_sendByte(new_password[i]);
					}

				}
				// unmatching
				else
				{
					LCD_displayString("unmatching");
					_delay_ms(100);
					LCD_clearScreen();
					s_flag = 0;
					no_of_tries ++;
				}

			}

			if (no_of_tries == 3)
			{
				Timer1_set_CallBack(LCD_clear);
				LCD_displayString("THIEF");
				uart_sendByte(READY);
				uart_sendByte(THEIF);
				g_clear = 1;
				Timer1_config timer_config = {F_CPU_1024, 0, 65535};
				Timer1_init(&timer_config);

			}

		}
	}
}
