/*
  HUZZAH Feather analog Input to serial and analog out with calibration
  additional smoothing with an array 
*/

// These constants won't change. They're used to give names to the pins used:
const int sensorPin = A0;  // Analog input pin that the sensor is attached to
const int ledPin = 4; // Analog output pin that the LED is attached to

// variables
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

// Define a number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  calibrateSensor();
}

void loop() {

  // optional switch to recalibrate
  if (digitalRead(5) == HIGH) {
    calibrateSensor();
  }

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(sensorPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  // apply the calibration to the sensor reading
  int outputValue = map(average, sensorMin, sensorMax, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  outputValue = constrain(outputValue, 0, 255);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor avg = ");
  Serial.print(average);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(5);
}

void calibrateSensor() {
  digitalWrite(LED_BUILTIN, LOW);

  sensorMin = 1023;        // reset minimum sensor value
  sensorMax = 0;           // reset maximum sensor value

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
