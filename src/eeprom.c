/******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: eeprom.c
 *
 * Description: Source file for the AVR EEPROM driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#include "../MCAL/EEPROM/eeprom.h"

/*
 * Description :
 * Write byte in given address in eeprom
 */
void EEPROM_Write(uint8 address, uint8 data)
{
    while (READ_BIT(EECR, 1) == 1)
    {
    }
    EEARL = address;
    EEDR = data;
    SET_BIT(EECR, 2);
    SET_BIT(EECR, 1);
}

/*
 * Description :
 * Read byte from given address in eeprom
 */

uint8 EEPROM_Read(uint8 address)
{
    while (READ_BIT(EECR, 1) == 1)
    {
    }
    EEARL = address;
    SET_BIT(EECR, 0);
    return EEDR;
}
