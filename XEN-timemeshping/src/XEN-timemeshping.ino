// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

SYSTEM_MODE(SEMI_AUTOMATIC);

int digitalD7 = D7;
bool bor_resp = false;
String datastring = "123456789012345678901234567890";

void pongHandler(const char *event, const char *data) {
  bor_resp = true;
}

void setup() {
  Mesh.on();
  Mesh.connect();
  pinMode(digitalD7,OUTPUT);		// This is the onboard led

  Mesh.subscribe("pong"+System.deviceID(), pongHandler);
}

void loop() {
  // execute only if the mesh connects
  if(Mesh.ready() == true){
    Serial.println("Mesh ready");
    bor_resp = false;

    // Issue a publish request to the boron
    Mesh.publish("ping"+System.deviceID(),datastring);

    // Wait for Boron's pong
    delay(2000);
    if(bor_resp == false){
      Mesh.publish("ping"+System.deviceID(),datastring);
    }
    delay(1000);

    System.sleep();
  }

  delay(1000);
}

