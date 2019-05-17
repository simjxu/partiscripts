#include <queue>
using namespace std;

std::queue<String> device_queue;      // queue of device ids
std::queue<String> data_queue;     // queue of attempts
String devid = "";
String xenons[] = {"","","","","","","","","","","","","","","","","","","",""};
String attemptcnt[] = {"","","","","","","","","","","","","","","","","","","",""};
int restart_time = 0;

// Change this to equate to number of devices
int num_devices = 1;

void pingHandler(const char *event, const char *data) {
  String incoming_data = data;

  // Grab the device ID: first 24 characters of the string
  devid = incoming_data.substring(0,24);
  device_queue.push(devid);

  data_queue.push(data);
}

void setup() {
  // Function to get devices connected to cloud
  Particle.function("xen_cnct",xenon_connect);
  // Function to reset devices
  Particle.function("xen_rst",xenon_reset);

	// Subscribe to the xen_ping and point to Handler
  Mesh.subscribe("bor_ping", pingHandler); 
  restart_time = millis();
} 

void loop() {
  while (!device_queue.empty()) { 
    Mesh.publish("bor_pong:"+device_queue.front());
    
    // Publish to the cloud
    Particle.publish("xenon-pub", data_queue.front());

    device_queue.pop(); 
    data_queue.pop();
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

int xenon_reset(String command) {
  if (command=="1") {
    Mesh.publish("reset","");
    return 1;
  }
  else {
    return -1;
  }
}

