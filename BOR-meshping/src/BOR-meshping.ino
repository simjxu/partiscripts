// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

// -----------------------------------------
// Function and Variable with Photoresistors
// -----------------------------------------

int pwm = A4;
int digitalD7 = D7;
int digitalD6 = D6;
int digitalD5 = D5;
int digitalD4 = D4;


double minim = 40.0;
double maxim = 300.0;
double fadeamount = 1.0;
double brightness = 0.0;

void myHandler(const char *event, const char *data) {
  String incoming_data = data;
  Serial.print(event);
  Serial.print(", data: ");
  Serial.println(data);

  if (incoming_data == "D7on"){
    digitalWrite(digitalD7, HIGH);
    Serial.print("HIGH");
  }
  else if (incoming_data == "D7off"){
    digitalWrite(digitalD7, LOW);
    Serial.print("LOW");
  }
  else if (incoming_data == "D6on"){
    digitalWrite(digitalD6, HIGH);
    Serial.print("HIGH");
  }
  else if (incoming_data == "D6off"){
    digitalWrite(digitalD6, LOW);
    Serial.print("LOW");
  }
  else if (incoming_data == "D5on"){
    digitalWrite(digitalD5, HIGH);
    Serial.print("HIGH");
  }
  else if (incoming_data == "D5off"){
    digitalWrite(digitalD5, LOW);
    Serial.print("LOW");
  }
  else if (incoming_data == "D4on"){
    digitalWrite(digitalD4, HIGH);
    Serial.print("HIGH");
  }
  else if (incoming_data == "D4off"){
    digitalWrite(digitalD4, LOW);
    Serial.print("LOW");
  }
}

void setup() {
	pinMode(digitalD7,OUTPUT);		// This is the onboard led
  pinMode(digitalD6,OUTPUT);		// This is the onboard led
  pinMode(digitalD5,OUTPUT);		// This is the onboard led
  pinMode(digitalD4,OUTPUT);		// This is the onboard led

	pinMode(pwm, OUTPUT); // Pin for the pwm output


	// Add brightness as variable to test it out
	Particle.variable("brightness", &brightness, DOUBLE);
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
