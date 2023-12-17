/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;  // variable to store the servo position


#define LED_BUILTIN 2  // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "yourAP";
const char *password = "yourPassword";

WiFiServer server(80);
int FIRE = 4;
int Buzzer_pin = 23;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(FIRE, INPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while (1)
      ;
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
    int flame_state = digitalRead(FIRE);
  //int analogValue = analogRead(LDR);
  //int gas_state = digitalRead(GAS);
    
  if (flame_state == HIGH){
    noTone(Buzzer_pin);
    Serial.println("No flame dected => The fire is NOT detected");
  }
  else{
    tone(Buzzer_pin, 1000);
    delay(8000);

    Serial.println("Flame dected => The fire is detected");
  }
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            // client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            // client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br><hr>");

            client.print("Click <a href=\"/Hi\">here</a> to turn ON the FAN.<br>");
            client.print("Click <a href=\"/Lo\">here</a> to turn OFF the FAN.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        // if (currentLine.endsWith("GET /H")) {
        //   digitalWrite(LED_BUILTIN, HIGH);  // GET /H turns the LED on
        // }
        // if (currentLine.endsWith("GET /L")) {
        //   digitalWrite(LED_BUILTIN, LOW);  // GET /L turns the LED off
        // }
 

        if (currentLine.endsWith("GET /Hi")) {
          digitalWrite(LED_BUILTIN, HIGH);
          myservo.attach(33);



          for (pos = 0; pos <= 64; pos += 1) {  // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos);  // tell servo to go to position in variable 'pos'
            delay(50);



            //myservo.detach();                    // waits 15ms for the servo to reach the position
          }
          myservo.detach();


          // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /Lo")) {
          myservo.attach(33);

          for (pos = 58; pos >= 8; pos -= 1) {  // goes from 180 degrees to 0 degrees
            myservo.write(pos);                 // tell servo to go to position in variable 'pos'
            delay(50);                          // waits 15ms for the servo to reach the position
          }                                     // GET /L turns the LED off
          myservo.detach();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
