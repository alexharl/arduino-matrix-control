#include "Layer.h"

Layer::Layer(uint8_t width, uint8_t height, uint8_t top, uint8_t right)
{
    offset_top = top;
    offset_right = right;

    WIDTH = width;
    HEIGHT = height;
}

void Layer::modify_buffer(modType_t mod, uint32_t *data = 0)
{
    for (int row = 0; row < HEIGHT; row++)
        modify_buffer_row(mod, row, data[row]);
}

void Layer::modify_buffer_row(modType_t mod, uint8_t row, uint32_t data = 0)
{
    modify_bits(mod, &buffer[row], data);
}

void Layer::clear()
{
    modify_buffer(CLEAR);
}

void Layer::apply(Layer *src)
{
    for (int row = 0; row < HEIGHT; row++)
    {
        int real_row = src->offset_top < 0 ? row + src->offset_top * -1 : row - src->offset_top;
        if (real_row < 0)
            continue;
        if (real_row > MAX_H)
            break;

        uint32_t value = src->buffer[real_row];
        if (src->offset_right > 0)
            value <<= src->offset_right;
        else if (src->offset_right < 0)
            value >>= src->offset_right;

        modify_buffer_row(WRITE, row, value);
    }
}

void Layer::sprite(uint8_t *data, int top, int right)
{
    for (int i = top; i < HEIGHT; i++) {
        uint32_t val = data[i];
        modify_buffer_row(WRITE, i, val << right);
    }
}

void Layer::move(int amount)
{
    // no amount = no shift
    if (amount == 0)
        return;

    int max = 32;

    // shift right if amount is positive
    bool right = amount > 0;

    int shift = amount;
    // normalize amount
    if (shift > max || shift < (max * -1))
        shift %= max;
    else if (!right)
        shift *= -1;

    // calculate offset
    int offset = max - shift;

    // shift each row
    for (int row = 0; row < HEIGHT; row++)
    {
        // all bits that would be lost after shift get stored here
        uint32_t overflow = 0;

        if (right)
        {
            overflow = (buffer[row] & ((1 << shift) - 1)) << offset;
            buffer[row] >>= shift;
        }
        else
        {
            overflow = buffer[row] >> offset;
            buffer[row] <<= shift;
        }

        // apply overflown bits
        if (WARPAROUND)
            modify_buffer_row(WRITE, row, overflow);
    }
}