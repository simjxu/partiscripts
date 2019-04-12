// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

SYSTEM_MODE(SEMI_AUTOMATIC);

int digitalD7 = D7;
bool bor_resp = false;
bool wake_called = false;
bool ping_attempt = false;
String datastring = "123456789012345678901234567890";

void wakeHandler(const char *event, const char *data) {
  Serial.println("wakeupcalled");
  Mesh.publish("bor_ping", System.deviceID() + " : " + datastring);
  wake_called = true;
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

void setup() {
  Mesh.on();
  Mesh.connect();
  pinMode(digitalD7,OUTPUT);		// This is the onboard led

  Mesh.subscribe("wakeup_xenon", wakeHandler);
  Mesh.subscribe("bor_pong:"+System.deviceID(), pongHandler);
  Mesh.subscribe("flash_update", updateHandler);
}

void loop() {
  if(wake_called==true){
    delay(1000);
    if(ping_attempt==true && bor_resp==false){
      Serial.println("retrying ping...");
      Mesh.publish("bor_ping", System.deviceID() + " : " + datastring);
    }
  }
  bor_resp = false;
  ping_attempt = false;
  wake_called = false;
}

