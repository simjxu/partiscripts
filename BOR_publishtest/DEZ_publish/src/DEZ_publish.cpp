/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/Users/simonxu/Projects/Github-simjxu/partiscripts/BOR_publishtest/DEZ_publish/src/DEZ_publish.ino"
/*
 * Project DEZ_publish
 * Description:
 * Author:
 * Date:
 */

// String pub_var = "{\"seq\":12,\"time\":1563399253,\"error\":2,\"source\":\"AH\"}";
void setup();
void loop();
#line 9 "/Users/simonxu/Projects/Github-simjxu/partiscripts/BOR_publishtest/DEZ_publish/src/DEZ_publish.ino"
String pub_var = "{\"seq\":12,\"time\":1563399253,\"error\":2}";

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  delay(10000);
  Particle.publish("alert",pub_var);

}