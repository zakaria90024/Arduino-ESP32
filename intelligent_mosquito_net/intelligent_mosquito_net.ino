#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

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

#define LED_BUILTIN 2  // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "yourAP";
const char *password = "yourPassword";
WiFiServer server(80);

int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

void setup() {


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




  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
 

  // Move DC motor forward with increasing speed
  // digitalWrite(motor1Pin1, HIGH);
  // digitalWrite(motor1Pin2, LOW);
  // while (dutyCycle <= 255){
  //   ledcWrite(pwmChannel, dutyCycle);   
  //   Serial.print("Forward with duty cycle: ");
  //   Serial.println(dutyCycle);
  //   dutyCycle = dutyCycle + 5;
  //   delay(500);
  // }
  // dutyCycle = 200;


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

            client.print("Click <a href=\"/Hi\">here</a> to turn ON Mosquito Net.<br>");
            client.print("Click <a href=\"/Lo\">here</a> to turn OFF Mosquito Net.<br>");

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
          // Move the DC motor forward at maximum speed
            Serial.println("Moving Forward");
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, HIGH); 
            delay(20000);

            
            // Stop the DC motor
            Serial.println("Motor stopped");
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, LOW);
            delay(10000);



          // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /Lo")) {
           // Move DC motor backwards at maximum speed
          Serial.println("Moving Backwards");
          digitalWrite(motor1Pin1, HIGH);
          digitalWrite(motor1Pin2, LOW); 
          delay(20000);

          // Stop the DC motor
          Serial.println("Motor stopped");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          delay(10000);

        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }



}