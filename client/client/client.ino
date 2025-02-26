#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Credentials
const char *ssid = "Venky";
const char *password = "98989898";

// Servers
const char *authServer = "https://test-three-kappa-52.vercel.app/login";
const char *verifyServerIP = "192.168.43.136";  // Replace with ESP #2's IP
const int verifyServerPort = 80;

WiFiClientSecure client;
String jwtToken = "";  // Store JWT token

// Time tracking variables
unsigned long jwtStartTime, jwtEndTime, jwtTotalTime = 0;
unsigned long verifyStartTime, verifyEndTime, totalVerifyTime = 0;
unsigned long totalCommunicationTime = 0;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500); 
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi!");

    getJWT();
}

void loop() {
    if (!jwtToken.isEmpty()) {
        sendTokenToServer();
    }
    delay(10000);  // Send every 10 seconds
}

// Function to get JWT token
void getJWT() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        client.setInsecure();  // Disable SSL verification
        
        Serial.println("Sending Authentication Request...");
        http.begin(client, authServer);
        http.addHeader("Content-Type", "application/json");

        // JSON Payload
        StaticJsonDocument<128> jsonDoc;
        jsonDoc["username"] = "admin";
        jsonDoc["password"] = "password123";

        String requestBody;
        serializeJson(jsonDoc, requestBody);

        jwtStartTime = millis();  // Start Timer

        // Send POST request
        int httpCode = http.POST(requestBody);
        String response = http.getString();

        jwtEndTime = millis();  // End Timer
        jwtTotalTime = jwtEndTime - jwtStartTime;

        Serial.println("Server Response:");
        Serial.println(response);
        Serial.printf("Time taken to get JWT Token: %lu ms\n", jwtTotalTime);

        if (httpCode == 200) {
            // Parse JSON Response
            StaticJsonDocument<256> responseDoc;
            DeserializationError error = deserializeJson(responseDoc, response);

            if (error) {
                Serial.println("Failed to parse JSON!");
            } else {
                jwtToken = responseDoc["token"].as<String>();  // Extract JWT Token
                Serial.println("JWT Token Received:");
                Serial.println(jwtToken);
            }
        } else {
            Serial.printf("Authentication Failed: Error %d\n", httpCode);
        }

        http.end();  // Close HTTP Connection
    }
}

// Function to send JWT token for verification
void sendTokenToServer() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        WiFiClient client;

        String url = "http://" + String(verifyServerIP) + ":" + String(verifyServerPort) + "/verify";

        Serial.println("Sending Token for Verification...");
        http.begin(client, url);
        http.addHeader("Content-Type", "application/json");

        // JSON Payload
        StaticJsonDocument<128> jsonDoc;
        jsonDoc["token"] = jwtToken;

        String requestBody;
        serializeJson(jsonDoc, requestBody);

        verifyStartTime = millis();  // Start Timer

        int httpCode = http.POST(requestBody);
        String response = http.getString();

        verifyEndTime = millis();  // End Timer
        totalVerifyTime = verifyEndTime - verifyStartTime;

        // Update total communication time
        totalCommunicationTime += (jwtTotalTime + totalVerifyTime);

        Serial.println("Server Response:");
        Serial.println(response);
        Serial.printf("Time taken for Token Verification: %lu ms\n", totalVerifyTime);
        Serial.printf("Total Communication Time: %lu ms\n", totalCommunicationTime);

        http.end();
    } else {
        Serial.println("WiFi Disconnected! Reconnecting...");
        WiFi.begin(ssid, password);
    }
}
