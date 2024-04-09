/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the AVR KEYPAD driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../include/std_types.h"
#include "../../include/comman_macros.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize pins connected to keypad
 */
void KEYPAD_Init();

/*
 * Description :
 * Get the pressed key and the take the type of keypad as a parameter
 * 3 for 4*3 keypad
 * 4 for 4*4 keypad
 */
uint8 KEYPAD_GetKeyPressed(int keypad_type);

#endif