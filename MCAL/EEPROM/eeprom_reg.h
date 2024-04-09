#ifndef EEPROM_REG_H_
#define EEPROM_REG_H_

#define EEARH (*(volatile unsigned char*)0x42)
#define EEARL (*(volatile unsigned char*)0x41)
#define EEDR (*(volatile unsigned char*)0x40)
#define EECR (*(volatile unsigned char*)0x3F)

#endif 