/*
 * Project electron_test
 * Description:
 * Author:
 * Date:
 */
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