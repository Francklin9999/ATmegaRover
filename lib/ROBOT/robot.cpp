#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "util/delay.h"

#include "robot.h"

#include "../DEL/del.h"
#include "../LINE_FOLLOWER/lineFollower.h"
#include "../UART/uart.h"

DEL Robot::_del(PORTB, DDRB, PB0, PB1); 
bool Robot::_isReady = false;
bool Robot::_isFirstTurnSet = false;
bool Robot::_isSecondTurnSet = false;
bool Robot::_firstTurn = false;
bool Robot::_secondTurn = false;
bool Robot::_isLocationSet = false;
bool Robot::_buttonReleased = false;

// Uart uart;
// uint8_t compteur = 0;

Robot::Robot() : 
    _lineTracker(LineTracker::getInstance()),
    _interruptButton(),
    _location(Location::getInstance()),
    _lineFollower(LineFollower::getInstance()),
    _edgeCase(),
    _wheels(Wheels::getInstance())
{
    _interruptButton.configure(InterruptChannel::CHANNEL_A);
    _interruptButton.configureAnyEdge(InterruptChannel::CHANNEL_A);
    _interruptButton.enableInterrupt(InterruptChannel::CHANNEL_A);
    _interruptButton.configure(InterruptChannel::CHANNEL_B);
    _interruptButton.configureAnyEdge(InterruptChannel::CHANNEL_B);
    _interruptButton.enableInterrupt(InterruptChannel::CHANNEL_B);
}

void Robot::handleInt0Interrupt() {
    _delay_ms(30);
    bool isPressed = buttonDPressed();

    if (isPressed) {
        _del.setMode(DELMode::RED);
        if(!_isFirstTurnSet) {
            _firstTurn = true;
            _isFirstTurnSet = true;
        }
        else if (!_isSecondTurnSet && _buttonReleased) {
            _buttonReleased = false;
            _secondTurn = true;
            _isSecondTurnSet = true;
            _isReady = true;
        }

    } else {
        _del.setMode(DELMode::OFF);
        _buttonReleased = true;
    }
}

void Robot::handleInt2Interrupt() {
    _delay_ms(30);
    bool isPressed = buttonBPressed();

    if (isPressed) {
        _del.setMode(DELMode::GREEN);
        if(!_isFirstTurnSet) {
            _firstTurn = false;
            _isFirstTurnSet = true;
        }
        else if (!_isSecondTurnSet) {
            _buttonReleased = false;
            _secondTurn = false;
            _isReady = true;
            _isSecondTurnSet = true;
        }
    } else {
        _del.setMode(DELMode::OFF);
        _buttonReleased = true;
    }
}

bool Robot::buttonDPressed() {
    return PIND & (1 << PD2);
}

bool Robot::buttonBPressed() {
    return !(PINB & (1 << PB2));
}

bool Robot::isReady() {
    return _isReady && _buttonReleased;
}

void Robot::configStart() {
    _edgeCase.setTurn(_firstTurn, _secondTurn);
    _interruptButton.disableInterrupt(InterruptChannel::CHANNEL_A);
    _interruptButton.disableInterrupt(InterruptChannel::CHANNEL_B);
    _delay_ms(2000); // Attendre 2
    _wheels.boost();
}

void Robot::run() {
    uint8_t code = _lineTracker.follow();

    switch(code) {
        case 0:
            // Normal pas de problème
            break;
        case 1:
            // Sensor detecte rien
            // _del.setMode(DELMode::RED);
            if (!_isLocationSet) {
                _location.setStartPosition(StartPosition::A);
                _isLocationSet = true;
            }
            {
                Position position = _location.getCurrentPosition();
                _edgeCase.handleEdgeCase(position);
                _location.nextPosition();
            }
            // _del.setMode(DELMode::OFF);
            break;
        case 2:
            // Sensor detecte tout
            // _del.setMode(DELMode::GREEN);
            if (!_isLocationSet) {
                _location.setStartPosition(StartPosition::J);
                _isLocationSet = true;
            }
            {
                Position position = _location.getCurrentPosition();
                _edgeCase.handleEdgeCase(position);
                _location.nextPosition();
            }
            // _del.setMode(DELMode::OFF);
            break;
        case 3:
            // _del.setMode(DELMode::RED);
            if (_isLocationSet) {
                Position position = _location.getCurrentPosition();
                _edgeCase.handleEdgeCase(position);
                _location.nextPosition();
            }
            // _del.setMode(DELMode::OFF);
            break;
        default:
            break;
    }
}
