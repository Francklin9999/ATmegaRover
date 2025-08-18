/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe LineFollower implémente la logique de suivi de ligne pour un robot en exploitant les lectures de capteurs et l’ajustement des vitesses des roues.
 */

#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <avr/io.h>
#include "../CAN_MANAGER/canManager.h"
#include "../WHEELS/wheels.h"

class LineFollower {
public:    
    LineFollower(const LineFollower&) = delete;
    LineFollower& operator=(const LineFollower&) = delete;

    static LineFollower& getInstance() {
        return lineFollowerInstance;
    }

    LineFollower() : _canManager(CanManager::getInstance()), _wheels(Wheels::getInstance()) { }


    void followLine();
    uint8_t getLeftValue();
    uint8_t getRightValue();
    void setDirection(bool backward);
    void setCurrentError(uint8_t value);

    int16_t previousError = 0;
    int16_t currentError = 0;
    bool _goingBackward = false;

    uint8_t direction = 0;

private:
    static LineFollower lineFollowerInstance;

    CanManager& _canManager;
    Wheels& _wheels;

    void setPreviousError();
    uint8_t readValue();
    void calculateCorrection();
    void calculateCorrectionRight();
    void calculateCorrectionLeft();
    void ajustWheelsSpeed();

    int16_t _integral = 0;

    int16_t _leftSpeed = 0;
    int16_t _rightSpeed = 0;

    float _kp = 1.0;
    float _ki = 0.0;
    float _kd = 0.5;
};

#endif
