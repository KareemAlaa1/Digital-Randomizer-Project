/******************************************************************************
 *
 * Module: Digital Randomizer Project
 *
 * File Name: main.c
 *
 * Description: Source file for Digital Randomizer Project
 *
 * Author: Kareem Alaa
 *
 *******************************************************************************/

#include "../MCAL/GPIO/gpio.h"
#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/SEVEN_SEG/seven_seg.h"
#include "../MCAL/TIMER/timer.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/SPI/spi.h"
#include "../MCAL/I2C/i2c.h"
#include "../MCAL/ADC/adc.h"
#include "../MCAL/EEPROM/eeprom.h"
#include <util/delay.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define mcu_type 1
// 0 for hmi
// 1 for rand
#define rand_alg_type 3
// 0 for counting
// 1 for timer
// 2 for adc
// 3 for xorshift

#if mcu_type == 0

/*******************************************************************************
 *                              Start of HMI code                              *
 *******************************************************************************/

#define servo_port 0
#define servo_pin 1

#define buzzer_port 0
#define buzzer_pin 2

#define generate_port 2
#define generate_pin 3

#define next_port 2
#define next_pin 2

#define previous_port 2
#define previous_pin 6

#define digit0_port 0
#define digit0_pin 3

#define digit1_port 0
#define digit1_pin 4

#define digit2_port 2
#define digit2_pin 4

#define digit3_port 2
#define digit3_pin 5

#define digit4_port 2
#define digit4_pin 7

uint16 currentNumber = 0;
uint8 currentDigit = 0;
uint8 digits[5] = {0, 0, 0, 0, 0}; // digits[0] --> most sig.
uint8 digitsPorts[5] = {0, 0, 2, 2, 2};
uint8 digitsPins[5] = {3, 4, 4, 5, 7};

// next
ISR(INT0_vect)
{
  if (currentDigit != 4)
  {
    currentDigit++;
    EEPROM_Write(0x03, currentDigit);
    GPIO_writePin(digitsPorts[currentDigit - 1], digitsPins[currentDigit - 1], LOGIC_LOW);
    GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_HIGH);
    SEVEN_SEG_Write(1, digits[currentDigit]);
  }
}

// generate
ISR(INT1_vect)
{
start_label:
  UART_vTransmit(0x23);
  _delay_ms(1030);
  uint8 i = 0;
  for (i = 0; i < 5; i++)
  {
    digits[i] = UART_vReceive();
    _delay_ms(50);
  }
  currentDigit = 0;
  currentNumber = digits[0] + digits[1] * 10 + digits[2] * 100 + digits[3] * 1000 + digits[4] * 10000;
  _delay_ms(2000);
  float buzzer_cycle;

  // Write new random number to eeprom
  EEPROM_Write(0x03, currentDigit);
  EEPROM_Write(0x01, digits[0]);
  EEPROM_Write(0x02, digits[1]);
  EEPROM_Write(0x04, digits[2]);
  EEPROM_Write(0x05, digits[3]);
  EEPROM_Write(0x06, digits[4]);

  GPIO_writePin(digit0_port, digit0_pin, LOGIC_LOW);
  GPIO_writePin(digit1_port, digit1_pin, LOGIC_LOW);
  GPIO_writePin(digit2_port, digit2_pin, LOGIC_LOW);
  GPIO_writePin(digit3_port, digit3_pin, LOGIC_LOW);
  GPIO_writePin(digit4_port, digit4_pin, LOGIC_LOW);

  _delay_ms(20);

  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_HIGH);
  SEVEN_SEG_Write(1, digits[currentDigit]);
  EEPROM_Write(0x03, currentDigit);
  buzzer_cycle = (float)digits[currentDigit] / 10 * 156.0;
  OCR1BL = 156 - (uint8)buzzer_cycle;
  uint16 z = 0;
  uint8 prev = 0;
  uint8 curr = 0;
  uint8 prev2 = 0;
  uint8 curr2 = 0;
  uint8 prev3 = GPIO_readPin(PORTD_ID, 6);
  uint8 curr3 = GPIO_readPin(PORTD_ID, 6);
  for (z = 0; z < 125; z++)
  {

    // for getting next button while current process is running
    curr = GPIO_readPin(PORTD_ID, 2);
    if (curr && !prev)
    {
      return;
    }
    prev = GPIO_readPin(PORTD_ID, 2);
    _delay_ms(2);

    // for getting previous button while current process is running
    curr2 = GPIO_readPin(PORTD_ID, 3);
    if (curr2 && !prev2)
    {
      goto start_label;
    }
    prev2 = GPIO_readPin(PORTD_ID, 3);
    _delay_ms(3);

    // for getting generate button while current process is running
    curr3 = GPIO_readPin(PORTD_ID, 6);
    if (curr3 != prev3)
    {
      return;
    }
    prev3 = GPIO_readPin(PORTD_ID, 6);
    _delay_ms(3);
  }
  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_LOW);

  currentDigit++;
  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_HIGH);
  SEVEN_SEG_Write(1, digits[currentDigit]);
  EEPROM_Write(0x03, currentDigit);
  buzzer_cycle = (float)digits[currentDigit] / 10 * 156.0;
  OCR1BL = 156 - (uint8)buzzer_cycle;
  for (z = 0; z < 125; z++)
  {

    // for getting next button while current process is running
    curr = GPIO_readPin(PORTD_ID, 2);
    if (curr && !prev)
    {
      return;
    }
    prev = GPIO_readPin(PORTD_ID, 2);
    _delay_ms(2);

    // for getting generate button while current process is running
    curr2 = GPIO_readPin(PORTD_ID, 3);
    if (curr2 && !prev2)
    {
      goto start_label;
    }
    prev2 = GPIO_readPin(PORTD_ID, 3);
    _delay_ms(3);

    // for getting previous button while current process is running
    curr3 = GPIO_readPin(PORTD_ID, 6);
    if (curr3 != prev3)
    {
      return;
    }
    prev3 = GPIO_readPin(PORTD_ID, 6);
    _delay_ms(3);
  }
  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_LOW);

  currentDigit++;
  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_HIGH);
  SEVEN_SEG_Write(1, digits[currentDigit]);
  EEPROM_Write(0x03, currentDigit);
  buzzer_cycle = (float)digits[currentDigit] / 10 * 156.0;
  OCR1BL = 156 - (uint8)buzzer_cycle;
  for (z = 0; z < 125; z++)
  {

    // for getting next button while current process is running
    curr = GPIO_readPin(PORTD_ID, 2);
    if (curr && !prev)
    {
      return;
    }
    prev = GPIO_readPin(PORTD_ID, 2);
    _delay_ms(2);

    // for getting previous button while current process is running
    curr2 = GPIO_readPin(PORTD_ID, 3);
    if (curr2 && !prev2)
    {
      goto start_label;
    }
    prev2 = GPIO_readPin(PORTD_ID, 3);
    _delay_ms(3);

    // for getting generate button while current process is running
    curr3 = GPIO_readPin(PORTD_ID, 6);
    if (curr3 != prev3)
    {
      return;
    }
    prev3 = GPIO_readPin(PORTD_ID, 6);
    _delay_ms(3);
  }
  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_LOW);

  currentDigit++;
  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_HIGH);
  SEVEN_SEG_Write(1, digits[currentDigit]);
  EEPROM_Write(0x03, currentDigit);
  buzzer_cycle = (float)digits[currentDigit] / 10 * 156.0;
  OCR1BL = 156 - (uint8)buzzer_cycle;
  for (z = 0; z < 125; z++)
  {

    // for getting next button while current process is running
    curr = GPIO_readPin(PORTD_ID, 2);
    if (curr && !prev)
    {
      return;
    }
    prev = GPIO_readPin(PORTD_ID, 2);
    _delay_ms(2);

    // for getting previous button while current process is running
    curr2 = GPIO_readPin(PORTD_ID, 3);
    if (curr2 && !prev2)
    {
      goto start_label;
    }
    prev2 = GPIO_readPin(PORTD_ID, 3);
    _delay_ms(3);

    // for getting generate button while current process is running
    curr3 = GPIO_readPin(PORTD_ID, 6);
    if (curr3 != prev3)
    {
      return;
    }
    prev3 = GPIO_readPin(PORTD_ID, 6);
    _delay_ms(3);
  }
  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_LOW);

  currentDigit++;
  GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_HIGH);
  SEVEN_SEG_Write(1, digits[currentDigit]);
  EEPROM_Write(0x03, currentDigit);
  buzzer_cycle = (float)digits[currentDigit] / 10 * 156.0;
  OCR1BL = 156 - (uint8)buzzer_cycle;
  for (z = 0; z < 125; z++)
  {

    // for getting next button while current process is running
    curr = GPIO_readPin(PORTD_ID, 2);
    if (curr && !prev)
    {
      return;
    }
    prev = GPIO_readPin(PORTD_ID, 2);
    _delay_ms(2);

    // for getting previous button while current process is running
    curr2 = GPIO_readPin(PORTD_ID, 3);
    if (curr2 && !prev2)
    {
      goto start_label;
    }
    prev2 = GPIO_readPin(PORTD_ID, 3);
    _delay_ms(3);

    // for getting generate button while current process is running
    curr3 = GPIO_readPin(PORTD_ID, 6);
    if (curr3 != prev3)
    {
      return;
    }
    prev3 = GPIO_readPin(PORTD_ID, 6);
    _delay_ms(3);
  }
  uint8 servo_angle = (currentNumber % 180) / 22 + 140;
  OCR1AL = servo_angle;
  buzzer_cycle = (float)currentNumber / 65535.0 * 156.0;
  OCR1BL = 156 - (uint8)buzzer_cycle;
}

// prev
ISR(PCINT2_vect)
{
  if (currentDigit != 0)
  {
    currentDigit--;
    EEPROM_Write(0x03, currentDigit);
    GPIO_writePin(digitsPorts[currentDigit + 1], digitsPins[currentDigit + 1], LOGIC_LOW);
    GPIO_writePin(digitsPorts[currentDigit], digitsPins[currentDigit], LOGIC_HIGH);
    SEVEN_SEG_Write(1, digits[currentDigit]);
  }
}

int main(void)
{

  Timer1_Configration timer1Config;
  timer1Config.Initial_Value = 0;
  timer1Config.Timer_Mode = Timer1_PWM_PHASE_FREQUENCY_CORRECT_Mode_ICR;
  timer1Config.Timer_Prescaller = TIMER1_PRESCALAR_CLK1024;
  timer1Config.ComA = TIMER1_SETA;
  timer1Config.ComB = TIMER1_SETB;
  timer1Config.ocrA = 8;
  timer1Config.ocrB = 78;
  timer1Config.icr = 156;

  TIMER1_init(&timer1Config);

  currentNumber = 0;
  digits[0] = EEPROM_Read(0x01);
  digits[1] = EEPROM_Read(0x02);
  digits[2] = EEPROM_Read(0x04);
  digits[3] = EEPROM_Read(0x05);
  digits[4] = EEPROM_Read(0x06);
  currentNumber = digits[0] + digits[1] * 10 + digits[2] * 100 + digits[3] * 1000 + digits[4] * 10000;
  uint8 servo_angle = (currentNumber % 180) / 22 + 140;
  OCR1AL = servo_angle;
  float buzzer_cycle = (float)currentNumber / 65535.0 * 156.0;
  OCR1BL = 156 - (uint8)buzzer_cycle;

  currentDigit = EEPROM_Read(0x03);

  GPIO_setupPinDirection(digit0_port, digit0_pin, PIN_OUTPUT);
  GPIO_setupPinDirection(digit1_port, digit1_pin, PIN_OUTPUT);
  GPIO_setupPinDirection(digit2_port, digit2_pin, PIN_OUTPUT);
  GPIO_setupPinDirection(digit3_port, digit3_pin, PIN_OUTPUT);
  GPIO_setupPinDirection(digit4_port, digit4_pin, PIN_OUTPUT);

  GPIO_setupPinDirection(servo_port, servo_pin, PIN_OUTPUT);
  GPIO_setupPinDirection(buzzer_port, buzzer_pin, PIN_OUTPUT);

  GPIO_setupPinDirection(next_port, next_pin, PIN_INPUT);
  GPIO_setupPinDirection(generate_port, generate_pin, PIN_INPUT);
  GPIO_setupPinDirection(previous_port, previous_pin, PIN_INPUT);

  SEVEN_SEG_Init(PORTC_ID);

  if (currentDigit == 0)
  {
    GPIO_writePin(digit0_port, digit0_pin, LOGIC_HIGH);
  }
  else
  {
    GPIO_writePin(digit0_port, digit0_pin, LOGIC_LOW);
  }

  if (currentDigit == 1)
  {
    GPIO_writePin(digit1_port, digit1_pin, LOGIC_HIGH);
  }
  else
  {
    GPIO_writePin(digit1_port, digit1_pin, LOGIC_LOW);
  }

  if (currentDigit == 2)
  {
    GPIO_writePin(digit2_port, digit2_pin, LOGIC_HIGH);
  }
  else
  {
    GPIO_writePin(digit2_port, digit2_pin, LOGIC_LOW);
  }

  if (currentDigit == 3)
  {
    GPIO_writePin(digit3_port, digit3_pin, LOGIC_HIGH);
  }
  else
  {
    GPIO_writePin(digit3_port, digit3_pin, LOGIC_LOW);
  }

  if (currentDigit == 4)
  {
    GPIO_writePin(digit4_port, digit4_pin, LOGIC_HIGH);
  }
  else
  {
    GPIO_writePin(digit4_port, digit4_pin, LOGIC_LOW);
  }

  SEVEN_SEG_Write(PORTC_ID, digits[currentDigit]);

  CLEAR_BIT(SREG, 7);
  EICRA = 0xff;
  EIMSK = 0xff;
  PCICR = 0xff;
  SET_BIT(PCMSK2, 6);
  SET_BIT(SREG, 7);

  UART_vInit();

  while (1)
  {
  }

  return 0;
}

/*******************************************************************************
 *                                End of HMI code                              *
 *******************************************************************************/

#else

/*******************************************************************************
 *                         Start of Randomizer code                            *
 *******************************************************************************/

uint8 digits[5] = {0, 0, 0, 0, 0};

#if rand_alg_type == 2
uint16 ADC_read()
{
  uint16 ADC_value = 0;
  SET_BIT(ADCSRA, 6);
  while (!READ_BIT(ADCSRA, 4))
    ;

  ADC_value = ADCH;
  ADC_value <<= 8;
  ADC_value |= ADCL;

  // if (ADCL == 0)
  //   GPIO_writePin(0, 5, LOGIC_LOW);
  // else
  //   GPIO_writePin(0, 5, LOGIC_HIGH);

  return ADC_value;
}

uint16 true_random_number_generator_using_adc()
{
  uint16 rand = 0;
  rand = ADC_read();
  rand *= 64;
  return rand;
}

#elif rand_alg_type == 3
uint16 randSeed = 1;

uint16 pseudo_random_number_generator()
{
  randSeed ^= randSeed << 7;
  randSeed ^= randSeed >> 9;
  randSeed ^= randSeed << 8;

  return randSeed;
}

#elif rand_alg_type == 1

uint16 true_random_number_generator_using_timer1()
{
  uint16 rand = 0;
  rand = TCNT1H;
  rand <<= 8;
  rand |= TCNT1L;
  return rand;
}

#endif

int main(void)
{

  UART_vInit();
  uint8 data = 0;
  uint16 number = 0;
  GPIO_setupPortDirection(PORTC_ID, PORT_OUTPUT);
  GPIO_writePort(PORTC_ID, 0x00);

  /*_______________For Using Timer 1 in Random Number generation___________________ */

  Timer1_Configration timer1Config;
  timer1Config.Initial_Value = 0;
  timer1Config.Timer_Mode = Timer1_Normal_Mode;
  timer1Config.Timer_Prescaller = TIMER1_PRESCALAR_CLK1024;
  timer1Config.ComA = TIMER1_NORMALA;
  timer1Config.ComB = TIMER1_NORMALB;
  TIMER1_init(&timer1Config);

  /*_________________________________________________________________________________*/

  /*_______________For Using ADC in Random Number generation________________________ */

  GPIO_setupPinDirection(PORTC_ID, PIN3_ID, PIN_INPUT);
  ADC_Configration adc_config;
  adc_config.adc_vref = AREF;
  adc_config.adc_channel = ADC3;
  adc_config.adc_prescaler = ADC_PRE_128;
  ADC_Init(&adc_config);

  /*_________________________________________________________________________________*/

  while (1)
  {
    while (UART_vReceive() != 0x23)
    {
      number++;
    }
#if rand_alg_type == 0
    number++;
#elif rand_alg_type == 1
    number = true_random_number_generator_using_timer1();
#elif rand_alg_type == 2
    number = true_random_number_generator_using_adc();
#else
    number = pseudo_random_number_generator();
#endif
    GPIO_writePin(PORTC_ID, PIN0_ID, LOGIC_HIGH);
    _delay_ms(1000);

    digits[0] = number / 10000;
    number %= 10000;
    digits[1] = number / 1000;
    number %= 1000;
    digits[2] = number / 100;
    number %= 100;
    digits[3] = number / 10;
    number %= 10;
    digits[4] = number;

    GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_HIGH);

    uint8 i = 0;
    for (i = 0; i < 5; i++)
    {
      UART_vTransmit(digits[i]);
      _delay_ms(50);
    }
    _delay_ms(1000);
    GPIO_writePin(PORTC_ID, PIN2_ID, LOGIC_HIGH);
    _delay_ms(1000);
    GPIO_writePort(PORTC_ID, 0x00);

    number++;
  }

  return 0;
}

/*******************************************************************************
 *                           End of Randomizer code                            *
 *******************************************************************************/

/*******************************************************************************
 *                for adc test in different simulide versions                  *
 *******************************************************************************/

// int main(void)
// {

//   GPIO_setupPinDirection(0, 5, PIN_OUTPUT);

//   uint16 number = 0;

//    /*_______________For Using ADC in Random Number generation________________________ */

//   GPIO_setupPinDirection(PORTC_ID, PIN3_ID, PIN_INPUT);
//   ADC_Configration adc_config;
//   adc_config.adc_vref = AREF;
//   adc_config.adc_channel = ADC3;
//   adc_config.adc_prescaler = ADC_PRE_128;
//   ADC_Init(&adc_config);

//    /*_________________________________________________________________________________*/

//   while (1)
//   {
//     number = ADC_read();
//   }

//   return 0;
// }

/*______________________________________________________________________________________*/

#endif
