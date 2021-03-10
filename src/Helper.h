#ifndef Helper_h
#define Helper_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**
 * returns an int with all 4 bytes set to value
 */
uint32_t set_all_bytes(uint8_t value);

/**
 * Ops that can be performed on modify_bits
 */
enum modType_t
{
    CLEAR = 1,
    CUT = 2,
    WRITE = 4,
    OVERWRITE = 5,
    REVERSE = 8
};

/**
 * modify bits in value
 */
void modify_bits(modType_t mod, uint32_t *value, uint32_t data = 0);

#endif