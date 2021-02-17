#ifndef Layer_h
#define Layer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

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
  uint32_t buffer[8];

  /**
   * clears the buffer
   * Shorthand for: bufferOf(CLEAR)
   */
  void clear();

  /**
   * sets data in buffer
   * Shorthand for: bufferOf(CLEAR)
   */
  void apply(uint32_t data[8]);

  /**
   * shifts buffer 'amount' bits horizontaly
   * shifts right for positive, left for negative values
   * \param amount shift size
   */
  void move(int amount);

private:
  /**
   * do something with buffer
   */
  void bufferOp(bufferOpType_t bOp, uint32_t *data);
};

#endif