 
 #include "../MCAL/GPIO/gpio.h"

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction){
    if(port_num > NUM_OF_PORTS){

    }
    else{
        if(port_num==0 && pin_num >NUM_OF_PINS_PER_PORTB){

        }else if(port_num==1 && pin_num >NUM_OF_PINS_PER_PORTC){

        }else if(port_num==2 && pin_num >NUM_OF_PINS_PER_PORTD){

        }else{
            switch (port_num)
            {
            case 0:
                if(direction == PIN_INPUT){
                    CLEAR_BIT(DDRB,pin_num);
                }else{
                    SET_BIT(DDRB,pin_num);
                }
                break;
            case 1:
                if(direction == PIN_INPUT){
                    CLEAR_BIT(DDRC,pin_num);
                }else{
                    SET_BIT(DDRC,pin_num);
                }
                break;
            case 2:
                if(direction == PIN_INPUT){
                    CLEAR_BIT(DDRD,pin_num);
                }else{
                    SET_BIT(DDRD,pin_num);
                }
            }
        }
    }


}



/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value){
    if(port_num > NUM_OF_PORTS){

    }
    else{
        if(port_num==0 && pin_num >NUM_OF_PINS_PER_PORTB){

        }else if(port_num==1 && pin_num >NUM_OF_PINS_PER_PORTC){

        }else if(port_num==2 && pin_num >NUM_OF_PINS_PER_PORTD){

        }else{
            switch (port_num)
            {
            case 0:
                if(value == LOGIC_LOW){
                    CLEAR_BIT(PORTB,pin_num);
                }else{
                    SET_BIT(PORTB,pin_num);
                }
                break;
            case 1:
                if(value == LOGIC_LOW){
                    CLEAR_BIT(PORTC,pin_num);
                }else{
                    SET_BIT(PORTC,pin_num);
                }
                break;
            case 2:
                if(value == LOGIC_LOW){
                    CLEAR_BIT(PORTD,pin_num);
                }else{
                    SET_BIT(PORTD,pin_num);
                }
            }
        }
    }
}



/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num){
    uint8 pin_value=0;
     if(port_num > NUM_OF_PORTS){

    }
    else{
        if(port_num==0 && pin_num >NUM_OF_PINS_PER_PORTB){

        }else if(port_num==1 && pin_num >NUM_OF_PINS_PER_PORTC){

        }else if(port_num==2 && pin_num >NUM_OF_PINS_PER_PORTD){

        }else{
            switch (port_num)
            {
            case 0:
                if(READ_BIT(PINB,pin_num)==LOGIC_HIGH){
                    pin_value=1;
                }else{
                    pin_value=0;
                }
                break;
            case 1:
                 if(READ_BIT(PINC,pin_num)==LOGIC_HIGH){
                    pin_value=1;
                }else{
                    pin_value=0;
                }
                break;
            case 2:
                if(READ_BIT(PIND,pin_num)==LOGIC_HIGH){
                    pin_value=1;
                }else{
                    pin_value=0;
                }
            }
        }
    }   
    return pin_value; 
}


/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, uint8 direction){
    if(port_num > NUM_OF_PORTS){

    }
    else{
       
            switch (port_num)
            {
            case 0:
                DDRB=direction;
                break;
            case 1:
                DDRC=direction;
                break;
            case 2:
                DDRD=direction;
            }
    }    
}


/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value){
     if(port_num > NUM_OF_PORTS){

    }
    else{
       
            switch (port_num)
            {
            case 0:
                PORTB=value;
                break;
            case 1:
                PORTC=value;
                break;
            case 2:
                PORTD=value;
            }
    }    
}


/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num){
    uint8 port_value=0;
     if(port_num > NUM_OF_PORTS){

    }
    else{
       
            switch (port_num)
            {
            case 0:
                port_value=PINB;
                break;
            case 1:
                port_value=PINC;
                break;
            case 2:
                port_value=PIND;
            }
    }  
    return port_value;  
}