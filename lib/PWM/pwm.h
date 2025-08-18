/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe Pwm fournit des méthodes pour générer des signaux PWM (Pulse Width Modulation) sur les broches du microcontrôleur. Elle permet de contrôler la largeur d'impulsion sur deux canaux (A et B) connectés aux broches PORTD6 et PORTD7. Cette classe bloque l’utilisation du timer 2.
*/

#ifndef PWM_H
#define PWM_H


#include <avr/io.h>


enum class PwmChannel {
    CHANNEL_A, // PWM sur PORTD6
    CHANNEL_B // PWM sur PORTD7
};

class Pwm {
private:
    uint8_t pwmChannelA = 0;
    uint8_t pwmChannelB = 0;

    void applyPwmSettings();

public:
    Pwm();

    void setPwmValue(PwmChannel channel, uint8_t value);
    void setPwmValues(uint8_t valueA, uint8_t valueB);
    void setPwmValues(uint8_t value);
};

#endif