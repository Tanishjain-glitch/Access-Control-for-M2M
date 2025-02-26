#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <DHT.h>

// WiFi Credentials
const char *ssid = "Venky";
const char *password = "98989898";

ESP8266WebServer server(80);

// DHT11 Sensor (Temperature & Humidity)
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ6 Gas Sensor
#define MQ6PIN A0

// Sample Valid Token (Ideally should be dynamically stored)
String validToken = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFkbWluIiwiaWF0IjoxNzM5MjY5Mjc5LCJleHAiOjE3MzkyNzI4Nzl9.LXtHtd7djRChPi7hb7OHEISCF8IkIm3R6xOnn73R5XI";  

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi!");

    // Print the IP Address assigned by the router
    Serial.print("ESP8266 Server IP Address: ");
    Serial.println(WiFi.localIP());  // Print IP Address

    dht.begin();

    server.on("/verify", HTTP_POST, handleTokenVerification);
    server.begin();
    Serial.println("Server started!");
}


void loop() {
    server.handleClient();
}

void handleTokenVerification() {
    if (server.hasArg("plain") == false) {
        server.send(400, "application/json", "{\"message\": \"Bad Request - No JSON\"}");
        return;
    }

    String body = server.arg("plain");
    Serial.println("Received Token:");
    Serial.println(body);

    // Parse JSON
    StaticJsonDocument<128> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, body);

    if (error) {
        server.send(400, "application/json", "{\"message\": \"Invalid JSON\"}");
        return;
    }

    String receivedToken = jsonDoc["token"].as<String>();

    if (receivedToken == validToken) { 
        Serial.println("Token Verified!");

        // Read DHT11 Sensor Data
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        // Read MQ6 Sensor Data
        int gasLevel = analogRead(MQ6PIN);

        // Prepare JSON Response
        StaticJsonDocument<256> responseDoc;
        responseDoc["message"] = "Token Verified!";
        responseDoc["temperature_C"] = temperature;
        responseDoc["humidity_%"] = humidity;
        responseDoc["gas_level"] = gasLevel;

        String jsonResponse;
        serializeJson(responseDoc, jsonResponse);

        server.send(200, "application/json", jsonResponse);
    } else {
        server.send(403, "application/json", "{\"message\": \"Invalid Token\"}");
    }
}
