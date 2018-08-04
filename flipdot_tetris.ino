#include <FlipDot_5x7.h>

//ESP32
#define CLOCK 18//SH_CP
#define DATA  23//DS
#define LATCH 19//ST_CP

FlipDot_5x7 flipdot(2, 5, false);

void setup() {
  Serial.begin(19200);
  Serial.println("Reset");
  flipdot.setPulseWidth(500);
  flipdot.begin(DATA, CLOCK, LATCH);
  flipdot.setTextColor(FLIPDOT_YELLOW, FLIPDOT_BLACK);

  
  flipdot.fillScreen(FLIPDOT_YELLOW);
  flipdot.display();
  delay(500);
  flipdot.fillScreen(FLIPDOT_BLACK);
  flipdot.display();
  delay(500);
  
  tetris_setup();
}

void loop() {
  tetris_loop();
  RefreshDisplay();
}
