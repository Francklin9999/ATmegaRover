#include <avr/interrupt.h>
#include "timer.h"
#include "../UART/uart.h"

volatile bool timerCompleted = true;

void Timer::start(uint16_t duration) {

    cli();
    Uart uart;
    uart.initialization();


    if (!timerCompleted) {
        uart.transmitString("Timer completed");
        return;
    }

    TCNT1 = 0;
    OCR1A = static_cast<uint16_t>(duration * TICKS_PER_TENTH_SECOND); 

    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12); 
    TCCR1C = 0;

    TIMSK1 = (1 << OCIE1A); 

    timerCompleted = false;
    hasBeenChecked = false;

    sei();
}

bool Timer::isFinished() {
    return timerCompleted;
}

bool Timer::wasChecked() {
    if (timerCompleted && !hasBeenChecked) {
        hasBeenChecked = true;
        return false;
    }
    return hasBeenChecked;
}

ISR(TIMER1_COMPA_vect) {
    timerCompleted = true;
}
