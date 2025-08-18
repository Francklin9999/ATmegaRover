#include "canManager.h"

CanManager CanManager::instance;

uint8_t CanManager::readLineFollower() {
    uint16_t lecture = _can.lecture(_lineFollowerPin);
    return lecture >> _BIT_SHIFT_DEUX;
}

uint16_t CanManager::readIRSensor() {
    uint16_t lecture = _can.lecture(_irSensorPin);
    return lecture;
}