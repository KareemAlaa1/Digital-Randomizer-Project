#ifndef SPI_REG_H_
#define SPI_REG_H_

#define SPDR (*(volatile unsigned char *)0x4E)
#define SPSR (*(volatile unsigned char *)0x4D)
#define SPCR (*(volatile unsigned char *)0x4C)

#endif