

#include "gpio.h"
#include "buzzer.h"

uint8 Buzzer_init(){
	GPIO_Set_pin_output(Buzzer_PORT,Buzzer_PIN) ;
	return E_OK;
}
uint8 Buzzer_on(){
    GPIO_set_pin_value(Buzzer_PORT,Buzzer_PIN,HIGH) ;

	return E_OK;
}
uint8 Buzzer_off(){
	GPIO_set_pin_value(Buzzer_PORT,Buzzer_PIN,LOW) ;
	return E_OK;
}
