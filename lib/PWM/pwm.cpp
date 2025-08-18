#define F_CPU 8000000UL
#include "pwm.h"

Pwm::Pwm() {
    DDRD |= (1 << PD6) | (1 << PD7);
}

void Pwm::applyPwmSettings() {
    TCNT2 = 0;
    
    OCR2A = pwmChannelA;
    OCR2B = pwmChannelB;

    TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
    TCCR2B |= (1 << CS21);    
}

void Pwm::setPwmValue(PwmChannel channel, uint8_t value) {
    if (channel == PwmChannel::CHANNEL_A) {
        pwmChannelA = value;
    } else {
        pwmChannelB = value;
    }

    applyPwmSettings();
}

void Pwm::setPwmValues(uint8_t valueA, uint8_t valueB) {
    pwmChannelA = valueA;
    pwmChannelB = valueB;
    applyPwmSettings();
}

void Pwm::setPwmValues(uint8_t value) {
    pwmChannelA = value;
    pwmChannelB = value;
    applyPwmSettings();
}