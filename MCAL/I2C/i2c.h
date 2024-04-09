// #ifndef I2C_H_
// #define I2C_H_

// #include "../../include//std_types.h"
// #include "../../include/comman_macros.h"
// #include "i2c_reg.h"
// #include "../GPIO/gpio.h"
// #include <util/delay.h>

// void I2C_Master_Init();

// void I2C_Slave_Init(uint8 adress);

// void I2C_Master_Transmit(uint8 data ,uint8 adress);

// uint8 I2C_Master_Recieve(uint8 adress);

// void I2C_Slave_Transmit(uint8 data);

// uint8 I2C_Slave_Recieve();

// #endif

/*
 * I2C.h
 *
 *  Created on: Jan 15, 2018
 *      Author: Mohamed
 */

#ifndef I2C_H_
#define I2C_H_

#include "../../include//std_types.h"
#include "../../include/comman_macros.h"
#include "i2c_reg.h"

#define TWINT 7
#define TWEA 6
#define TWSTA 5
#define TWSTO 4
#define TWWC 3
#define TWEN 2
#define TWIE 0
#define BITRATE(TWSR) (16000000 - 16) / (2 * pow(4, (TWSR & ((1 << 0) | (1 << 1)))))

void I2C_Init();

uint8 I2C_Start(uint8 write_address);
uint8 I2C_Repeated_Start(uint8 read_address);
uint8 I2C_Write(uint8 data);
uint8 I2C_Read_Ack();
uint8 I2C_Read_Nack();
void I2C_Stop();

void I2C_Slave_Init(uint8 slave_address);
uint8 I2C_Slave_Listen();
uint8 I2C_Slave_Transmit(uint8 data);
uint8 I2C_Slave_Receive();
#endif 