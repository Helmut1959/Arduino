//www.elegoo.com
//2016.12.08

#include "pitches.h"
 
// notes in the melody:
int melody[] = {
 NOTE_G4,
NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
NOTE_D4, NOTE_F4, NOTE_B3,
NOTE_C4
};
int duration = 500;  // 500 miliseconds
 
void setup() {
 
}
 
void loop() {  
  for (int thisNote = 0; thisNote < 27; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(8, melody[thisNote], duration);
     
    // Output the voice after several minutes
    delay(500);
  }
   
  // restart after two seconds 
  delay(2000);
}
