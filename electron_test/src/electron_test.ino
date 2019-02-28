/*
 * Project electron_test
 * Description:
 * Author:
 * Date:
 */
SerialLogHandler logHandler(115200, LOG_LEVEL_TRACE);
int digi_in = D0;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  // Set pin D0 to input
  pinMode(digi_in,INPUT);
  Particle.variable("digivalue", &digi_in, INT);
  cellular_set_power_mode(0, NULL);
  Particle.connect();
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