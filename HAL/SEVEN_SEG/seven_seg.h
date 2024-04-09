/******************************************************************************
 *
 * Module: SEVEN SEGMENT
 *
 * File Name: seven_seg.h
 *
 * Description: Header file for the AVR SEVEN SEGMENT driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#ifndef seven_seg_H_
#define seven_seg_H_

#include "std_types.h"
#include "comman_macros.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize SEVEN SEGMENT at given port
 */
void SEVEN_SEG_Init(uint8 port);

/*
 * Description :
 * Display given digit on SEVEN SEGMENT
 */
uint8 SEVEN_SEG_Write(uint8 port, uint8 number);

#endif