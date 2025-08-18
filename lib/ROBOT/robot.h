/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe Robot fournit des méthodes pour contrôler le robot.
*/

#ifndef ROBOT_H
#define ROBOT_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../LINE_TRACKER/lineTracker.h"
#include "../LOCATION/location.h"
#include "../DEL/del.h"
#include "../INTERRUPT_BUTTON/interruptButton.h"
#include "../EDGE_CASE/edgeCase.h"
#include "../WHEELS/wheels.h"



class Robot {
public:
    Robot();
    void run();
    static bool buttonDPressed();
    static bool buttonBPressed();
    bool isReady();
    void configStart();
    static const char* positionToString(Position position);
    
    static void handleInt0Interrupt();
    static void handleInt2Interrupt();

protected:
    static DEL _del;
    static bool _isReady;
    static bool _isFirstTurnSet;
    static bool _isSecondTurnSet;
    static bool _firstTurn; // False -> left, True -> right
    static bool _secondTurn; // False -> left, True -> right
    static bool _isLocationSet;
    static bool _buttonReleased;

private:
    LineTracker& _lineTracker;
    InterruptButton _interruptButton;
    Location& _location;
    LineFollower& _lineFollower;
    EdgeCase _edgeCase;
    Wheels& _wheels;
};

#endif
