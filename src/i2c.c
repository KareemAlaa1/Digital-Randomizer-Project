#include "../MCAL/I2C/i2c.h"

void I2C_Init()
{
    TWBR = 0x50;
    SET_BIT(TWCR, TWEN);
}

uint8 I2C_Start(uint8 write_address)
{
    uint8 status;
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    status = TWSR & 0xF8;
    if (status != 0x08)
        return 0;
    TWDR = write_address;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    status = TWSR & 0xF8;
    if (status == 0x18)
        return 1;
    if (status == 0x20)
        return 2;
    else
        return 3;
}

uint8 I2C_Repeated_Start(uint8 read_address)
{
    uint8 status;
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    status = TWSR & 0xF8;
    if (status != 0x10)
        return 0;
    TWDR = read_address;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    status = TWSR & 0xF8;
    if (status == 0x40)
        return 1;
    if (status == 0x48)
        return 2;
    else
        return 3;
}

uint8 I2C_Write(uint8 data)
{
    uint8 status;
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    status = TWSR & 0xF8;
    if (status == 0x28)
        return 0;
    if (status == 0x30)
        return 1;
    else
        return 2;
}

uint8 I2C_Read_Ack()
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}

uint8 I2C_Read_Nack()
{
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}

void I2C_Stop()
{
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
    while (TWCR & (1 << TWSTO))
        ;
}

void I2C_Slave_Init(uint8 slave_address)
{
    TWAR = slave_address;
    TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
}

uint8 I2C_Slave_Listen()
{
    while (1)
    {
        uint8 status;
        while (!(TWCR & (1 << TWINT)))
            ;
        status = TWSR & 0xF8;
        if (status == 0x60 || status == 0x68)
            return 0;
        if (status == 0xA8 || status == 0xB0)
            return 1;
        if (status == 0x70 || status == 0x78)
            return 2;
        else
            continue;
    }
}

uint8 I2C_Slave_Transmit(uint8 data)
{
    uint8 status;
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)))
        ;
    status = TWSR & 0xF8;
    if (status == 0xA0)
    {
        TWCR |= (1 << TWINT);
        return -1;
    }
    if (status == 0xB8)
        return 0;
    if (status == 0xC0)
    {
        TWCR |= (1 << TWINT);
        return -2;
    }
    if (status == 0xC8)
        return -3;
    else
        return -4;
}

uint8 I2C_Slave_Receive()
{
    uint8 status;
    TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    status = TWSR & 0xF8;
    if (status == 0x80 || status == 0x90)
        return TWDR;

    if (status == 0x88 || status == 0x98)
        return TWDR;
    if (status == 0xA0)
    {
        TWCR |= (1 << TWINT);
        return -1;
    }
    else
        return -2;
}