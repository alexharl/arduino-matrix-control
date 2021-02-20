#include <Renderer.h>
#include <Layer.h>
#include <Number_Sprites.h>

#define CS_PIN 53
#define DATA_PIN 50
#define CLK_PIN 52

// arrow right
uint32_t sprite_0[8] = {0xe0, 0x70, 0x38, 0x1c, 0xe, 0x1c, 0x38, 0x70};

// arrow left
uint32_t sprite_1[8] = {0x7, 0xe, 0x1c, 0x38, 0x70, 0x38, 0x1c, 0xe};

// vertical line
uint32_t sprite_2[8] = {1,1,1,1,1,1,1,1};


// 32.2 small right
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
  
  layer_0.sprite(small_0); 
  layer_1.apply(sprite_4);
}

void loop()
{
  renderer.clear();
  
  renderer.apply(layer_0.buffer);
  renderer.apply(layer_1.buffer);
  
  renderer.render();
  
  layer_1.move(1);

  delay(10);
  draw_counter();
}

// test code - count to 99
int counter = 0;
int spriteNum = 0;
int spriteNum_1 = 0;
bool shouldInc = false;
bool shouldInc_1 = false;
void draw_counter() {
  if (shouldInc){
    shouldInc = false;
    layer_0.clear();

    if (spriteNum == 0) {
      layer_0.sprite(small_0);  
    } else if (spriteNum == 1) {
      layer_0.sprite(small_1);  
    } else if (spriteNum == 2) {
      layer_0.sprite(small_2);  
    } else if (spriteNum == 3) {
      layer_0.sprite(small_3);  
    } else if (spriteNum == 4) {
      layer_0.sprite(small_4);  
    } else if (spriteNum == 5) {
      layer_0.sprite(small_5);  
    } else if (spriteNum == 6) {
      layer_0.sprite(small_6);  
    } else if (spriteNum == 7) {
      layer_0.sprite(small_7);  
    } else if (spriteNum == 8) {
      layer_0.sprite(small_8);  
    } else if (spriteNum == 9) {
      layer_0.sprite(small_9);  
    }

    if (spriteNum_1 == 1) {
      layer_0.sprite(small_1, 0, 4);  
    } else if (spriteNum_1 == 2) {
      layer_0.sprite(small_2, 0, 4);  
    } else if (spriteNum_1 == 3) {
      layer_0.sprite(small_3, 0, 4);  
    } else if (spriteNum_1 == 4) {
      layer_0.sprite(small_4, 0, 4);  
    } else if (spriteNum_1 == 5) {
      layer_0.sprite(small_5, 0, 4);  
    } else if (spriteNum_1 == 6) {
      layer_0.sprite(small_6, 0, 4);  
    } else if (spriteNum_1 == 7) {
      layer_0.sprite(small_7, 0, 4);  
    } else if (spriteNum_1 == 8) {
      layer_0.sprite(small_8, 0, 4);  
    } else if (spriteNum_1 == 9) {
      layer_0.sprite(small_9, 0, 4);  
    }
  }

  counter++;
  if (counter > 50) {
    counter = 0;
    shouldInc = true;
    spriteNum++;
    if (spriteNum == 10) {
      spriteNum = 0;
      spriteNum_1++;
      if (spriteNum_1 == 10){
        spriteNum_1 = 0;
      }
    }
  }
}