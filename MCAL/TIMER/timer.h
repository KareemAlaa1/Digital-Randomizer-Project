/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR TIMER driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "../../include//std_types.h"
#include "../../include/comman_macros.h"
#include "timer_reg.h"
#include "../GPIO/gpio.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef void (*CallbackFunction)(void);

typedef enum
{
	Timer0_Normal_Mode,
	Timer0_PWM_PHASE_CORRECT_Mode_0XFF,
	TIMER0_CTC_MODE,
	TIMER0_FAST_PWM_MODE_0XFF,
	Timer0_PWM_PHASE_CORRECT_Mode_OCRA,
	TIMER0_FAST_PWM_MODE_OCRA
} Timer0_Modes;

typedef enum
{
	TIMER0_NO_CLK_SRC,
	TIMER0_NO_PRESCALAR,
	TIMER0_PRESCALAR_CLK8,
	TIMER0_PRESCALAR_CLK64,
	TIMER0_PRESCALAR_CLK256,
	TIMER0_PRESCALAR_CLK1024,
} Timer0_PRESCALAR;

typedef struct
{
	uint8 Timer0_Interrupt_A;
	uint8 Timer0_Interrupt_B;
	uint8 Timer0_Interrupt_OV;

} Timer0_Interrupt;

typedef enum
{
	TIMER0_NORMALA,
	TIMER0_TOGGLEA,
	TIMER0_CLEARA,
	TIMER0_SETA,

} TIMER0_COMA;

typedef enum
{
	TIMER0_NORMALB,
	TIMER0_TOGGLEB,
	TIMER0_CLEARB,
	TIMER0_SETB,

} TIMER0_COMB;

typedef struct
{
	uint8 Initial_Value;
	Timer0_Modes Timer_Mode;
	Timer0_PRESCALAR Timer_Prescaller;
	TIMER0_COMA ComA;
	TIMER0_COMB ComB;
	uint8 ocrA;
	uint8 ocrB;
	Timer0_Interrupt Timer_Interrupt;

} Timer0_Configration;

typedef enum
{
	Timer1_Normal_Mode,
	Timer1_PWM_PHASE_CORRECT_8_BIT_Mode,
	Timer1_PWM_PHASE_CORRECT_9_BIT_Mode,
	Timer1_PWM_PHASE_CORRECT_10_BIT_Mode,
	TIMER1_CTC_MODE_OCRA,
	TIMER1_FAST_PWM_8_MODE,
	TIMER1_FAST_PWM_9_MODE,
	TIMER1_FAST_PWM_10_MODE,
	Timer1_PWM_PHASE_FREQUENCY_CORRECT_Mode_ICR,
	Timer1_PWM_PHASE_FREQUENCY_CORRECT_Mode_OCRA,
	Timer1_PWM_PHASE_CORRECT_ICR,
	Timer1_PWM_PHASE_CORRECT_OCRA,
	TIMER1_CTC_MODE_ICR,
	TIMER1_FAST_PWM_ICR,
	TIMER1_FAST_PWM_8_OCRA,
} Timer1_Modes;

typedef enum
{
	TIMER1_NO_CLK_SRC,
	TIMER1_NO_PRESCALAR,
	TIMER1_PRESCALAR_CLK8,
	TIMER1_PRESCALAR_CLK64,
	TIMER1_PRESCALAR_CLK256,
	TIMER1_PRESCALAR_CLK1024,
	TIMER1_PRESCALAR_EXTERNAL_CLOCK_FALLING_EDGE,
	TIMER1_PRESCALAR_EXTERNAL_CLOCK_RISING_EDGE,
} Timer1_PRESCALAR;

typedef struct
{
	uint8 Timer1_Interrupt_A;
	uint8 Timer1_Interrupt_B;
	uint8 Timer1_Interrupt_OV;
	uint8 Timer1_Input_Capture_Interrupt;
} Timer1_Interrupt;

typedef enum
{
	TIMER1_NORMALA,
	TIMER1_TOGGLEA,
	TIMER1_CLEARA,
	TIMER1_SETA,

} TIMER1_COMA;

typedef enum
{
	TIMER1_NORMALB,
	TIMER1_TOGGLEB,
	TIMER1_CLEARB,
	TIMER1_SETB,

} TIMER1_COMB;

typedef struct
{
	uint8 Initial_Value;
	Timer1_Modes Timer_Mode;
	Timer1_PRESCALAR Timer_Prescaller;
	TIMER1_COMA ComA;
	TIMER1_COMB ComB;
	uint16 ocrA;
	uint16 ocrB;
	uint16 icr;
	Timer1_Interrupt Timer_Interrupt;

} Timer1_Configration;

typedef enum
{
	Timer2_Normal_Mode,
	Timer2_PWM_PHASE_CORRECT_Mode_0XFF,
	TIMER2_CTC_MODE,
	TIMER2_FAST_PWM_MODE_0XFF,
	Timer2_PWM_PHASE_CORRECT_Mode_OCRA,
	TIMER2_FAST_PWM_MODE_OCRA
} Timer2_Modes;

typedef enum
{
	TIMER2_NO_CLK_SRC,
	TIMER2_NO_PRESCALAR,
	TIMER2_PRESCALAR_CLK8,
	TIMER2_PRESCALAR_CLK32,
	TIMER2_PRESCALAR_CLK64,
	TIMER2_PRESCALAR_CLK128,
	TIMER2_PRESCALAR_CLK256,
	TIMER2_PRESCALAR_CLK1024,
} Timer2_PRESCALAR;

typedef struct
{
	uint8 Timer2_Interrupt_A;
	uint8 Timer2_Interrupt_B;
	uint8 Timer2_Interrupt_OV;

} Timer2_Interrupt;

typedef enum
{
	TIMER2_NORMALA,
	TIMER2_TOGGLEA,
	TIMER2_CLEARA,
	TIMER2_SETA,

} TIMER2_COMA;

typedef enum
{
	TIMER2_NORMALB,
	TIMER2_TOGGLEB,
	TIMER2_CLEARB,
	TIMER2_SETB,

} TIMER2_COMB;

typedef struct
{
	uint8 Initial_Value;
	Timer2_Modes Timer_Mode;
	Timer2_PRESCALAR Timer_Prescaller;
	TIMER0_COMA ComA;
	TIMER0_COMB ComB;
	uint8 ocrA;
	uint8 ocrB;
	Timer2_Interrupt Timer_Interrupt;

} Timer2_Configration;

typedef struct
{
	uint8 days;
	uint8 hours;
	uint8 minutes;
	uint8 seconds;

} clock;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize Timer0 configrations
 */
void TIMER0_init(Timer0_Configration *Config_Ptr);

/*
 * Description :
 * Initialize Timer1 configrations
 */
void TIMER1_init(Timer1_Configration *Config_Ptr);

/*
 * Description :
 * Initialize Timer2 configrations
 */
void TIMER2_init(Timer2_Configration *Config_Ptr);

/*
 * Description :
 * Delay milli seconds for timer0 using interrupt and ocrA
 */
void TIMER0_delay_ms(ullint64 number);

/*
 * Description :
 * Delay micro seconds for timer0 using interrupt and ocrA
 */
void TIMER0_delay_us(ullint64 number);

/*
 * Description :
 * Delay milli seconds for timer1 using interrupt and ocrA
 */
void TIMER1_delay_ms(ullint64 number);

/*
 * Description :
 * Delay micro seconds for timer1 using interrupt and ocrA
 */
void TIMER1_delay_us(ullint64 number);

/*
 * Description :
 * Delay milli seconds for timer2 using interrupt and ocrA
 */
void TIMER2_delay_ms(ullint64 number);

/*
 * Description :
 * Delay micro seconds for timer2 using interrupt and ocrA
 */
void TIMER2_delay_us(ullint64 number);

/*
 * Description :
 * Start using interrupt in timer0 for callback functions
 */
void startcallback();

/*
 * Description :
 * Set pointers to callback functions to call it according to its corresponding time in (delays) array
 */
void setCallback(CallbackFunction cb);

/*
 * Description :
 * Set time of callback function to be called at it
 */
void setCallbackdelay(ullint64 number);

#endif /* TIMER_H_ */