/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe InterruptButton fournit des méthodes pour gérer les interruptions externes déclenchées par un bouton-poussoir. Connecté à un PIN au choix sur le PORTD.
*/

#ifndef INTERRUPT_BUTTON_H
#define INTERRUPT_BUTTON_H

#include <avr/io.h>

enum class InterruptChannel {
    CHANNEL_A, // PD2
    CHANNEL_B // PB2
};

class InterruptButton {
public:
    void configure(InterruptChannel interruptChannel);
    void configureRisingEdge(InterruptChannel interruptChannel);
    void configureFallingEdge(InterruptChannel interruptChannel);
    void configureAnyEdge(InterruptChannel interruptChannel);
    void enableInterrupt(InterruptChannel interruptChannel);
    void disableInterrupt(InterruptChannel interruptChannel);
    void resetInterruptSettings(InterruptChannel interruptChannel);
};

#endif
