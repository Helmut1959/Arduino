//www.elegoo.com
//2016.12.08

int ledPin = 5;
int buttonApin = 9;
bool status = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
}

void loop() 
{
 /* 
  if ( (digitalRead(buttonApin) == LOW) && (status == 0) )    
  {
    digitalWrite(ledPin, HIGH);
    status = 1;
    delay (1000);
  } 
    else if ( (digitalRead(buttonApin) == LOW) && (status == 1) )    
  {
    digitalWrite(ledPin, LOW);
    status = 0;    
    delay (1000);
  }
*/

if  (digitalRead(buttonApin) == LOW)
{
  if (status == 0) 
  {
    status = 1;
    digitalWrite(ledPin, HIGH);
  }
    else
    {
      status = 0;
      digitalWrite(ledPin, LOW);
    }
    delay(1000);
  }


  
}
