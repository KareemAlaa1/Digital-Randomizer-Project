
/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the AVR ADC driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#include "../MCAL/ADC/adc.h"

/*
 * Description :
 * Initialize the configrations of ADC
 */

void ADC_Init(ADC_Configration *Config_Ptr)
{

    SET_BIT(ADCSRA, 7);
    if (Config_Ptr->adc_vref == AREF)
    {
        CLEAR_BIT(ADMUX, 7);
        CLEAR_BIT(ADMUX, 6);
    }
    else if (Config_Ptr->adc_vref == AVCC)
    {
        CLEAR_BIT(ADMUX, 7);
        SET_BIT(ADMUX, 6);
    }
    else
    {
        SET_BIT(ADMUX, 7);
        SET_BIT(ADMUX, 6);
    }

    if (Config_Ptr->adc_channel == ADC0)
    {
        CLEAR_BIT(ADMUX, 0);
        CLEAR_BIT(ADMUX, 1);
        CLEAR_BIT(ADMUX, 2);
        CLEAR_BIT(ADMUX, 3);
    }
    else if (Config_Ptr->adc_channel == ADC1)
    {
        SET_BIT(ADMUX, 0);
        CLEAR_BIT(ADMUX, 1);
        CLEAR_BIT(ADMUX, 2);
        CLEAR_BIT(ADMUX, 3);
    }
    else if (Config_Ptr->adc_channel == ADC2)
    {
        CLEAR_BIT(ADMUX, 0);
        SET_BIT(ADMUX, 1);
        CLEAR_BIT(ADMUX, 2);
        CLEAR_BIT(ADMUX, 3);
    }
    else if (Config_Ptr->adc_channel == ADC3)
    {
        SET_BIT(ADMUX, 0);
        SET_BIT(ADMUX, 1);
        CLEAR_BIT(ADMUX, 2);
        CLEAR_BIT(ADMUX, 3);
    }
    else if (Config_Ptr->adc_channel == ADC4)
    {
        CLEAR_BIT(ADMUX, 0);
        CLEAR_BIT(ADMUX, 1);
        SET_BIT(ADMUX, 2);
        CLEAR_BIT(ADMUX, 3);
    }
    else
    {
        SET_BIT(ADMUX, 0);
        CLEAR_BIT(ADMUX, 1);
        SET_BIT(ADMUX, 2);
        CLEAR_BIT(ADMUX, 3);
    }

    if (Config_Ptr->adc_prescaler == ADC_PRE_2)
    {
        CLEAR_BIT(ADCSRA, 0);
        CLEAR_BIT(ADCSRA, 1);
        CLEAR_BIT(ADCSRA, 2);
    }
    else if (Config_Ptr->adc_prescaler == ADC_PRE_4)
    {
        CLEAR_BIT(ADCSRA, 0);
        SET_BIT(ADCSRA, 1);
        CLEAR_BIT(ADCSRA, 2);
    }
    else if (Config_Ptr->adc_prescaler == ADC_PRE_8)
    {
        SET_BIT(ADCSRA, 0);
        SET_BIT(ADCSRA, 1);
        CLEAR_BIT(ADCSRA, 2);
    }
    else if (Config_Ptr->adc_prescaler == ADC_PRE_16)
    {
        CLEAR_BIT(ADCSRA, 0);
        CLEAR_BIT(ADCSRA, 1);
        SET_BIT(ADCSRA, 2);
    }
    else if (Config_Ptr->adc_prescaler == ADC_PRE_32)
    {
        SET_BIT(ADCSRA, 0);
        CLEAR_BIT(ADCSRA, 1);
        SET_BIT(ADCSRA, 2);
    }
    else if (Config_Ptr->adc_prescaler == ADC_PRE_64)
    {
        CLEAR_BIT(ADCSRA, 0);
        SET_BIT(ADCSRA, 1);
        SET_BIT(ADCSRA, 2);
    }
    else
    {
        SET_BIT(ADCSRA, 0);
        SET_BIT(ADCSRA, 1);
        SET_BIT(ADCSRA, 2);
    }
}
