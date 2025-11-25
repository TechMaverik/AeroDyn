#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Ai Lab";
const char* password = "Welc0me@123";

#define M1 D8
#define M2 D7
#define M3 D6
#define M4 D5

ESP8266WebServer server(80);

// ---------- GET API ----------
void handleHello() {
  server.send(200, "application/json", "{\"message\":\"AeroDyn Flying Machine\"}");
}

void front()
{
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    digitalWrite(M3, HIGH);
    digitalWrite(M4, LOW);
    server.send(200, "application/json", "{\"message\":\"AeroDyn Flying Machine front\"}");  
}

void back()
{
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);
    server.send(200, "application/json", "{\"message\":\"AeroDyn Flying Machine front\"}");  
}

void stop()
{
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M4, LOW);
    server.send(200, "application/json", "{\"message\":\"AeroDyn Flying Machine stop\"}");
}

void quick_left()
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);
  server.send(200, "application/json", "{\"message\":\"AeroDyn Flying Machine quick left\"}");

}

void left()
{

    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    server.send(200, "application/json", "{\"message\":\"AeroDyn Flying Machine left\"}");
  
}

void right()
{
    digitalWrite(M3, HIGH);
    digitalWrite(M4, LOW);  
    server.send(200, "application/json", "{\"message\":\"AeroDyn Flying Machine right\"}");
}

void quick_right()
{
    digitalWrite(M3, HIGH);
    digitalWrite(M4, LOW);  
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    server.send(200, "application/json", "{\"message\":\"AeroDyn Flying Machine right quick right\"}");
}



// ---------- POST API ----------
void handlePostData() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    String reply = "{\"received\":\"" + body + "\"}";
    server.send(200, "application/json", reply);
  } else {
    server.send(400, "application/json", "{\"error\":\"No JSON received\"}");
  }
}

void setup() {

  // Set all pins as OUTPUT
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Start motors OFF
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);

  Serial.begin(115200);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
   
    pinMode(LED_BUILTIN, LOW);  
    delay(250);
    pinMode(LED_BUILTIN, HIGH);  
    delay(250);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  pinMode(LED_BUILTIN, HIGH);  
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Register API endpoints
  server.on("/hello", HTTP_GET, handleHello);
  server.on("/left", HTTP_GET, left);
  server.on("/right", HTTP_GET, right);
  server.on("/front", HTTP_GET, front);
  server.on("/stop", HTTP_GET, stop);
  server.on("/back", HTTP_GET, back);
  server.on("/quick_right", HTTP_GET, quick_right);
  server.on("/quick_left", HTTP_GET, quick_left);
  server.on("/post", HTTP_POST, handlePostData);


  server.begin();
  Serial.println("API Server started!");
}

void loop() {
  server.handleClient();
}
