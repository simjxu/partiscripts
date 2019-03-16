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
#line 7 "/Users/simonxu/Projects/Github-simjxu/partiscripts/electron_test/src/electron_test.ino"
bool claimflag = false;

void setup() {
  
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  if(claimflag==false){
    claimflag = true;
    Particle.publish("claim_flag");
  }
  delay(50);
}