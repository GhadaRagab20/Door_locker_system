/******************************************************************************
 *
 * Module: I2C MODULE
 *
 * File Name: i2c.c
 *
 * Description: I2C driver source file for AVR
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/
#include "i2c.h"

void TWI_init (const TWI_config * cofig_Ptr)
{

	/*pre_scalar */
	TWBR = 0x02;
	TWSR = 0x00;

	/* address (in case of slave) */
	TWAR = cofig_Ptr->add;
    /* enable TWI */
	TWCR = (1 << TWEN);
}

void TWI_start (void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 <<TWSTA);
	while (BIT_IS_CLEAR(TWCR, TWINT));
}

void TWI_stop (void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 <<TWSTO);
	//while (BIT_IS_CLEAR(TWCR, TWINT));
}

void TWI_write(uint8 data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT));
}

uint8 TWI_readWithACK(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (BIT_IS_CLEAR(TWCR, TWINT));
	return TWDR;
}

uint8 TWI_readWithNACK(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT));
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	return (TWSR & 0xF8);
}
