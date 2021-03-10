#include "Renderer.h"

Renderer::Renderer(Layer **_layers, int _num_layers, int _framerate)
{
    layers = _layers;
    num_layers = _num_layers;
    set_framerate(_framerate);
}

void Renderer::set_framerate(int f)
{
    frametime = 1000 / f;
}

void Renderer::render()
{
    clear();
    for (int i = 0; i < num_layers; i++)
        apply(layers[i]);
}

long Renderer::tick()
{
    uint32_t t = millis();
    if (last_render == 0 || t - last_render >= frametime)
    {
        last_render += last_render == 0 ? t : frametime;

        render();
        
        return millis() - t;
    }
    return -1;
}
