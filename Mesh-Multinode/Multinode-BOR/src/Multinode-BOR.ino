#include <queue>
using namespace std;

std::queue<String> device_queue;      // queue of device ids
std::queue<String> attempt_queue;     // queue of attempts
String devid = "";
String xenons[] = {"","","","","","","","","","","","","","","","","","","",""};
String attempts = "";
String attemptcnt[] = {"","","","","","","","","","","","","","","","","","","",""};
int restart_time = 0;

// Change this to equate to number of devices
int num_devices = 1;
int meshcount = num_devices;

void pingHandler(const char *event, const char *data) {
  String incoming_data = data;

  // Grab the device ID: first 24 characters of the string
  devid = incoming_data.substring(0,24);
  device_queue.push(devid);
  attempts = incoming_data.substring(58,incoming_data.length());     // maybe length isn't correct?
  attempt_queue.push(attempts);
}

void setup() {
  // Function to get devices connected to cloud
  Particle.function("xen_cnct",xenon_connect);

	// Subscribe to the xen_ping and point to Handler
  Mesh.subscribe("bor_ping", pingHandler); 
  restart_time = millis();
} 

void loop() {
  bool isUnique = true;
  while (!device_queue.empty()) { 
    Mesh.publish("bor_pong:"+device_queue.front());
    
    // Check if the device id is unique
    if(meshcount==0) {
      xenons[0] = device_queue.front();
    }

    // Make sure that the device id is unique, otherwise, do not count it
    for(int i=0;i<meshcount;i++) {
      if(xenons[i]==device_queue.front()) {
        isUnique = false;
        break;
      }
    }
    // If device ID is not found in array, then count it!
    if(isUnique==true) {
      xenons[meshcount] = device_queue.front();
      attemptcnt[meshcount] = attempt_queue.front();
      meshcount += 1;
    }
    device_queue.pop(); 
    attempt_queue.pop();
    isUnique = true;      // reset
  } 
  

  // Reset
  if(millis()-restart_time >= 10000){
    Serial.println("Count: " + String(meshcount));
    for(int i=0;i<meshcount;i++){
      Serial.println(xenons[i] + " : " + attemptcnt[i]);
      xenons[i] = "";
    }
    Mesh.publish("wakeup_xenon", "nothing");
    delay(1000);            // give some time for the xenons to respond and fill queue
    meshcount = 0;
    restart_time = millis();
  }
  
}

int xenon_connect(String command) {
  if (command=="1") {
    Mesh.publish("flash_update","");
    return 1;
  }
  else {
    return -1;
  }
}

