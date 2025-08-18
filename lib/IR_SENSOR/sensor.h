/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe Sensor fournit les méthodes pour lire et pour interpréter les données lues par le capteur infrarouge. 
 * Connecté à un PIN au choix sur le PORTA.
*/

#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <avr/io.h>
#include "../CAN_MANAGER/canManager.h"

class Sensor {
public:
    Sensor(uint8_t portPin) : _portPin(portPin), _canManager(CanManager::getInstance()) {
        DDRA &= ~(1 << _portPin);
    }

    uint16_t readValue();
    bool isHouseObstacleDetected();
    bool isGridObstacleDetected();

private:
    uint8_t _portPin;
    CanManager& _canManager;
    
    static constexpr uint16_t _maxHouseReferenceDistance = 1023;
    static constexpr uint16_t _minHouseReferenceDistance = 200;
    static constexpr uint16_t _maxGridReferenceDistance = 1023;
    static constexpr uint16_t _minGridReferenceDistance = 150;
};

#endif
