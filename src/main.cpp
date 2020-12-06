#include <Arduino.h>

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#ifndef ESP8266
#include <WiFi.h>
#include <SPIFFS.h>
#else
#include <ESP8266WiFi.h>
#include <FS.h>
#endif

// Ersetzen Sie durch Ihre Netzwerkanmeldeinformationen
char* ssid           = "DEINE_SSID";
const char* password = "DEIN_WLAN_PASSWORD";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

float currentTemp;
float currentHyg;

unsigned long old_millis = 0;
#define DELAY_MILLIS 5000

// Variablen einstellen
bool setupWiFi();
void setupWebSockets();
void setupWebServer();
void newMeasurement();
void sendMeasurementJson(AsyncWebSocketClient *client);
bool timeIsUp();

// =============================================================================================
//   Arduino Setup- und Loop-Funktion
// =============================================================================================
void setup() {
  Serial.begin(115200);
  Serial.println(F("Startet den ESP-Webserver"));
  SPIFFS.begin();

  setupWiFi();
  setupWebSockets();
  setupWebServer();

  Serial.printf("Setup fertig ...\n");
}

void loop() {
  if (timeIsUp()) {
    newMeasurement();
    sendMeasurementJson(nullptr);
  }
}

// =============================================================================================
//   Richtet Sie die Teile unseres Programms ein
// =============================================================================================
bool setupWiFi() {
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Verbinden mit ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi verbunden.");
  Serial.println("IP Adresse: ");
  Serial.println(WiFi.localIP());
}

void setupWebSockets() {
  ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void* arg, uint8_t *data, size_t len) {
    if (type == AwsEventType::WS_EVT_CONNECT) {
        // send first measurement to newly connected client
        sendMeasurementJson(client);
    }
  });

  server.addHandler(&ws);
}

void setupWebServer() {
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "404 - Not Found");
  });

  server.on("/api/sensors", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Serial.printf("Arg - Path: %s\n", request->pathArg(0).c_str());

    request->send(200, "application/json", "{\n" 
                                            "  \"Temperatur\": \"23\",\n" 
                                            "  \"Luftfeuchtikeit\": \"58\"\n" 
                                            "}\n");
  });

  server.serveStatic("/", SPIFFS, "/");

  server.begin();
}

// =============================================================================================
//   Hilfsfunktionen
// =============================================================================================
bool timeIsUp() {
  if (millis() > old_millis + DELAY_MILLIS) {
    old_millis = millis();
    return true;
  } 

  return false;
}

void sendMeasurementJson(AsyncWebSocketClient *client) {
    DynamicJsonDocument doc(1024);
    doc["temp"] =currentTemp;
    doc["hyg"] = currentHyg;
    
    char ch[1024];
    serializeJsonPretty(doc, ch);

    if (client != nullptr) {
      client->text(ch);
    } else {
      ws.textAll(ch);
    }
}

// =============================================================================================
//   Create the actual Measurement (don't forget to init the sensor in setup)
// =============================================================================================
void newMeasurement() {
  // put in only example values
  currentTemp = 21.4;
  currentHyg = 56;
}