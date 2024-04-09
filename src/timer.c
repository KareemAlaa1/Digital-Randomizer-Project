/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR TIMER driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#include "../MCAL/TIMER/timer.h"

/*******************************************************************************
 *                                Variables                                    *
 *******************************************************************************/

Timer0_Configration TIMER0_current_config;
Timer1_Configration TIMER1_current_config;
Timer2_Configration TIMER2_current_config;

clock current_clock;

volatile ullint64 micro_delay = 0;
volatile ullint64 milli_delay = 0;

volatile ullint64 call_back_cnt = 0;

volatile uint8 max_call_back = 19;
volatile uint8 curr_call_back = 0;

volatile CallbackFunction arr[20];
volatile ullint64 delays[20];

/*
 * Description :
 * Initialize Timer0 configrations
 */

void TIMER0_init(Timer0_Configration *Config_Ptr)
{
    CLEAR_BIT(SREG, 7);

    TCNT0 = Config_Ptr->Initial_Value;
    OCR0A = Config_Ptr->ocrA;
    OCR0B = Config_Ptr->ocrB;

    if (Config_Ptr->Timer_Mode == Timer0_Normal_Mode)
    {
        CLEAR_BIT(TCCR0A, 0);
        CLEAR_BIT(TCCR0A, 1);
        CLEAR_BIT(TCCR0B, 3);
    }
    else if (Config_Ptr->Timer_Mode == Timer0_PWM_PHASE_CORRECT_Mode_0XFF)
    {
        SET_BIT(TCCR0A, 0);
        CLEAR_BIT(TCCR0A, 1);
        CLEAR_BIT(TCCR0B, 3);
    }
    else if (Config_Ptr->Timer_Mode == TIMER0_CTC_MODE)
    {
        CLEAR_BIT(TCCR0A, 0);
        SET_BIT(TCCR0A, 1);
        CLEAR_BIT(TCCR0B, 3);
    }
    else if (Config_Ptr->Timer_Mode == TIMER0_FAST_PWM_MODE_0XFF)
    {
        SET_BIT(TCCR0A, 0);
        SET_BIT(TCCR0A, 1);
        CLEAR_BIT(TCCR0B, 3);
    }
    else if (Config_Ptr->Timer_Mode == Timer0_PWM_PHASE_CORRECT_Mode_OCRA)
    {
        SET_BIT(TCCR0A, 0);
        CLEAR_BIT(TCCR0A, 1);
        SET_BIT(TCCR0B, 3);
    }
    else
    {
        SET_BIT(TCCR0A, 0);
        SET_BIT(TCCR0A, 1);
        SET_BIT(TCCR0B, 3);
    }

    if (Config_Ptr->Timer_Prescaller == TIMER0_NO_CLK_SRC)
    {
        CLEAR_BIT(TCCR0B, 0);
        CLEAR_BIT(TCCR0B, 1);
        CLEAR_BIT(TCCR0B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER0_NO_PRESCALAR)
    {
        SET_BIT(TCCR0B, 0);
        CLEAR_BIT(TCCR0B, 1);
        CLEAR_BIT(TCCR0B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER0_PRESCALAR_CLK8)
    {
        CLEAR_BIT(TCCR0B, 0);
        SET_BIT(TCCR0B, 1);
        CLEAR_BIT(TCCR0B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER0_PRESCALAR_CLK64)
    {
        SET_BIT(TCCR0B, 0);
        SET_BIT(TCCR0B, 1);
        CLEAR_BIT(TCCR0B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER0_PRESCALAR_CLK256)
    {
        CLEAR_BIT(TCCR0B, 0);
        CLEAR_BIT(TCCR0B, 1);
        SET_BIT(TCCR0B, 2);
    }
    else
    {
        SET_BIT(TCCR0B, 0);
        CLEAR_BIT(TCCR0B, 1);
        SET_BIT(TCCR0B, 2);
    }

    if (Config_Ptr->ComA == TIMER0_NORMALA)
    {
        CLEAR_BIT(TCCR0A, 7);
        CLEAR_BIT(TCCR0A, 6);
    }
    else if (Config_Ptr->ComA == TIMER0_TOGGLEA)
    {
        CLEAR_BIT(TCCR0A, 7);
        SET_BIT(TCCR0A, 6);
    }
    else if (Config_Ptr->ComA == TIMER0_CLEARA)
    {
        SET_BIT(TCCR0A, 7);
        CLEAR_BIT(TCCR0A, 6);
    }
    else
    {
        SET_BIT(TCCR0A, 7);
        SET_BIT(TCCR0A, 6);
    }

    if (Config_Ptr->ComB == TIMER0_NORMALB)
    {
        CLEAR_BIT(TCCR0A, 5);
        CLEAR_BIT(TCCR0A, 4);
    }
    else if (Config_Ptr->ComB == TIMER0_TOGGLEB)
    {
        CLEAR_BIT(TCCR0A, 5);
        SET_BIT(TCCR0A, 4);
    }
    else if (Config_Ptr->ComB == TIMER0_CLEARB)
    {
        SET_BIT(TCCR0A, 5);
        CLEAR_BIT(TCCR0A, 4);
    }
    else
    {
        SET_BIT(TCCR0A, 5);
        SET_BIT(TCCR0A, 4);
    }
    if (Config_Ptr->Timer_Interrupt.Timer0_Interrupt_A == 1)
    {
        SET_BIT(TIMSK0, 1);
    }
    else
    {
        CLEAR_BIT(TIMSK0, 1);
    }
    if (Config_Ptr->Timer_Interrupt.Timer0_Interrupt_B == 1)
    {
        SET_BIT(TIMSK0, 2);
    }
    else
    {
        CLEAR_BIT(TIMSK0, 2);
    }
    if (Config_Ptr->Timer_Interrupt.Timer0_Interrupt_OV == 1)
    {
        SET_BIT(TIMSK0, 0);
    }
    else
    {
        CLEAR_BIT(TIMSK0, 0);
    }
    TIMER0_current_config.Initial_Value = Config_Ptr->Initial_Value;
    TIMER0_current_config.Timer_Mode = Config_Ptr->Timer_Mode;
    TIMER0_current_config.Timer_Prescaller = Config_Ptr->Timer_Prescaller;
    TIMER0_current_config.ComA = Config_Ptr->ComA;
    TIMER0_current_config.ComB = Config_Ptr->ComB;
    TIMER0_current_config.ocrA = Config_Ptr->ocrA;
    TIMER0_current_config.ocrB = Config_Ptr->ocrB;
    TIMER0_current_config.Timer_Interrupt = Config_Ptr->Timer_Interrupt;

    SET_BIT(SREG, 7);
}

/*
 * Description :
 * Initialize Timer1 configrations
 */
void TIMER1_init(Timer1_Configration *Config_Ptr)
{
    CLEAR_BIT(SREG, 7);

    TCNT1L = Config_Ptr->Initial_Value;
    OCR1AL = Config_Ptr->ocrA;
    OCR1BL = Config_Ptr->ocrB;
    ICR1L = Config_Ptr->icr;

    if (Config_Ptr->Timer_Mode == Timer1_Normal_Mode)
    {
        CLEAR_BIT(TCCR1A, 0);
        CLEAR_BIT(TCCR1A, 1);
        CLEAR_BIT(TCCR1B, 3);
        CLEAR_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == Timer1_PWM_PHASE_CORRECT_8_BIT_Mode)
    {
        SET_BIT(TCCR1A, 0);
        CLEAR_BIT(TCCR1A, 1);
        CLEAR_BIT(TCCR1B, 3);
        CLEAR_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == Timer1_PWM_PHASE_CORRECT_9_BIT_Mode)
    {
        CLEAR_BIT(TCCR1A, 0);
        SET_BIT(TCCR1A, 1);
        CLEAR_BIT(TCCR1B, 3);
        CLEAR_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == Timer1_PWM_PHASE_CORRECT_10_BIT_Mode)
    {
        SET_BIT(TCCR1A, 0);
        SET_BIT(TCCR1A, 1);
        CLEAR_BIT(TCCR1B, 3);
        CLEAR_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == TIMER1_CTC_MODE_OCRA)
    {
        CLEAR_BIT(TCCR1A, 0);
        CLEAR_BIT(TCCR1A, 1);
        SET_BIT(TCCR1B, 3);
        CLEAR_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == TIMER1_FAST_PWM_8_MODE)
    {
        SET_BIT(TCCR1A, 0);
        CLEAR_BIT(TCCR1A, 1);
        SET_BIT(TCCR1B, 3);
        CLEAR_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == TIMER1_FAST_PWM_9_MODE)
    {
        CLEAR_BIT(TCCR1A, 0);
        SET_BIT(TCCR1A, 1);
        SET_BIT(TCCR1B, 3);
        CLEAR_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == TIMER1_FAST_PWM_10_MODE)
    {
        SET_BIT(TCCR1A, 0);
        SET_BIT(TCCR1A, 1);
        SET_BIT(TCCR1B, 3);
        CLEAR_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == Timer1_PWM_PHASE_FREQUENCY_CORRECT_Mode_ICR)
    {
        CLEAR_BIT(TCCR1A, 0);
        CLEAR_BIT(TCCR1A, 1);
        CLEAR_BIT(TCCR1B, 3);
        SET_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == Timer1_PWM_PHASE_FREQUENCY_CORRECT_Mode_OCRA)
    {
        SET_BIT(TCCR1A, 0);
        CLEAR_BIT(TCCR1A, 1);
        CLEAR_BIT(TCCR1B, 3);
        SET_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == Timer1_PWM_PHASE_CORRECT_ICR)
    {
        CLEAR_BIT(TCCR1A, 0);
        SET_BIT(TCCR1A, 1);
        CLEAR_BIT(TCCR1B, 3);
        SET_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == Timer1_PWM_PHASE_CORRECT_OCRA)
    {
        SET_BIT(TCCR1A, 0);
        SET_BIT(TCCR1A, 1);
        CLEAR_BIT(TCCR1B, 3);
        SET_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == TIMER1_CTC_MODE_ICR)
    {
        CLEAR_BIT(TCCR1A, 0);
        CLEAR_BIT(TCCR1A, 1);
        SET_BIT(TCCR1B, 3);
        SET_BIT(TCCR1B, 4);
    }
    else if (Config_Ptr->Timer_Mode == TIMER1_FAST_PWM_ICR)
    {
        CLEAR_BIT(TCCR1A, 0);
        SET_BIT(TCCR1A, 1);
        SET_BIT(TCCR1B, 3);
        SET_BIT(TCCR1B, 4);
    }
    else
    {
        SET_BIT(TCCR1A, 0);
        SET_BIT(TCCR1A, 1);
        SET_BIT(TCCR1B, 3);
        SET_BIT(TCCR1B, 4);
    }

    if (Config_Ptr->Timer_Prescaller == TIMER1_NO_CLK_SRC)
    {
        CLEAR_BIT(TCCR1B, 0);
        CLEAR_BIT(TCCR1B, 1);
        CLEAR_BIT(TCCR1B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER1_NO_PRESCALAR)
    {
        SET_BIT(TCCR1B, 0);
        CLEAR_BIT(TCCR1B, 1);
        CLEAR_BIT(TCCR1B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER1_PRESCALAR_CLK8)
    {
        CLEAR_BIT(TCCR1B, 0);
        SET_BIT(TCCR1B, 1);
        CLEAR_BIT(TCCR1B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER1_PRESCALAR_CLK64)
    {
        SET_BIT(TCCR1B, 0);
        SET_BIT(TCCR1B, 1);
        CLEAR_BIT(TCCR1B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER1_PRESCALAR_CLK256)
    {
        CLEAR_BIT(TCCR1B, 0);
        CLEAR_BIT(TCCR1B, 1);
        SET_BIT(TCCR1B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER1_PRESCALAR_CLK1024)
    {
        SET_BIT(TCCR1B, 0);
        CLEAR_BIT(TCCR1B, 1);
        SET_BIT(TCCR1B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER1_PRESCALAR_EXTERNAL_CLOCK_FALLING_EDGE)
    {
        CLEAR_BIT(TCCR1B, 0);
        SET_BIT(TCCR1B, 1);
        SET_BIT(TCCR1B, 2);
    }
    else
    {
        SET_BIT(TCCR1B, 0);
        SET_BIT(TCCR1B, 1);
        SET_BIT(TCCR1B, 2);
    }

    if (Config_Ptr->ComA == TIMER1_NORMALA)
    {
        CLEAR_BIT(TCCR1A, 7);
        CLEAR_BIT(TCCR1A, 6);
    }
    else if (Config_Ptr->ComA == TIMER1_TOGGLEA)
    {
        CLEAR_BIT(TCCR1A, 7);
        SET_BIT(TCCR1A, 6);
    }
    else if (Config_Ptr->ComA == TIMER1_CLEARA)
    {
        SET_BIT(TCCR1A, 7);
        CLEAR_BIT(TCCR1A, 6);
    }
    else
    {
        SET_BIT(TCCR1A, 7);
        SET_BIT(TCCR1A, 6);
    }

    if (Config_Ptr->ComB == TIMER1_NORMALB)
    {
        CLEAR_BIT(TCCR1A, 5);
        CLEAR_BIT(TCCR1A, 4);
    }
    else if (Config_Ptr->ComB == TIMER1_TOGGLEB)
    {
        CLEAR_BIT(TCCR1A, 5);
        SET_BIT(TCCR1A, 4);
    }
    else if (Config_Ptr->ComB == TIMER1_CLEARB)
    {
        SET_BIT(TCCR1A, 5);
        CLEAR_BIT(TCCR1A, 4);
    }
    else
    {
        SET_BIT(TCCR1A, 5);
        SET_BIT(TCCR1A, 4);
    }

    if (Config_Ptr->Timer_Interrupt.Timer1_Interrupt_A == 1)
    {
        SET_BIT(TIMSK1, 1);
    }
    else
    {
        CLEAR_BIT(TIMSK1, 1);
    }
    if (Config_Ptr->Timer_Interrupt.Timer1_Interrupt_B == 1)
    {
        SET_BIT(TIMSK1, 2);
    }
    else
    {
        CLEAR_BIT(TIMSK1, 2);
    }
    if (Config_Ptr->Timer_Interrupt.Timer1_Interrupt_OV == 1)
    {
        SET_BIT(TIMSK1, 0);
    }
    else
    {
        CLEAR_BIT(TIMSK1, 0);
    }
    if (Config_Ptr->Timer_Interrupt.Timer1_Input_Capture_Interrupt == 1)
    {
        SET_BIT(TIMSK1, 5);
    }
    else
    {
        CLEAR_BIT(TIMSK1, 5);
    }

    TIMER1_current_config.Initial_Value = Config_Ptr->Initial_Value;
    TIMER1_current_config.Timer_Mode = Config_Ptr->Timer_Mode;
    TIMER1_current_config.Timer_Prescaller = Config_Ptr->Timer_Prescaller;
    TIMER1_current_config.ComA = Config_Ptr->ComA;
    TIMER1_current_config.ComB = Config_Ptr->ComB;
    TIMER1_current_config.ocrA = Config_Ptr->ocrA;
    TIMER1_current_config.ocrB = Config_Ptr->ocrB;
    TIMER1_current_config.Timer_Interrupt = Config_Ptr->Timer_Interrupt;

    SET_BIT(SREG, 7);
}

/*
 * Description :
 * Initialize Timer2 configrations
 */
void TIMER2_init(Timer2_Configration *Config_Ptr)
{
    CLEAR_BIT(SREG, 7);

    TCNT2 = Config_Ptr->Initial_Value;
    OCR2A = Config_Ptr->ocrA;
    OCR2B = Config_Ptr->ocrB;

    if (Config_Ptr->Timer_Mode == Timer2_Normal_Mode)
    {
        CLEAR_BIT(TCCR2A, 0);
        CLEAR_BIT(TCCR2A, 1);
        CLEAR_BIT(TCCR2B, 3);
    }
    else if (Config_Ptr->Timer_Mode == Timer2_PWM_PHASE_CORRECT_Mode_0XFF)
    {
        SET_BIT(TCCR2A, 0);
        CLEAR_BIT(TCCR2A, 1);
        CLEAR_BIT(TCCR2B, 3);
    }
    else if (Config_Ptr->Timer_Mode == TIMER2_CTC_MODE)
    {
        CLEAR_BIT(TCCR2A, 0);
        SET_BIT(TCCR2A, 1);
        CLEAR_BIT(TCCR2B, 3);
    }
    else if (Config_Ptr->Timer_Mode == TIMER2_FAST_PWM_MODE_0XFF)
    {
        SET_BIT(TCCR2A, 0);
        SET_BIT(TCCR2A, 1);
        CLEAR_BIT(TCCR2B, 3);
    }
    else if (Config_Ptr->Timer_Mode == Timer2_PWM_PHASE_CORRECT_Mode_OCRA)
    {
        SET_BIT(TCCR2A, 0);
        CLEAR_BIT(TCCR2A, 1);
        SET_BIT(TCCR2B, 3);
    }
    else
    {
        SET_BIT(TCCR2A, 0);
        SET_BIT(TCCR2A, 1);
        SET_BIT(TCCR2B, 3);
    }

    if (Config_Ptr->Timer_Prescaller == TIMER2_NO_CLK_SRC)
    {
        CLEAR_BIT(TCCR2B, 0);
        CLEAR_BIT(TCCR2B, 1);
        CLEAR_BIT(TCCR2B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER2_NO_PRESCALAR)
    {
        SET_BIT(TCCR2B, 0);
        CLEAR_BIT(TCCR2B, 1);
        CLEAR_BIT(TCCR2B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER2_PRESCALAR_CLK8)
    {
        CLEAR_BIT(TCCR2B, 0);
        SET_BIT(TCCR2B, 1);
        CLEAR_BIT(TCCR2B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER2_PRESCALAR_CLK32)
    {
        SET_BIT(TCCR2B, 0);
        SET_BIT(TCCR2B, 1);
        CLEAR_BIT(TCCR2B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER2_PRESCALAR_CLK64)
    {
        CLEAR_BIT(TCCR2B, 0);
        CLEAR_BIT(TCCR2B, 1);
        SET_BIT(TCCR2B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER2_PRESCALAR_CLK128)
    {
        SET_BIT(TCCR2B, 0);
        CLEAR_BIT(TCCR2B, 1);
        SET_BIT(TCCR2B, 2);
    }
    else if (Config_Ptr->Timer_Prescaller == TIMER2_PRESCALAR_CLK256)
    {
        CLEAR_BIT(TCCR2B, 0);
        SET_BIT(TCCR2B, 1);
        SET_BIT(TCCR2B, 2);
    }
    else
    {
        SET_BIT(TCCR2B, 0);
        SET_BIT(TCCR2B, 1);
        SET_BIT(TCCR2B, 2);
    }

    if (Config_Ptr->ComA == TIMER2_NORMALA)
    {
        CLEAR_BIT(TCCR2A, 7);
        CLEAR_BIT(TCCR2A, 6);
    }
    else if (Config_Ptr->ComA == TIMER2_TOGGLEA)
    {
        CLEAR_BIT(TCCR2A, 7);
        SET_BIT(TCCR2A, 6);
    }
    else if (Config_Ptr->ComA == TIMER2_CLEARA)
    {
        SET_BIT(TCCR2A, 7);
        CLEAR_BIT(TCCR2A, 6);
    }
    else
    {
        SET_BIT(TCCR2A, 7);
        SET_BIT(TCCR2A, 6);
    }

    if (Config_Ptr->ComB == TIMER2_NORMALB)
    {
        CLEAR_BIT(TCCR2A, 5);
        CLEAR_BIT(TCCR2A, 4);
    }
    else if (Config_Ptr->ComB == TIMER2_TOGGLEB)
    {
        CLEAR_BIT(TCCR2A, 5);
        SET_BIT(TCCR2A, 4);
    }
    else if (Config_Ptr->ComB == TIMER2_CLEARB)
    {
        SET_BIT(TCCR2A, 5);
        CLEAR_BIT(TCCR2A, 4);
    }
    else
    {
        SET_BIT(TCCR2A, 5);
        SET_BIT(TCCR2A, 4);
    }
    if (Config_Ptr->Timer_Interrupt.Timer2_Interrupt_A == 1)
    {
        SET_BIT(TIMSK2, 1);
    }
    else
    {
        CLEAR_BIT(TIMSK2, 1);
    }
    if (Config_Ptr->Timer_Interrupt.Timer2_Interrupt_B == 1)
    {
        SET_BIT(TIMSK2, 2);
    }
    else
    {
        CLEAR_BIT(TIMSK2, 2);
    }
    if (Config_Ptr->Timer_Interrupt.Timer2_Interrupt_OV == 1)
    {
        SET_BIT(TIMSK2, 0);
    }
    else
    {
        CLEAR_BIT(TIMSK2, 0);
    }
    TIMER2_current_config.Initial_Value = Config_Ptr->Initial_Value;
    TIMER2_current_config.Timer_Mode = Config_Ptr->Timer_Mode;
    TIMER2_current_config.Timer_Prescaller = Config_Ptr->Timer_Prescaller;
    TIMER2_current_config.ComA = Config_Ptr->ComA;
    TIMER2_current_config.ComB = Config_Ptr->ComB;
    TIMER2_current_config.ocrA = Config_Ptr->ocrA;
    TIMER2_current_config.ocrB = Config_Ptr->ocrB;
    TIMER2_current_config.Timer_Interrupt = Config_Ptr->Timer_Interrupt;

    SET_BIT(SREG, 7);
}

ISR(TIMER0_COMPA_vect)
{
    /*
    struct task --> poiter callback / task time


    */
    call_back_cnt++;
    ullint64 maxi = 0;
    uint8 i = 0;
    for (i = 0; i < curr_call_back; i++)
    {
        if (maxi < delays[i])
        {
            maxi = delays[i];
        }
        if (call_back_cnt % delays[i] == 0)
        {
            arr[i]();
        }
    }
    if (call_back_cnt >= maxi)
    {
        call_back_cnt = 0;
    }

    milli_delay--;
    micro_delay--;
}

ISR(TIMER1_COMPA_vect)
{

    milli_delay--;
    micro_delay--;
}

/*
 * Description :
 * Delay milli seconds for timer0 using interrupt and ocrA
 */
void TIMER0_delay_ms(ullint64 number)
{

    Timer0_Configration config;
    config.Initial_Value = 0;
    config.ocrA = 250;
    config.Timer_Prescaller = TIMER0_PRESCALAR_CLK64;
    config.Timer_Interrupt.Timer0_Interrupt_A = 1;
    config.Timer_Mode = TIMER0_CTC_MODE;
    TIMER0_init(&config);

    milli_delay = number;
    micro_delay = number;

    while (milli_delay > 0)
    {
    }
}

/*
 * Description :
 * Delay milli seconds for timer1 using interrupt and ocrA
 */
void TIMER1_delay_ms(ullint64 number)
{

    Timer1_Configration config;
    config.Initial_Value = 0;
    config.ocrA = 250;
    config.Timer_Prescaller = TIMER1_PRESCALAR_CLK64;
    config.Timer_Interrupt.Timer1_Interrupt_A = 1;
    config.Timer_Mode = TIMER1_CTC_MODE_OCRA;
    TIMER1_init(&config);

    milli_delay = number;
    micro_delay = number;

    while (milli_delay > 0)
    {
    }
}

/*
 * Description :
 * Delay milli seconds for timer2 using interrupt and ocrA
 */
void TIMER2_delay_ms(ullint64 number)
{

    Timer2_Configration config;
    config.Initial_Value = 0;
    config.ocrA = 250;
    config.Timer_Prescaller = TIMER2_PRESCALAR_CLK64;
    config.Timer_Interrupt.Timer2_Interrupt_A = 1;
    config.Timer_Mode = TIMER2_CTC_MODE;
    TIMER2_init(&config);

    milli_delay = number;
    micro_delay = number;

    while (milli_delay > 0)
    {
        if (READ_BIT(TIFR2, 1))
        {
            milli_delay--;
            SET_BIT(TIFR2, 1);
        }
    }
}

/*
 * Description :
 * Delay micro seconds for timer0 using interrupt and ocrA
 */
void TIMER0_delay_us(ullint64 number)
{
    Timer0_Configration config;
    config.Initial_Value = 0;
    config.ocrA = 16;
    config.Timer_Prescaller = TIMER0_NO_PRESCALAR;
    config.Timer_Interrupt.Timer0_Interrupt_A = 1;
    config.Timer_Mode = TIMER0_CTC_MODE;
    TIMER0_init(&config);

    milli_delay = number;
    micro_delay = number;

    while (micro_delay > 0)
    {
    }
}

/*
 * Description :
 * Delay micro seconds for timer1 using interrupt and ocrA
 */
void TIMER1_delay_us(ullint64 number)
{

    Timer1_Configration config;
    config.Initial_Value = 0;
    config.ocrA = 16;
    config.Timer_Prescaller = TIMER1_NO_PRESCALAR;
    config.Timer_Interrupt.Timer1_Interrupt_A = 1;
    config.Timer_Mode = TIMER1_CTC_MODE_OCRA;
    TIMER1_init(&config);

    milli_delay = number;
    micro_delay = number;

    while (micro_delay > 0)
    {
    }
}

/*
 * Description :
 * Delay micro seconds for timer2 using interrupt and ocrA
 */
void TIMER2_delay_us(ullint64 number)
{

    Timer2_Configration config;
    config.Initial_Value = 0;
    config.ocrA = 16;
    config.Timer_Prescaller = TIMER2_NO_PRESCALAR;
    config.Timer_Interrupt.Timer2_Interrupt_A = 1;
    config.Timer_Mode = TIMER2_CTC_MODE;
    TIMER2_init(&config);

    milli_delay = number;
    micro_delay = number;

    while (micro_delay > 0)
    {
    }
}

/*
 * Description :
 * Start using interrupt in timer0 for callback functions
 */
void startcallback()
{

    // activates timer0 in overflow mode to start callback
    Timer0_Configration config;
    config.Initial_Value = 0;
    config.ocrA = 16;
    config.Timer_Prescaller = TIMER0_NO_PRESCALAR;
    config.Timer_Interrupt.Timer0_Interrupt_A = 1;
    config.Timer_Mode = TIMER0_CTC_MODE;
    TIMER0_init(&config);
}

/*
 * Description :
 * Set pointers to callback functions to call it according to its corresponding time in (delays) array
 */
void setCallback(CallbackFunction cb)
{
    if (curr_call_back <= max_call_back)
    {
        arr[curr_call_back] = cb;
        curr_call_back++;
    }
}

/*
 * Description :
 * Set time of callback function to be called at it
 */
void setCallbackdelay(ullint64 number)
{
    if (curr_call_back <= max_call_back + 1)
    {
        delays[curr_call_back - 1] = number;
    }
}
