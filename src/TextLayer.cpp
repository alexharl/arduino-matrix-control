#include "TextLayer.h"
#include "small_numbers.h"
#include "small_chars.h"

void TextLayer::add_character(int character)
{
    if (character <= 10)
    {
        sprite(get_small_number(character), 0, character_offset);

        if (character == 10) // dot
        {
            character_offset += SPACING + 1;
        }
        else // 0 - 9
        {
            character_offset += SPACING + 3;
        }
    }
    else if (character == 11)
    {
        character_offset += SPACING;
    }
    else
    {
        // sprite characters
        sprite(get_small_char(character), 0, character_offset);
        character_offset += SPACING + 3;
    }
}

void TextLayer::draw_number(int number, int float_at)
{
    clear();
    character_offset = 0;

    int u = number % 10;           // units
    int t = (number / 10) % 10;    // tens
    int h = (number / 100) % 10;   // hundreds
    int th = (number / 1000) % 10; // thousands

    // draw units
    add_character(u);

    if (float_at == 1)
        add_character(10);

    if (t > 0)
    {
        add_character(t);
    }
    else if (float_at >= 1 || h > 0)
    {
        add_character(0);
    }

    if (float_at == 2)
        add_character(10);

    if (h > 0)
    {
        add_character(h);
    }
    else if (float_at >= 2 || th > 0)
    {
        add_character(0);
    }

    if (float_at == 3)
        add_character(10);

    if (th > 0)
    {
        add_character(th);
    }
    else if (float_at >= 3)
    {
        add_character(0);
    }
}