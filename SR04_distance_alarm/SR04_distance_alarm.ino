//www.elegoo.com
//2016.12.08

#include "SR04.h"
#include "pitches.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define ALARM_PIN 8


SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;
//int duration = 500;

void setup() {
  Serial.begin(9600);
  delay(500);
}

void loop() {
  a = sr04.Distance();
  Serial.print(a);
  Serial.println("cm");

  if (a < 10) {
    tone(ALARM_PIN, NOTE_G5, 100);
    delay(100);
  } else if (a < 30) {
    tone(ALARM_PIN, NOTE_E5, 300);
    delay(300);
  } else if (a < 50) {
    tone(ALARM_PIN, NOTE_C5, 500);
    delay(500);
  } else {
    delay(1000);
  }
}

