#include <ESP32Servo.h>
#define LIGHT_SENSOR_PIN 33
#define LED_BUILTIN 19  // ESP32 pin GIOP33 (ADC0)
Servo myservo;          // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 30;

void setup() {

  Serial.begin(9600);
  //pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);


  //start code for servo ==========================================================================
  myservo.attach(18);
  for (pos = 0; pos <= 64; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(50);
    //myservo.detach();                    // waits 15ms for the servo to reach the position
  }
  delay(1000);
  myservo.attach(18);

  for (pos = 58; pos >= 8; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(50);                          // waits 15ms for the servo to reach the position
  }
  myservo.detach();
  //end code for servo ==========================================================================

}

void loop() {
  
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  delay(10);
  Serial.print("Analog Value = ");
  Serial.print(analogValue);
  Serial.println();


  if (analogValue < 200) {
    digitalWrite(LED_BUILTIN,LOW );

    Serial.println(" => Dark");
    // Turn the LED on
    delay(15);


    //Wait for 1 second
    //delay(40000);
    // Turn the LED off

    // // Wait for 1 second
    //delay(1000);
    // for (pos = 0; pos <= 30; pos += 1) {  // goes from 0 degrees to 180 degrees
    //   // in steps of 1 degree
    //   myservo.write(pos);  // tell servo to go to position in variable 'pos'
    //   delay(1);            // waits 15ms for the servo to reach the position
    // }
    // for (pos = 30; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    //   myservo.write(pos);                 // tell servo to go to position in variable 'pos'
    //   delay(1);                           // waits 15ms for the servo to reach the position
    // }

  } else {
    delay(10);
        digitalWrite(LED_BUILTIN, HIGH);


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

  //delay(1000);
}
