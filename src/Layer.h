#ifndef Layer_h
#define Layer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Helper.h"

#define MAX_H 8
#define MAX_W 32
class Layer
{

public:
  uint8_t offset_top = 0;
  uint8_t offset_right = 0;

  uint8_t WIDTH;
  uint8_t HEIGHT;

  Layer(uint8_t width = MAX_W, uint8_t height = MAX_H, uint8_t top = 0, uint8_t right = 0);

  /**
   * move overflown bits to the other side on move
   */
  uint8_t WARPAROUND = 1;

  /**
   * when applying this layer you may check if 0 bits should be forced
   */
  uint8_t TRANSPARENT = 1;

  /**
   * buffer
   */
  uint32_t buffer[MAX_H];

  /**
   * clears the buffer
   * Shorthand for: bufferOp(CLEAR)
   */
  void clear();

  /**
   * sets data in buffer
   * Shorthand for: bufferOp(write data)
   */
  void apply(Layer *src);

  /**
   * shifts buffer 'amount' bits horizontaly
   * shifts right for positive, left for negative values
   * \param amount shift size
   */
  void move(int amount);

  /**
   * loads a sprite with offsets into buffer
   */
  void sprite(uint8_t *data, int top = 0, int right = 0);

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