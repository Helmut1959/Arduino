//www.elegoo.com
//2016.12.9

#include <LiquidCrystal.h>
#include "SR04.h"

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//         ECHO_PIN TRIG_PIN
SR04 sr04 = SR04(3, 2);
long a;

void setup()
{
  lcd.begin(16, 2);
}

void loop()
{
  lcd.setCursor(0, 0);
  a = sr04.Distance();
  lcd.print("Distance    cm  ");
  lcd.setCursor(9, 0);
  lcd.print(a);
  delay(500);
}