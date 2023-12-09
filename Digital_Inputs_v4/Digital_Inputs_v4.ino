//www.elegoo.com
//2016.12.08

int ledPin = 5;
int buttonApin = 9;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
}

void loop() 
{

if  (digitalRead(buttonApin) == LOW)
{
  if (digitalRead(ledPin) == LOW) 
  {
    digitalWrite(ledPin, HIGH);
  }
    else
    {
      digitalWrite(ledPin, LOW);
    }
    delay(1000);
  }
  
}
