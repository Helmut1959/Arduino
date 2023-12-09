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

LedControl lc = LedControl(3, 13, 10, 1);

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

/*
  This function lights up a some Leds in a row.
  The pattern will be repeated on every row.
  The pattern will blink along with the row-number.
  row number 4 (index==3) will blink 4 times etc.
*/
void rows() {
  for (int row = 0; row < 8; row++) {
    delay(delaytime2);
    lc.setRow(0, row, B10100000);
    delay(delaytime2);
    lc.setRow(0, row, (byte)0);
    for (int i = 0; i < row; i++) {
      delay(delaytime2);
      lc.setRow(0, row, B10100000);
      delay(delaytime2);
      lc.setRow(0, row, (byte)0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
  The pattern will be repeated on every column.
  The pattern will blink along with the column-number.
  column number 4 (index==3) will blink 4 times etc.
*/
void columns() {
  for (int col = 0; col < 8; col++) {
    delay(delaytime2);
    lc.setColumn(0, col, B10100000);
    delay(delaytime2);
    lc.setColumn(0, col, (byte)0);
    for (int i = 0; i < col; i++) {
      delay(delaytime2);
      lc.setColumn(0, col, B10100000);
      delay(delaytime2);
      lc.setColumn(0, col, (byte)0);
    }
  }
}

/*
  This function will light up every Led on the matrix.
  The led will blink along with the row-number.
  row number 4 (index==3) will blink 4 times etc.
*/
void single() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      delay(delaytime2);
      lc.setLed(0, row, col, true);
      delay(delaytime2);
      for (int i = 0; i < col; i++) {
        lc.setLed(0, row, col, false);
        delay(delaytime2);
        lc.setLed(0, row, col, true);
        delay(delaytime2);
      }
    }
  }
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);

}

void single2() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      delay(delaytime2);
      lc.setLed(0, row, col, true);
      delay(delaytime2);
    }
  }
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
}

void alea()  {
  //1:
  lc.setColumn(0, 3, B00011000);
  lc.setColumn(0, 4, B00011000);
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
  //2:
  lc.setColumn(0, 0, B00000011);
  lc.setColumn(0, 1, B00000011);
  lc.setColumn(0, 6, B11000000);
  lc.setColumn(0, 7, B11000000);
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
  //3:
  lc.setColumn(0, 0, B00000011);
  lc.setColumn(0, 1, B00000011);
  lc.setColumn(0, 3, B00011000);
  lc.setColumn(0, 4, B00011000);
  lc.setColumn(0, 6, B11000000);
  lc.setColumn(0, 7, B11000000);
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
  //4:
  lc.setColumn(0, 0, B11000011);
  lc.setColumn(0, 1, B11000011);
  lc.setColumn(0, 6, B11000011);
  lc.setColumn(0, 7, B11000011);
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
  //5:
  lc.setColumn(0, 0, B11000011);
  lc.setColumn(0, 1, B11000011);
  lc.setColumn(0, 3, B00011000);
  lc.setColumn(0, 4, B00011000);
  lc.setColumn(0, 6, B11000011);
  lc.setColumn(0, 7, B11000011);
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
  //6:
  lc.setColumn(0, 0, B11000011);
  lc.setColumn(0, 1, B11000011);
  lc.setColumn(0, 3, B11000011);
  lc.setColumn(0, 4, B11000011);
  lc.setColumn(0, 6, B11000011);
  lc.setColumn(0, 7, B11000011);
  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
  delay(delaytime1);
  delay(delaytime1);

}

void loop() {
  //  rows();
  //  columns();
  single2();
  // alea();
}
