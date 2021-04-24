/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: motor.c
 *
 * Description: Source file for the  MOTOTR driver
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/
/*******************************************************************************
 *                                Includes                                     *
 * ******************************************************************************/
#include "motor.h"


/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/
uint8 Motor_init(void){
	/*
	 * EN , IN1 ,IN2 IS OUTPUT
	 * */
	/*  IN1 */
	GPIO_Set_pin_output(Motor_IN1_PORT,Motor_IN1) ;
//	SET_BIT(Motor_IN1_PORT_DIR,Motor_IN1);
//	CLEAR_BIT(Motor_IN1_PORT_DATA,Motor_IN1);
	/*  IN2 */
	GPIO_Set_pin_output(Motor_IN2_PORT,Motor_IN2) ;
//	SET_BIT(Motor_IN2_PORT_DIR,Motor_IN2);
//	CLEAR_BIT(Motor_IN2_PORT_DATA,Motor_IN2);
	/*  EN */
	//GPIO_Set_pin_output(Motor_EN_PORT,Motor_EN) ;
//	SET_BIT(Motor_EN_PORT_DIR,Motor_EN);
//	CLEAR_BIT(Motor_EN_PORT_DATA,Motor_EN);
	return E_OK;
}



uint8 Motor_rotate_AntiClockwise(void){
	/*
	 * IN1 --> HIGH
	 * IN2 --> LOW
	 * */
	 GPIO_set_pin_value(Motor_IN1_PORT,Motor_IN1,HIGH) ;
	 GPIO_set_pin_value(Motor_IN2_PORT,Motor_IN2,LOW) ;
//	SET_BIT(Motor_IN1_PORT_DATA,Motor_IN1);
//	CLEAR_BIT(Motor_IN2_PORT_DATA,Motor_IN2);
	 return E_OK;
}

uint8 Motor_rotate_Clockwise(void){
	/*
	 * IN1 --> LOW
	 * IN2 --> HIGH
	 * */
	GPIO_set_pin_value(Motor_IN1_PORT,Motor_IN1,LOW) ;
    GPIO_set_pin_value(Motor_IN2_PORT,Motor_IN2,HIGH) ;
//	CLEAR_BIT(Motor_IN1_PORT_DATA,Motor_IN1);
//	SET_BIT(Motor_IN2_PORT_DATA,Motor_IN2);
    return E_OK;
}
uint8 Motor_stop(void){
	/*
	 * IN1 --> LOW
	 * IN2 --> LOW
	 * */
	GPIO_set_pin_value(Motor_IN1_PORT,Motor_IN1,LOW) ;
	GPIO_set_pin_value(Motor_IN2_PORT,Motor_IN2,LOW) ;
//	CLEAR_BIT(Motor_IN1_PORT_DATA,Motor_IN1);
//	CLEAR_BIT(Motor_IN2_PORT_DATA,Motor_IN2);
	return E_OK;
}

uint8 Motor_toggle(void){
	 GPIO_toggle_pin_val(Motor_IN1_PORT,Motor_IN1);
	 GPIO_toggle_pin_val(Motor_IN2_PORT,Motor_IN2);
//	TOGGLE_BIT(Motor_IN1_PORT_DATA,Motor_IN1);
//	TOGGLE_BIT(Motor_IN2_PORT_DATA,Motor_IN2);
	return E_OK;
}


