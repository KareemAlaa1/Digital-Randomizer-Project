/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the AVR UART driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../../include//std_types.h"
#include "../../include/comman_macros.h"
#include "uart_reg.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize configrations for uart
 */
void UART_vInit(void);

/*
 * Description :
 * Transmit byte
 */
void UART_vTransmit(uint8 data);

/*
 * Description :
 * Receive byte
 */
uint8 UART_vReceive();

#endif