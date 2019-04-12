#include <queue>
using namespace std;

std::queue<String> device_queue;     // queue of device ids for  
String devid = "";
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
  delay(5000);
  while (!device_queue.empty()) { 
    Serial.println(device_queue.front());
    Mesh.publish("bor_pong:"+device_queue.front());
    device_queue.pop(); 
    meshcount += 1;
  } 
  Serial.println("Count: " + String(meshcount));
  delay(1000);
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


// // PRODUCT_ID(8184);
// // PRODUCT_VERSION(1);

// int meshcount = 0;
// String dataarray[] = {"","","","","","","","","","","","","","","","",""};
// String queue[] = {"","","","","","","","","","","","","","","","",""};
// String devid = "";

// void pingHandler(const char *event, const char *data) {
//   String incoming_data = data;

//   // Grab the device ID: first 24 characters of the string
//   devid = incoming_data.substring(0,24);

//   // // Publish response
//   // Mesh.publish("bor_pong:"+devid);

//   queue[meshcount] = devid;
//   meshcount += 1;
// }

// void setup() {
//   // Function to get devices connected to cloud
//   Particle.function("xen_cnct",xenon_connect);

// 	// Subscribe to the xen_ping and point to Handler
//   Mesh.subscribe("bor_ping", pingHandler); 

// }


// // Next is the loop function...

// void loop() {
//   meshcount = 0;
//   Serial.println(Time.second());
//   Mesh.publish("wakeup_xenon", "nothing");
//   delay(10000);
//   Serial.println("Count:" + String(meshcount));
//   for(int i=0;i<meshcount;i++){
//     Serial.println(dataarray[i]);
//     dataarray[i] = "";
//   }

// }

// int xenon_connect(String command) {
//   if (command=="1") {
//     Mesh.publish("flash_update","");
//     return 1;
//   }
//   else {
//     return -1;
//   }
// }

