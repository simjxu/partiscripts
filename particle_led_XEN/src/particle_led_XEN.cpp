#include "application.h"
#line 1 "/Users/simonxu/Projects/Github-simjxu/partiscripts/particle_led_XEN/src/particle_led_XEN.ino"
// PRODUCT_ID(8184);
// PRODUCT_VERSION(1);

// -----------------------------------------
// Function and Variable with Photoresistors
// -----------------------------------------
/*
In this example, we're going to register a Particle.variable() with
 the cloud so that we can read brightness levels from the photoresistor.
We'll also register a Particle.function so that we can turn the LED on 
and off remotely.

We're going to start by declaring which pins everything is plugged into.
*/
void myHandler(const char *event, const char *data);
void setup();
void loop();
int ledToggle(String command);
#line 15 "/Users/simonxu/Projects/Github-simjxu/partiscripts/particle_led_XEN/src/particle_led_XEN.ino"
int led = D6; // This is where your LED is plugged in. 
							//The other side goes to a resistor connected to GND.
int pwm = A4;

int boardled = D7;

int photoresistor = A0; // This is where your photoresistor is plugged in. 
												// The other side goes to the "power" pin (below).

int power = A5; // This is the other end of your photoresistor. The other side 
// is plugged into the "photoresistor" pin (above).
// The reason we have plugged one side into an analog pin instead of to 
// "power" is because we want a very steady voltage to be sent to the photoresistor.
// That way, when we read the value from the other side of the photoresistor,
// we can accurately calculate a voltage drop.

double analogvalue; // Here we are declaring the integer variable analogvalue, 
										// which we will use later to store the value of the photoresistor.
double setpoint;
double minim = 40.0;
double maxim = 300.0;
double fadeamount = 1.0;
double brightness = 0.0;

void myHandler(const char *event, const char *data) {
  String incoming_data = data;
  int setpoint = incoming_data.toInt();
	brightness = setpoint;
  // Serial.print(event);
  // Serial.print(", data: ");
  // Serial.println(data);


  // analogWrite(pwm, setpoint);
  Serial.print(setpoint);
  Particle.publish("change_brightness", "testing");
}

void setup() {

	// First, declare all of our pins. This lets our device know which ones will be 
	// used for outputting voltage, and which ones will read incoming voltage.
	pinMode(led,OUTPUT); // Our LED pin is output (lighting up the LED)
	pinMode(boardled,OUTPUT);		// This is the onboard led
	pinMode(photoresistor,INPUT);  // Our photoresistor pin is input 
																 // (reading the photoresistor)
	pinMode(power,OUTPUT); // The pin powering the photoresistor is output 
												 // (sending out consistent power)
	pinMode(pwm, OUTPUT); // Pin for the pwm output

	// Next, write one pin of the photoresistor to be the maximum possible, so that 
	// we can use this for power.
	digitalWrite(power,HIGH);

	// We are going to declare a Particle.variable() here so that we can access 
	// the value of the photoresistor from the cloud.
	Particle.variable("analogvalue", &analogvalue, DOUBLE);
	// This is saying that when we ask the cloud for "analogvalue", this will reference 
	// the variable analogvalue in this app, which is an integer variable.

	// Add brightness as variable to test it out
	Particle.variable("brightness", &brightness, DOUBLE);
	Particle.variable("setpoint", &setpoint, DOUBLE);


	// We are also going to declare a Particle.function so that we can turn the LED on 
	// and off from the cloud.
	Particle.function("led",ledToggle);
	// This is saying that when we ask the cloud for the function "led", it will employ 
	//the function ledToggle() from this app.

	// Subscribe to the light_level and point to Handler
  Mesh.subscribe("change_brightness", myHandler);
}


// Next is the loop function...

void loop() {
	delay(5);

	// Check the setpoint vs the brightness
	if (brightness < setpoint && brightness < 252) {
		brightness = brightness + fadeamount;
		analogWrite(pwm, brightness);
	} else if (brightness > setpoint && brightness > 1.3) {
		brightness = brightness - fadeamount;
		analogWrite(pwm, brightness);
	} else {
		brightness = brightness;
	}
	
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