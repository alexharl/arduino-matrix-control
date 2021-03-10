#include <Control.h>
#include <TextLayer.h>

#define CS_PIN 53
#define DATA_PIN 50
#define CLK_PIN 52

TextLayer layer_0;
Layer layer_1;
Layer layer_2;

#define NUM_LAYERS 3
Layer *layers[NUM_LAYERS];
Control matrix(layers, NUM_LAYERS, 60);

void setup()
{
  Serial.begin(115200);
  layers[0] = &layer_0;
  layers[1] = &layer_1;
  layers[2] = &layer_2;
  matrix.setPins(DATA_PIN, CLK_PIN, CS_PIN);
  matrix.init();
}

void loop()
{
  matrix.tick();
  line_effect();
  draw_counter();
  write_input();
}

int incomingByte = 0;
int byteNum = 0;
int rowNum = 0;
uint32_t allBytes = 0;
bool reading = false;
void write_input() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (!reading && incomingByte == 60) {
      reading = true;
      layer_2.clear();
      // start
      byteNum = 0;
      allBytes = 0;
    } else if (reading) {
      if (byteNum != 0) {
        allBytes <<= 8;  
      }
      allBytes |= incomingByte;
      byteNum++;
      if (byteNum >= 4) {
        byteNum = 0;
        layer_2.modify_buffer_row(OVERWRITE, rowNum, allBytes);
        allBytes = 0;
        rowNum++;
        if (rowNum >= 8) {
          rowNum = 0;
          byteNum = 0;
          reading = false;
        }
      }
    }
  }
}

int last = 0;
unsigned long last_line_effect = 0;
int line_effect_refresh = 50;
void line_effect() {
  if (last_line_effect == 0){
    layer_1.WARPAROUND = 0;
  }
  // line effect
  if (millis() - last_line_effect >= line_effect_refresh)
  {
    last_line_effect += line_effect_refresh;
    
    layer_1.move(1);
    int next = random(0, 3);
    int value = last;
    if (next == 1)
      value += 1;
    else if (next == 2)
      value -= 1;

    if (value < 0)
      value = 0;
    else if (value > 7)
      value = 7;
      
    layer_1.buffer[value] |= 0b10000000000000000000000000000000;  
    last = value;
  }
}

int counter = 1800;
uint32_t last_render = 0;
int count_delay = 100;
int count_float = 1;
void draw_counter() {
    uint32_t t = millis();
    if (last_render == 0 || t - last_render >= count_delay)
    {
        last_render += last_render == 0 ? t : count_delay;
        layer_0.draw_number(counter, count_float);
        counter++;
        if (counter == 10000) {
          counter = 0;
        }
    }
  }