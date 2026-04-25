# Access-Control-for-M2M

Secure Machine-to-Machine (M2M) authentication and access control using ESP8266 with JWT-based authentication for secure IoT communication.

---

## 📌 Project Overview

This project demonstrates secure communication between two ESP8266 devices using **JWT authentication** and **access control mechanisms**.

- **ESP8266 Client (ESP #1)** requests access to sensor data
- **ESP8266 Server (ESP #2)** verifies authentication token before granting access
- Uses **DHT11** sensor for temperature/humidity monitoring
- Uses **MQ6** sensor for gas detection
- Measures authentication and response time

This project simulates secure IoT communication for Machine-to-Machine environments.

---

## ✨ Features

- JWT-based authentication
- Secure token verification
- Machine-to-Machine communication
- Temperature monitoring
- Humidity monitoring
- Gas leakage detection
- Authentication latency measurement
- Lightweight IoT security implementation

---

## 🛠 Hardware Requirements

| Component | Quantity |
|------------|------------|
| ESP8266 NodeMCU | 2 |
| DHT11 Sensor | 1 |
| MQ6 Gas Sensor | 1 |
| Breadboard | 1 |
| Jumper Wires | As required |
| WiFi Network | 1 |

---

## 🔌 Circuit Connections

### DHT11 Sensor
| DHT11 Pin | ESP8266 Pin |
|------------|--------------|
| VCC | 3.3V |
| GND | GND |
| DATA | D4 |

### MQ6 Sensor
| MQ6 Pin | ESP8266 Pin |
|----------|--------------|
| VCC | 5V |
| GND | GND |
| AO/DO | D2 |

---

## ⚙️ Software Requirements

- Arduino IDE
- ESP8266 Board Package

### Required Libraries

```cpp
ESP8266WiFi.h
ESP8266HTTPClient.h
ArduinoJson.h
DHT.h
Hash.h



📝 Author
👤 Tanish Jain
🔗 GitHub: Tanishjain-glitch
