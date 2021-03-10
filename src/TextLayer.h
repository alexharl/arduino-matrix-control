#ifndef TextLayer_h
#define TextLayer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Layer.h>
class TextLayer : public Layer
{
public:
    int SPACING = 1;
    void draw_number(int number, int float_at = 0);

private:
    int character_offset = 0;
    void add_character(int character);
};

#endif