//www.elegoo.com
//2016.12.12

int latchpin = 9; //74HC595  pin 9 STCP
int clockpin = 10; //74HC595  pin 10 SHCP
int datapin = 8; //74HC595  pin 8 DS
int d_time1 = 1000;

unsigned char table[] =
{ 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c
  , 0x39, 0x5e, 0x79, 0x71, 0x00
};
byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };
 

void setup() {
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
}

void Display(unsigned char num)
{
  digitalWrite(latchpin, LOW);
  shiftOut(datapin, clockpin, MSBFIRST, table[num]);
  digitalWrite(latchpin, HIGH);
}
void sevenSegWrite(byte digit) {
  digitalWrite(latchpin, LOW);
  shiftOut(datapin, clockpin, LSBFIRST, seven_seg_digits[digit]);  
  digitalWrite(latchpin, HIGH);
}
 
void loop() {
  
  for (int i = 1; i < 16; i++)
  {
    Display(i);
    delay(d_time1);
  }
  delay(d_time1);

  
}
