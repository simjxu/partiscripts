// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

// -----------------------------------------
// Function and Variable with Photoresistors
// -----------------------------------------

int digitalD4 = D4;
int digitalD7 = D7;
String onoff;


void setup() {
  pinMode(digitalD4,OUTPUT);		
  pinMode(digitalD7,OUTPUT);		// This is the onboard led
  // Make ability to communicate with LED
  Particle.function("led",ledToggle);
}


// Next is the loop function...

void loop() {

	// If global variable shows on, switch to off, and vice versa
  if (onoff == "D4on") {
    onoff = "D4off";
  }
  else {
    onoff = "D4on";
  }

  Serial.print(onoff);

  Mesh.publish("bor_ping", String(onoff));
  digitalWrite(digitalD7, HIGH);
  delay(1000);
  digitalWrite(digitalD7, LOW);

  // Delay for 1 seconds
	delay(1000);
}

// Finally, we will write out our ledToggle function, which is referenced by the Particle.function() called "led"

int ledToggle(String command) {

	if (command=="on") {
		digitalWrite(digitalD4,HIGH);
		return 1;
	}
	else if (command=="off") {
		digitalWrite(digitalD4,LOW);
		return 0;
	}
	else {
		return -1;
	}

}