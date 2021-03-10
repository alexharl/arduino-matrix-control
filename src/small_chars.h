#ifndef small_chars_h
#define small_chars_h

unsigned char small_a[8] = {
    0b00000111,
    0b00000101,
    0b00000111,
    0b00000101,
    0b00000101,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_b[8] = {
    0b00000110,
    0b00000101,
    0b00000110,
    0b00000101,
    0b00000110,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_c[8] = {
    0b00000111,
    0b00000100,
    0b00000100,
    0b00000100,
    0b00000111,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char *get_small_char(byte character)
{
    switch (character)
    {
    case 12:
        return small_a;
    case 13:
        return small_b;
    case 14:
        return small_c;
    default:
        return small_a;
    }
}

#endif