/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
  Written by BARRAGAN and modified by Scott Fitzgerald
*********/

#include <ESP32Servo.h>
               
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(18);


  
    for (pos = 0; pos <=68; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50); 

  
    
    //myservo.detach();                    // waits 15ms for the servo to reach the position
  }


  delay(90000);
  
  //myservo.attach(18);

  for (pos = 62; pos >= 3; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();  

  

    // attaches the servo on pin 13 to the servo object
}

void loop() {

  
}

