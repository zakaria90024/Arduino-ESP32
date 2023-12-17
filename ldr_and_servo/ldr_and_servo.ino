#include <ESP32Servo.h>
#define LIGHT_SENSOR_PIN 33  // ESP32 pin GIOP33 (ADC0)
Servo myservo;               // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 30;

void setup() {
  Serial.begin(9600);
  myservo.attach(18);
}

void loop() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);
  Serial.println();


  if (analogValue < 350) {
    Serial.println(" => Dark");

    for (pos = 0; pos <= 30; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      delay(1);            // waits 15ms for the servo to reach the position
    }
    for (pos = 30; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
      myservo.write(pos);                 // tell servo to go to position in variable 'pos'
      delay(1);                           // waits 15ms for the servo to reach the position
    }

  } 

  // else if (analogValue < 2000) {
  //   Serial.println(" => Dim");



  // } else if (analogValue < 2500) {
  //   Serial.println(" => Light");
  // } else if (analogValue < 4000) {
  //   Serial.println(" => Bright");
  // } else {
  //   Serial.println(" => Very bright");
  // }

  delay(1000);
}
