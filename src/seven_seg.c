
#include "../HAL/SEVEN_SEG/seven_seg.h"
#include "../MCAL/GPIO/gpio.h"

/*
 * Description :
 * Initialize SEVEN SEGMENT at given port
 */
void SEVEN_SEG_Init(uint8 port)
{
  GPIO_setupPortDirection(port, PORT_OUTPUT);
  GPIO_setupPinDirection(0, 0, PIN_OUTPUT);
}

/*
 * Description :
 * Display given digit on SEVEN SEGMENT
 */
uint8 SEVEN_SEG_Write(uint8 port, uint8 number)
{
  const uint8 arr[] = {0b10111111, 0b00000110, 0b11011011, 0b11001111, 0b01100110, 0b11101101, 0b11111101, 0b10000111, 0b11111111, 0b11101111};
  GPIO_writePort(port, arr[number]);
  if (((arr[number] >> 6) & 0b00000001))
  {
    GPIO_writePin(0, 0, LOGIC_HIGH);
  }
  else
  {
    GPIO_writePin(0, 0, LOGIC_LOW);
  }
}