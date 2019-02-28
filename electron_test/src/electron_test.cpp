#include "application.h"
#line 1 "/Users/simonxu/Projects/Github-simjxu/partiscripts/electron_test/src/electron_test.ino"
/*
 * Project electron_test
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "/Users/simonxu/Projects/Github-simjxu/partiscripts/electron_test/src/electron_test.ino"
int digi_in = D0;

void setup() {
  // Set pin D0 to input
  pinMode(digi_in,INPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  int status = digitalRead(digi_in);
  if (status == 1) {
    Particle.publish("HIGH");
  }
  delay(50);
}