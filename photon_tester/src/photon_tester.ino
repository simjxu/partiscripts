

int count = 0;
int digitalD7 = D7;
void setup() {
  pinMode(digitalD7,OUTPUT);		// This is the onboard led
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  Particle.publish("ppinterval");
  digitalWrite(digitalD7, HIGH);
  delay(150000);
  digitalWrite(digitalD7, LOW);
  delay(150000);
}