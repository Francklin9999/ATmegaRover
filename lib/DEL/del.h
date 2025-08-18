/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe DEL fournit des méthodes pour contrôler une DEL bicolore (rouge et verte) sur le robot. Elle permet d’allumer la DEL en vert, rouge ou ambre (alterne entre vert et rouge).
*/

#ifndef DEL_H
#define DEL_H

#include <avr/io.h>
#include <stdint.h>

using Register = volatile uint8_t&;

enum class DELMode { OFF, RED, GREEN, AMBER };

class DEL {
public:
    DEL(Register& dataRegister, Register& directionRegister, uint8_t greenPin, uint8_t redPin);

    void setMode(DELMode mode);

private:
    void turnOff();
    void turnOn(uint8_t pin);

    Register _dataRegister;
    Register _directionRegister;
    uint8_t _greenPin;
    uint8_t _redPin;
    static constexpr uint8_t AMBER_DELAY_MS = 10;
};

#endif
