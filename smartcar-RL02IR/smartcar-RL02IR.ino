//www.elegoo.com

//Verbesserungsvorschlag:
// nur leicht rechts und leicht links
// verhindert ausbrechen und lernt schneller

#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

#include <IRremote.h>

////////// IR REMOTE CODES //////////
#define F 16736925  // FORWARD
#define B 16754775  // BACK
#define L 16720605  // LEFT
#define R 16761405  // RIGHT
#define GOSLEEP 16712445  // GOSLEEP
#define UNKNOWN_F 5316027     // FORWARD
#define UNKNOWN_B 2747854299  // BACK
#define UNKNOWN_L 1386468383  // LEFT
#define UNKNOWN_R 553536955   // RIGHT
#define GOSLEEP1 3622325019  // GOSLEEP

#define RECV_PIN  12  //IR-PIN

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;

int Echo = A4;  
int Trig = A5; 
double x1, x2, alpha, alpha_opt1, distance1 , alpha_opt2, distance2, alpha_opt, distance;
double pol_mat [5][6]; // 5 Zuataende, 6 Aktionen
double distance_t0;
int epsilon;
int go_sleep=0;

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 150
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
//  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
//  Serial.println("Back");
}

void left() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
//  Serial.println("Left");
}

void right() {
  analogWrite(ENA, 195);  //Damit links und rechtsdrehung übereinstimmen
  analogWrite(ENB, 195);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
//  Serial.println("Right");
}

void stop_Stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
//  Serial.println("Stop!");
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
                
  //Searches for shortest distance to wall and respective alpha_opt to wall
  //Two sweeps left-to-right and right-to-left, then average of both
  //Most stable result so far

  distance1=10000;
  for (int i1 = 1;i1<11; i1 ++) {
    alpha=40.0 + i1*10;
    myservo.write(alpha);
    
    check_IR();
    
    delay(1000);
    x1 = 0.0;
    for (int i2 = 1;i2<4; i2 ++) {
      x1 += watch();
      delay(70);
    }
    x1 /= 3.0;    
    if (x1<distance1) {
      distance1 = x1;
      alpha_opt1=alpha;
     }
  }
  
  distance2=10000;
  for (int i1 = 1;i1<11; i1 ++) {
    alpha=140.0 - i1*10;
    myservo.write(alpha);

    check_IR();
    
    delay(1000);
    x1 = 0.0;
    for (int i2 = 1;i2<4; i2 ++) {
      x1 += watch();
      delay(70);
    }
    x1 /= 3.0;    
    if (x1<distance2) {
      distance2 = x1;
      alpha_opt2=alpha;
     }
  }
  distance = (distance1 + distance2 )/2.0;
  alpha_opt = (alpha_opt1 + alpha_opt2 )/2.0;
  
  Serial.println(alpha_opt); 
  Serial.println(distance); 
}

void actionSpace(int as1) {  
  
// Defines possibel actions of vehicle
  
    Serial.println(as1); 

  switch (as1) {
  case 1:     // stark nach links
    left();
    delay(400);
    break;
  case 2:     // stark nach rechts
    right();
    delay(400);
    break;
  case 3:    // leicht nach links
    left();
    delay(200);
    break;
  case 4:     //leicht nach rechts
    right();
    delay(200);
    break;
  case 5:    // Geradeaus
    break;
  case 6:    // Rückwärts
    back();
    delay(400);
    break;
  }
  stop_Stop();
  delay(500);
  forward();
  delay(200);
  stop_Stop();
}

void policy() {
  
// Either random action or determistic best action for respecitve state
// State defined as alpha_opt to wall
  int s_t, a_t;
  int random_number = random(0,100);  // Random number between 0 and 100

    if(alpha_opt > 80 && alpha_opt < 100 ) {  // Zustand 1
      s_t = 0;
    }
    else if(alpha_opt >= 100 && alpha_opt <= 120) {  // Zustand 2
       s_t = 1;
    }
    else if(alpha_opt >= 60 && alpha_opt <= 80) {  // Zustand 3
       s_t = 2;
    }
    else if(alpha_opt > 120) {  // Zustand 4
       s_t = 3;
    }
    else if(alpha_opt < 60) {  // Zustand 5
       s_t = 4;
    }
 
    if (random_number < epsilon) {  // Zufaellige Aktion
      a_t = random(0,5);
    }
    else {  // do best known action
      a_t = search_max(s_t);
    }
     actionSpace(a_t);
     reward(a_t, s_t);
     epsilon--;
}

void dump_pol_mat() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      Serial.print( pol_mat[i][j] );
      Serial.print( " ");
      }    
      Serial.println();
    }  
  }
  
void reward(int a_t, int s_t) {
  double delta = distance_t0 - distance;
  pol_mat[s_t][a_t] = delta;  

  distance_t0 = distance;
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
  
  pinMode(13, OUTPUT);
  
  stop_Stop();
  
  irrecv.enableIRIn();  

  epsilon = 100;
  watchsurrounding();
  distance_t0 = distance;
} 

void check_IR() {
  if (irrecv.decode(&results)){ 
      val = results.value;
      irrecv.resume();
      if (val==GOSLEEP){
        go_sleep=1;
      }
  }     
}

void loop() { 

  dump_pol_mat();
  watchsurrounding();
  policy();   
  
  if (go_sleep==1) {
    go_sleep=0;
//    delay(10000);
    for(int i = 0; i < 11; i++) {
       digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
       delay(500);                       // wait for a second
       digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
       delay(500);  
    }
    watchsurrounding();
    distance_t0 = distance;
  }
  
}

