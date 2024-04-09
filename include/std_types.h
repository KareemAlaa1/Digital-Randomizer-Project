#ifndef std_types
#define std_types

typedef unsigned char uint8;
typedef unsigned int uint16;

typedef long long ullint64;
#define NULL 0

#define LOGIC_HIGH (1u)
#define LOGIC_LOW (0u)

// external interrups registers
#define EICRA (*(volatile unsigned char *)0x69)
#define EIMSK (*(volatile unsigned char *)0x3D)
#define EIFR (*(volatile unsigned char *)0x3D)
#define PCICR (*(volatile unsigned char *)0x68)
#define PCIFR (*(volatile unsigned char *)0x3B)
#define PCMSK2 (*(volatile unsigned char *)0x6D)
#define PCMSK1 (*(volatile unsigned char *)0x6C)
#define PCMSK0 (*(volatile unsigned char *)0x6B)

#endif
