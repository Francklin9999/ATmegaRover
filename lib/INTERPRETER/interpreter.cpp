#include "avr/io.h"
#include "interpreter.h"

/*
dbt: 0000 0001
att: 0000 0010
dal: 0100 0100
det: 0100 0101
sgo: 0100 1000
sar: 0000 1001
mar: 0110 0000 
mav: 0110 0010
mre: 0110 0011
trd: 0110 0100
trg: 0110 0101
dbc: 1100 0000
fbc: 1100 0001
fin: 1111 1111
*/

Interpreter::Interpreter()
    : _led(PORTA, DDRA, PA0, PA1) {  
}


void Interpreter::doATT(uint8_t operande) {
    for (uint8_t i = 0; i < operande; i++) {
        _delay_ms(25);
    }
}

void Interpreter::doDAL(uint8_t operande) {
    switch (operande) {
        case 1:
            _led.setMode(DELMode::RED);
            break;
        case 2:
            _led.setMode(DELMode::GREEN);
            break;
        default:
            break;  
    }
}

void Interpreter::doDET() {
    _led.setMode(DELMode::OFF);
}

void Interpreter::doSGO(uint8_t operande) {
    if ((operande < 45) || (operande > 81)) {
        return;
    }
    double frequence = 440.0 * pow(2, (operande - 69)/12);
    _sound.playTone(frequence);
}

void Interpreter::doSAR() {
    _sound.stopTone();
}

void Interpreter::doMAR() {
    _wheels.setDirection(Direction::STOP);
    _wheels.update();
}

void Interpreter::doMAV(uint8_t operande) {
    _wheels.setDirection(Direction::FORWARD);
    _wheels.setSpeed(operande);
    _wheels.update();
}

void Interpreter::doMRE(uint8_t operande) {
    _wheels.setDirection(Direction::BACKWARD);
    _wheels.setSpeed(operande);
    _wheels.update();
}

void Interpreter::doTRD() {
    _wheels.setDirection(Direction::RIGHT);
    _wheels.setSpeed(128);
    _wheels.update();
    _delay_ms(1300);
    _wheels.setDirection(Direction::STOP);
    _wheels.update();
}

void Interpreter::doTRG() {
    _wheels.setDirection(Direction::LEFT);
    _wheels.setSpeed(128);
    _wheels.update();
    _delay_ms(1300);
    _wheels.setDirection(Direction::STOP);
    _wheels.update();
}

void Interpreter::doDBC(uint8_t operande) {
    _nIteration = operande;
    _boucleStartAddress = _currentAddress;
}

void Interpreter::doFBC() {
    if (_nIteration > 0) {
        --_nIteration;
        _currentAddress = _boucleStartAddress;
    }
}

void Interpreter::doFIN() {
    _wheels.setDirection(Direction::STOP);
    _wheels.update();
    _led.setMode(DELMode::OFF);
    _sound.stopTone();
}

void Interpreter::interpreteCode(uint8_t code, uint8_t operande) {
    switch (code) {
    case DBT:
        break;
    case ATT:
        doATT(operande);
        break;
    case DAL:
    _led.setMode(DELMode::RED);
        doDAL(operande);
        break;
    case DET:
        doDET();
        break;
    case SGO:
        doSGO(operande);
        break;
    case SAR:
        doSAR();
        break;
    case MAR:
        doMAR();
        break;
    case MAR_2:
        doMAR();
        break;
    case MAV:
        doMAV(operande);
        break;
    case MRE:
        doMRE(operande);
        break;
    case TRD:
        doTRD();
        break;
    case TRG:
        doTRG();
        break;
    case DBC:
        doDBC(operande);
        break;
    case FBC:
        doFBC();
        break;
    case FIN:
        doFIN();
        break;
    default:
        break;
    }
}

void Interpreter::run() {
    _currentAddress = 0x02;
    uint8_t code = 0x00;
    uint8_t operande = 0x00;
    
    while (code != DBT) {
        _memory.lecture(_currentAddress, &code);
        _currentAddress+=2;
        // _memory.lecture(_currentAddress, &operande);
        // _currentAddress++;
    }

    while (code != FIN) {
        _memory.lecture(_currentAddress, &code);
        _currentAddress++;
        _memory.lecture(_currentAddress, &operande);
        _currentAddress++;
        interpreteCode(code, operande);
    }
}