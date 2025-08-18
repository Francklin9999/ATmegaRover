/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe Timer fournit des méthodes pour gérer un timer. Cette classe bloque l’utilisation du timer 1.
*/


#ifndef TIMER_H
#define TIMER_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

class Timer {
private:
    constexpr static float TICKS_PER_TENTH_SECOND = 780;
    bool hasBeenChecked = false;
public:
    void start(uint16_t duration);
    bool isFinished();
    bool wasChecked();
};

#endif
