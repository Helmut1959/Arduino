//www.elegoo.com
//2016.12.12

/************************
  Exercise the motor using
  the L293D chip
************************/

#define ENABLE 5
#define DIRA 3
#define DIRB 4

int i;

void setup() {
  //---set pin direction
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  //---back and forth example
  Serial.println("One way, then reverse");
  digitalWrite(ENABLE, HIGH); // enable on
  Serial.println("An");
  for (i = 0; i < 5; i++) {
    Serial.println("Links");
    digitalWrite(DIRA, HIGH); //one way
    digitalWrite(DIRB, LOW);
    Serial.println("Aus");
    delay(3000);
  digitalWrite(ENABLE, LOW); // enable on
    Serial.println("Rechts");
    digitalWrite(DIRA, LOW); //reverse
    digitalWrite(DIRB, HIGH);
  digitalWrite(ENABLE, HIGH); // enable on
    delay(750);
  }
  digitalWrite(ENABLE, LOW); // enable on
  Serial.println("Aus");
  delay(3000);
}

