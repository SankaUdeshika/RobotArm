#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

Servo myServo;

WiFiServer server(80);  // Corrected server initialization
const int servoPin = 13;


int x = 90;
int y = 90;
int z = 90;


void setup() {
  // pinMode(13, OUTPUT);
  // pinMode(servoPin, OUTPUT);
  myServo.attach(13);
  myServo.write(0);


  Serial.begin(115200);
  WiFi.begin("Dialog 4G 043", "b134BA0F");
  Serial.print("Connecting ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.begin();
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();  // Corrected method to accept client

  if (client) {
    String requestText = "";  // Fixed typo: requestText

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        requestText += c;

        if (c == '\n') {

          if (requestText.startsWith("GET /?status=up HTTP/1.1")) {
            y = y + 10;
          } else if (requestText.startsWith("GET /?status=left HTTP/1.1")) {
            x = x - 10;
          } else if (requestText.startsWith("GET /?status=right HTTP/1.1")) {
            x = x + 10;
          } else if (requestText.startsWith("GET /?status=down HTTP/1.1")) {
            y = y - 10;
          }

          Serial.println(requestText);
          Serial.println(x);

          myServo.write(x);




          // Send HTTP response
          client.print("HTTP/1.1 200 OK\r\n");
          client.print("Content-Type: text/plain\r\n");
          client.print("\r\n");
          client.print("LED toggled based on status.\r\n");

          break;
        }
      }
    }
    client.stop();  // Close the connection
  }
}




void moveServo(int pulseWidth) {
  for (int i = 0; i < 50; i++) {            // Repeat to maintain 50 Hz frequency
    digitalWrite(servoPin, HIGH);           // Set signal high
    delayMicroseconds(pulseWidth);          // Keep high for pulse width
    digitalWrite(servoPin, LOW);            // Set signal low
    delayMicroseconds(20000 - pulseWidth);  // Complete 20 ms period
  }
}
