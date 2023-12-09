//www.elegoo.com

#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

char getstr; // for BLE

int Echo = A4;  
int Trig = A5; 
double alpha_opt, distance, distance_t0;
double pol_mat [5][6]; // 5 Zuataende, 6 Aktionen
int epsilon;
boolean go_sleep=false;
boolean dump_mat=false;
boolean eps_reset=false;

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 150

void forward(){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
}

void right() {
  analogWrite(ENA, 195);  //Damit links und rechtsdrehung übereinstimmen
  analogWrite(ENB, 195);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop_Stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
} 

//Ultrasonic distance measurement Sub function
int watch() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  

void watchsurrounding(){     
double x1, alpha, alpha_opt1, distance1 , alpha_opt2, distance2;
                
  //Searches for shortest distance to wall and respective alpha_opt to wall
  //Two sweeps left-to-right and right-to-left, then average of both
  //Most stable result so far

  distance1=10000.0;
  for (int i1 = 1;i1<=14; i1 ++) {
    check_BLE();    
    alpha = i1*12;
    myservo.write(alpha);
    delay(850);
    x1 = watch();
//    Serial.print(String (x1,1)); 
//    delay(70);
    if (x1<distance1) {
      distance1 = x1;
      alpha_opt1=alpha;
     } 
 }
  
  distance2=10000.0;
  for (int i1 = 1;i1<=13; i1 ++) {
    check_BLE();
    alpha=168.0 - i1*12;
    myservo.write(alpha);
    delay(850);
    x1 = watch();
//    Serial.print(String (x1,1)); 
//    delay(70);
    if (x1<distance2) {
      distance2 = x1;
      alpha_opt2=alpha;
     }
  }
  
  distance = (distance1 + distance2 )/2.0;
  alpha_opt = (alpha_opt1 + alpha_opt2 )/2.0;
  
  Serial.print("A / D: " + String (alpha_opt,1) + " " + String (distance,1)); 
  delay(100);
}

void actionSpace(int as1) {   
// Defines possibel actions of vehicle
 
  switch (as1) {
  case 0:     // stark nach links
    left();
    Serial.println("A: Left");
    delay(300);
    break;
  case 1:     // stark nach rechts
    right();
    Serial.println("A: Right");
    delay(300);
    break;
  case 2:    // leicht nach links
    left();
    Serial.println("A: Slight Left");
    delay(150);
    break;
  case 3:     //leicht nach rechts
    right();
    Serial.println("A: Slight Right");
    delay(150);
    break;
  case 4:    // Geradeaus
    Serial.println("A: Forward");
    delay(150);
    break;
  case 5:    // Rückwärts
    back();
    Serial.println("A: Back");
    delay(400);
    break;
  }
  stop_Stop();
  delay(100);
  forward();
  delay(100);
  stop_Stop();
  delay(500);
}

void policy() {
  
// Either random action or determistic best action for respecitve state
// State defined as alpha_opt to wall
  int s_t, a_t;
  int random_number = random(0,100);  // Random number between 0 and 100

    if(alpha_opt > 80 && alpha_opt < 100 ) {  // Zustand 1
      s_t = 0;
      Serial.println("ST: Straight");
      delay(100);
    }
    else if(alpha_opt >= 100 && alpha_opt <= 120) {  // Zustand 2
       s_t = 1;
      Serial.println("ST: Slight Right");
      delay(100);
    }
    else if(alpha_opt >= 60 && alpha_opt <= 80) {  // Zustand 3
       s_t = 2;
      Serial.println("ST: Slight Left");
      delay(100);
    }
    else if(alpha_opt > 120 && alpha_opt <= 150) {  // Zustand 4
       s_t = 3;
      Serial.println("ST: Right");
      delay(100);
    }
    else if(alpha_opt < 60 && alpha_opt >= 30) {  // Zustand 5
       s_t = 4;
      Serial.println("ST: Left ");
      delay(100);
    }

    if (alpha_opt < 30 ) {  //Abfangen, wenn zu weit links
      s_t = 5;
      right();
      delay(300);
      stop_Stop();
      Serial.println("OR: Left ");
      delay(100);
      watchsurrounding();
      distance_t0 = distance;
    }
    if (alpha_opt > 150) {  //Abfangen, wenn zu weit rechts
      s_t = 5;
      left();
      delay(300);
      stop_Stop();
      Serial.println("OR: Right ");
      delay(100);
      watchsurrounding();
      distance_t0 = distance;
    }
    
    if (s_t < 5 )  {    //Ausführen nur wenn valider Zustand (0..4)
      if (random_number < epsilon) {  // Zufaellige Aktion
        a_t = random(0,6);    //Zufallszahlen 0..5
        Serial.println("Random ");
      }
      else {  // do best known action
        a_t = search_max(s_t);
        Serial.println("Best ");
      }
       delay(100);
       actionSpace(a_t);
       reward(a_t, s_t);
       epsilon--;
    }
}

void dump_pol_mat() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {      
      Serial.print(String (pol_mat[i][j], 1 ));
          delay(100);
      }    
      Serial.println(" ");
          delay(100);
    }  
}

void reward(int a_t, int s_t) {
  distance_t0 = distance;
  watchsurrounding();  
  double delta = distance_t0 - distance;
  pol_mat[s_t][a_t] = (pol_mat[s_t][a_t] + delta) / 2.0;  // Nur 50% der neuen Info zum Update verwenden
}

int search_max(int s_t) {
  double max_wert = 0.0;
  int a_best = 0;
  for(int i = 0; i < 6; i++) {
    if(pol_mat[s_t][i] > max_wert) {
      max_wert = pol_mat[s_t][i];
      a_best = i;
    }
  }
  return a_best;
}

void check_BLE() {
 getstr = Serial.read();
  if(getstr == 's'){
        go_sleep=true;    
        Serial.print("Sleep!"); 
        delay(100); 
  } 
  else if  (getstr == 'd'){
        dump_mat=true;    
        Serial.print("Dump Matrix!");  
        delay(100);
  }  
  else if  (getstr == 'e'){
        eps_reset =true;    
        Serial.print("Reset Eps!");  
        delay(100);
  }      
}

void setup() { 
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(13, OUTPUT);  //onboard LED  
  stop_Stop();  
  epsilon = 100;
  watchsurrounding();
  distance_t0 = distance;
} 

void loop() { 

  policy();   
  //watchsurrounding();

  if (dump_mat) {
      dump_mat=false;
      dump_pol_mat();
  }  

  if (eps_reset) {
      epsilon +=10;
      eps_reset = false;
      Serial.print("Epsilon: " + String (epsilon,0)); 
      delay(100);
    }
  
  if (go_sleep) {
    delay(200);               
    Serial.print("Sleeping!");  
    go_sleep=false;
    for(int i = 0; i < 11; i++) {
       digitalWrite(13, HIGH);   
       delay(500);               
       digitalWrite(13, LOW);    
       delay(500);  
    }
    Serial.print("Awake!");  
    watchsurrounding();
    distance_t0 = distance;
  }
  
}

