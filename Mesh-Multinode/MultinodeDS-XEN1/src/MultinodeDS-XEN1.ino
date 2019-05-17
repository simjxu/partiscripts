SYSTEM_MODE(MANUAL);

bool bor_resp = false;
int attempts = 0;
int starttime = 0;
int timecheck = 0;
int sendTime = 0;
String datastring = "123456789012345678901234567890";

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
  sendTime = Time.now();
  starttime = millis();
  Mesh.on();
  Mesh.connect();
  waitFor(Network.ready, 10000);

  timecheck = millis()-starttime;

  Mesh.subscribe("bor_pong:"+System.deviceID(), pongHandler);
  Mesh.subscribe("flash_update", updateHandler);
  Mesh.subscribe("reset", resetHandler);
}

void loop() {
  bor_resp = false;
  attempts = 0;
  Serial.println("woke up from deep sleep");
  Mesh.publish("bor_ping", System.deviceID() + " : " + datastring + " : " + String(attempts) + " : " + String(timecheck));
  Serial.println("sent message");
  while(bor_resp==false && attempts<5) {
    delay(2000);
    if(bor_resp==false){
      Serial.println("retrying ping...");
      attempts += 1;
      Mesh.publish("bor_ping", System.deviceID() + " : " + datastring + " : " + String(attempts) + " : " + String(timecheck));
    }
  }
  Serial.println(timecheck);
  System.sleep(SLEEP_MODE_DEEP);
}

