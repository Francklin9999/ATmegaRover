/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe LineTracker fournit des méthodes pour suivre une ligne en utilisant un capteur de ligne.
*/

#ifndef LINE_TRACKER_H
#define LINE_TRACKER_H

#include <avr/io.h>
#include "../DEL/del.h"
#include "../LINE_DETECTOR/lineDetector.h"
#include "../WHEELS/wheels.h"
#include "../LOCATION/location.h"
#include "../LINE_FOLLOWER/lineFollower.h"

class LineTracker {
private:
    static LineTracker lineTrackerInstance;
    LineDetector& _lineDetector;
    Wheels& _wheels;
    Direction lastDirection;
    Location& _location;
    LineFollower& _lineFollower;

    bool running;
    
    LineTracker() : _lineDetector(LineDetector::getInstance()), _wheels(Wheels::getInstance()), _location(Location::getInstance()), _lineFollower(LineFollower::getInstance()) {
        lastDirection = Direction::FORWARD;
        running = false;
    }

public:
    LineTracker(const LineTracker&) = delete;
    LineTracker& operator=(const LineTracker&) = delete;

    static LineTracker& getInstance() {
        return lineTrackerInstance;
    }

    uint8_t follow();
    void changeRunning();
    void changeRunning(bool running);

    uint8_t getValue();
    bool isMiddleOnLine();
    bool isMiddleNotOnLine();
    bool isRightOnLine();
    bool isLeftOnLine();
    bool isRightNotOnLine();
    bool isLeftNotOnLine();
    void resetWhenTurning();

    bool isEdge = false;
    bool is4Exception = false;
};

#endif
