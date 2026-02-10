int rfRxPin = 11;
int buzzer = 9;

unsigned long lastSignalTime = 0;
unsigned long timeout = 3000;  // 3 seconds

void setup() {
  pinMode(rfRxPin, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int signal = digitalRead(rfRxPin);

  if (signal == HIGH) {
    lastSignalTime = millis();
    digitalWrite(buzzer, LOW);
  }

  // If signal lost
  if (millis() - lastSignalTime > timeout) {
    Serial.println("Unsafe Condition Detected!");
    digitalWrite(buzzer, HIGH);
    delay(1000);
  }
}
