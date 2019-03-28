// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);


int pwm = A4;
int digitalD7 = D7;
int digitalD6 = D6;
int digitalD5 = D5;
int digitalD4 = D4;
bool flagD7 = false;
bool flagD6 = false;
bool flagD5 = false;
bool flagD4 = false;
String deviceID1 = "e00fce685d8bc3665e1975a6";
String deviceID2 = "e00fce68791f786043777851";


double minim = 40.0;
double maxim = 300.0;
double fadeamount = 1.0;
double brightness = 0.0;

void myHandler(const char *event, const char *data) {
  String incoming_data = data;

  if (incoming_data == deviceID1){
    if(flagD7==false){
      digitalWrite(digitalD7, HIGH);
      Serial.print("HIGH1");
      flagD7 = true;
    } else {
      digitalWrite(digitalD7, LOW);
      Serial.print("LOW1");
      flagD7 = false;
    }
    Mesh.publish("pong"+deviceID1);
  } else {
    if(flagD6==false){
      digitalWrite(digitalD6, HIGH);
      Serial.print("HIGH1");
      flagD6 = true;
    } else {
      digitalWrite(digitalD6, LOW);
      Serial.print("LOW1");
      flagD6 = false;
    }
    Mesh.publish("pong"+deviceID2)
  }

}

void sendHandler(const char *event, const char *data) {
  String incoming_data = data;
  Particle.publish("ppinterval", incoming_data);
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
  Mesh.subscribe("bor_send", sendHandler);
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
