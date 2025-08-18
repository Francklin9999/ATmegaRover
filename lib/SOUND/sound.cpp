#define F_CPU 8000000UL
#include "sound.h"

Sound::Sound() {
    DDRB |= (1 << PB3) | (1 << PB5);

    PORTB |= (1 << PB3);
    
    PORTB |= (1 << PB5);
}

void Sound::playTone(double freq) {
    uint32_t compareValue = (F_CPU / (2.0 * 256 * freq)) - 1;
    TCNT0 = 0;
    
    OCR0A = compareValue;

    TCCR0A |= (1 << COM0A0);  
    TCCR0A |= (1 << WGM01);   
    TCCR0B |= (1 << CS02);    
}

void Sound::stopTone() {
    PORTB &= ~(1 << PB3);  
    TCCR0A &= ~(1 << COM0A0);  
}

