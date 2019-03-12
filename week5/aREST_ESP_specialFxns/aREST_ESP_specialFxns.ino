// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "your_wifi_network_name";
const char* password = "your_wifi_network_password";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Declare functions to be exposed to the API
int readButtons(String command);

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Function to be exposed
  // http://myip/buttons?params=r
  rest.function("buttons", readButtons);

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
int readButtons(String command) {
  String values = "";
  int b0val = digitalRead(6);
  int b1val = digitalRead(7);
  int b2val = digitalRead(8);
  int b3val = digitalRead(9);
  values = String(b0val) + String(b1val) + String(b2val) + String(b3val);
  int output = values.toInt();
  return output;
}
