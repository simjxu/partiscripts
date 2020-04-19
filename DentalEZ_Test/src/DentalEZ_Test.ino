/*
 * Project DentalEZ_Test
 * Description:
 * Author:
 * Date:
 */

#include "application.h"
#include "deviceid_hal.h"

String result_string = "{\"seq\":12,\"model_number\":OSP24B,\"hi_pot_passed\":true,\"grounding_passed\":true,\"purge_valve_cycled\":true,\"heat_exchanger_runs\":true,\"no_abnormal_noise\":true,\"headcheck_left\":true,\"headcheck_center\":true,\"headcheck_right\":true,\"pre_end_decay\":[108,107,1],\"post_end_decay\":[111,109,2],\"pre_end_volt\":220,\"pre_end_amp\":15.8,\"post_end_volt\":218,\"post_end_amp\":14.5,\"head_leak_check_passed\":true,\"endurance_time_start\":[1571046600,0],\"endurance_time_stop\":[1571137200,10.1]}";
bool pubresults = false;

int funcCMD(String fcn){
  if(fcn=="run_test"){
    pubresults = true;
    
  }
  return 0;
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Particle.function("CMD", funcCMD);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  delay(10000);
  if(pubresults==true){
    Particle.publish("dz_testresults", result_string);
    pubresults = false;
  }
}