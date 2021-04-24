 /******************************************************************************
 *
 * Module: KEYPAD MODULE
 *
 * File Name: keypad.h
 *
 * Description: keypad driver header file for AVR
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 4
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA 

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
extern uint8 KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
