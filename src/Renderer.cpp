#include "Renderer.h"
#include <SPI.h>
#include "HardwareSerial.h"

#define DEVICES 8
#define HEIGHT 8

#define LAST(k, n) ((k) & ((1 << (n)) - 1))
#define MID(k, m, n) LAST((k) >> (m), ((n) - (m)))
#define OUT(v, s, e) (shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, MID(v, s, e)))

Renderer::Renderer(int dataPin, int clkPin, int csPin)
{
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
    sendOpAll(DISPLAYTEST, OFF);
    sendOpAll(SCANLIMIT, MAX_SCANLIMIT);
    sendOpAll(DECODEMODE, OFF);
    sendOpAll(SHUTDOWN, ON);
    sendOpAll(INTENSITY, MAX_INTENSITY);
}

void Renderer::render()
{
    for (int row = 1; row <= HEIGHT; row++)
        send(dup(row), buffer[row - 1]);
}

uint32_t Renderer::dup(uint8_t value)
{
    uint32_t values = value;
    for (int i = 0; i < DEVICES - 1; i++)
        values = values << 8 | value;

    return values;
}

void Renderer::sendOp(uint8_t op, uint32_t values)
{
    send(dup(op), values);
}

void Renderer::sendOpAll(uint8_t op, uint8_t value)
{
    sendOp(op, dup(value));
}

void Renderer::send(uint32_t ops, uint32_t values)
{
    digitalWrite(CS_PIN, LOW);
    for (int device = DEVICES; device > 0; device--)
    {
        int offset_low = (device - 1) * HEIGHT;
        int offset_high = offset_low + 8;

        OUT(ops, offset_low, offset_high);
        OUT(values, offset_low, offset_high);
    }
    digitalWrite(CS_PIN, HIGH);
}
