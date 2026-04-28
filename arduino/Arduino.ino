#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
const int trigPin = 9;
const int echoPin = 10;
#define A9G_TX 3
#define A9G_RX 2
SoftwareSerial A9G(A9G_RX, A9G_TX);
LiquidCrystal_I2C lcd(0x27, 16, 2);
const float riverWidth = 250.0;
const float riverMaxHeight = 7.0;
const float thresholdLevel = 6.3;
long duration;
float distanceToWater;
float waterLevelInMeters;
float precipitationData[5];
float cumulativeVolume = 0.0;
String precipitationDataStr = "";
int linesReceived = 0;
String lastFloodRisk = "NONE";
void setup() {
Serial.begin(9600);
Serial.println("System Initializing...");
lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("Initializing...");
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
A9G.begin(9600);
delay(5000);
}
void loop() {
if (Serial.available()) {
char receivedChar = Serial.read();
precipitationDataStr += receivedChar;
39if (receivedChar == '\n') {
linesReceived++;
}
}
if (linesReceived >= 5) {
parsePrecipitationData();
displayWaterLevel();
String floodRisk = performFloodPrediction();
if (floodRisk != lastFloodRisk) {
sendSMS("+254783610694", "Flood Risk: " + floodRisk);
lastFloodRisk = floodRisk;
}
precipitationDataStr = "";
linesReceived = 0;
}
}
float measureDistance() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
return (duration * 0.0343) / 2;
}
void displayWaterLevel() {
distanceToWater = measureDistance();
waterLevelInMeters = (15.0 - distanceToWater) * (7.0 / 15.0);
waterLevelInMeters = max(0, waterLevelInMeters);
Serial.println("===== Water Level in River =====");
Serial.print("Water Level: ");
Serial.print(waterLevelInMeters);
Serial.println(" meters");
Serial.println("==============================");
lcd.clear();
lcd.setCursor(0, 0);
40lcd.print("Water Level:");
lcd.setCursor(0, 1);
lcd.print(waterLevelInMeters);
lcd.print("m");
}
void parsePrecipitationData() {
int index = 0;
String line = "";
Serial.println("===== Precipitation Data =====");
for (int i = 0; i < precipitationDataStr.length(); i++) {
char currentChar = precipitationDataStr.charAt(i);
if (currentChar == '\n' || i == precipitationDataStr.length() - 1) {
if (i == precipitationDataStr.length() - 1 && currentChar != '\n') {
line += currentChar;
}
precipitationData[index] = line.toFloat();
Serial.print("Day ");
Serial.print(index + 1);
Serial.print(": Precipitation = ");
Serial.print(precipitationData[index]);
Serial.println(" mm");
line = "";
index++;
}
}
Serial.println("==============================");
}
String performFloodPrediction() {
cumulativeVolume = 0.0;
float totalRiseInMeters = 0.0;
Serial.println("===== Expected Water Rise =====");
for (int i = 0; i < 5; i++) {
float runoff = precipitationData[i] * 0.6;
float heightIncrease = runoff / (riverWidth * 1000);
cumulativeVolume += runoff;
totalRiseInMeters += heightIncrease;
Serial.print("Day ");
Serial.print(i + 1);
Serial.print(": Expected rise = ");
41Serial.print(heightIncrease);
Serial.println(" meters");
}
float predictedWaterLevel = waterLevelInMeters + totalRiseInMeters;
float riverMaxVolume = riverWidth * 1000 * riverMaxHeight;
float predictedVolume = riverWidth * 1000 * predictedWaterLevel;
float remainingStorage = riverMaxVolume - predictedVolume;
Serial.println("===== Cumulative Rise and Storage =====");
Serial.print("Cumulative Rise (in meters): ");
Serial.println(totalRiseInMeters);
Serial.print("Predicted Water Level: ");
Serial.println(predictedWaterLevel);
Serial.print("Remaining Storage Capacity: ");
Serial.print(remainingStorage);
Serial.println(" m³");
Serial.println("==============================");
String floodRisk = "LOW";
if (predictedWaterLevel >= 5.0) {
floodRisk = "HIGH";
} else if (predictedWaterLevel >= 4.5) {
floodRisk = "CRITICAL";
}
Serial.print("Flood Risk: ");
Serial.println(floodRisk);
lcd.setCursor(0, 0);
lcd.print("Flood Risk:");
lcd.setCursor(0, 1);
lcd.print(floodRisk);
return floodRisk;
}