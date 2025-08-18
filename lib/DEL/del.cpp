#define F_CPU 8000000UL
#include "del.h"
#include <util/delay.h>

DEL::DEL(Register& dataRegister, Register& directionRegister, uint8_t greenPin, uint8_t redPin)
    : _dataRegister(dataRegister), _directionRegister(directionRegister), _greenPin(greenPin), _redPin(redPin) {
    _directionRegister |= (1 << greenPin) | (1 << redPin); 
}

void DEL::turnOff() {
    _dataRegister &= ~((1 << _greenPin) | (1 << _redPin));
}

void DEL::turnOn(uint8_t pin) {
    turnOff();
    _dataRegister |= (1 << pin);
}

void DEL::setMode(DELMode mode) {
    switch (mode) {
        case DELMode::OFF:
            turnOff();
            break;
        case DELMode::RED:
            turnOn(_redPin);
            break;
        case DELMode::GREEN:
            turnOn(_greenPin);
            break;
        case DELMode::AMBER:
            turnOn(_greenPin);
            _delay_ms(AMBER_DELAY_MS);
            turnOn(_redPin);
            _delay_ms(AMBER_DELAY_MS);
            break;
    }
}