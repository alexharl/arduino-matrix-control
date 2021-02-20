#include "Helper.h"

uint32_t set_all_bytes(uint8_t value)
{
    uint32_t values = value;
    return values | (values << 8 | value) | (values << 16 | value) | (values << 24 | value);
}

void modify_bits(modType_t mod, uint32_t *value, uint32_t data)
{
    if (mod & CLEAR)
        *value = 0;
    if (mod & WRITE)
        *value |= data;
    if (mod & REVERSE)
    {
        // O(1) solution for bit reverse
        *value = (*value >> 1) & 0x55555555 | (*value << 1) & 0xaaaaaaaa;
        *value = (*value >> 2) & 0x33333333 | (*value << 2) & 0xcccccccc;
        *value = (*value >> 4) & 0x0f0f0f0f | (*value << 4) & 0xf0f0f0f0;
        *value = (*value >> 8) & 0x00ff00ff | (*value << 8) & 0xff00ff00;
        *value = (*value >> 16) & 0x0000ffff | (*value << 16) & 0xffff0000;
    }
}