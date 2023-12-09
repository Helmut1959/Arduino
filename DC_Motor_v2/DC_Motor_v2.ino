//Helmut Schafer
// 2018.01.20
//--------------------------------------------

#define ENABLE 5
#define DIRA 3
#define DIRB 4

int i;
int PWM_level;

void setup() {

  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // Richtung festlegen
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);

  for (i = 0; i < 10; i++) {
    delay(500);
    PWM_level = i * 20;
    digitalWrite(ENABLE, PWM_level);
    Serial.println(PWM_level);
    delay(500);
  }

  // Pause
  delay(2000);

  for (i = 10; i > 1; i--) {
    delay(500);
    PWM_level = i * 20;
    digitalWrite(ENABLE, PWM_level);
    Serial.println(PWM_level);
    delay(500);
  }

  // Pause
  delay(2000);

}

