#include "debug.h"

void printUint16(uint16_t x) { 
    static Uart uart; 
    uart.initialization(); 
    uart.transmitUint16(x); 
}