/*
 * Auteurs: Aly Abdoulaye-Idriss, Hoang Thong Nguyen, Shunyi Wang, Haitam Magdoul, Walid Benakmoum et Franck Fongang
 * Description: Permet de Debug le programme.
*/
#include "../UART/uart.h"

void printUint16(uint16_t x);

#ifdef DEBUG
    #define DEBUG_PRINT(x) printUint16(x);
#else
    #define DEBUG_PRINT(x) do {} while (0) // code mort
#endif