/*
  Blink the HUZZAH
*/

int led = 4; // variable to hold the LED

// the setup routine runs once when you press reset or power the board :
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off (voltage is LOW, or 0V)
  delay(1000);               // wait for a second
}
