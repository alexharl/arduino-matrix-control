#include "Layer.h"

int WARPAROUND = 1;

void Layer::bufferOp(bufferOpType_t op, uint32_t *data = 0)
{
    for (int row = 0; row < HEIGHT; row++)
        bufferRowOp(op, row, data[row]);
}

void Layer::bufferRowOp(bufferOpType_t bOp, uint8_t row, uint32_t data = 0)
{
    if (bOp & CLEAR)
        buffer[row] = 0;
    if (bOp & WRITE)
        buffer[row] |= data;
}

void Layer::clear()
{
    bufferOp(CLEAR);
}

void Layer::apply(uint32_t *data)
{
    bufferOp(WRITE, data);
}

void Layer::sprite(uint8_t *data, int offset_top, int offset_right)
{
    for (int i = offset_top; i < HEIGHT; i++)
        bufferRowOp(WRITE, i, data[i] << offset_right);
}

void Layer::move(int amount)
{
    // no amount = no shift
    if (amount == 0)
        return;

    // shift right if amount is positive
    bool right = amount > 0;
    // normalize amount
    int shift = right ? amount : amount * -1;
    // calculate offset
    int offset = 32 - shift;

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
            bufferRowOp(WRITE, row, overflow);
    }
}
