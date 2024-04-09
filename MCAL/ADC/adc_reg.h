#ifndef ADC_REG_H_
#define ADC_REG_H_

#define ADMUX (*(volatile unsigned char*)0x7C)
#define ADCSRA (*(volatile unsigned char*)0x7A)
#define ADCL (*(volatile unsigned char*)0x79)
#define ADCH (*(volatile unsigned char*)0x78)
#define ADCSRB (*(volatile unsigned char*)0x7B)
#define DIDR0 (*(volatile unsigned char*)0x7E)


#endif