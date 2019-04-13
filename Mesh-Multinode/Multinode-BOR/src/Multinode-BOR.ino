#include <queue>
using namespace std;

std::queue<String> device_queue;     // queue of device ids for  
String devid = "";
String xenons[] = {"","","","","","","","","","","","","","","","","","","",""};
int meshcount = 0;

void pingHandler(const char *event, const char *data) {
  String incoming_data = data;

  // Grab the device ID: first 24 characters of the string
  devid = incoming_data.substring(0,24);
  device_queue.push(devid);
}

void setup() {
  // Function to get devices connected to cloud
  Particle.function("xen_cnct",xenon_connect);

	// Subscribe to the xen_ping and point to Handler
  Mesh.subscribe("bor_ping", pingHandler); 
} 

void loop() {
  bool isUnique = true;
  delay(10000);
  while (!device_queue.empty()) { 
    Mesh.publish("bor_pong:"+device_queue.front());
    
    // Check if the device id is unique
    if(meshcount==0) {
      xenons[0] = device_queue.front();
    }
    for(int i=0;i<meshcount;i++) {
      if(xenons[i]==device_queue.front()) {
        isUnique = false;
        break;
      }
    }
    // If device ID is not found in array, then count it!
    if(isUnique==true) {
      xenons[meshcount] = device_queue.front();
      meshcount += 1;
    }
    device_queue.pop(); 
    isUnique = true;      // reset
  } 
  Serial.println("Count: " + String(meshcount));
  for(int i=0;i<meshcount;i++){
    Serial.println(xenons[i]);
    xenons[i] = "";
  }

  // Reset
  Mesh.publish("wakeup_xenon", "nothing");
  meshcount = 0;
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

