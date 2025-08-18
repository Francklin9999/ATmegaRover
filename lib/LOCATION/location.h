/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe Location fournit des méthodes pour gérer la localisation du robot.
*/

#ifndef LOCATION_H
#define LOCATION_H

#include <avr/io.h>

enum class StartPosition {
    A,
    J
};

enum class Position {
    FIRST_STOP,
    SECOND_STOP,
    A_CORNER,
    B_CORNER,
    C_CORNER,
    D_CORNER,
    J_CORNER,
    OBSTACLE_CORNER,
    HOUSE_CORNER,
    HOUSE,
    F_CORNER,
    OBSTACLE,
    FINISHED
};

enum class Bifork { RIGHT, LEFT };

class Location {
public:
    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;

    static Location& getInstance() {
        return locationInstance;
    }

    Location() { }

    void initializeRoute(StartPosition start);
    Position getCurrentPosition();
    void setStartPosition(StartPosition start);
    void nextPosition();
    bool isHouse();
    bool isFinished();

private:
    static Location locationInstance;

    Position _currentPosition;
    StartPosition _startPosition;
    uint8_t _positionIndex = 0;
    uint8_t _routeLength = 0; // ✅ Fixed: not static or const
    static const Position _routeFromA[];
    static const Position _routeFromJ[];
    static const uint8_t _routeFromALength;
    static const uint8_t _routeFromJLength;  
};

#endif
