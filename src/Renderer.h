#ifndef Renderer_h
#define Renderer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Layer.h>

class Renderer : public Layer
{
private:
  uint32_t dup(uint8_t value);
  void sendOp(uint8_t op, uint32_t values);
  void sendOpAll(uint8_t op, uint8_t value);
  void send(uint32_t ops, uint32_t values);
  uint8_t DATA_PIN;
  uint8_t CLK_PIN;
  uint8_t CS_PIN;

public:
  Renderer(int dataPin, int clkPin, int csPin);
  void render();
  enum renderOp_t
  {
    DECODEMODE = 9,
    INTENSITY = 0xa,
    SCANLIMIT = 0xb,
    SHUTDOWN = 0xc,
    DISPLAYTEST = 0xf
  };
  enum opVals_t
  {
    OFF = 0,
    ON = 1,
    MAX_INTENSITY = 0xf,
    MAX_SCANLIMIT = 7
  };
};

#endif