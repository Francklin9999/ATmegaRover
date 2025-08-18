#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "lineFollower.h"

LineFollower LineFollower::lineFollowerInstance;

void LineFollower::followLine() {
    uint8_t value = readValue();
    setCurrentError(value);
    switch (direction) {
    case 0:
        calculateCorrection();
        break;
    case 1:
        calculateCorrectionRight();
        break;
    case 2:
        calculateCorrectionLeft();
        break;
    default:
        break;
    }
    ajustWheelsSpeed();
    setPreviousError();
}

uint8_t LineFollower::readValue() {
    uint8_t lecture = _canManager.readLineFollower();
    return lecture;
}

void LineFollower::setPreviousError() {
    previousError = currentError;
}

void LineFollower::calculateCorrection() {
    int16_t derivative = currentError - previousError;
    _integral += currentError;

    int16_t pid = _kp * currentError + _ki * _integral + _kd * derivative;

    int16_t baseLeft = _wheels.defaultLeftSpeed;
    int16_t baseRight = _wheels.defaultRightSpeed;

    _leftSpeed = baseLeft - pid * 0.6;
    _rightSpeed = baseRight + pid * 0.6;

    _leftSpeed = (_leftSpeed > 255) ? 255 : (_leftSpeed < 0 ? 0 : _leftSpeed);
    _rightSpeed = (_rightSpeed > 255) ? 255 : (_rightSpeed < 0 ? 0 : _rightSpeed);
}

void LineFollower::calculateCorrectionRight() {
    int16_t derivative = currentError - previousError;
    _integral += currentError;

    int16_t pid = _kp * currentError + _ki * _integral + _kd * derivative;

    int16_t baseLeft = _wheels.defaultLeftSpeed;
    int16_t baseRight = _wheels.defaultRightSpeed;

    _leftSpeed = baseLeft - pid * 0.5;
    _rightSpeed = baseRight + pid * 0.6;

    _leftSpeed = (_leftSpeed > 255) ? 255 : (_leftSpeed < 0 ? 0 : _leftSpeed);
    _rightSpeed = (_rightSpeed > 255) ? 255 : (_rightSpeed < 0 ? 0 : _rightSpeed);
}

void LineFollower::calculateCorrectionLeft() {
    int16_t derivative = currentError - previousError;
    _integral += currentError;

    int16_t pid = _kp * currentError + _ki * _integral + _kd * derivative;

    int16_t baseLeft = _wheels.defaultLeftSpeed;
    int16_t baseRight = _wheels.defaultRightSpeed;

    _leftSpeed = baseLeft - pid * 0.6;
    _rightSpeed = baseRight + pid * 0.5;

    _leftSpeed = (_leftSpeed > 255) ? 255 : (_leftSpeed < 0 ? 0 : _leftSpeed);
    _rightSpeed = (_rightSpeed > 255) ? 255 : (_rightSpeed < 0 ? 0 : _rightSpeed);
}

void LineFollower::ajustWheelsSpeed() {
    _wheels.setDirection(_goingBackward ? Direction::BACKWARD : Direction::FORWARD);
    _wheels.setSpeed(_leftSpeed, _rightSpeed);
    _wheels.update();
    _delay_ms(15);
}


uint8_t LineFollower::getLeftValue() {
    return _leftSpeed;
}

uint8_t LineFollower::getRightValue() {
    return _rightSpeed;
}

void LineFollower::setDirection(bool backward) {
    _goingBackward = backward;
}

void LineFollower::setCurrentError(uint8_t value) {
    currentError = value - 127;

    if (_goingBackward) {
        currentError = -currentError;
    }
}
