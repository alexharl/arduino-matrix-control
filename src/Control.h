#ifndef Control_h
#define Control_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Renderer.h>
class Control : public Renderer
{

public:
    Control(Layer **layers, long num_layers, int framerate = 30);

    void setPins(int dataPin, int clkPin, int csPin);

    void init(int intensity = 1);

    long tick();
    /**
   * renders complete buffer
   */
    void print();

    /**
   * renders a single row
   */
    void print_row(uint8_t row);

    // flip rows on render (vertical)
    uint8_t FLIP_V;

    // flip bits on render (horizontal)
    uint8_t FLIP_H;

    // invert bits on render
    uint8_t INVERT;

    enum deviceCmd_t
    {
        DECODEMODE = 9,
        INTENSITY = 0xa,
        SCANLIMIT = 0xb,
        SHUTDOWN = 0xc,
        DISPLAYTEST = 0xf
    };

    enum cmdVals_t
    {
        OFF = 0,
        ON = 1,
        MAX_INTENSITY = 0xf,
        MAX_SCANLIMIT = 7
    };
    /**
   * sends a command to all devices
   */
    void send_cmd(uint8_t cmd, uint8_t value);

    /**
   * sends multiple commands with multiple values
   */
    void send(uint32_t cmds, uint32_t values);

private:
    // pin where data will be transmitted
    uint8_t DATA_PIN;

    // clock
    uint8_t CLK_PIN;

    // chip select
    uint8_t CS_PIN;

    // number of connected devices
    uint8_t DEVICES;
};

#endif