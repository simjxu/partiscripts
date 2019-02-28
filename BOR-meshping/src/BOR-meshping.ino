// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

// -----------------------------------------
// Function and Variable with Photoresistors
// -----------------------------------------

int pwm = A4;
int boardled = D7;


double setpoint;
double minim = 40.0;
double maxim = 300.0;
double fadeamount = 1.0;
double brightness = 0.0;

void myHandler(const char *event, const char *data) {
  String incoming_data = data;
  Serial.print(event);
  Serial.print(", data: ");
  Serial.println(data);
  int setpoint = incoming_data.toInt();

  if (setpoint == 1){
    // analogWrite(pwm, 250);
    digitalWrite(boardled, HIGH);
    Serial.print("HIGH");
  }
  else {
    // analogWrite(pwm, 0);
    digitalWrite(boardled, LOW);
    Serial.print("LOW");
  }
  
}

void setup() {
	pinMode(boardled,OUTPUT);		// This is the onboard led

	pinMode(pwm, OUTPUT); // Pin for the pwm output


	// Add brightness as variable to test it out
	Particle.variable("brightness", &brightness, DOUBLE);
	Particle.variable("setpoint", &setpoint, DOUBLE);
	Particle.function("led",ledToggle);

	// // Subscribe to the xen_ping and point to Handler
  Mesh.subscribe("bor_ping", myHandler); 
}


// Next is the loop function...

void loop() {

  delay(5);


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
