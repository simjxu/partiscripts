/*
 * Project DEZ_publish
 * Description:
 * Author:
 * Date:
 */

// String pub_var = "{\"seq\":12,\"time\":1563399253,\"error\":2,\"source\":\"AH\"}";
String pub_var = "{\"seq\":12,\"time\":1563399253,\"error\":0,\"source\":\"AH\"}";

void test_publish(){
  Particle.publish("function_tested");
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Particle.function("pubtest", test_publish);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  
  Particle.publish("dz_alert",pub_var);
  delay(10000);
}