//www.elegoo.com
//2016.12.9

int tDelay = 200;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595

byte leds = 0;

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  leds = 0;
  updateShiftRegister();
  delay(tDelay);
}

void clearlight()
{
  leds = 0;
  updateShiftRegister();
  delay(tDelay);
}

void runlight01()
{
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
}
void runlight02()
{
  for (int i = 7; i >= 0; i--)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
}

void blinky01()
{
  for (int i = 0; i < 8; i++)
  {
    leds = B10101010;
    updateShiftRegister();
    delay(tDelay);
    leds = B01010101;
    updateShiftRegister();
    delay(tDelay);
  }
}

void blinky02()
{
  for (int i = 0; i < 8; i++)
  {
    leds = B00111100;
    updateShiftRegister();
    delay(tDelay);
    leds = B11000011;
    updateShiftRegister();
    delay(tDelay);
  }
}

void loop()
{
  runlight01();
  clearlight();
  runlight02();
  clearlight();
  blinky01();
  clearlight();
  blinky02();
  clearlight();
  blinky01();
  clearlight();
}

