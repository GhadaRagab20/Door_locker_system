/******************************************************************************
 *
 * Module: TWI MODULE
 *
 * File Name: i2c.h
 *
 * Description: I2C driver  header file for AVR
 *
 * Author: Ghada Ragab
 *
 *******************************************************************************/

#ifndef I2C_H_
#define I2C_H_


/*******************************************************************************
 *                                Includes                                     *
 * ******************************************************************************/
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                           Definitions and Configurations                    *
 *******************************************************************************/

#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave


typedef struct
{
 uint8 add;
}TWI_config;
/*******************************************************************************
 *                               Function Declarations                        *
 *******************************************************************************/
void TWI_init (const TWI_config * cofig_Ptr);
void TWI_start (void);
void TWI_stop (void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void);
uint8 TWI_readWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* I2C_H_ */
