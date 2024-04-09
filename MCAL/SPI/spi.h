/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.h
 *
 * Description: Header file for the AVR SPI driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "../../include//std_types.h"
#include "../../include/comman_macros.h"
#include "spi_reg.h"
#include "../GPIO/gpio.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
    SPI_Master,
    SPI_Slave,
} SPI_Role;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize the SPI according to the role Slave or Master
 */

void SPI_Init(SPI_Role role);

/*
 * Description :
 * Transmit byte
 */

void SPI_Transmit(uint8 data);

/*
 * Description :
 * Recieve byte
 */

uint8 SPI_Recieve();

#endif