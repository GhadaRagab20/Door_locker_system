/******************************************************************************
 *
 * Module: EEPROM MODULE
 *
 * File Name: eeprom.c
 *
 * Description: EEPROM driver  source file
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/
#include "eeprom.h"


uint8 EEPROM_init(const TWI_config * cofig_Ptr)
{
	TWI_init (cofig_Ptr);
	return E_OK;
}

uint8 EEPROM_writeByte(uint16 a_address,uint8 a_data)
{
	TWI_start();
	if (TWI_getStatus() != TW_START )
		return E_NOT_OK;

	TWI_write((uint8)(0xA0 | ((a_address & 0x700) >> 7))) ;  //device address (salve) EEPROM
	if (TWI_getStatus() != TW_MT_SLA_W_ACK )
		return E_NOT_OK;

	TWI_write((uint8)a_address); // memory location in EEPROM
	if (TWI_getStatus() != TW_MT_DATA_ACK )
		return E_NOT_OK;

	TWI_write(a_data); // data
	if (TWI_getStatus() != TW_MT_DATA_ACK )
		return E_NOT_OK;

	TWI_stop ();

	return E_OK;
}


uint8 EEPROM_readByte(uint16 a_address,uint8 *a_data_ptr)
{
	TWI_start();
	if (TWI_getStatus() != TW_START )
		return E_NOT_OK;

	TWI_write((uint8)(0xA0 | ((a_address & 0x700) >> 7))) ;
	if (TWI_getStatus() != TW_MT_SLA_W_ACK )
		return E_NOT_OK;

	TWI_write((uint8)a_address);
	if (TWI_getStatus() != TW_MT_DATA_ACK )
		return E_NOT_OK;

	TWI_start();
	if (TWI_getStatus() != TW_REP_START)
		return E_NOT_OK;

	TWI_write((uint8)(0xA0 | ((a_address & 0x700) >> 7)|1)) ;
	if (TWI_getStatus() != TW_MT_SLA_R_ACK)
		return E_NOT_OK;

	*a_data_ptr = TWI_readWithNACK();
	if (TWI_getStatus() != TW_MR_DATA_NACK )
		return E_NOT_OK;

	TWI_stop();

	return E_OK;
}
