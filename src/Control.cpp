#include "Control.h"
#include "Helper.h"

Control::Control(Layer **layers, long num_layers, int framerate)
    : Renderer(layers, num_layers, framerate)
{
    FLIP_H = OFF;
    FLIP_V = OFF;
    INVERT = OFF;

    DEVICES = 4; // currently only matrix with 4 devices supported
}

long Control::tick()
{
    long t = Renderer::tick();
    if (t >= 0) print();
    return t;
}

void Control::setPins(int dataPin, int clkPin, int csPin)
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
}

void Control::init(int intensity)
{
    // clear buffer
    clear();

    // initialize display
    send_cmd(DISPLAYTEST, OFF);
    send_cmd(SCANLIMIT, MAX_SCANLIMIT);
    send_cmd(DECODEMODE, OFF);
    send_cmd(SHUTDOWN, ON);
    send_cmd(INTENSITY, intensity);
}

void Control::print()
{
    for (int row = HEIGHT; row > 0; row--)
        print_row(row);
}

void Control::print_row(uint8_t row)
{
    // reverse output vertically
    int index = FLIP_V ? HEIGHT - row : row - 1;

    uint32_t values = buffer[index];

    // reverse order horizontally
    if (FLIP_H)
        modify_bits(REVERSE, &values);

    // invert bits
    values = INVERT ? ~values : values;

    send(set_all_bytes(row), values);
}

void Control::send_cmd(uint8_t cmd, uint8_t value)
{
    send(set_all_bytes(cmd), set_all_bytes(value));
}

void Control::send(uint32_t cmds, uint32_t values)
{
    digitalWrite(CS_PIN, LOW);

    // iterate devices from highest
    for (int i = DEVICES - 1; i >= 0; i--)
    {
        // shift out op byte at device index
        shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, ((uint8_t *)&cmds)[i]);

        // shift out value byte
        shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, ((uint8_t *)&values)[i]);
    }

    digitalWrite(CS_PIN, HIGH);
}