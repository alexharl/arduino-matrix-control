#include "Layer.h"

void Layer::bufferOp(bufferOpType_t bOp, uint32_t *data = 0)
{
    for (int row = 0; row < 8; row++)
    {
        if (bOp & CLEAR)
            buffer[row] = 0;
        if (bOp & WRITE)
            buffer[row] |= data[row];
    }
}

void Layer::clear()
{
    bufferOp(CLEAR);
}

void Layer::apply(uint32_t *data)
{
    bufferOp(WRITE, data);
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
    for (int row = 0; row < 8; row++)
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
        buffer[row] |= overflow;
    }
}
