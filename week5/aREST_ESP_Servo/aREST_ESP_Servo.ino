// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <Servo.h>

// Create aREST instance
aREST rest = aREST();

Servo myServo;

// WiFi parameters
const char* ssid = "NETWORKNAME";
const char* password = "PASSWORD";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Declare functions to be exposed to the API
int moveServo(String command);

void setup(void)
{
  // Start Serial
  Serial.begin(115200);
  myServo.attach(5);
  // Function to be exposed
  // http://myip/servo?params=r
  rest.function("servo", moveServo);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("1");
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);
}

// Custom function accessible by the API
int moveServo(String command) {
  int pos = command.toInt();

  for (int i = 0 ; i < pos; i++) {
    int pos;

    for (pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
      myServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  return pos;
}
