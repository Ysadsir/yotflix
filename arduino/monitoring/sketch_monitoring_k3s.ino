#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "arduino_secrets.h"

// Config wifi
const char* wifi_ssid = SECRET_SSID;
const char* wifi_password = SECRET_PASS;

//////////////////// WIFI & HTTP /////////////////////////
// Wifi & http declaration
WiFiClient client;
HTTPClient http;

// Config Prometheus API
const char* monitoring_server = SECRET_SERVER_HOSTNAME;
const int monitoring_port = SECRET_SERVER_PORT;
const char* monitoring_api = SECRET_API_URI;

// Sleep configuration
uint64_t uS_TO_S_FACTOR = 1000000;  // microseconds factor
uint64_t TIME_TO_SLEEP = 3600; // Sleep for 1 hour

//////////////////// ALERTMANAGER /////////////////////////
// Alerts 
bool alertsPresents = false;
int numberAlerts = 0;
bool serverDown = false;
bool nodeDown = false;
bool appDown = false;

const char* alertName = "";
const char* serverAlert = "NodeExporterDown";
const char* nodesAlert = "NodesNotReady";
const char* appsAlert = "AppsNotReady";

//////////////////// LEDS /////////////////////////
// The pins for the leds
int serverDownLed = D1;
int serverUpLed = D2;
int nodeDownLed = D3;
int nodeUpLed = D4;
int appDownLed = D5;
int appUpLed = D6;
int ledList[] = {D1, D2, D3, D4, D5, D6};
// The pins for the failed status
int redLedList[] = {D1, D3, D5};
// The pins for the ok status
int greenLedList[] = {D2, D4, D6};

// The number of pins
int numPins = 6;
// The number of pins of each color
int numPinsEachColor = 3;

void setup() {
  // Initialize serial
  Serial.begin(9600);

  // Initialize wifi
  connectWifi();

  // Initialize leds
  configureLeds();

  delay(2000);

  // Query promotheus alerts
  if (WiFi.status() == WL_CONNECTED) {
    requestMonitoring();
  }

  // send alerts to Uno
  if (numberAlerts > 0) {
    displayAlerts();
  }

  delay(5000);

  // Deep sleep for 1 hour
//  Serial.println("Going to sleep now");
//  ESP.deepSleep(TIME_TO_SLEEP * uS_TO_S_FACTOR);

}

void loop() {
}

/*
 * Connect Wifi
 */
void connectWifi() {
  
  WiFi.disconnect();
  delay(5000);

  Serial.println("Booting");
  WiFi.mode(WIFI_STA);

  //connect to your local wi-fi network
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.hostname());
  Serial.println("");
}

/*
 * Get monitoring status
 */
void requestMonitoring() {
  Serial.print("[HTTP] begin...\n");
  
  if (http.begin(client, monitoring_server, monitoring_port, monitoring_api)) {  // HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
        Serial.println("");
        parseJSON(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      delay(1000);
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
    delay(1000);
  }
}

/*
 * Parse http response
 */
void parseJSON(String payload) {

  DynamicJsonDocument doc(2048);

  DeserializationError error = deserializeJson(doc, payload);

  if (error) 
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }

  numberAlerts = doc["data"]["alerts"].size();
  if (numberAlerts > 0)
  {
    alertsPresents = true;
  }

  const char* status = doc["status"]; // "success"
  for (int i = 0; i < numberAlerts; i++) 
  {
    
    JsonObject alert = doc["data"]["alerts"][i];
    JsonObject alert_labels = alert["labels"];
    alertName = alert_labels["alertname"]; // "NodeExporterDown"
    const char* alerts_labels_instance = alert_labels["instance"]; // "nodeexporter:9100"
    const char* alert_labels_job = alert_labels["job"]; // "prometheus-node-exporter"

    Serial.printf("Loop i : %i\n", i);
    // Print values.
    if (alertsPresents)
    {
 //     Serial.printf("Alerts are present : %b\n", alertsPresents);
 //      Serial.printf("Number od alerts : %i alerts\n", numberAlerts);
      Serial.printf("Alertname : %s\n", alertName);
 //     Serial.printf("Instance : %s\n", alerts_labels_instance);
 //     Serial.printf("Job : %s\n", alert_labels_job);
    }

    // Update status values
    if (strcmp (alertName ,serverAlert) == 0){
      serverDown = true;
    }
    else if (strcmp (alertName ,nodesAlert) == 0) {
      nodeDown = true; 
    }
    else if (strcmp (alertName ,appsAlert) == 0) {
      appDown = true;
    }
  }

  delay(5000);
}

/*
 * Configure pins for all the leds
 */
void configureLeds() {
  int i;
  for(i=0; i<numPins; i++)
  {
    // set pins to OUTPUT 
    pinMode(ledList[i], OUTPUT);
  }

  for(i=0; i<numPins; i++)
  {
    // turn on all LEDs
    digitalWrite(ledList[i], HIGH);
  }
  
  // wait 1 second
  delay(1000);
  
  for(i=0; i<numPins; i++)
  {
    // turn off all LEDs
    digitalWrite(ledList[i], LOW);
  }

  // wait 1 second
  delay(1000);

  for(i=0; i<numPinsEachColor; i++)
  {
    // turn on red LEDs
    digitalWrite(redLedList[i], HIGH);
  }

  // wait 1 second
  delay(1000);
  
  for(i=0; i<numPinsEachColor; i++)
  {
    // turn on green LEDs
    digitalWrite(greenLedList[i], HIGH);
  }

  // wait 1 second
  delay(1000);

  for(i=0; i<numPins; i++)
  {
    // turn off all LEDs
    digitalWrite(ledList[i], LOW);
  }

  // wait 1 second
  delay(1000);
}

/*
 * Display alerts with leds
 */
void displayAlerts() {

  // if Cluster K3s down turn on red server down led
  if (serverDown) {
    digitalWrite(serverDownLed, HIGH);
  }
  // if Cluster K3s up turn on green server up led
  else {
    digitalWrite(serverUpLed, HIGH);
  }

  // if Node K3s down turn on red node down led
   if (nodeDown) {
    digitalWrite(nodeDownLed, HIGH);
  }
  // if Node K3s up turn on green node up led
  else {
    digitalWrite(nodeUpLed, HIGH);
  }

  // if App K3s down turn on red app down led
  if (appDown) {
    digitalWrite(appDownLed, HIGH);
  }
  // if App K3s up turn on green app up led
  else {
    digitalWrite(appUpLed, HIGH);
  }
}