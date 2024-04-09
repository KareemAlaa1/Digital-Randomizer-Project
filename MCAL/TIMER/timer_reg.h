#ifndef TIMER_REG_H_
#define TIMER_REG_H_

// Timer0 registers
#define TCCR0A (*(volatile unsigned char *)0x44)
#define TCCR0B (*(volatile unsigned char *)0x45)
#define TCNT0 (*(volatile unsigned char *)0x46)
#define OCR0A (*(volatile unsigned char *)0x47)
#define OCR0B (*(volatile unsigned char *)0x48)
#define TIMSK0 (*(volatile unsigned char *)0x6E)
#define TIFR0 (*(volatile unsigned char *)0x35)
#define SREG (*(volatile unsigned char *)0x5F)

// Timer1 registers
#define TCCR1A (*(volatile unsigned char *)0x80)
#define TCCR1B (*(volatile unsigned char *)0x81)
#define TCCR1C (*(volatile unsigned char *)0x82)

#define TCNT1H (*(volatile unsigned char *)0x85)
#define TCNT1L (*(volatile unsigned char *)0x84)

#define OCR1AH (*(volatile unsigned char *)0x89)
#define OCR1AL (*(volatile unsigned char *)0x88)

#define OCR1BH (*(volatile unsigned char *)0x8B)
#define OCR1BL (*(volatile unsigned char *)0x8A)

#define ICR1H (*(volatile unsigned char *)0x87)
#define ICR1L (*(volatile unsigned char *)0x86)

#define TIMSK1 (*(volatile unsigned char *)0x6F)
#define TIFR1 (*(volatile unsigned char *)0x36)

// Timer2 registers
#define TCCR2A (*(volatile unsigned char *)0xB0)
#define TCCR2B (*(volatile unsigned char *)0xB1)
#define TCNT2 (*(volatile unsigned char *)0xB2)
#define OCR2A (*(volatile unsigned char *)0xB3)
#define OCR2B (*(volatile unsigned char *)0xB4)
#define TIMSK2 (*(volatile unsigned char *)0x70)
#define TIFR2 (*(volatile unsigned char *)0x37)

#endif /* TIMER_REG_H_ */