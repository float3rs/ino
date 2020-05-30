//  What does the line “while (! Serial);” do in an Arduino program?
//
//  On boards with an FT232 chip or other USB->Serial bridge chip (Uno, Mega, etc) it does absolutely nothing.
//  On boards with a direct USB connection, such as the Leonardo or the Yùn it waits for an active serial connection to be established by the PC (i.e., for the serial port to be opened by a piece of software).
//  When you open the serial port of a board like the Uno or Mega the whole board usually resets*, so opening the serial port allows you to see the first bits of the serial data. On the Leonardo etc it doesn't reset when you open the serial, so any serial output during the setup() function would be missed. Adding that line makes the board pause until you open the serial port, so you get to see that initial bit of data.
//  *) Unless you specifically write some software that doesn't assert DTR when you open the port
//




#include <Arduino_LSM6DS3.h>

const int buttonPin = 4;
const int buzzerPin = 5;
const int ledRedPin = 9;
const int ledGreenPin = 10;
const int ledBluePin = 6;
const int joystickPin = 7;
const int joystickPinX = A0;
const int joystickPinY = A1;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // while (! Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
  
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(joystickPin, INPUT_PULLUP);
  pinMode(joystickPinX, INPUT);
  pinMode(joystickPinY, INPUT);

//  analogWrite(ledBluePin, 255);

}

void loop() {
  // put your main code here, to run repeatedly:

//  delay(5000);

  tone(buzzerPin, 500); // Send 1KHz sound signal...
  analogWrite(ledRedPin, 255);
  delay(1000);        // ...for 1 sec
  noTone(buzzerPin);     // Stop sound...
  analogWrite(ledRedPin, 0);
  delay(1000);        // ...for 1sec
  
  
  Serial.println(">");
//  Serial.println(analogRead(joystickPinX));
//
//  Serial.println(analogRead(joystickPinY));
//
//  Serial.println(digitalRead(joystickPin)); // 1 when depressed, 0 when pressed
//  Serial.println(digitalRead(buttonPin));

  








//  analogWrite(ledRedPin, 255);   // set PWM value for red
//  analogWrite(ledGreenPin, 165); // set PWM value for green
//  analogWrite(ledBluePin, 0);    // set PWM value for blue

//  tone(buzzerPin, 1000); // Send 1KHz sound signal...
//  delay(1000);        // ...for 1 sec
//  noTone(buzzerPin);     // Stop sound...
//  delay(1000);        // ...for 1sec

//  if (digitalRead(buttonPin) == HIGH) 
//  {
//     analogWrite(ledRedPin, 255);
//     analogWrite(ledGreenPin, 0);
//     analogWrite(ledBluePin, 0);
//  } 
//  else 
//  {
//    analogWrite(ledRedPin, 0);
//    analogWrite(ledGreenPin, 255);
//    analogWrite(ledBluePin, 0);
//  }
}
