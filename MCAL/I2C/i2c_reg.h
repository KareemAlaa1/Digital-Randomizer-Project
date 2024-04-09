#ifndef I2C_REG_H_
#define I2C_REG_H_


#define TWBR (*(volatile unsigned char*)0xB8)
#define TWCR (*(volatile unsigned char*)0xBC)
#define TWSR (*(volatile unsigned char*)0xB9)
#define TWDR (*(volatile unsigned char*)0xBB)
#define TWAR (*(volatile unsigned char*)0xBA)
#define TWAMR (*(volatile unsigned char*)0xBD)



#endif