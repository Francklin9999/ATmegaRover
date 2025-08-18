/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe Sound permet de jouer et d’arrêter des tonalités sonores en gérant différents canaux audio.
 */

#ifndef SOUND_H
#define SOUND_H


#include <avr/io.h>


enum class SoundChannel {
    CHANNEL_A, 
    CHANNEL_B 
};

class Sound {
public:
    Sound();

    void playTone(double freq);
    void stopTone();
};

#endif