//www.elegoo.com
//2016.12.9

//We always have to include the library
#include "LedControl.h"

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to LOAD(CS)
  pin 10 is connected to the CLK
  We have only a single MAX72XX.
*/
//LedControl lc = LedControl(12, 10, 11, 1);
LedControl lc = LedControl(3, 13, 10, 1);       //v3: DIN auf 3, CS auf 10, CLK auf 13 beim Osoyoo Car

/* we always wait a bit between updates of the display */
unsigned long delaytime1 = 200;
unsigned long delaytime2 = 50;

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
}

void short_clear() {
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
}

void very_short_clear() {
  delay(delaytime2);
  lc.clearDisplay(0);
  delay(delaytime2);
}

void single2() {

    lc.setLed(0, 3, 5, true);
    lc.setLed(0, 4, 5, true);

}

void loop() {

  single2();
}
