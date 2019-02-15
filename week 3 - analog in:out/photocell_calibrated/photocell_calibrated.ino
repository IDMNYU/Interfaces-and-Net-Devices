/*
  HUZZAH Feather analog Input to serial and analog out with calibration
*/

// These constants won't change. They're used to give names to the pins used:
const int sensorPin = A0;  // Analog input pin that the sensor is attached to
const int ledPin = 4; // Analog output pin that the LED is attached to

// variables
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  calibrateSensor();
}

void loop() {

  // optional switch to recalibrate
  if (digitalRead(5) == HIGH) {
    calibrateSensor();
  }

  // read the sensor:
  sensorValue = analogRead(sensorPin);

  // apply the calibration to the sensor reading
  int outputValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  outputValue = constrain(outputValue, 0, 255);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(5);
}

void calibrateSensor() {
  digitalWrite(LED_BUILTIN, LOW);

  // calibrate during the first five seconds
  long currentTime = millis();
  Serial.println("calibration");
  while (millis() < (currentTime + 5000)) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
    Serial.print(".");
    yield(); // THIS IS IMPORTANT
  }
  Serial.println();
  // signal the end of the calibration period
  digitalWrite(LED_BUILTIN, HIGH);

}
