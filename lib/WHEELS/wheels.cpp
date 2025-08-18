#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "util/delay.h"

#include "wheels.h"

Wheels Wheels::wheelsInstance;

void Wheels::update() {
    pwm.setPwmValues(this->speedLeft, this->speedRight);

    switch (this->direction) {
        case Direction::FORWARD:
            this->setWheel(Wheel::LEFT, Direction::FORWARD);
            this->setWheel(Wheel::RIGHT, Direction::FORWARD);
            break;
        case Direction::BACKWARD:
            this->setWheel(Wheel::LEFT, Direction::BACKWARD);
            this->setWheel(Wheel::RIGHT, Direction::BACKWARD);
            break;
        case Direction::LEFT:
            this->setWheel(Wheel::LEFT, Direction::STOP);
            this->setWheel(Wheel::RIGHT, Direction::FORWARD);
            break;
        case Direction::RIGHT:
            this->setWheel(Wheel::LEFT, Direction::FORWARD);
            this->setWheel(Wheel::RIGHT, Direction::STOP);
            break;
        case Direction::ONLY_LEFT:
            this->setWheel(Wheel::LEFT, Direction::BACKWARD);
            this->setWheel(Wheel::RIGHT, Direction::FORWARD);
            break;
        case Direction::ONLY_RIGHT:
            this->setWheel(Wheel::LEFT, Direction::FORWARD);
            this->setWheel(Wheel::RIGHT, Direction::BACKWARD);
            break;
        case Direction::STOP:
            this->setWheel(Wheel::LEFT, Direction::STOP);
            this->setWheel(Wheel::RIGHT, Direction::STOP);
            break;
    }
}

void Wheels::setDirection(Direction direction) {
    this->direction = direction;
}

void Wheels::setSpeed(uint8_t speed) {
    this->speedLeft = speed;
    this->speedRight = speed;
}

void Wheels::setSpeed(uint8_t speedLeft, uint8_t speedRight) {
    this->speedLeft = speedLeft;
    this->speedRight = speedRight;
}

void Wheels::setSpeedLeft(uint8_t speedLeft) {
    this->speedLeft = speedLeft;
}

void Wheels::setSpeedRight(uint8_t speedRight) {
    this->speedRight = speedRight;
}

Direction Wheels::getDirection() const { 
    return this->direction; 
}

void Wheels::setWheel(Wheel wheel, Direction direction) {
    switch (wheel) {
        case Wheel::LEFT:
            if (direction == Direction::FORWARD) {
                PORTD &= ~(1 << PD4);
            } else if (direction == Direction::STOP) {
                pwm.setPwmValue(PwmChannel::CHANNEL_B, 0);
            } else {
                PORTD |= (1 << PD4);
            }
            break;
        case Wheel::RIGHT:
            if (direction == Direction::FORWARD) {
                PORTD &= ~(1 << PD5);
            } else if (direction == Direction::STOP) {
                pwm.setPwmValue(PwmChannel::CHANNEL_A, 0);
            } else {
                PORTD |= (1 << PD5);
            }
            break;
    }
}

void Wheels::turn90Right() {
    this->setDirection(Direction::ONLY_RIGHT);
    this->setSpeed(150, 150);
    this->update();
    _delay_ms(800);
}

void Wheels::turn90Left() {
    this->setDirection(Direction::ONLY_LEFT);
    this->setSpeed(150, 150);
    this->update();
    _delay_ms(800);
}

void Wheels::turn45Right() {
    this->setDirection(Direction::RIGHT);
    this->setSpeed(defaultLeftSpeed, defaultRightSpeed);
    this->update();
    _delay_ms(350);
}

void Wheels::turn45Left() {
    this->setDirection(Direction::LEFT);
    this->setSpeed(150, 150);
    this->update();
    _delay_ms(350);
}

void Wheels::boost() {
    this->setDirection(Direction::FORWARD);
    this->setSpeed(255, 255);
    this->update();
    _delay_ms(5);
}
