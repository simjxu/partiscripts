// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

SYSTEM_MODE(SEMI_AUTOMATIC);

int digitalD7 = D7;

void setup() {
  pinMode(digitalD7, OUTPUT);
}

void loop() {
  // Send wakeup to D8 pin
  digitalWrite(digitalD7, HIGH);
  delay(1000);
  digitalWrite(digitalD7, LOW);

  Serial.println(Time.now());
  delay(599000);
}
