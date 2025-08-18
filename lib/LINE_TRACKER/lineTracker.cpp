#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "util/delay.h"
#include "lineTracker.h"
#include "../DEL/del.h"

LineTracker LineTracker::lineTrackerInstance;

uint8_t LineTracker::follow() {
    uint8_t value = _lineDetector.readValue();

    switch (value) {
    // Stop
    case 0b00000000:
        _wheels.setDirection(Direction::FORWARD);
        _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
        _wheels.update();
        _delay_ms(1000);
        return 1;

    // Stop
    case 0b11110000:
    case 0b01111000:
    case 0b11111000:
        if(is4Exception) {
            _lineFollower.followLine();
            break;
        }
        _wheels.setDirection(Direction::FORWARD);
        _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
        _wheels.update();
        _delay_ms(1000);
        return 2;

    // Seulement dans edge sinon erreur
    case 0b11100000:
    case 0b00111000:
        if (isEdge) {
            _wheels.setDirection(Direction::FORWARD);
            _wheels.setSpeed(_wheels.defaultLeftSpeed, _wheels.defaultRightSpeed);
            _wheels.update();
            _delay_ms(1000);
            return 3;
        }
    
    default:
        _lineFollower.followLine();
        return 0;
    }

    return 0;

}

void LineTracker::changeRunning() {
    running = !running;
}

void LineTracker::changeRunning(bool running) {
    this->running = running;
}

uint8_t LineTracker::getValue(){
    return _lineDetector.readValue();
}

bool LineTracker::isMiddleOnLine() {
    return _lineDetector.isMiddleOnLine();
}

bool LineTracker::isMiddleNotOnLine() {
    return _lineDetector.isMiddleNotOnLine();
}

bool LineTracker::isRightOnLine() {
    return _lineDetector.isRightOnLine();
}

bool LineTracker::isLeftOnLine() {
    return _lineDetector.isLeftOnLine();
}

bool LineTracker::isRightNotOnLine() {
    return _lineDetector.isRightNotOnLine();
}

bool LineTracker::isLeftNotOnLine() {
    return _lineDetector.isLeftNotOnLine();
}

void LineTracker::resetWhenTurning() {
    _lineFollower.previousError = 0;
}

