#ifndef Layer_h
#define Layer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Helper.h"

#define HEIGHT 8

class Layer
{

public:
  /**
   * move overflown bits to the other side on move
   */
  uint8_t WARPAROUND = 1;

  /**
   * buffer
   */
  uint32_t buffer[HEIGHT];

  /**
   * clears the buffer
   * Shorthand for: bufferOp(CLEAR)
   */
  void clear();

  /**
   * sets data in buffer
   * Shorthand for: bufferOp(write data)
   */
  void apply(uint32_t *data);

  /**
   * shifts buffer 'amount' bits horizontaly
   * shifts right for positive, left for negative values
   * \param amount shift size
   */
  void move(int amount);

  /**
   * loads a sprite with offsets into buffer
   */
  void sprite(uint8_t *data, int offset_top = 0, int offset_right = 0);

private:
  /**
   * do something with complete buffer
   */
  void modify_buffer(modType_t mod, uint32_t *data);

  /**
   * do something with one buffer row only
   */
  void modify_buffer_row(modType_t mod, uint8_t row, uint32_t data);
};

#endif