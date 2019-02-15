// HUZZAH fade

int ledPin = 2;    // onboard blue LED connected to digital pin 2

void setup() {
  // declare pinModes
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // fade in from min to max 
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue++) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 16 milliseconds to see the dimming effect
    delay(16);
  }

  // fade out from max to min 
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue--) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 16 milliseconds to see the dimming effect
    delay(16);
  }
}
