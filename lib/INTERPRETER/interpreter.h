/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: La classe Interpreter fournit des méthodes pour interpréter un programme à partir d'un fichier.
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../DEL/del.h"
#include "../PWM/pwm.h"
#include "../WHEELS/wheels.h"
#include "../MEMOIRE_24/memoire_24.h"
#include "../SOUND/sound.h"
#include <util/delay.h>
#include <math.h>
#ifndef F_CPU
#define F_CPU 8000000UL
#endif


class Interpreter {
public:
    Interpreter();
    void run();
    void interpreteCode(uint8_t code, uint8_t operande);

    static const uint8_t DBT = 0x01;  
    static const uint8_t ATT = 0x02;  
    static const uint8_t DAL = 0x44;  
    static const uint8_t DET = 0x45;  
    static const uint8_t SGO = 0x48;  
    static const uint8_t SAR = 0x09;  
    static const uint8_t MAR = 0x60;  
    static const uint8_t MAR_2 = 0x61; 
    static const uint8_t MAV = 0x62;  
    static const uint8_t MRE = 0x63;  
    static const uint8_t TRD = 0x64;  
    static const uint8_t TRG = 0x65;  
    static const uint8_t DBC = 0xC0;  
    static const uint8_t FBC = 0xC1;  
    static const uint8_t FIN = 0xFF;

private:
    bool _debut = false;
    bool _fin = false;

    uint16_t _programLength;
    Memoire24CXXX _memory;
    DEL _led;
    Wheels _wheels;
    Sound _sound;
    uint8_t _boucleStartAddress = 0x00;
    uint8_t _nIteration = 0;
    uint8_t _currentAddress = 0x00;
    uint8_t _currentInstruction;

    void doATT(uint8_t operande);
    void doDAL(uint8_t operande);
    void doDET();
    void doSGO(uint8_t operande);
    void doSAR();
    void doMAR();
    void doMAV(uint8_t operande);
    void doMRE(uint8_t operande);
    void doTRD();
    void doTRG();
    void doDBC(uint8_t operande);
    void doFBC();
    void doFIN();
};

#endif