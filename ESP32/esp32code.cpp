#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
// Wi-Fi credentials
const char* ssid = "silicon valley";
const char* password = "#teslaModelS300";
// API endpoint URL
const
char*
apiUrl
=
"https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/Garissa?u
nitGroup=us&include=days%2Calerts%2Ccurrent&key=R5FCNQ7ZPUHAW7RXC5DZMSLR
C&contentType=json";
// Initialize Serial2 for communication with Arduino (TX2=GPIO 17, RX2=GPIO 16)
HardwareSerial SerialESP(2);
void setup() {
Serial.begin(115200); // Debugging
SerialESP.begin(9600, SERIAL_8N1, 16, 17); // Communication with Arduino
// Connect to Wi-Fi
Serial.print("Connecting to Wi-Fi...");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
36Serial.println("\nWi-Fi Connected!");
}
void loop() {
if (WiFi.status() == WL_CONNECTED) {
WiFiClientSecure client;
client.setInsecure();
HTTPClient https;
https.begin(client, apiUrl);
https.addHeader("Accept-Encoding", "identity");
int httpResponseCode = https.GET();
if (httpResponseCode > 0) {
String payload = https.getString();
StaticJsonDocument<4096> doc;
DeserializationError error = deserializeJson(doc, payload);
if (error) {
Serial.print("JSON Parsing failed: ");
Serial.println(error.c_str());
} else {
JsonArray days = doc["days"];
int dayCount = 0;
for (JsonObject day : days) {
if (dayCount >= 5) break; // Only process the first 5 days
const char* date = day["datetime"];
37float precipitation = day["precip"] | 0.0;
// Send data to Arduino
SerialESP.print("Date: ");
SerialESP.print(date);
SerialESP.print(" - Precipitation: ");
SerialESP.print(precipitation);
SerialESP.println(" mm");
dayCount++;
}
}
} else {
Serial.print("Error on HTTP request: ");
Serial.println(httpResponseCode);
}
https.end();
} else {
Serial.println("WiFi not connected");
}
delay(10000); // Delay before next request
}