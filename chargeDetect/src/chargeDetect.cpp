/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/simonxu/Projects/Github-simjxu/partiscripts/chargeDetect/src/chargeDetect.ino"
/*
 * Project chargeDetect
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "/Users/simonxu/Projects/Github-simjxu/partiscripts/chargeDetect/src/chargeDetect.ino"
FuelGauge fuel;
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  delay(5000);
  String soc = String(fuel.getSoC());
  Particle.publish("charge", soc);
}