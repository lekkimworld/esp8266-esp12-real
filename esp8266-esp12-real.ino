#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "MM";
const char* password = "chippo-lekkim";

const int button1 = 2;
const int button2 = 0;
const int button3 = 13;
const int button4 = 12;
const int button5 = 14;
const int button6 = 16;
const int led1 = 15;
const int led2 = 4;
const int led3 = 5;

ESP8266WebServer server(80);  

void setup() {
  // configure pins
  initializePins();

  // do start blink
  startupBlink();
  
  // init wifi
  initWifi();

  // start server
  initServer();
}

void loop() {
  server.handleClient();
}

void initializePins() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void startupBlink() {
  for (int i=0; i<5; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(200);
  }
}

void initWifi() {
  digitalWrite(led1, HIGH);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    delay(200);
  }
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  for (int i=0; i<5; i++) {
    digitalWrite(led3, HIGH);
    delay(200);
    digitalWrite(led3, LOW);
    delay(200);
  }
  digitalWrite(led2, LOW);
}

void handleRoot() {
  String msg = "<html><body>";
  msg += "<h1>6 slutte, 3 led</h1>";
  msg += "<p>";
  msg += "<br/><a href=\"/led1/on\">led 1, on</a>";
  msg += "<br/><a href=\"/led1/off\">led 1, off</a>";
  msg += "<br/><a href=\"/led2/on\">led 2, on</a>";
  msg += "<br/><a href=\"/led2/off\">led 2, off</a>";
  msg += "<br/><a href=\"/led3/on\">led 3, on</a>";
  msg += "<br/><a href=\"/led3/off\">led 3, off</a>";
  msg += "</p>";
  msg += "<p>";
  msg += "<br/><a href=\"/blink\">blink</a>";
  msg += "</p>";
  msg += "</body></html>";
  server.send(200, "text/html", msg);
}
void handleBlink() {
  sendOK();
  startupBlink();
}
void handleNotFound() {
  server.send(404, "text/plain", "Unknown...");
} 
void handleLed1On() {
  digitalWrite(led1, HIGH);
  sendOK();
}
void handleLed1Off() {
  digitalWrite(led1, LOW);
  sendOK();
}
void handleLed2On() {
  digitalWrite(led2, HIGH);
  sendOK();
}
void handleLed2Off() {
  digitalWrite(led2, LOW);
  sendOK();
}
void handleLed3On() {
  digitalWrite(led3, HIGH);
  sendOK();
}
void handleLed3Off() {
  digitalWrite(led3, LOW);
  sendOK();
}
void sendOK() {
  server.sendHeader("Location", String("/"), true);
  server.send (302, "text/plain", "OK");

}

void initServer() {
  if (MDNS.begin("esp8266"))
  
  server.on("/",          handleRoot);
  server.on("/led1/on",   handleLed1On);
  server.on("/led1/off",  handleLed1Off);
  server.on("/led2/on",   handleLed2On);
  server.on("/led2/off",  handleLed2Off);
  server.on("/led3/on",   handleLed3On);
  server.on("/led3/off",  handleLed3Off);
  server.on("/blink",     handleBlink);
  server.onNotFound(handleNotFound);
  
  // start server
  server.begin();
}
