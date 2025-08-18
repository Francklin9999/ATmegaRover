/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe EdgeCase fournit des méthodes pour gérer les cas particuliers.
*/

#ifndef EDGE_CASE_H
#define EDGE_CASE_H

#include <avr/io.h>

#include "../LOCATION/location.h"
#include "../WHEELS/wheels.h"
#include "../SOUND/sound.h"
#include "../IR_SENSOR/sensor.h"
#include "../LINE_TRACKER/lineTracker.h"
#include "../TIMER/timer.h"
#include "../LINE_DETECTOR/lineDetector.h"
#include "../LINE_FOLLOWER/lineFollower.h"


class EdgeCase {
public:
    EdgeCase();
    void handleEdgeCase(Position position);
    void setTurn(bool firstTurn, bool secondTurn);

private:
    void handleStop();
    void handleFirstStop();
    void handleSecondStop();
    void handleACorner();
    void handleBCorner();
    void handleCCorner();
    void handleDCorner();
    void handleJCorner();
    void handleFCorner();
    void handleObstacleCorner(bool direction);
    void handleHouseFirstCorner();
    void handleHouse();
    void handleObstacle1();
    void handleObstacleCenter();
    void handleObstacleCorner1();
    void handleObstacleCorner2();
    void handleFinished();
    void follow();
    bool houseFollow();
    void flashDelWhileStopped(DELMode mode, uint8_t duration);

    void turnDirectRight();
    void turnDirectLeft();
    void turnMidAndFollowRight();
    void turnMidAndFollowLeft();
    void turnMidRight();
    void turnMidLeft();
    void turnMidRightGrid();
    void turnMidLeftGrid();
    void turnMinRight();
    void turnMinLeft();
    void turnRight();
    void turnLeft();

    const uint8_t _lowTone = 130;
    const uint8_t _highTone = 200;

    bool _firstTurn; // False -> left, True -> right
    bool _secondTurn; // False -> left, True -> right

    bool _isLeftObstacleDetected;
    bool _isMiddleObstacleDetected;
    bool _isRightObstacleDetected;

    Wheels& _wheels;
    Sound _sound;
    Sensor _sensor;
    LineTracker& _lineTracker;
    Timer _timer;
    LineDetector& _lineDetector;
    LineFollower& _lineFollower;
};

#endif
