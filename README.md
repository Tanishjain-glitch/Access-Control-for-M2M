# Access-Control-for-M2M

📌 Project Overview
Secure Machine-to-Machine (M2M) authentication and access control using ESP8266.
Uses JWT-based authentication for secure communication.
Integrates DHT11 (temperature & humidity) and MQ6 (gas sensor).
🛠️ Hardware Requirements
ESP8266 x 2 (Client & Server)
DHT11 (Temperature & Humidity Sensor) – Connected to D4
MQ6 (Gas Sensor) – Connected to D2
Wi-Fi Network
⚙️ Software Requirements
Arduino IDE (With ESP8266 board support)
Required Libraries:

🚦 Working Flow
🔹 ESP #1 (Client)
✅ Connects to WiFi
✅ Sends username & password to the authentication server
✅ Receives a JWT Token upon successful authentication
✅ Starts a timer when sending a token to ESP #2

🔹 ESP #2 (Server)
✅ Receives the JWT Token
✅ Verifies it
✅ If valid, reads DHT11 & MQ6 sensor data
✅ Sends temperature, humidity, and gas levels back to ESP #1
✅ Stops timer upon response

🔹 ESP #1 (Client)
✅ Prints received sensor data
✅ Logs total authentication & response time



📝 Author
👤 Tanish Jain
🔗 GitHub: Tanishjain-glitch
