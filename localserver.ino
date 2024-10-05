#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Terrace";        // Replace with your WiFi SSID
const char* password = "dalipluthra"; // Replace with your WiFi password

// Pin connected to the relay
const int relayPin = D1; // Change this to your chosen GPIO pin

ESP8266WebServer server(80);  // Create a web server on port 80

void setup() {
  Serial.begin(115200);
  
  // Set up relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Start with the relay off
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP()); // Print the IP address of the ESP8266

  // Define routes
  server.on("/relay/on", []() {
    digitalWrite(relayPin, HIGH);  // Turn relay ON
    server.send(200, "text/plain", "Relay is ON");
  });

  server.on("/relay/off", []() {
    digitalWrite(relayPin, LOW);  // Turn relay OFF
    server.send(200, "text/plain", "Relay is OFF");
  });

  server.begin(); // Start the server
  Serial.println("Server started");
}

void loop() {
  server.handleClient(); // Handle incoming client requests
}
