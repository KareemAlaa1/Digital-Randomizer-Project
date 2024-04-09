#ifndef GPIO_REG_H_
#define GPIO_REG_H_

#define PINB (*(volatile unsigned char*)0x23)
#define DDRB (*(volatile unsigned char*)0x24)
#define PORTB (*(volatile unsigned char*)0x25)


#define PINC (*(volatile unsigned char*)0x26)
#define DDRC (*(volatile unsigned char*)0x27)
#define PORTC (*(volatile unsigned char*)0x28)


#define PIND (*(volatile unsigned char*)0x29)
#define DDRD (*(volatile unsigned char*)0x2A)
#define PORTD (*(volatile unsigned char*)0x2B)

#endif /* GPIO_REG_H_ */