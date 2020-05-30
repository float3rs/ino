#define PASSLENGHT 4


#include <Keypad.h>

const byte ROWS = 1; 
const byte COLS = 4; 

char keys[ROWS][COLS] = 
{
  {'1', '2', '3', '4'}
};

byte rowPins[ROWS] = {1};
byte colPins[COLS] = {8,9,11,12};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );;

const int rPin = 2;
const int gPin = 3;
const int bPin = 4;
const int yPin = 5;

const int switchPin = 6;
const int buzzerPin = 7;

int buttonState = 0;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(yPin, OUTPUT);

  pinMode(switchPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

}

void loop() 
{
  // put your main code here, to run repeatedly:

  char key = keypad.getKey();
 
  if (key)
  {
    Serial.println(key);
  }
  
  

}
