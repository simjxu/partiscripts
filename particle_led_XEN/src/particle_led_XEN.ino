// 37.33773842860023, -122.01428063652223
// 37.337772088687366, -122.00540290465861
// Output ---> 90 degrees

// 37.337652150532776, -122.01422938622564
// 37.34138504412391, -122.01425213575031
// Output ---> 360 degrees


#include <math.h>

double PI = 3.14159265359;
double a = PI/6;			// 30 degrees = pi/6



double pre_lat_deg = 37.337652150532776;
double pre_lng_deg = -122.01422938622564;
double lat_deg = 37.34138504412391;
double lng_deg = -122.01425213575031;

double pre_lat = pre_lat_deg*PI/180;
double pre_lng = pre_lng_deg*PI/180;
double lat = lat_deg*PI/180;
double lng = lng_deg*PI/180;
double d;


SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {

}


// Next is the loop function...
// (atan2(cos(lat)*sin(lng-pre_lng), cos(pre_lat)*sin(lat) - sin(pre_lat)*cos(lat)*cos(lng-pre_lng)) * 180 / pi() + 360  ) % 360

void loop() {
	// Capture how long it takes to run
	unsigned long stop;
	unsigned long start;
	start = micros();


	Serial.println("Answer:");

	d = fmod(atan2(cos(lat)*sin(lng-pre_lng), cos(pre_lat)*sin(lat) - sin(pre_lat)*cos(lat)*cos(lng-pre_lng)) * 180.0/PI + 360.0, 360.0);
	Serial.println(d,10);

	// Check how long it took
	Serial.println("Time elapsed:");
	stop = micros();
	Serial.println(stop-start);

	delay(5000);
	
}


// Finally, we will write out our ledToggle function, which is referenced by the Particle.function() called "led"

int calculator(String command) {

	// if (command=="on") {
	// 	digitalWrite(boardled,HIGH);
	// 	return 1;
	// }
	// else if (command=="off") {
	// 	digitalWrite(boardled,LOW);
	// 	return 0;
	// }
	// else {
	// 	return -1;
	// }

}