
#ifndef MCAL_GPIO_H_
#define MCAL_GPIO_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

#define PortA 1
#define PortB 2
#define PortC 3
#define PortD 4

uint8 GPIO_Set_pin_output(uint8 a_port,uint8 a_pin) ;
uint8 GPIO_Set_pin_input_float(uint8 a_port,uint8 a_pin) ;
uint8 GPIO_Set_pin_input_pullup(uint8 a_port,uint8 a_pin) ;
uint8 GPIO_get_pin_value(uint8 a_port,uint8 a_pin,uint8 * val_ptr) ;
uint8 GPIO_set_pin_value(uint8 a_port,uint8 a_pin,uint8 val) ;
uint8 GPIO_toggle_pin_val(uint8 a_port,uint8 a_pin) ;
#endif /* MCAL_GPIO_H_ */
