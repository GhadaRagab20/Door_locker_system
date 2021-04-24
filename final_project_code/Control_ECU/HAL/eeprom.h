/******************************************************************************
 *
 * Module: EEPROM MODULE
 *
 * File Name: eeprom.h
 *
 * Description: EEPROM driver  header file
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_
//#include "std_types.h"
//#include "common_macros.h"
//#include "micro_config.h"
#include "i2c.h"
 uint8 EEPROM_init(const TWI_config * cofig_Ptr);
 uint8 EEPROM_writeByte(uint16 a_address,uint8 a_data);
 uint8 EEPROM_readByte(uint16 a_address,uint8 *a_data_ptr);

#endif /* EEPROM_H_ */
