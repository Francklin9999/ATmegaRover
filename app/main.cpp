#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "DEL/del.h"
#include "INTERRUPT_BUTTON/interruptButton.h"
#include "PWM/pwm.h"
#include "DEBUG/debug.h"
#include "WHEELS/wheels.h"
#include "TIMER/timer.h"
#include "SOUND/sound.h"
#include "INTERPRETER/interpreter.h"
#include "LINE_DETECTOR/lineDetector.h"
#include "UART/uart.h"
#include "IR_SENSOR/sensor.h"
#include "CAN/can.h"
#include "LOCATION/location.h"
#include "EDGE_CASE/edgeCase.h"
#include "ROBOT/robot.h"
#include "LINE_FOLLOWER/lineFollower.h"

ISR(INT0_vect) {
    Robot::handleInt0Interrupt();
}

ISR(INT2_vect) {
    Robot::handleInt2Interrupt();
}

int main() {
    Robot robot;
    // Sensor infra(PA0);
    // Uart uart;
    // uart.initialization();
    while (!robot.isReady());
    robot.configStart();

    while (true) {
        // if (infra.isGridObstacleDetected()) {
        //     DEL(PORTB, DDRB, PB0, PB1).setMode(DELMode::GREEN);
        // } else {
        //     DEL(PORTB, DDRB, PA0, PA1).setMode(DELMode::OFF);
        // }
        robot.run();
        // uint16_t valeur = infra.readValue();
        // uart.transmitUint16(valeur);
        // _delay_ms(1000);
    }

    // Wheels wheels;
    // wheels.setDirection(Direction::ONLY_RIGHT);
    // wheels.setSpeed(120, 120);
    // wheels.update();

    // while (true);

    // LineFollower lineFollower(PA1); 
    // while (true) {
    //     lineFollower.followLine();
    // }

    return 0;
}


// ISR (INT0_vect) {
//     DEL LED(PORTA, DDRA, PA6, PA7);
//     LED.setMode(DELMode::RED);
//     _delay_ms(5000);
// }

// int main() {
//     DDRD &= ~(1 << PD2);
//     EICRA |= (1 << ISC00);
//     EIMSK |= (1 << INT0);
//     sei();

//     while (true);
// }

// constexpr uint8_t THIRTY_MS = 30;

// bool gPressB = false;
// bool gReleaseB = false;
// bool gPressC = false;
// bool gReleaseC = false;

// Location location;
// DEL LED(PORTA, DDRA, PA6, PA7);

// void initialisation() {
//     cli();

//     // Any edge
//     EICRA |= (1 << ISC00) | (1 << ISC20);
//     EIMSK |= (1 << INT0) | (1 << INT2);

//     sei();
// }

// ISR (INT0_vect) {
//     _delay_ms ( THIRTY_MS );

//     if (!gPressB) {
//         location.selectB(Bifork::RIGHT);
//         gPressB = true;
//     }

//     else if (!gReleaseB) {
//         LED.setMode(DELMode::OFF);
//         gReleaseB = true;
//     }

//     else if (!gPressC) {
//         location.selectC(Bifork::RIGHT);
//         gPressC = true;
//     }

//     else {
//         LED.setMode(DELMode::OFF);
//         gReleaseC = true;
//     }
    
//     LED.setMode(DELMode::GREEN);
//     // _delay_ms(5000);
// }

// ISR (INT2_vect) {
//     _delay_ms ( THIRTY_MS );

//     if (!gPressB) {
//         location.selectB(Bifork::LEFT);
//         gPressB = true;
//     }

//     else if (!gReleaseB) {
//         LED.setMode(DELMode::OFF);
//         gReleaseB = true;
//     }

//     else if (!gPressC) {
//         location.selectC(Bifork::LEFT);
//         gPressC = true;
//     }

//     else {
//         LED.setMode(DELMode::OFF);
//         gReleaseC = true;
//     }

//     LED.setMode(DELMode::RED);
//     // _delay_ms(5000);
// }

// int main() {
//     initialisation();

//     do {}
//     while (!gPressB && !gReleaseB);

//     do {}
//     while (!gPressC && !gReleaseC);
// }
// int main() {
//     Location location(PC3);

//     while (true) {
//         location.follow();
//     }

//     return 0;
// }

// Wheels wheel;

// ISR (PCINT2_vect) {
//     if (PINC & (1 << PC7)) {
//         _delay_ms(150);
//         wheel.setDirection(Direction::ONLY_LEFT);
//         wheel.setSpeed(100, 130);
//         wheel.update();
//     }
//     if (PINC & (1 << PC3)) {
//         _delay_ms(150);
//         wheel.setDirection(Direction::ONLY_LEFT);
//         wheel.setSpeed(100, 130);
//         wheel.update();
//     }
//     if (PINC & (1 << PC6)) {
        
//     }
//     if (PINC & (1 << PC4)) {
       
//     }
//     if (PINC & (1 << PC5)) {
        
//     }
// }

// void config() {
//     cli();

    
// }

// void detecterPotoLAB(uint8_t distance,DEL& del){
    

// }
// int main() {
//     // InterruptButton interruptButton;
//     // interruptButton.configure(InterruptChannel::CHANNEL_A);
//     // interruptButton.configureAnyEdge(InterruptChannel::CHANNEL_A);
//     // interruptButton.enableInterrupt(InterruptChannel::CHANNEL_A);
//     // interruptButton.configure(InterruptChannel::CHANNEL_B);
//     // interruptButton.configureAnyEdge(InterruptChannel::CHANNEL_B);
//     // interruptButton.enableInterrupt(InterruptChannel::CHANNEL_B);
//     Wheels wheel;
//     DEL del(PORTB, DDRB, PB0, PB1);
//     del.setMode(DELMode::GREEN); 
//     Uart uart;
//     uart.initialization();

//     Sensor infra(PA0);
//     while (true){
//     uint8_t valeur=infra.readValue();
//     uart.transmitUint8(valeur);
//     _delay_ms(500);
//     if( valeur > 100){
//         del.setMode(DELMode::RED); 
        
        
//     }
//     // wheel.setDirection(Direction::LEFT);
//     // wheel.setSpeed(100);
//     // wheel.update();

//     // _delay_ms(2500);  

//     // wheel.setDirection(Direction::STOP);
//     // wheel.update();
//     // if( valeur > 100){
//     //     del.setMode(DELMode::RED);;  
//     // }
//     // wheel.setDirection(Direction::RIGHT);
//     // wheel.setSpeed(100);
//     // wheel.update();

//     // _delay_ms(5000);  

//     // wheel.setDirection(Direction::STOP);
//     // wheel.update();
//     // if( valeur > 100){
//     //     del.setMode(DELMode::RED);;  
//     // }
//     }
   

//     return 0;
// }


// int main() {
//     LineDetector _lineDetector(PC4);
//     Uart uart;
//     uart.initialization();

//     while (true) {
//         uart.transmitUint8(_lineDetector.readValue());
//         _delay_ms(100);
//     }

//     return 0;
// }
