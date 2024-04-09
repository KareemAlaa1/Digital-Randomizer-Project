/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the AVR UART driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#include "../MCAL/UART/uart.h"

/*
 * Description :
 * Initialize configrations for uart
 */
void UART_vInit(void)
{
  UCSR0B = 0b00011000;
  UCSR0C = 0b00000110;
  UBRR0L = 103;
}

/*
 * Description :
 * Transmit byte
 */
void UART_vTransmit(uint8 data)
{
  while (READ_BIT(UCSR0A, 6) == 0)
  {
  }
  UDR0 = data;
  SET_BIT(UCSR0A, 6);
}

/*
 * Description :
 * Receive byte
 */
uint8 UART_vReceive()
{
  while (READ_BIT(UCSR0A, 7) == 0)
  {
  }
  SET_BIT(UCSR0A, 7);
  return UDR0;
}