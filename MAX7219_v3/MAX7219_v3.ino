//www.elegoo.com
//2016.12.9

//We always have to include the library
#include "LedControl.h"
#include "IRremote.h"

int receiver = 9; // Signal Pin of IR receiver to Arduino Digital Pin 9
int counter = 0;

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to LOAD(CS)
  pin 10 is connected to the CLK
  We have only a single MAX72XX.
*/
LedControl lc = LedControl(12, 10, 11, 1);
//LedControl lc = LedControl(3, 13, 10, 1);       //v3: DIN auf 3, CS auf 10, CLK auf 13

/* we always wait a bit between updates of the display */
unsigned long delaytime1 = 200;
unsigned long delaytime2 = 50;

void translateIR() // takes action based on IR code received
// describing Remote IR codes
{
  switch (results.value)
  {
    case 0xFFA25D: Serial.println("POWER"); break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("FAST BACK");    break;
    case 0xFF02FD: Serial.println("PAUSE");    break;
    case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    case 0xFFE01F: Serial.println("DOWN");    break;
    case 0xFFA857: Serial.println("VOL-");    break;
    case 0xFF906F: Serial.println("UP");    break;
    case 0xFF9867: Serial.println("EQ");    break;
    case 0xFFB04F: Serial.println("ST/REPT");    break;
    case 0xFF6897: Serial.println("0"); counter = 0;   break;
    case 0xFF30CF: Serial.println("1"); counter = 1;    break;
    case 0xFF18E7: Serial.println("2"); counter = 2;   break;
    case 0xFF7A85: Serial.println("3"); counter = 3;   break;
    case 0xFF10EF: Serial.println("4");    break;
    case 0xFF38C7: Serial.println("5");    break;
    case 0xFF5AA5: Serial.println("6");    break;
    case 0xFF42BD: Serial.println("7");    break;
    case 0xFF4AB5: Serial.println("8");    break;
    case 0xFF52AD: Serial.println("9");    break;
    case 0xFFFFFFFF: Serial.println(" REPEAT"); break;
    default:
      Serial.println(" other button   ");
  }// End Case
  delay(500); // Do not get immediate repeat
} //END translateIR

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

  // für die Fernbedienung:
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver

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
}

void writePhilippOnMatrix() {
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
}

void writeBabetteOnMatrix() {
  write_B();  short_clear();
  write_A();  short_clear();
  write_B();  short_clear();
  write_E();  short_clear();
  write_T();  short_clear();
  write_T();  short_clear();
  write_E();  short_clear();
}

void loop() {

  if (irrecv.decode(&results)) // Fernbedienung wird nicht erkannt, solange Wort ausgegeben wird.
  {
    translateIR();
    Serial.print("Counter: ");
    Serial.println(counter);
    irrecv.resume(); // receive the next value
    if (counter == 0) {
      lc.clearDisplay(0);
    }
    if (counter == 1) {
      writeBabetteOnMatrix();
      counter = 0;
    }
    if (counter == 2) {
      writePhilippOnMatrix();
      counter = 0;
    }
    if (counter == 3) {
      writeMaximilianOnMatrix();
      counter = 0;
    }
  }

}
