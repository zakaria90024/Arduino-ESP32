
// void setup() {
//   // put your setup code here, to run once:
//   pinMode(Buzzer_pin, OUTPUT);

// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   tone(Buzzer_pin, 1000);
//   delay(10000);

// }
/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-flame-sensor
 */
//INPUT PIN 
int FIRE = 4;
int GAS = 22;
int LDR = 4;
int MOTION = 15;
int warm_up;

//OUTPUT PIN
int Buzzer_pin = 23;
int ldr_outputpin = 18;
int motion_outputpin = 22;

  // ESP32's pin GPIO13 connected to DO pin of the flame sensor

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  // initialize the ESP32's pin as an input
  pinMode(FIRE, INPUT);
  //pinMode(GAS, INPUT);
  //pinMode(Buzzer_pin, OUTPUT);
  //pinMode(ldr_outputpin, OUTPUT);

  // pinMode(MOTION, INPUT);
  // Serial.begin(115200); /* Define baud rate for serial communication */
  // Serial.println("Waiting For Power On Warm Up");
  // delay(20000); /* Power On Warm Up Delay */
  // Serial.println("Ready!");


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

  //FOR LDR SENSOR 
  //  if (analogValue < 1) {
  //   Serial.println(" => Light");
  //   digitalWrite(ldr_outputpin, HIGH);
  // } else if (analogValue < 2000) {
  //   Serial.println(" => Dim");
  //   digitalWrite(ldr_outputpin, HIGH);
  // } else if (analogValue < 2500) {
  //   digitalWrite(ldr_outputpin, HIGH);
  //   Serial.println(" => Light");
  // } else if (analogValue < 4096) {
  //   Serial.println(" => dark");
  //   digitalWrite(ldr_outputpin, LOW);
  // } else {
  //   Serial.println(" => dark");
  // }

  // // delay(1000);



  // int sensor_output;
  // sensor_output = digitalRead(MOTION);
  // if( sensor_output == LOW )
  // {
  //   if( warm_up == 1 )
  //    {
  //     Serial.print("Warming Up\n\n");
  //     warm_up = 0;
  //     //delay(2000);
  //   }
  //   Serial.print("No object in sight\n\n");
  //   //delay(1000);
  //   digitalWrite(motion_outputpin, LOW);
  // }
  // else
  // {
    
  //   Serial.print("Object detected\n\n");   
  //   warm_up = 1;
  //   //delay(1000);
  //   digitalWrite(motion_outputpin, HIGH);
  // } 

  //   if (flame_state == HIGH){
  //   noTone(Buzzer_pin);
  //   Serial.println("No flame dected => The fire is NOT detected");
  // }
  // else{
  //   tone(Buzzer_pin, 1000);
  //   delay(8000);

  //   Serial.println("Flame dected => The fire is detected");
  // }
    
    
}
