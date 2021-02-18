#include "Renderer.h"
#include <SPI.h>

Renderer::Renderer(int dataPin, int clkPin, int csPin, int devices)
{
    FLIP_H = OFF;
    FLIP_V = OFF;
    INVERT = OFF;

    DEVICES = devices;

    // initialize connected pins
    DATA_PIN = dataPin;
    CLK_PIN = clkPin;
    CS_PIN = csPin;

    // set pins to output
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);

    // activate chip select
    digitalWrite(CS_PIN, HIGH);

    // clear buffer
    clear();

    // initialize display
    sendOp(DISPLAYTEST, OFF);
    sendOp(SCANLIMIT, MAX_SCANLIMIT);
    sendOp(DECODEMODE, OFF);
    sendOp(SHUTDOWN, ON);
    sendOp(INTENSITY, MAX_INTENSITY);
}

void Renderer::render()
{
    for (int row = HEIGHT; row > 0; row--)
        renderRow(row);
}

void Renderer::renderRow(uint8_t row)
{
    // reverse output order vertically
    int index = FLIP_V ? HEIGHT - row : row - 1;
    send(dup(row), buffer[index], FLIP_H, INVERT);
}

uint32_t Renderer::dup(uint8_t value)
{
    uint32_t values = value;

    for (int i = 0; i < DEVICES - 1; i++)
        values = values << 8 | value;

    return values;
}

void Renderer::sendOp(uint8_t op, uint8_t value)
{
    send(dup(op), dup(value));
}

void Renderer::send(uint32_t ops, uint32_t values, uint8_t reverse, uint8_t invert)
{
    digitalWrite(CS_PIN, LOW);

    for (int i = DEVICES - 1; i >= 0; i--)
    {
        // shift out ops
        shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, ((uint8_t *)&ops)[i]);

        // shift out values
        // reverse output order horizontally
        // ON - shift out data lsb first & take opposite byte in int
        int index = reverse ? DEVICES - 1 - i : i;
        uint8_t bitOrder = reverse ? LSBFIRST : MSBFIRST;
        uint8_t value = ((uint8_t *)&values)[index];

        shiftOut(DATA_PIN, CLK_PIN, bitOrder, invert ? ~value : value);
    }

    digitalWrite(CS_PIN, HIGH);
}
