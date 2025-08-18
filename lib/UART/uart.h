/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe UART gère la communication série asynchrone via l'USART0 du microcontrôleur. Elle permet d'envoyer et recevoir des données via le port série.
*/

#ifndef UART_HPP
#define UART_HPP
#define F_CPU 8000000UL
#include <stdint.h>
#include "util/delay.h"

class Uart{
public:
    void initialization(void);
    void transmitUint8(uint8_t data);
    uint8_t recieveUint8();
    void transmitUint16(uint16_t integer);
    void transmitString(const char str[]);
};

#endif