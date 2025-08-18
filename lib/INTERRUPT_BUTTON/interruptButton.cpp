#include <avr/io.h>
#include <avr/interrupt.h>
#include "interruptButton.h"


void InterruptButton::configure(InterruptChannel interruptChannel) {
    if (interruptChannel == InterruptChannel::CHANNEL_A) {
        DDRD &= ~(1 << PD2);
    } else if (interruptChannel == InterruptChannel::CHANNEL_B) {
        DDRB &= ~(1 << PB2);
    }
}

void InterruptButton::configureRisingEdge(InterruptChannel interruptChannel) {
    resetInterruptSettings(interruptChannel);
    if (interruptChannel == InterruptChannel::CHANNEL_A) {
        EICRA |= (1 << ISC00) | (1 << ISC01);
    } else if (interruptChannel == InterruptChannel::CHANNEL_B) {
        EICRA |= (1 << ISC20) | (1 << ISC21);
    }
}

void InterruptButton::configureFallingEdge(InterruptChannel interruptChannel) {
    resetInterruptSettings(interruptChannel);
    if (interruptChannel == InterruptChannel::CHANNEL_A) {
        EICRA |= (1 << ISC01);
    } else if (interruptChannel == InterruptChannel::CHANNEL_B) {
        EICRA |= (1 << ISC21);
    }
}

void InterruptButton::configureAnyEdge(InterruptChannel interruptChannel) {
    resetInterruptSettings(interruptChannel);
    if (interruptChannel == InterruptChannel::CHANNEL_A) {
        EICRA |= (1 << ISC00);
    } else if (interruptChannel == InterruptChannel::CHANNEL_B) {
        EICRA |= (1 << ISC20);
    }
}

void InterruptButton::enableInterrupt(InterruptChannel interruptChannel) {
    if (interruptChannel == InterruptChannel::CHANNEL_A) {
        EIMSK |= (1 << INT0);
    } else if (interruptChannel == InterruptChannel::CHANNEL_B) {
        EIMSK |= (1 << INT2);
    }
    sei();
}

void InterruptButton::disableInterrupt(InterruptChannel interruptChannel) {
    cli();
    if (interruptChannel == InterruptChannel::CHANNEL_A) {
        EIMSK &= ~(1 << INT0);
    } else if (interruptChannel == InterruptChannel::CHANNEL_B) {
        EIMSK &= ~(1 << INT2);
    }
}

void InterruptButton::resetInterruptSettings(InterruptChannel interruptChannel) {
    if (interruptChannel == InterruptChannel::CHANNEL_A) {
        EICRA &= ~(1 << ISC00);
        EICRA &= ~(1 << ISC01);
    } else if (interruptChannel == InterruptChannel::CHANNEL_B) {
        EICRA &= ~(1 << ISC20);
        EICRA &= ~(1 << ISC21);
    }
}
 