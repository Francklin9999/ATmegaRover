#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>

#include "edgeCase.h"
#include "../DEL/del.h"
#include "../UART/uart.h"

EdgeCase::EdgeCase() 
    : _sensor(PA0),
      _wheels(Wheels::getInstance()),
      _lineTracker(LineTracker::getInstance()),
      _isLeftObstacleDetected(false),
      _isMiddleObstacleDetected(false),
      _isRightObstacleDetected(false),
      _lineDetector(LineDetector::getInstance()),
      _lineFollower(LineFollower::getInstance())
{ }

void EdgeCase::setTurn(bool firstTurn, bool secondTurn) {
    _firstTurn = firstTurn;
    _secondTurn = secondTurn;
}

void EdgeCase::handleEdgeCase(Position position) {
    switch(position) {
        case Position::FIRST_STOP:
            handleFirstStop();
            // _lineTracker.isEdge = true;
            break;
        case Position::SECOND_STOP:
            handleSecondStop();
            break;
        case Position::A_CORNER:
            handleACorner();
            break;
        case Position::B_CORNER:
            handleBCorner();
            _lineTracker.is4Exception = true;
            break;
        case Position::C_CORNER:
            _lineTracker.is4Exception = false;
            handleCCorner();
            break;
        case Position::D_CORNER:
            handleDCorner();
            break;
        case Position::J_CORNER:
        DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::GREEN);
            handleJCorner();
            break;
        case Position::OBSTACLE_CORNER:
            // JSP
            break;
        case Position::HOUSE_CORNER:
            _lineTracker.isEdge = true;
            handleHouseFirstCorner();
            break;
        case Position::HOUSE:
            _lineTracker.isEdge = true;
            handleHouse();
            _lineTracker.isEdge = false;
            break;
        case Position::F_CORNER:
            DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::RED);
            _lineTracker.isEdge = true;
            handleFCorner();
            _lineTracker.isEdge = false;
            break;
        case Position::OBSTACLE:
        DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::AMBER);
            handleObstacle1();
            _lineTracker.isEdge = false;
            break;
        case Position::FINISHED:
            handleFinished();
            break;
    }
}

void EdgeCase::follow() {
    while(_lineTracker.follow() == 0);  
}

bool EdgeCase::houseFollow() {
	bool isObstacle = false;
    while(_lineTracker.follow() == 0) {
		if (_sensor.isHouseObstacleDetected()) {
			isObstacle = true;
			break;
		}
	}
	return isObstacle;  
}

void EdgeCase::handleStop() {
    _wheels.setDirection(Direction::STOP);  
    _wheels.update();  
    _sound.playTone(_highTone);
    // Attendre 1 seconde (Voir instructions)
    _delay_ms(1000);
    _sound.stopTone();
}

void EdgeCase::handleFirstStop() {
    handleStop();
    if (_firstTurn) {
        turnLeft(); 
        turnDirectRight();
    } else {
        turnRight();
        turnDirectLeft();  
    }

    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();

    while (_lineDetector.isOneOnLine()) {
        _lineFollower.followLine();
    }
    DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::RED);
}

void EdgeCase::handleSecondStop() {
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    handleStop();
    if (_secondTurn) {
        turnLeft();  
    } else {
        turnDirectRight(); 
    }
}

void EdgeCase::handleACorner() {
    turnMidRight();
}

void EdgeCase::handleBCorner() {
    if (_firstTurn) {
        turnMidRight();  
    } else {
        turnMidLeft();
    }
}

void EdgeCase::handleCCorner() {
    if (_secondTurn) {
        _wheels.setDirection(Direction::ONLY_RIGHT);
        _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
        _wheels.update();
        _delay_ms(200);
        while (!_lineTracker.isMiddleOnLine()) {
            _delay_ms(5);
        }
        _lineTracker.resetWhenTurning();  
    } else {
        _wheels.setDirection(Direction::ONLY_LEFT);
        _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
        _wheels.update();
        _delay_ms(200);
        while (!_lineTracker.isMiddleOnLine()) {
            _delay_ms(5);
        }
        _lineTracker.resetWhenTurning(); 
    }
}

void EdgeCase::handleDCorner() {
    turnMidRight();
}

void EdgeCase::handleJCorner() {
    turnMidRight();
}

void EdgeCase::handleFCorner() {
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _timer.start(15);
    while (!_timer.isFinished()) {
        _lineTracker.follow();
    }
}


void EdgeCase::handleObstacleCorner(bool direction) {
    // direction == 0 left direction == 1 right
    if (direction) {
        turnMidRight();
    } else {  
        turnMidLeft();
    }
}

void EdgeCase::handleHouseFirstCorner() {
}

void EdgeCase::handleHouse() {
    bool isObstacle = false;
    
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(1200);
    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(1500);
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();

    while(_lineTracker.follow() == 0);
    while(_lineTracker.follow() != 0);
    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    while(_lineTracker.isMiddleNotOnLine());
    while (_lineTracker.isLeftNotOnLine()) {
        if (_sensor.isHouseObstacleDetected()) {
            isObstacle = true;
        }
    }

    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();

    while (_lineTracker.isMiddleNotOnLine());

    _timer.start(30);
    while (!_timer.isFinished()) {
        _lineFollower.followLine();
        if (_sensor.isHouseObstacleDetected()) {
            isObstacle = true;
            break;
        }
    }

    // while(_lineTracker.follow() == 0) {
    //     if (_sensor.isHouseObstacleDetected()) {
    //         isObstacle = true;
    //         break;
    //     }
    // }

    if (isObstacle) {
        flashDelWhileStopped(DELMode::RED, 2);
        _wheels.setDirection(Direction::ONLY_RIGHT);
        _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
        _wheels.update();
        while (_lineTracker.isMiddleOnLine());
        while (_lineTracker.isMiddleNotOnLine());
        while (_lineTracker.follow() == 0);
        _wheels.setDirection(Direction::FORWARD);
        _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
        _wheels.update();
        _delay_ms(750);
        _wheels.setDirection(Direction::ONLY_RIGHT);
        _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
        _wheels.update();
        while (!_lineTracker.isMiddleOnLine()) {
            _delay_ms(5);
        }
        while (_lineTracker.follow() == 0);
        _lineTracker.resetWhenTurning();
    } else {
        flashDelWhileStopped(DELMode::GREEN, 2);
        _wheels.setDirection(Direction::ONLY_LEFT);
        _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
        _wheels.update();
        while (!_lineTracker.isMiddleOnLine()) {
            _delay_ms(5);
        }
        while(_lineTracker.follow() == 0);
        turnMidRight();
        while(_lineTracker.follow() == 0);
        while(_lineTracker.follow() == 0);
    }

    turnMidRight();

    while (_lineDetector.isOneOnLine()) {
        _lineFollower.followLine();
    }
}

void EdgeCase::flashDelWhileStopped(DELMode mode, uint8_t duration) {
    _wheels.setDirection(Direction::STOP);
    _wheels.update();

    for (uint8_t i = 0; i < duration * 2; ++i) {
        DEL(PORTB, DDRB, PB0, PB1).setMode(mode);
        _delay_ms(125);
        DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::OFF);
        _delay_ms(125);
        DEL(PORTB, DDRB, PB0, PB1).setMode(mode);
        _delay_ms(125);
        DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::OFF);
        _delay_ms(125);
    }
}

void EdgeCase::handleObstacle1() {
    _timer.start(15);
    while (!_timer.isFinished()) {
        _lineFollower.followLine();
    }

    if (!_sensor.isGridObstacleDetected()) {
        flashDelWhileStopped(DELMode::GREEN, 2);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        handleObstacleCenter();
        return;
    }

    // _wheels.boost();
    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(800);

    while (_lineTracker.isMiddleNotOnLine()) {
        if(_sensor.isGridObstacleDetected()) {
            _isRightObstacleDetected = true;
            break;
        }
        _delay_ms(5);
    }

    if (!_isRightObstacleDetected) {
        while (_lineTracker.follow() == 0);
        turnMidLeft();
        flashDelWhileStopped(DELMode::GREEN, 2);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        handleObstacleCorner1();
        return;
    }

    // _wheels.boost();
    DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::GREEN);
    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    while (_lineTracker.isMiddleNotOnLine()) {
        _delay_ms(5);
    }

    while (_lineTracker.isLeftNotOnLine());
    while (_lineTracker.isMiddleNotOnLine());
    while (_lineTracker.follow() == 0);
    turnMidRight();
    flashDelWhileStopped(DELMode::GREEN, 2);
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    handleObstacleCorner2();
    return;
}

void EdgeCase::handleObstacleCenter() {
    _isRightObstacleDetected = false;
    _timer.start(22);
    while (!_timer.isFinished()) {
        _lineFollower.followLine();
    }

    if (!_sensor.isGridObstacleDetected()) {
        flashDelWhileStopped(DELMode::GREEN, 2);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        turnMidRight();
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        return;
    }

    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(800);
    while (_lineTracker.isMiddleNotOnLine()) {
        if(_sensor.isGridObstacleDetected()) {
            _isRightObstacleDetected = true;
            break;
        }
        _delay_ms(5);
    }

    if (!_isRightObstacleDetected) {
        while (_lineTracker.follow() == 0);
        turnMidLeft();
        flashDelWhileStopped(DELMode::GREEN, 2);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        turnMidRight();
        while (_lineTracker.follow() == 0);
        return;
    }

    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    while (_lineTracker.isMiddleNotOnLine()) {
        _delay_ms(5);
    }

    while (_lineTracker.isLeftNotOnLine());
    while (_lineTracker.isMiddleNotOnLine());
    while (_lineTracker.follow() == 0);
    turnMidRight();
    flashDelWhileStopped(DELMode::GREEN, 2);
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    turnMidRight();
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    return;
}

void EdgeCase::handleObstacleCorner1() {
    _isRightObstacleDetected = false;
    _timer.start(15);
    while (!_timer.isFinished()) {
        _lineFollower.followLine();
    }

    if (!_sensor.isGridObstacleDetected()) {
        flashDelWhileStopped(DELMode::GREEN, 2);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        turnMidRight();
        while (_lineTracker.follow() == 0);
        return;
    }

    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(800);
    while (_lineTracker.isMiddleNotOnLine()) {
        if(_sensor.isGridObstacleDetected()) {
            _isRightObstacleDetected = true;
        }
        _delay_ms(5);
    }

    if (!_isRightObstacleDetected) {
        while (_lineTracker.follow() == 0);
        turnMidRight();
        flashDelWhileStopped(DELMode::GREEN, 2);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        turnMidRight();
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        return;
    }
    
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    turnMidRight();
    flashDelWhileStopped(DELMode::GREEN, 2);
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    turnMidRight();
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    return;
}

void EdgeCase::handleObstacleCorner2() {
    _isRightObstacleDetected = false;
    _timer.start(15);
    while (!_timer.isFinished()) {
        _lineFollower.followLine();
    }

    if (!_sensor.isGridObstacleDetected()) {
        flashDelWhileStopped(DELMode::GREEN, 2);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        turnMidRight();
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        return;
    }

    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(800);
    while (_lineTracker.isMiddleNotOnLine()) {
        if(_sensor.isGridObstacleDetected()) {
            _isRightObstacleDetected = true;
        }
        _delay_ms(5);
    }

    if (!_isRightObstacleDetected) {
        while (_lineTracker.follow() == 0);
        turnMidLeft();
        flashDelWhileStopped(DELMode::GREEN, 2);
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        turnMidRight();
        while (_lineTracker.follow() == 0);
        while (_lineTracker.follow() == 0);
        return;
    }
    
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    turnMidLeft();
    flashDelWhileStopped(DELMode::GREEN, 2);
    while (_lineTracker.follow() == 0);
    while (_lineTracker.follow() == 0);
    turnMidRight();
    while (_lineTracker.follow() == 0);
    return;
}

void EdgeCase::handleFinished() {
    turnMidRight();
    _wheels.setDirection(Direction::STOP);
    _wheels.update();

    while (true) {
        DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::GREEN);
        _delay_ms(2000);
        DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::RED);
        _delay_ms(2000);
    } 
}

void EdgeCase::turnRight() {
    _wheels.boost();
    _wheels.setDirection(Direction::RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnLeft() {
    _wheels.boost();
    _wheels.setDirection(Direction::LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnDirectRight() {
    _wheels.boost();
    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnDirectLeft() {
    _wheels.boost();
    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnMidAndFollowRight() {
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _timer.start(15);
    while (!_timer.isFinished()) {
        _lineTracker.follow();
    }
    _wheels.boost();
    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed + 10, _wheels.defaultRightSpeed  + 10);
    _wheels.update();
    _delay_ms(350);
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnMidAndFollowLeft() {
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _timer.start(20);
    while (!_timer.isFinished()) {
        _lineTracker.follow();
    }
    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnMidRight() {
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(1200);
    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnMidLeft() {
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(1600);
    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnMidRightGrid() {
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(1000);
    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnMidLeftGrid() {
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(1500);
    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    while (!_lineTracker.isMiddleOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnMinRight() {
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    _wheels.setDirection(Direction::ONLY_RIGHT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    while (!_lineTracker.isRightOnLine()) { 
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}

void EdgeCase::turnMinLeft() {
    _wheels.boost();
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    _wheels.setDirection(Direction::ONLY_LEFT);
    _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
    _wheels.update();
    _delay_ms(500);
    while (!_lineTracker.isLeftOnLine()) {
        _delay_ms(5);
    }
    _lineTracker.resetWhenTurning();
    _wheels.boost();
}
