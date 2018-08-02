#include <FlipDot_5x7.h>

//ESP32
#define CLOCK 18//SH_CP
#define DATA  23//DS
#define LATCH 19//ST_CP

FlipDot_5x7 flipdot(2, 3, false);

const char* text = "Hello, World!!";

void setup() {
  Serial.begin(19200);
  flipdot.begin(DATA, CLOCK, LATCH);
  flipdot.setTextColor(FLIPDOT_YELLOW, FLIPDOT_BLACK);
  tetris_setup();
}

void loop() {
  tetris_loop();
  RefreshDisplay();
}
