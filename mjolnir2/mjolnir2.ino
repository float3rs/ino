#include <Keypad.h>
#include <MKRIMU.h>

#define PASSLENGHT 4

///////////////////////////////

const int rPin = 2;
const int gPin = 3;
const int bPin = 4;
const int yPin = 5;

const int buttonPin = 6;
const int buzzerPin = 7;

int buttonState = 0;

///////////////////////////////

const byte ROWS = 1; 
const byte COLS = 4; 

char keys[ROWS][COLS] = 
{
  {'1', '2', '3', '4'}
};

byte rowPins[ROWS] = {A4};
byte colPins[COLS] = {A3,A2,A1,A0};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );;

///////////////////////////////

float tolerance = 1.0; // sensitivity norm

boolean standby = true; // mjolnir standby
boolean calibrated = false; // accelerometer calibrated
boolean armed = false; // accelerometer armed
boolean detected = false; // motion detected

int cursor;
int passwordLength = 4;
char* password = "4321";

float minX; // minimum x-axis value
float maxX; // maximum x-axis value
float curX; // current x-axis value
float minY; // minimum y-axis value
float maxY; // maximum y-axis value
float curY; // current y-axis value
float minZ; // minimum z-axis value
float maxZ; // maximum z-axis value
float curZ; // current z-axis value

/////////////////////////////////////////////

void calibratePrint()
{
  Serial.print("minX = ");
  Serial.print(minX);
  Serial.print(" // ");
  Serial.print("maxX = ");
  Serial.print(maxX);
  Serial.println();

  Serial.print("minY = ");
  Serial.print(minY);
  Serial.print(" // ");
  Serial.print("maxY = ");
  Serial.print(maxY);
  Serial.println();

  Serial.print("minZ = ");
  Serial.print(minZ);
  Serial.print(" // ");
  Serial.print("maxZ = ");
  Serial.print(maxZ);
  Serial.println();
}

/////////////////////////////////////////

boolean calibrate()
{
  boolean temp = false;
  float x, y, z;
  
  if (IMU.accelerationAvailable()) 
  {
    IMU.readAcceleration(x, y, z);
    curX = x;
    minX = x;
    maxX = x;
    curY = y;
    minY = y;
    maxY = y;
    curZ = z;
    minZ = z;
    maxZ = z;

    for (int i=0; i<50; i++)
    {
      IMU.readAcceleration(x, y, z);
      curX = x;
      curY = y;
      curZ = z;
      
      if (curX > maxX)
      {
        maxX = curX;
      }
      else
      {
        minX = curX;
      }

      if (curY > maxY)
      {
        maxY = curY;
      }
      else
      {
        minY = curY;
      }

      if (curZ > maxZ)
      {
        maxZ = curZ;
      }
      else
      {
        minZ = curZ;
      }

      delay(10);
    }

    calibratePrint();

    for (int i=0; i<5; i++)
    {
    
      for (int j=0; j<100; j++)
      {
      digitalWrite(buzzerPin,HIGH);
      delay(1);
      digitalWrite(buzzerPin,LOW);
      delay(1);
      }
      digitalWrite(bPin,HIGH);
      delay(200);
      digitalWrite(bPin,LOW);
    }

    digitalWrite(rPin,LOW);
    digitalWrite(gPin,HIGH);
    digitalWrite(bPin,LOW);
    digitalWrite(yPin,LOW);
    
    temp = true;
  }
  else
  {
    temp = false;
  }

  return temp;
}

////////////////////////////////////////

boolean detect()
{
  float x, y, z;
  boolean temp = false;
  
  if (IMU.accelerationAvailable()) 
  {
    IMU.readAcceleration(x, y, z);
    curX = x;
    curY = y;
    curZ = z;

    if (curX > (maxX + tolerance) || curX < (minX - tolerance))
    {
      temp = true;
      Serial.print("x detected = ");
      Serial.print(curX);
      Serial.println();
    }

    if (curY > (maxY + tolerance) || curY < (minY - tolerance))
    {
      temp = true;
      Serial.print("y detected = ");
      Serial.print(curY);
      Serial.println();
    }

    if (curZ > (maxZ + tolerance) || curZ < (minZ - tolerance))
    {
      temp = true;
      Serial.print("z detected = ");
      Serial.print(curZ);
      Serial.println();
    }
  }

  return temp;
}

//////////////////////////////////////////////////
//boolean arm(int passwordLength, char* password)
//{
//  boolean temp = false;
//}
//////////////////////////////////////////////////

void alarm()
{
  digitalWrite(rPin, HIGH);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
  digitalWrite(yPin, LOW);
  digitalWrite(buzzerPin,HIGH);
  delay(2);
  digitalWrite(buzzerPin,LOW);
  delay(2);
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////



void setup() {
  // put your setup code here, to run once:

  if (!IMU.begin()) 
  {
    Serial.println("FAIL");
    while (1);
  }

  Serial.begin(9600);

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(yPin, OUTPUT);

  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

}

void loop() 
{
  // put your main code here, to run repeatedly:

//  char key = keypad.getKey();
// 
//  if (key)
//  {
//    Serial.println(key);
//  }

  if (standby)
  {
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(yPin, HIGH);

    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH)
    {
      if (calibrate())
      {
        standby = false;
        calibrated = true;
        armed = false;
        detected = false;

        digitalWrite(rPin, LOW);
        digitalWrite(gPin, LOW);
        digitalWrite(bPin, HIGH);
        digitalWrite(yPin, LOW);

        cursor = 0;
      }
    }
  }

  if (calibrated)
  {
    char key = keypad.getKey();
    if (key == '1' || key == '2' || key == '3' | key == '4')
    {

      if (key == password[cursor])
      {
        cursor++;

        // Serial.println(cursor);
      
        if (cursor == passwordLength)
        {
          standby = false;
          calibrated = false;
          armed = true;
          detected = false;  

          for (int i=0; i<100; i++)
          {
            digitalWrite(buzzerPin,HIGH);
            delay(2);
            digitalWrite(buzzerPin,LOW);
            delay(2); 
          }
          digitalWrite(gPin, HIGH);
          for (int i=0; i<100; i++)
          {
            digitalWrite(buzzerPin,HIGH);
            delay(1);
            digitalWrite(buzzerPin,LOW);
            delay(1); 
          }
          delay(50);
                     
          digitalWrite(rPin, LOW);
          digitalWrite(gPin, HIGH);
          digitalWrite(bPin, LOW);
          digitalWrite(yPin, LOW);

          cursor = 0;
        }
      }
      else
      {
        cursor = 0;

        for (int i=0; i<100; i++)
        {
          digitalWrite(buzzerPin,HIGH);
          delay(1);
          digitalWrite(buzzerPin,LOW);
          delay(1); 
        }
        digitalWrite(rPin, HIGH);
        for (int i=0; i<100; i++)
        {
          digitalWrite(buzzerPin,HIGH);
          delay(2);
          digitalWrite(buzzerPin,LOW);
          delay(2); 
        }
        delay(50);
        digitalWrite(rPin, LOW);
      }
    }

    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH)
    {
      standby = true;
      calibrated = false;
      armed = false;
      detected = false;

      digitalWrite(rPin, LOW);
      digitalWrite(gPin, LOW);
      digitalWrite(bPin, LOW);
      digitalWrite(yPin, HIGH);

      cursor = 0;
      delay(1000);
    }
  }

  if (armed)
  {
    if (detect())
    {
      standby = false;
      calibrated = false;
      armed = false;
      detected = true;
    }
  }

  if (detected)
  {
    Serial.println("ALARM");
    alarm();

    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH)
    {
      standby = true;
      calibrated = false;
      armed = false;
      detected = false;

      cursor = 0;
      delay(1000);
    }
  }

}
