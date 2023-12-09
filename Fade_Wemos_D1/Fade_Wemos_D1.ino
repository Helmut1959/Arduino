/*
 Fade

 This example fades the on-board LED on the 
 Wemos D1 development board using the 
 analogWrite() function.

 Created by Addicore LLC, https://www.addicore.com/
 */

#define led  BUILTIN_LED  // the pin that the ESP-12 built in LED is attached to
int brightness = 0;       // variable to store the LED's brightness
int fadeAmount = 2;       // how much to fade the LED by each time through the loop

// the setup routine runs once when you press reset:
void setup() {
  pinMode(led, OUTPUT);   // declare led pin to be an output
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of the LED:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness > PWMRANGE) {
    fadeAmount = -fadeAmount ;
  }
  // small delay
  delay(1);
}

