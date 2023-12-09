//www.elegoo.com

#define LED 13    //Define 13 pin for LED
bool state = LOW; //The initial state of the function is defined as a low level
char getstr;      //Defines a function that receives the Bluetooth character
double test=3.1415;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

//Control LED sub function
void stateChange() {
  state = !state; 
  digitalWrite(LED, state);  
}

void loop() {
  //The Bluetooth serial port to receive the data in the function
  getstr = Serial.read();
  if(getstr == 'a'){
    stateChange();
    String stringOne =  String(test, 3) + " " +  String(test, 3) ;  
    Serial.print(stringOne);  
    delay(100);
    Serial.print(test , 3);  
    delay(100);
    Serial.print(String(test, 3));  
    delay(100);
  }
}
