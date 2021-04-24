/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: motor.h
 *
 * Description: Header file for the  MOTOTR driver
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "gpio.h"
/*******************************************************************************
 *                                Includes                                     *
 * ******************************************************************************/
//#include "common_macros.h"
//#include "micro_config.h"
//#include "std_types.h"

/*******************************************************************************
 *                           Definitions and Configurations                    *
 *******************************************************************************/
#define Motor_IN1  PB5
#define Motor_IN2  PB4
#define Motor_EN

#define Motor_IN1_PORT      2 //PORTB
#define Motor_IN2_PORT      2
#define Motor_EN_PORT

/*******************************************************************************
 *                               Function Declarations                        *
 *******************************************************************************/

/*
 *
 *
 * */
uint8 Motor_init(void);
uint8 Motor_rotate_AntiClockwise(void);
uint8 Motor_rotate_Clockwise(void);
uint8 Motor_stop(void);
uint8 Motor_toggle(void);





#endif /* MOTOR_H_ */
