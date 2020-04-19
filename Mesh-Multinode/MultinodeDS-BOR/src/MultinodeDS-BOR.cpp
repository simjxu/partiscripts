/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/simonxu/Projects/Github-simjxu/partiscripts/Mesh-Multinode/MultinodeDS-BOR/src/MultinodeDS-BOR.ino"
#include "application.h"
#include "deviceid_hal.h"

void pingHandler(const char *event, const char *data);
void setup();
void loop();
#line 4 "/Users/simonxu/Projects/Github-simjxu/partiscripts/Mesh-Multinode/MultinodeDS-BOR/src/MultinodeDS-BOR.ino"
SerialLogHandler dbg(LOG_LEVEL_ALL);

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

struct QueueData {
  char deviceId[HAL_DEVICE_ID_SIZE * 2 + 1];
  char data[255];
};

os_queue_t device_queue = nullptr;

int restart_time = 0;
int publish_flag = 0;
int current_count = 0; 
// Change this to equate to number of devices
int num_devices = 1;
void pingHandler(const char *event, const char *data) {
  Log.trace("ping received");
  QueueData d = {};
  memcpy(d.deviceId, data, HAL_DEVICE_ID_SIZE * 2);
  if (data) {
    Log.trace(data);
    memcpy(d.data, data, std::max(strlen(data), sizeof(d.data)));
  }
  os_queue_put(device_queue, &d, CONCURRENT_WAIT_FOREVER, nullptr);
}
void setup() {
  os_queue_create(&device_queue, sizeof(QueueData), 10, nullptr);

  waitUntil(Serial.isConnected);
  
  Log.trace("Connecting to mesh");
  Mesh.on();
  Mesh.connect();
  Cellular.connect();
  Particle.connect();
  // Subscribe to the xen_ping and point to Handler
  Mesh.subscribe("bor_ping", pingHandler); 
  restart_time = millis();
}

void loop() {
  QueueData data = {};
  while (!os_queue_take(device_queue, &data, 0, nullptr)) { 
    Log.trace("Sending response pong to %s", data.deviceId);
    Mesh.publish("bor_pong:" + String(data.deviceId));
    Particle.publish("xenon-pub", data.data);
  }

  if(millis()-restart_time >= 600000){
    Particle.publish("bor_online");
    restart_time = millis();
  }  
}