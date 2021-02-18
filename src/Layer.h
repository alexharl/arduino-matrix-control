#ifndef Layer_h
#define Layer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define HEIGHT 8
class Layer
{

public:
  /**
   * Ops that can be performed on the buffer via bufferOp
   */
  enum bufferOpType_t
  {
    CLEAR = 1,
    WRITE = 2,
    OVERWRITE = 3
  };

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
  void apply(uint32_t data[HEIGHT]);

  /**
   * shifts buffer 'amount' bits horizontaly
   * shifts right for positive, left for negative values
   * \param amount shift size
   */
  void move(int amount);

  void sprite(uint8_t *data, int offset_top, int offset_right);

private:
  /**
   * do something with buffer
   */
  void bufferOp(bufferOpType_t bOp, uint32_t *data);

  void bufferRowOp(bufferOpType_t bOp, uint8_t row, uint32_t data);
};

#endif