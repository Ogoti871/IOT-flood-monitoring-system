void sendSMS(String phoneNumber, String message) {
Serial.println("Sending SMS...");
A9G.println("AT+CMGF=1");
delay(1000);
A9G.print("AT+CMGS=\"");
A9G.print(phoneNumber);
42A9G.println("\"");
delay(1000);
A9G.print(message);
delay(1000);
A9G.write(26);
delay(5000);
Serial.println("SMS Sent!");
}