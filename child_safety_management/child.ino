#include <SoftwareSerial.h>

// GPS and GSM serial
SoftwareSerial gpsSerial(4, 3);   // RX, TX
SoftwareSerial gsmSerial(7, 8);   // RX, TX

int rfTxPin = 12;

String latitude = "";
String longitude = "";

void setup() {
  pinMode(rfTxPin, OUTPUT);

  Serial.begin(9600);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);

  delay(2000);
}

void loop() {
  // Continuously transmit RF signal
  digitalWrite(rfTxPin, HIGH);
  delay(100);
  digitalWrite(rfTxPin, LOW);
  delay(100);

  // Read GPS data
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    Serial.print(c);
  }
}

// Function to send alert SMS
void sendAlert() {
  gsmSerial.println("AT");
  delay(1000);

  gsmSerial.println("AT+CMGF=1");  // Text mode
  delay(1000);

  gsmSerial.println("AT+CMGS=\"+91XXXXXXXXXX\""); // Parent number
  delay(1000);

  gsmSerial.print("ALERT! Child out of safe zone.");
  gsmSerial.write(26); // Ctrl+Z
  delay(3000);
}
