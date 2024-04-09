/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.c
 *
 * Description: Source file for the AVR SPI driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#include "../MCAL/SPI/spi.h"

/*
 * Description :
 * Initialize the SPI according to the role Slave or Master
 */
void SPI_Init(SPI_Role role)
{
  SET_BIT(SPCR, 6);
  SET_BIT(SPCR, 5);
  CLEAR_BIT(SPCR, 3);
  CLEAR_BIT(SPCR, 2);
  SET_BIT(SPCR, 1);
  SET_BIT(SPCR, 0);
  SET_BIT(SPSR, 0);

  // Set the direction of pins MISO, MOSI, SCK and SS according to the role
  if (role == SPI_Master)
  {
    SET_BIT(SPCR, 4);
    GPIO_setupPinDirection(PORTB_ID, 5, PIN_OUTPUT);
    GPIO_setupPinDirection(PORTB_ID, 4, PIN_INPUT);
    GPIO_setupPinDirection(PORTB_ID, 3, PIN_OUTPUT);
    GPIO_setupPinDirection(PORTB_ID, 2, PIN_OUTPUT);
  }
  else
  {
    CLEAR_BIT(SPCR, 4);
    GPIO_setupPinDirection(PORTB_ID, 5, PIN_INPUT);
    GPIO_setupPinDirection(PORTB_ID, 4, PIN_OUTPUT);
    GPIO_setupPinDirection(PORTB_ID, 3, PIN_INPUT);
    GPIO_setupPinDirection(PORTB_ID, 2, PIN_INPUT);
  }
}

/*
 * Description :
 * Transmit byte
 */
void SPI_Transmit(uint8 data)
{
  SPDR = data;
  while (READ_BIT(SPSR, 7) == 0)
  {
  }
}

/*
 * Description :
 * Recieve byte
 */
uint8 SPI_Recieve()
{
  while (READ_BIT(SPSR, 7) == 0)
  {
  }
  return SPDR;
}