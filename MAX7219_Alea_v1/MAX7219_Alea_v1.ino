//www.elegoo.com
//2016.12.9

//We always have to include the library
#include "LedControl.h"

/*
  pin 12 is connected to the DataIn of MAX72XX
  pin 11 is connected to LOAD(CS) of MAX72XX
  pin 10 is connected to the CLK of MAX72XX

  pin 9 is connected to the button
*/

LedControl lc = LedControl(12, 10, 11, 1);

unsigned long previous_time;
unsigned long current_time;
unsigned long delta_time;
long randNumber;
int buttonApin = 9;
boolean button_pushed;

void setup() {
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);

  randomSeed(analogRead(0));

  pinMode(buttonApin, INPUT_PULLUP);
}

void alea()  {
  randNumber = random(1, 7);
  switch (randNumber) {
    case 1:
      lc.setColumn(0, 3, B00011000);
      lc.setColumn(0, 4, B00011000);
      break;
    case 2:
      lc.setColumn(0, 0, B00000011);
      lc.setColumn(0, 1, B00000011);
      lc.setColumn(0, 6, B11000000);
      lc.setColumn(0, 7, B11000000);
      break;
    case 3:
      lc.setColumn(0, 0, B11000000);
      lc.setColumn(0, 1, B11000000);
      lc.setColumn(0, 3, B00011000);
      lc.setColumn(0, 4, B00011000);
      lc.setColumn(0, 6, B00000011);
      lc.setColumn(0, 7, B00000011);
      break;
    case 4:
      lc.setColumn(0, 0, B11000011);
      lc.setColumn(0, 1, B11000011);
      lc.setColumn(0, 6, B11000011);
      lc.setColumn(0, 7, B11000011);
      break;
    case 5:
      lc.setColumn(0, 0, B11000011);
      lc.setColumn(0, 1, B11000011);
      lc.setColumn(0, 3, B00011000);
      lc.setColumn(0, 4, B00011000);
      lc.setColumn(0, 6, B11000011);
      lc.setColumn(0, 7, B11000011);
      break;
    case 6:
      lc.setColumn(0, 0, B11000011);
      lc.setColumn(0, 1, B11000011);
      lc.setColumn(0, 3, B11000011);
      lc.setColumn(0, 4, B11000011);
      lc.setColumn(0, 6, B11000011);
      lc.setColumn(0, 7, B11000011);
      break;
  }
}

void loop() {
  if  (digitalRead(buttonApin) == LOW) {
    lc.clearDisplay(0);
    button_pushed = true;
  }
  if  ((digitalRead(buttonApin) == HIGH) && (button_pushed)) {
    button_pushed = false;
    previous_time = millis();
    alea();
  }

  current_time = millis();
  delta_time = (current_time - previous_time) / 1000;

  if (delta_time > 10) {
    lc.clearDisplay(0);
  }
}
