/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe LineDetector fournit des méthodes pour lire et pour interpréter les données lues par le capteur de lignes. 
 * Connecté à des PINs au choix sur le PORTC.
*/

#ifndef LINE_DETECTOR_H
#define LINE_DETECTOR_H

#include <avr/io.h>

class LineDetector {
public:
    LineDetector(const LineDetector&) = delete;
    LineDetector& operator=(const LineDetector&) = delete;
    
    static LineDetector& getInstance() {
        return lineDetectorInstance;
    }

    LineDetector() {
        _leftMost = PC3;
        _leftMiddle = PC4;
        _middle = PC5;
        _rightMiddle = PC6;
        _rightMost = PC7;
    
        PORTC &= ~((1 << _leftMost) | (1 << _leftMiddle) | (1 << _middle) | (1 << _rightMiddle) | (1 << _rightMost));
    }

    uint8_t readValue();
    bool isMiddleOnLine();
    bool isMiddleNotOnLine();
    bool isRightOnLine();
    bool isLeftOnLine();
    bool isRightNotOnLine();
    bool isLeftNotOnLine();
    bool isNoneOnLine();
    bool isOneOnLine();

private:
    static LineDetector lineDetectorInstance;

    uint8_t _leftMost, _leftMiddle, _middle, _rightMiddle, _rightMost;
    uint8_t _firstPin;
};

#endif
