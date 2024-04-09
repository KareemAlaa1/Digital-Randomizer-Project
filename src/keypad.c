/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the AVR KEYPAD driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#include "../HAL/KEYPAD/keypad.h"
#include "../MCAL/GPIO/gpio.h"

// values foe keypad 4*4*
const uint8 switch_values44[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

// values foe keypad 4*3
const uint8 switch_values43[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

/*
 * Description :
 * Initialize pins connected to keypad
 */
void KEYPAD_Init()
{

	GPIO_setupPinDirection(PORTD_ID, PIN0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_OUTPUT);

	GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_INPUT);

	GPIO_writePin(PORTD_ID, PIN0_ID, LOGIC_LOW);
	GPIO_writePin(PORTD_ID, PIN1_ID, LOGIC_LOW);
	GPIO_writePin(PORTD_ID, PIN2_ID, LOGIC_LOW);
	GPIO_writePin(PORTD_ID, PIN3_ID, LOGIC_LOW);
}

/*
 * Description :
 * Get the pressed key and the take the type of keypad as a parameter
 * 3 for 4*3 keypad
 * 4 for 4*4 keypad
 */
uint8 KEYPAD_GetKeyPressed(int keypad_type)
{
	int cond;
	if (keypad_type == 4)
		cond = 4;
	else
		cond = 3;
	uint8 pressed_value = 0xff, pressed_check = 0;
	int row;
	int col;
	for (row = 0; row < 4; row++)
	{
		GPIO_writePin(PORTD_ID, row, LOGIC_HIGH);
		//_delay_ms(500);
		for (col = 0; col < cond; col++)
		{
			///_delay_ms(500);
			uint8 pin_num = col + cond;
			if (GPIO_readPin(PORTD_ID, pin_num) == LOGIC_HIGH)
			{

				// while(GPIO_readPin(PORTD_ID , col + 4 ) == LOGIC_HIGH);
				uint8 cell = row * 4 + col;
				if (keypad_type == 4)
				{
					pressed_value = switch_values44[cell];
				}
				else
				{
					pressed_value = switch_values43[cell];
				}
				pressed_check = 1;
				break;
			}
		}
		GPIO_writePin(PORTD_ID, row, LOGIC_LOW);
		if (pressed_check == 1)
		{
			break;
		}
	}
	return pressed_value;
}