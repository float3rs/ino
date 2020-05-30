const int buzzerPin = 7;
const int buttonPin = 6;
const int redPin = 4;
const int yellowPin = 3;
const int greenPin = 2;

int buttonState = 0; 
int i = 0;

void setup()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop()
{
  
  buttonState = digitalRead(buttonPin);
  digitalWrite(redPin,LOW);
  digitalWrite(yellowPin,LOW);
  digitalWrite(greenPin,LOW);

  if (buttonState == HIGH)
  {
    digitalWrite(buzzerPin,HIGH);
    delay(1);
    digitalWrite(buzzerPin,LOW);
    delay(1);
    digitalWrite(redPin,HIGH);
    digitalWrite(yellowPin,HIGH);
    digitalWrite(greenPin,HIGH);

    
  }
}
