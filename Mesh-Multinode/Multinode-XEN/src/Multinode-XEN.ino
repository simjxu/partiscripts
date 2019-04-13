// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

SYSTEM_MODE(SEMI_AUTOMATIC);

int digitalD7 = D7;
bool bor_resp = false;
bool ping_attempt = false;
int attempts = 0;
String datastring = "123456789012345678901234567890";

void wakeHandler(const char *event, const char *data) {
  Serial.println("wakeupcalled");
  Mesh.publish("bor_ping", System.deviceID() + " : " + datastring);
  ping_attempt = true;
}

void pongHandler(const char *event, const char *data) {
  Serial.println("ack received");
  bor_resp = true;
}

void updateHandler(const char *event, const char *data) {
  Serial.println("getting update...");
  Particle.connect();
  while(Particle.connected()!=true) {
    delay(1000);
  }
  Serial.println("connected!");
}

void resetHandler(const char *event, const char *data) {
  System.reset();
}

void setup() {
  Mesh.on();
  Mesh.connect();
  pinMode(digitalD7,OUTPUT);		// This is the onboard led

  Mesh.subscribe("wakeup_xenon", wakeHandler);
  Mesh.subscribe("bor_pong:"+System.deviceID(), pongHandler);
  Mesh.subscribe("flash_update", updateHandler);
  Mesh.subscribe("reset", resetHandler);
}

void loop() {
  // Serial.println("Pingattempt:"+String(ping_attempt));
  // Serial.println("bor_resp:"+String(bor_resp));
  // Serial.println("attempts:"+String(attempts));
  while(ping_attempt==true && bor_resp==false && attempts<5) {
    delay(2000);
    if(bor_resp==false){
      Serial.println("retrying ping...");
      Mesh.publish("bor_ping", System.deviceID() + " : " + datastring);
      attempts += 1;
    }
  }
  bor_resp = false;
  ping_attempt = false;
  attempts = 0;
}

