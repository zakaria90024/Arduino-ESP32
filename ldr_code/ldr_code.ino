 
//Prateek
//www.prateks.in
//https://www.youtube.com/c/JustDoElectronics

#define LIGHT_SENSOR_PIN 4 // ESP32 pin GIOP33 (ADC0)

void setup() {

  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);  


  if (analogValue < 1) {
    Serial.println(" => Light");
  } else if (analogValue < 2000) {
    Serial.println(" => Dim");
  } else if (analogValue < 2500) {
    Serial.println(" => Light");
  } else if (analogValue < 4096) {
    Serial.println(" => dark");
  } else {
    Serial.println(" => dark");
  }

  delay(1000);
}

