#include "location.h"

Location Location::locationInstance;

// Define the arrays first
const Position Location::_routeFromA[] = {
    Position::FIRST_STOP,
    // Position::B_CORNER,
    Position::SECOND_STOP,
    Position::C_CORNER,
    Position::D_CORNER,
    Position::HOUSE_CORNER,
    Position::HOUSE,
    // Position::F_CORNER,
    Position::J_CORNER,
    Position::OBSTACLE,
    Position::FINISHED
};

const Position Location::_routeFromJ[] = {
    Position::OBSTACLE,
    Position::A_CORNER,
    Position::FIRST_STOP,
    // Position::B_CORNER,
    Position::SECOND_STOP,
    Position::C_CORNER,
    Position::D_CORNER,
    Position::HOUSE_CORNER,
    Position::HOUSE,
    // Position::F_CORNER,
    Position::FINISHED
};

// Then calculate the lengths
const uint8_t Location::_routeFromALength = sizeof(_routeFromA) / sizeof(Position);
const uint8_t Location::_routeFromJLength = sizeof(_routeFromJ) / sizeof(Position);

void Location::initializeRoute(StartPosition start) {
    _startPosition = start;
    _positionIndex = 0;

    if (start == StartPosition::A) {
        _routeLength = _routeFromALength;
        _currentPosition = _routeFromA[0];
    } else {
        _routeLength = _routeFromJLength;
        _currentPosition = _routeFromJ[0];
    }
}

Position Location::getCurrentPosition() {
    return _currentPosition;
}

void Location::nextPosition() {
    if (_positionIndex + 1 < _routeLength) {
        _positionIndex++;
        if (_startPosition == StartPosition::A) {
            _currentPosition = _routeFromA[_positionIndex];
        } else {
            _currentPosition = _routeFromJ[_positionIndex];
        }
    }
}

bool Location::isHouse() {
    return (_currentPosition == Position::HOUSE || _currentPosition == Position::HOUSE_CORNER);
}

bool Location::isFinished() {
    return _currentPosition == Position::FINISHED;
}

void Location::setStartPosition(StartPosition start) {
    _startPosition = start;
    _positionIndex = 0;
    if (start == StartPosition::A) {
        _routeLength = _routeFromALength;
        _currentPosition = _routeFromA[0];
    } else {
        _routeLength = _routeFromJLength;
        _currentPosition = _routeFromJ[0];
    }
}
