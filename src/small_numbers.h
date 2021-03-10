#ifndef Small_Numbers_h
#define Small_Numbers_h

unsigned char small_0[8] = {
    0b00000111,
    0b00000101,
    0b00000101,
    0b00000101,
    0b00000111,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_1[8] = {
    0b00000001,
    0b00000001,
    0b00000001,
    0b00000001,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_2[8] = {
    0b00000111,
    0b00000001,
    0b00000111,
    0b00000100,
    0b00000111,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_3[8] = {
    0b00000111,
    0b00000001,
    0b00000111,
    0b00000001,
    0b00000111,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_4[8] = {
    0b00000101,
    0b00000101,
    0b00000111,
    0b00000001,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_5[8] = {
    0b00000111,
    0b00000100,
    0b00000111,
    0b00000001,
    0b00000111,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_6[8] = {
    0b00000111,
    0b00000100,
    0b00000111,
    0b00000101,
    0b00000111,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_7[8] = {
    0b00000111,
    0b00000001,
    0b00000001,
    0b00000001,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_8[8] = {
    0b00000111,
    0b00000101,
    0b00000111,
    0b00000101,
    0b00000111,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_9[8] = {
    0b00000111,
    0b00000101,
    0b00000111,
    0b00000001,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char small_dot[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
};

unsigned char *get_small_number(int number)
{
    switch (number)
    {
    case 0:
        return small_0;
    case 1:
        return small_1;
    case 2:
        return small_2;
    case 3:
        return small_3;
    case 4:
        return small_4;
    case 5:
        return small_5;
    case 6:
        return small_6;
    case 7:
        return small_7;
    case 8:
        return small_8;
    case 9:
        return small_9;
    case 10:
        return small_dot;
    default:
        return small_0;
    }
}

#endif