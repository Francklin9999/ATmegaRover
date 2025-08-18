/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe Wheels fournit des méthodes pour contrôler les deux roues du robot, permettant de gérer leur direction et leur vitesse via la classe PWM et contrôle des broches. La roue de gauche est configuré sur les pins PD4 et PD6, et la roue de droite PD5 et PD7.
*/

#ifndef WHEELS_H
#define WHEELS_H

#include <avr/io.h>
#include "../PWM/pwm.h"


enum class Direction {
    FORWARD, BACKWARD, RIGHT, LEFT, STOP, ONLY_LEFT, ONLY_RIGHT
};

enum class Wheel {
    RIGHT, LEFT
};

class Wheels {
private:
    static Wheels wheelsInstance;
    
    uint8_t speedLeft;
    uint8_t speedRight;
    Direction direction;
    Pwm pwm;
    
    void setWheel(Wheel wheel, Direction direction);

public:
    Wheels(const Wheels&) = delete;
    Wheels& operator=(const Wheels&) = delete;

    static Wheels& getInstance() {
        return wheelsInstance;
    }

    Wheels() {
        DDRD |= (1 << PD4) | (1 << PD5);
        speedLeft = 0;
        speedRight = 0;
        direction = Direction::STOP;
    }

    static constexpr uint8_t defaultLeftSpeed = 90;
    static constexpr uint8_t defaultRightSpeed = 80;

    static constexpr uint8_t turningLeftSpeed = 120;
    static constexpr uint8_t turningRightSpeed = 120;

    void setDirection(Direction direction);
    void setSpeed(uint8_t speed);
    void setSpeed(uint8_t speedLeft, uint8_t speedRight);
    void setSpeedLeft(uint8_t speedLeft);
    void setSpeedRight(uint8_t speedRight);
    Direction getDirection() const;
    void update();
    void turn90Right();
    void turn90Left();
    void turn45Right();
    void turn45Left();
    void boost();
};

#endif
