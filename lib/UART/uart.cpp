#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include <string.h>

void Uart::initialization(void) 
{
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0
    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C &= ~(1 << USBS0);
}

// Du USART vers le PC
void Uart::transmitUint8(uint8_t data) 
{
    while (!(UCSR0A & (1 << UDRE0)))
    ;
    UDR0 = data;
}

uint8_t Uart::recieveUint8()
{
    while (!(UCSR0A & (1 << RXC0)))
    ;
    return UDR0;
}

void Uart::transmitUint16(uint16_t integer) {
    char buffer[6];
    sprintf(buffer, "%u", integer);

    for (uint8_t i = 0; buffer[i] != '\0'; ++i) {
        transmitUint8(buffer[i]);
    }

    transmitUint8(' ');
    _delay_ms(50);
}


void Uart::transmitString(const char str[]) {
    int stringLength = strlen(str);
    for(uint8_t i = 0; i < stringLength; i++){
        transmitUint8(str[i]);
    }
    _delay_ms(50);
}
