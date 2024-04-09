
/******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: eeprom.h
 *
 * Description: Header file for the AVR EEPROM driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../include//std_types.h"
#include "../../include/comman_macros.h"
#include "eeprom_reg.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Write byte in given address in eeprom
 */

void EEPROM_Write(uint8 address, uint8 data);

/*
 * Description :
 * Read byte from given address in eeprom
 */

uint8 EEPROM_Read(uint8 address);

#endif