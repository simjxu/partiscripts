// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

SYSTEM_MODE(SEMI_AUTOMATIC);

int digitalD7 = D7;
String onoff;
String pingpong = "";
int count = 0;
int sleep_time = 15;
String datamessage = "";

bool pong_flag = false;
bool meshlock = false;
bool pub_success = false;
bool publock = false;        // race condition lock/mutex
bool mesh_ack = false;

void pongHandler(const char *event, const char *data) {
  if(meshlock == false){
    pong_flag = true;
  }
}

void setup() {
  pinMode(digitalD7,OUTPUT);		// This is the onboard led
  // Make ability to communicate with LED
  Particle.function("led",ledToggle);

  // Listen for the D7 pong
  Mesh.subscribe("pong"+System.deviceID(), pongHandler);
}

void loop() {
  Mesh.off();

  delay(2000);

  Mesh.on();

  Mesh.connect();

  // execute only if the mesh connects
  if(Mesh.ready() == true){
    meshlock = false;
    Mesh.publish("bor_ping", String(System.deviceID()));
    digitalWrite(digitalD7, HIGH);
    delay(5000);

    // Wait for pong response show LED dark
    digitalWrite(digitalD7, LOW);

    // Check for length, publish success rate every 30 minutes
    Serial.println(pong_flag);
    if (pingpong.length() >= 60 && pong_flag == true){
      count = 0;
      for (int i = 0;i<pingpong.length();i++){
        if (pingpong[i] == '1'){    // Use single quotes for a character
          count++;
        }
      }
      
      // Try to publish the ppinterval with 60 mesh pingpongs, but if not successful, 
      // append more. Counting the number of additional 1s indicates how long network is down
      datamessage = String(System.deviceID()) + "," + String(count);
      Mesh.publish("bor_send", datamessage);
      
      pingpong = 1;
      
    } else if(pong_flag == true){
      pingpong += "1";
    } else {   // no mesh pong received in 5 seconds
      meshlock = true;
      pingpong += "0";
    }
    pong_flag = false;

    // // Sleep
    // System.sleep({},{},sleep_time);
    delay(5000);
    Serial.println(pingpong);
  }

  meshlock = false;
  Mesh.publish("bor_ping", String(System.deviceID()));
  digitalWrite(digitalD7, HIGH);
  delay(5000);

  // Wait for pong response show LED dark
  digitalWrite(digitalD7, LOW);

  // Check for length, publish success rate every 30 minutes
  Serial.println(pong_flag);
  if (pingpong.length() >= 60 && pong_flag == true){
    count = 0;
    for (int i = 0;i<pingpong.length();i++){
      if (pingpong[i] == '1'){    // Use single quotes for a character
        count++;
      }
    }
    
    // Try to publish the ppinterval with 60 mesh pingpongs, but if not successful, 
    // append more. Counting the number of additional 1s indicates how long network is down
    datamessage = String(System.deviceID()) + "," + String(count);
    Mesh.publish("bor_send", datamessage);
    
    pingpong = 1;
    
  } else if(pong_flag == true){
    pingpong += "1";
  } else {   // no mesh pong received in 5 seconds
    meshlock = true;
    pingpong += "0";
  }
  pong_flag = false;

  // // Sleep
	// System.sleep({},{},sleep_time);
  delay(5000);
  Serial.println(pingpong);
}

// Finally, we will write out our ledToggle function, which is referenced 
// by the Particle.function() called "led"
int ledToggle(String command) {

	if (command=="on") {
		digitalWrite(digitalD7,HIGH);
		return 1;
	}
	else if (command=="off") {
		digitalWrite(digitalD7,LOW);
		return 0;
	}
	else {
		return -1;
	}

}