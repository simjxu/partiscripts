// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

// -----------------------------------------
// Function and Variable with Photoresistors
// -----------------------------------------

int boardled = D7;
bool onoff = true;


void setup() {
  pinMode(boardled,OUTPUT);		// This is the onboard led
  // Make ability to communicate with LED
  Particle.function("led",ledToggle);
}


// Next is the loop function...

void loop() {

	// If global variable shows on, switch to off, and vice versa
  if (onoff == true) {
    onoff = false;
  }
  else {
    onoff = true;
  }

  Serial.print(onoff);

  Mesh.publish("bor_ping", String(onoff));

  // Delay for 2 seconds
	delay(2000);
}

// Finally, we will write out our ledToggle function, which is referenced by the Particle.function() called "led"

int ledToggle(String command) {

	if (command=="on") {
		digitalWrite(boardled,HIGH);
		return 1;
	}
	else if (command=="off") {
		digitalWrite(boardled,LOW);
		return 0;
	}
	else {
		return -1;
	}

}