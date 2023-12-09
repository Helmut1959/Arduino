//www.elegoo.com
//2016.12.08

int buzzer = 12;//the pin of the active buzzer
int buttonApin = 9;

void setup()
{
 pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
 pinMode(buttonApin, INPUT_PULLUP);  
}

void loop()
{

if  (digitalRead(buttonApin) == LOW)
{ 
    digitalWrite(buzzer,HIGH);
    delay(300);
    digitalWrite(buzzer,LOW);
    delay(200);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(200);   
  
} 
} 
