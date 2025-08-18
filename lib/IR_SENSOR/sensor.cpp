#include "sensor.h"

uint16_t Sensor::readValue() {
    return _canManager.readIRSensor();
}

bool Sensor::isHouseObstacleDetected() {
    uint16_t valueRead = readValue();
    return (valueRead <= _maxHouseReferenceDistance && valueRead >= _minHouseReferenceDistance);
}

bool Sensor::isGridObstacleDetected() {
    uint16_t valueRead = readValue();
    return (valueRead <= _maxGridReferenceDistance && valueRead >= _minGridReferenceDistance);
}
