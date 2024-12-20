#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

#define BuzzerPin 27

// Musice Notes
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define fF4 369

#define G4 392
#define A4 440
#define B4 494
#define C5 523

Servo myServo1;  //X
Servo myservo2;  //y
Servo myservo3;  //z

// sadaj weka mandaram-----------------------------------------------------------------------------------------------------------------------------------------------
int SandakWelaManaram_noteDurations[] = { 200, 300, 200, 400, 200, 200, 1000, 200, 300, 200, 300, 200, 300, 200, 300, 200, 200, 500 };
int SandakWelaManaram_melody[] = {
  E4, E4, G4, fF4,
  G4, fF4, E4,
  E4, E4, fF4, G4,
  fF4, fF4, fF4, fF4,
  G4, A4, G4
};
// sadaj weka mandaram-----------------------------------------------------------------------------------------------------------------------------------------------

// Jingle Bells-----------------------------------------------------------------------------------------------------------------------------------------------
int JingleBells_noteDuration[] = { 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800,
                                   400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 800 };
int jingleBells_melody[] = { E4, E4, E4, E4, E4, E4, E4, G4, C4, D4, E4,
                             F4, F4, F4, F4, F4, E4, E4, E4, E4, E4, D4, D4, E4, D4, G4 };
// Jingle Bells-----------------------------------------------------------------------------------------------------------------------------------------------

// Happy Birthday-----------------------------------------------------------------------------------------------------------------------------------------------
int nothingonYOu_notation_duration[] = {
  400,
  400,
  400,
  400,
  400,
  800,
  400,
  400,
  400,
  400,
  800,
  400,
  400,
  400,
  400,
  400,
  400,
  800,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
};
int nothingonYOu_Melody[] = {
  523,
  523,
  587,
  523,
  698,
  659,
  523,
  523,
  587,
  523,
  784,
  698,
  523,
  523,
  523,
  880,
  698,
  659,
  523,
  784,
  698,
  523,
  659,
  587,
  523,
};
// Happy Birthday-----------------------------------------------------------------------------------------------------------------------------------------------


// Piret of the caribian -----------------------------------------------------------------------------------------------------------------------------------------------
int caribian_melody[] = {
  440,
  523,
  587,
  587,
  587,
  659,
  698,
  698,
  698,
  784,
  659,
  659,
  587,
  523,
  523,
  587,
  440,
  523,
  587,
  587,
  587,
  659,
  698,
  698,
  698,
  784,
  659,
  659,
  587,
  523,
  587,
  440,
  523,
  587,
  587,
  587,
  698,
  784,
  784,
  784,
  440,
  466,
  466,
  440,
  784,
  440,
  587,
  587,
  659,
  698,
  784,
  440,
  440,
  698,
  659,
  659,
  698,
  587,
  659,
  440,
  523,
  587,
  587,
  587,
  659,
  698,
  698,
  698,
  784,
  659,
  659,
};
int caribian_duration[] = {
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
};
// Piret of the caribian -----------------------------------------------------------------------------------------------------------------------------------------------
int nothingonyouBaby_melody[] = {
  392,
  440,
  392,
  587,
  392,
  392,
  440,
  392,
  587,
  392,
  392,
  440,
  392,
  587,
  392,
  392,
  392,
  440,
  392,
  587,
  493,
  392,
  392,
  392,
  440,
  392,
  587,
  493,
  493,
  493,
  493,
  587,
  740,
  587,
  493,
  880,
  783,
  659,
  740,
  587,
  392,
  440,
  392,
  587,
  392,
  392,
  440,
  392,
  587,
  392,
  440,
  392,
  587,
  493,
  392,
  392,
  392,
  440,
  392,
  587,
  493,
  493,
  493,
  493,
  587,
  740,
  587,
  493,
  880,
  783,
  659,
  740,
};
int nothingonyou_duration[] = {
  400,
  400,
  400,
  700,

  400,
  400,
  400,
  400,
  700,

  400,
  400,
  400,
  600,
  700,

  400,
  400,
  500,
  400,
  700,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
  400,
};





WiFiServer server(80);  // Corrected server initialization
const int servoPin = 13;


int x = 0;
int y = 0;
int inverty = 180;
int z = 0;


void setup() {
  myServo1.attach(13);  // left right
  myServo1.write(90);

  myservo2.attach(12);  // UP and Down
  myservo2.write(180);

  myservo3.attach(14);  // forwoerd and back
  myservo3.write(40);

  pinMode(BuzzerPin, OUTPUT);


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

          Serial.println(requestText);
          String action = requestText.substring(13, 14);
          String pulsText = requestText.substring(21, 24);
          double puls = pulsText.toDouble();

          Serial.println(action + " " + pulsText + " " + puls);

          if (action.equals("X")) {
            myServo1.write(puls);
          } else if (action.equals("Y")) {
            myservo2.write(puls);
          } else if (action.equals("Z")) {
            myservo3.write(puls);
          } else if (action.equals("1")) {
            Serial.println(pulsText);
            for (int i = 0; i < sizeof(SandakWelaManaram_noteDurations) / sizeof(SandakWelaManaram_noteDurations[0]); i++) {

              int duration = SandakWelaManaram_noteDurations[i];
              tone(BuzzerPin, SandakWelaManaram_melody[i], duration);
              delay(duration + 50);  // Add a slight delay between notes
            }
          } else if (action.equals("2")) {
            for (int i = 0; i < sizeof(JingleBells_noteDuration) / sizeof(JingleBells_noteDuration[0]); i++) {

              int duration = JingleBells_noteDuration[i];
              tone(BuzzerPin, jingleBells_melody[i], duration);
              delay(duration + 50);  // Add a slight delay between notes
            }
          } else if (action.equals("3")) {
            for (int i = 0; i < sizeof(nothingonYOu_notation_duration) / sizeof(nothingonYOu_notation_duration[0]); i++) {

              int duration = nothingonYOu_notation_duration[i];
              tone(BuzzerPin, nothingonYOu_Melody[i], duration);
              delay(duration + 50);  // Add a slight delay between notes
            }
          } else if (action.equals("4")) {
            for (int i = 0; i < sizeof(caribian_duration) / sizeof(caribian_duration[0]); i++) {

              int duration = caribian_duration[i];
              tone(BuzzerPin, caribian_melody[i], duration);
              delay(duration + 50);  // Add a slight delay between notes
            }
          } else if (action.equals("5")) {
            for (int i = 0; i < sizeof(nothingonyou_duration) / sizeof(nothingonyou_duration[0]); i++) {

              int duration = nothingonyou_duration[i];
              tone(BuzzerPin, nothingonyouBaby_melody[i], duration);
              delay(duration + 50);  // Add a slight delay between notes
            }
          }





          // int firstComma = requestText.indexOf('&&');
          // int secondComma = requestText.indexOf('+', firstComma + 1);

          // String text1 = requestText.substring(0, 5);
          // Serial.println(text1);



          // if (requestText.startsWith("GET /?action=X HTTP/1.1")) {
          //   y = y + 10;
          // }

          // Serial.println(requestText);


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
