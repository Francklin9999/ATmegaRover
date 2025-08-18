/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe CanManager gère la communication sur le bus CAN et fournit des méthodes pour lire les capteurs de suivi de ligne et IR.
 */

#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H

#include <avr/io.h>
#include "../CAN/can.h"

class CanManager {
public:
    static CanManager& getInstance() {
        return instance;
    }

    CanManager(const CanManager&) = delete;
    CanManager& operator=(const CanManager&) = delete;

    uint8_t readLineFollower();
    uint16_t readIRSensor();

    void setPins(uint8_t lineFollowerPin, uint8_t irSensorPin) {
        _lineFollowerPin = lineFollowerPin;
        _irSensorPin = irSensorPin;
    }

private:
    static CanManager instance;

    CanManager() { }
    
    can _can;
    uint8_t _lineFollowerPin = PA1;  
    uint8_t _irSensorPin = PA0;   
    
    static constexpr uint8_t _BIT_SHIFT_DEUX = 2;
};

#endif