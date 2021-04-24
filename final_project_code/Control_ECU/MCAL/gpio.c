#include "gpio.h"

uint8 GPIO_Set_pin_output(uint8 a_port,uint8 a_pin) {
	switch(a_port){
	case PortA:
		SET_BIT(DDRA,a_pin);
		CLEAR_BIT(PORTA,a_pin);
		break;
	case PortB:
			SET_BIT(DDRB,a_pin);
			CLEAR_BIT(PORTB,a_pin);
			break;
	case PortC:
			SET_BIT(DDRC,a_pin);
			CLEAR_BIT(PORTC,a_pin);
			break;
	case PortD:
			SET_BIT(DDRD,a_pin);
			CLEAR_BIT(PORTD,a_pin);
			break;
	default:
		return E_NOT_OK;
	}
	return E_OK;
}
uint8 GPIO_Set_pin_input_float(uint8 a_port,uint8 a_pin) {
	switch(a_port){
		case PortA:
			CLEAR_BIT(DDRA,a_pin);
			break;
		case PortB:
				CLEAR_BIT(DDRB,a_pin);
				break;
		case PortC:
				CLEAR_BIT(DDRC,a_pin);
				break;
		case PortD:
				CLEAR_BIT(DDRD,a_pin);
				break;
		default:
			return E_NOT_OK;
		}
	return E_OK;
}
uint8 GPIO_Set_pin_input_pullup(uint8 a_port,uint8 a_pin) {
	switch(a_port){
	case PortA:
		CLEAR_BIT(DDRA,a_pin);
		SET_BIT(PORTA,a_pin);
		break;
	case PortB:
		CLEAR_BIT(DDRB,a_pin);
			SET_BIT(PORTB,a_pin);
			break;
	case PortC:
		CLEAR_BIT(DDRC,a_pin);
		SET_BIT(PORTC,a_pin);
			break;
	case PortD:
		CLEAR_BIT(DDRD,a_pin);
		SET_BIT(PORTD,a_pin);
			break;
	default:
		return E_NOT_OK;
	}
	return E_OK;
}
uint8 GPIO_get_pin_value(uint8 a_port,uint8 a_pin,uint8 * val_ptr){
     if(val_ptr == NULL) return E_NOT_OK;
     switch(a_port){
     		case PortA:
     			* val_ptr=	( PINA & (1<<a_pin) );
     			break;
     		case PortB:
     			* val_ptr=	( PINB & (1<<a_pin) );
     				break;
     		case PortC:
     			* val_ptr=	( PINC & (1<<a_pin) );
     				break;
     		case PortD:
     			* val_ptr=	( PIND & (1<<a_pin) );
     				break;
     		default:
     			return E_NOT_OK;
     		}

	return E_OK;
}
uint8 GPIO_set_pin_value(uint8 a_port,uint8 a_pin,uint8 val) {
	switch(a_port){
	case PortA:
		if(val)PORTA|=(val<<a_pin);
		else CLEAR_BIT(PORTA,a_pin);
		break;
	case PortB:
		//PORTB|=(val<<a_pin);
		if(val)PORTB|=(val<<a_pin);
		else CLEAR_BIT(PORTB,a_pin);
		break;
	case PortC:
		//PORTC|=(val<<a_pin);
		if(val)PORTC|=(val<<a_pin);
		else CLEAR_BIT(PORTC,a_pin);
		break;
	case PortD:
		//PORTD|=(val<<a_pin);
		if(val)PORTD|=(val<<a_pin);
		else CLEAR_BIT(PORTD,a_pin);
		break;
	default:
		return E_NOT_OK;
	}
	return E_OK;
}
uint8 GPIO_toggle_pin_val(uint8 a_port,uint8 a_pin) {
	switch(a_port){
		case PortA:
			TOGGLE_BIT(PORTA,a_pin);
			break;
		case PortB:
			TOGGLE_BIT(PORTB,a_pin);
				break;
		case PortC:
			TOGGLE_BIT(PORTC,a_pin);
				break;
		case PortD:
			TOGGLE_BIT(PORTD,a_pin);
				break;
		default:
			return E_NOT_OK;
		}
		return E_OK;
}
