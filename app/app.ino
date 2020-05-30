const int ledRedPin = 9;
const int ledGreenPin = 10;
const int ledBluePin = 6;
const int buzzerPin = 5;
const int buttonPin = 4;
const int joystickPinSw = 7;
const int joystickPinX = A0;
const int joystickPinY = A1;

int state = 0; // 0: STANDBY, 1: ARMED, 2: TRIGGERED, 3: AUTHENTICATING

void setup() {
  // put your setup code here, to run once:

  state = 0;
  analogWrite(ledRedPin, 0);   
  analogWrite(ledGreenPin, 0); 
  analogWrite(ledBluePin, 255);   

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(100);

}
