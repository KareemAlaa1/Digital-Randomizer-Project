
/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the AVR ADC driver
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../../include//std_types.h"
#include "../../include/comman_macros.h"
#include "adc_reg.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
    AREF,
    AVCC,
    Internal_1
} ADC_Vref;

typedef enum
{
    ADC0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5
} ADC_Channel;

typedef enum
{
    ADC_PRE_2,
    ADC_PRE_4,
    ADC_PRE_8,
    ADC_PRE_16,
    ADC_PRE_32,
    ADC_PRE_64,
    ADC_PRE_128,

} ADC_Prescaler;

typedef struct
{
    ADC_Vref adc_vref;
    ADC_Channel adc_channel;
    ADC_Prescaler adc_prescaler;
} ADC_Configration;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize the configrations of ADC
 */

void ADC_Init(ADC_Configration *Config_Ptr);

#endif