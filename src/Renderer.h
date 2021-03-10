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
  public:
    Layer **layers;
    int num_layers;
    uint32_t frametime;

    Renderer(Layer **_layers, int _num_layers, int _framerate = 30);

    void render();

    void set_framerate(int framerate);
    
    long tick();

  private:
    uint32_t last_render = 0;
};

#endif