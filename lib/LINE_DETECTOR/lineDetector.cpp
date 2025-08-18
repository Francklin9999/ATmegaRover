#include "lineDetector.h"

LineDetector LineDetector::lineDetectorInstance;

uint8_t LineDetector::readValue() {
    return (PINC & ((1  << _leftMost) | (1 << _leftMiddle) | (1 << _middle) | (1 << _rightMiddle) | (1 << _rightMost)));
}

bool LineDetector::isMiddleOnLine() {
    return PINC & (1 << _middle);
}

bool LineDetector::isMiddleNotOnLine() {
    return !(PINC & (1 << _middle));
}

bool LineDetector::isRightOnLine() {
    return PINC & (1 << _rightMost);
}

bool LineDetector::isLeftOnLine() {
    return PINC & (1 << _leftMost);
}

bool LineDetector::isRightNotOnLine() {
    return !(PINC & (1 << _rightMost));
}

bool LineDetector::isLeftNotOnLine() {
    return !(PINC & (1 << _leftMost));
}

bool LineDetector::isNoneOnLine() {
    return !(PINC & ((1  << _leftMost) | (1 << _leftMiddle) | (1 << _middle) | (1 << _rightMiddle) | (1 << _rightMost)));
}

bool LineDetector::isOneOnLine() {
    return PINC & ((1  << _leftMost) | (1 << _leftMiddle) | (1 << _middle) | (1 << _rightMiddle) | (1 << _rightMost));
}