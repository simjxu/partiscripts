
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

// Next we go into the setup function.

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

	// bool success;
	// success = Particle.publish("light_level");
	// if (!success) {
	// // get here if event publish did not work
	// }

}


// Next is the loop function...

void loop() {

	// check to see what the value of the photoresistor is and store it in the int variable analogvalue
	// To get the value of this variable, you will have to run
	// Ou need to change device ID, but access token is same for your account
	// curl https://api.particle.io/v1/devices/5c0032001951353338363036/analogvalue?access_token=39c7655424cc7f16ac8363b2c8913d3cccea141d
	analogvalue = analogRead(photoresistor);
	delay(5);

	// if (analogvalue < 2500) {
	//     digitalWrite(led,HIGH);
	// }
	// else if (analogvalue > 2500) {
	//     digitalWrite(led,LOW);
	// }

	// min is 40, max is 340
	if (analogvalue > minim && analogvalue < maxim) {
			setpoint = 255-(analogvalue-minim)/300*255;
	} else if (analogvalue <= minim) {
	setpoint = 254;
	} else if (analogvalue >= maxim) {
		setpoint = 0;
	} else {
		setpoint = 0;
	}
	pinMode(pwm, OUTPUT);

	// // Set the D7 on board LED
	// if (analogvalue > 100) {
	// 	digitalWrite(boardled, LOW);
	// } else {
	// 	digitalWrite(boardled, HIGH);
	// }

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
	
	// Publish light level event, which connects to slack webhook 
	// (change threshold to something lower if you want)
	if (analogvalue < 50) {
	    Particle.publish("low_light", String(analogvalue), NO_ACK);
	}

	// Make sure it doesn't publish too much
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