#include <Renderer.h>
#include <Layer.h>

#define CS_PIN 53
#define DATA_PIN 50
#define CLK_PIN 52

// arrow right
uint32_t sprite_0[8] = {0xe0, 0x70, 0x38, 0x1c, 0xe, 0x1c, 0x38, 0x70};

// arrow left
uint32_t sprite_1[8] = {0x7, 0xe, 0x1c, 0x38, 0x70, 0x38, 0x1c, 0xe};

// vertical line
uint32_t sprite_2[8] = {1, 1, 1, 1, 1, 1, 1, 1};

// 22 small right
uint32_t sprite_3[8] = {
    0b00000000000000000001110111000111,
    0b00000000000000000000010001000001,
    0b00000000000000000001110111000111,
    0b00000000000000000000010100000100,
    0b00000000000000000001110111010111,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
};

// bottom squigly line
uint32_t sprite_4[8] = {
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000011000000100000000000000000,
    0b10000100100001010000001110110001,
    0b01111000111110001111111001001110,
};

Renderer renderer(DATA_PIN, CLK_PIN, CS_PIN);

Layer layer_0;
Layer layer_1;

void setup()
{
    Serial.begin(9600);
    renderer.render();

    layer_0.apply(sprite_3);
    layer_1.apply(sprite_4);
}

void loop()
{
    renderer.clear();

    renderer.apply(layer_0.buffer);
    renderer.apply(layer_1.buffer);

    renderer.render();

    layer_1.move(1);

    delay(20);
}
