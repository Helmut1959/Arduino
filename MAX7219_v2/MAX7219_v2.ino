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
LedControl lc = LedControl(12, 10, 11, 1);

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

void write_A() {
  byte a[5] = {B01111110, B10001000, B10001000, B10001000, B01111110};
  lc.setRow(0, 2, a[0]);
  lc.setRow(0, 3, a[1]);
  lc.setRow(0, 4, a[2]);
  lc.setRow(0, 5, a[3]);
  lc.setRow(0, 6, a[4]);
}

void write_B() {
  byte b[5] = {B11111110, B10010010, B10010010, B10010010, B01101100};
  lc.setRow(0, 2, b[4]);
  lc.setRow(0, 3, b[3]);
  lc.setRow(0, 4, b[2]);
  lc.setRow(0, 5, b[1]);
  lc.setRow(0, 6, b[0]);
}

void write_E() {
  byte e[5] = {B11111110, B10010010, B10010010, B10010010, B00000000};
  lc.setRow(0, 2, e[4]);
  lc.setRow(0, 3, e[3]);
  lc.setRow(0, 4, e[2]);
  lc.setRow(0, 5, e[1]);
  lc.setRow(0, 6, e[0]);
}
void write_H() {
  byte h[5] = {B11111110, B00010000, B00010000, B00010000, B11111110};
  lc.setRow(0, 2, h[4]);
  lc.setRow(0, 3, h[3]);
  lc.setRow(0, 4, h[2]);
  lc.setRow(0, 5, h[1]);
  lc.setRow(0, 6, h[0]);
}

void write_I() {
  byte i[5] = {B00000000, B00000000, B11111110, B00000000, B00000000};
  lc.setRow(0, 2, i[4]);
  lc.setRow(0, 3, i[3]);
  lc.setRow(0, 4, i[2]);
  lc.setRow(0, 5, i[1]);
  lc.setRow(0, 6, i[0]);
}

void write_L() {
  byte l[5] = {B11111110, B00000010, B00000010, B00000010, B00000000};
  lc.setRow(0, 2, l[4]);
  lc.setRow(0, 3, l[3]);
  lc.setRow(0, 4, l[2]);
  lc.setRow(0, 5, l[1]);
  lc.setRow(0, 6, l[0]);
}

void write_M() {
  byte m[7] = {B11111110, B01000000, B00100000, B00111000, B00100000, B01000000, B11111110};
  lc.setRow(0, 0, m[6]);
  lc.setRow(0, 1, m[5]);
  lc.setRow(0, 2, m[4]);
  lc.setRow(0, 3, m[3]);
  lc.setRow(0, 4, m[2]);
  lc.setRow(0, 5, m[1]);
  lc.setRow(0, 6, m[0]);
}

void write_N() {
  byte n[6] = {B11111110, B00000100, B00011000, B00110000, B01000000, B11111110};
  lc.setRow(0, 1, n[0]);
  lc.setRow(0, 2, n[1]);
  lc.setRow(0, 3, n[2]);
  lc.setRow(0, 4, n[3]);
  lc.setRow(0, 5, n[4]);
  lc.setRow(0, 6, n[5]);
}

void write_P() {
  byte p[5] = {B11111110, B10010000, B10010000, B10010000, B01100000};
  lc.setRow(0, 2, p[4]);
  lc.setRow(0, 3, p[3]);
  lc.setRow(0, 4, p[2]);
  lc.setRow(0, 5, p[1]);
  lc.setRow(0, 6, p[0]);
}

void write_T() {
  byte t[5] = {B10000000, B10000000, B11111110, B10000000, B10000000};
  lc.setRow(0, 2, t[4]);
  lc.setRow(0, 3, t[3]);
  lc.setRow(0, 4, t[2]);
  lc.setRow(0, 5, t[1]);
  lc.setRow(0, 6, t[0]);
}

void write_X() {
  byte x[5] = {B11000110, B01101100, B00111000, B01101100, B11000110};
  lc.setRow(0, 2, x[4]);
  lc.setRow(0, 3, x[3]);
  lc.setRow(0, 4, x[2]);
  lc.setRow(0, 5, x[1]);
  lc.setRow(0, 6, x[0]);
}

void write_excl() {
  byte excl[5] = {B00000000, B00000000, B11110010, B00000000, B00000000};
  lc.setRow(0, 2, excl[0]);
  lc.setRow(0, 3, excl[1]);
  lc.setRow(0, 4, excl[2]);
  lc.setRow(0, 5, excl[3]);
  lc.setRow(0, 6, excl[4]);
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

void writeMaximilianOnMatrix() {
  write_M();  short_clear();
  write_A();  short_clear();
  write_X();  short_clear();
  write_I();  short_clear();
  write_M();  short_clear();
  write_I();  short_clear();
  write_L();  short_clear();
  write_I();  short_clear();
  write_A();  short_clear();
  write_N();  short_clear();
  write_excl();  very_short_clear();
  write_excl();  very_short_clear();
  write_excl();  very_short_clear();
  delay(delaytime1);
  delay(delaytime1);
}

void writePhilippOnMatrix() {
  // Alles Großbuchstaben:

  write_P();  short_clear();
  write_H();  short_clear();
  write_I();  short_clear();
  write_L();  short_clear();
  write_I();  short_clear();
  write_P();  short_clear();
  write_P();  short_clear();
  write_excl();  very_short_clear();
  write_excl();  very_short_clear();
  write_excl();  very_short_clear();

  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
  delay(delaytime1);
  delay(delaytime1);
}
void writeBabetteOnMatrix() {
  // Alles Großbuchstaben:

  write_B();  short_clear();
  write_A();  short_clear();
  write_B();  short_clear();
  write_E();  short_clear();
  write_T();  short_clear();
  write_T();  short_clear();
  write_E();  short_clear();

  delay(delaytime1);
  lc.clearDisplay(0);
  delay(delaytime1);
  delay(delaytime1);
  delay(delaytime1);
}

void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  byte a[5] = {B01111110, B10001000, B10001000, B10001000, B01111110};
  byte r[5] = {B00010000, B00100000, B00100000, B00010000, B00111110};
  byte d[5] = {B11111110, B00010010, B00100010, B00100010, B00011100};
  byte u[5] = {B00111110, B00000100, B00000010, B00000010, B00111100};
  byte i[5] = {B00000000, B00000010, B10111110, B00100010, B00000000};
  byte n[5] = {B00011110, B00100000, B00100000, B00010000, B00111110};
  byte o[5] = {B00011100, B00100010, B00100010, B00100010, B00011100};

  /* now display them one by one with a small delay */
  lc.setRow(0, 0, a[0]);
  lc.setRow(0, 1, a[1]);
  lc.setRow(0, 2, a[2]);
  lc.setRow(0, 3, a[3]);
  lc.setRow(0, 4, a[4]);
  delay(delaytime1);
  lc.setRow(0, 0, r[0]);
  lc.setRow(0, 1, r[1]);
  lc.setRow(0, 2, r[2]);
  lc.setRow(0, 3, r[3]);
  lc.setRow(0, 4, r[4]);
  delay(delaytime1);
  lc.setRow(0, 0, d[0]);
  lc.setRow(0, 1, d[1]);
  lc.setRow(0, 2, d[2]);
  lc.setRow(0, 3, d[3]);
  lc.setRow(0, 4, d[4]);
  delay(delaytime1);
  lc.setRow(0, 0, u[0]);
  lc.setRow(0, 1, u[1]);
  lc.setRow(0, 2, u[2]);
  lc.setRow(0, 3, u[3]);
  lc.setRow(0, 4, u[4]);
  delay(delaytime1);
  lc.setRow(0, 0, i[0]);
  lc.setRow(0, 1, i[1]);
  lc.setRow(0, 2, i[2]);
  lc.setRow(0, 3, i[3]);
  lc.setRow(0, 4, i[4]);
  delay(delaytime1);
  lc.setRow(0, 0, n[0]);
  lc.setRow(0, 1, n[1]);
  lc.setRow(0, 2, n[2]);
  lc.setRow(0, 3, n[3]);
  lc.setRow(0, 4, n[4]);
  delay(delaytime1);
  lc.setRow(0, 0, o[0]);
  lc.setRow(0, 1, o[1]);
  lc.setRow(0, 2, o[2]);
  lc.setRow(0, 3, o[3]);
  lc.setRow(0, 4, o[4]);
  delay(delaytime1);
  lc.setRow(0, 0, 0);
  lc.setRow(0, 1, 0);
  lc.setRow(0, 2, 0);
  lc.setRow(0, 3, 0);
  lc.setRow(0, 4, 0);
  delay(delaytime1);
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
}

void loop() {
//  writeMaximilianOnMatrix();
//  writeBabetteOnMatrix();
  writePhilippOnMatrix();
  //  writeArduinoOnMatrix();
  //  rows();
  //  columns();
  //  single();
}
