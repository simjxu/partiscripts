// #include "application.h"
// #include "deviceid_hal.h"

// SerialLogHandler dbg(LOG_LEVEL_ALL);

// SYSTEM_MODE(SEMI_AUTOMATIC);
// SYSTEM_THREAD(ENABLED);

// struct QueueData {
//   char deviceId[HAL_DEVICE_ID_SIZE * 2 + 1];
//   char data[255];
// };

// os_queue_t device_queue = nullptr;

// int restart_time = 0;
// int publish_flag = 0;
// int current_count = 0; 
// // Change this to equate to number of devices
// int num_devices = 1;

// void selectExternalMeshAntenna() {
//   #if (PLATFORM_ID == PLATFORM_ARGON)
//     digitalWrite(ANTSW1, 1);
//     digitalWrite(ANTSW2, 0);
//   #elif (PLATFORM_ID == PLATFORM_BORON)
//     digitalWrite(ANTSW1, 0);
//   #else
//     digitalWrite(ANTSW1, 0);
//     digitalWrite(ANTSW2, 1);
//   #endif
// }

// STARTUP(selectExternalMeshAntenna);

// void pingHandler(const char *event, const char *data) {
//   Log.trace("ping received");
//   QueueData d = {};
//   memcpy(d.deviceId, data, HAL_DEVICE_ID_SIZE * 2);
//   if (data) {
//     Log.trace(data);
//     memcpy(d.data, data, std::max(strlen(data), sizeof(d.data)));
//   }
//   os_queue_put(device_queue, &d, CONCURRENT_WAIT_FOREVER, nullptr);
// }

// void resultsHandler(const char *event, const char *data) {
//   Log.trace("results received");
// }

// void setup() {
//   os_queue_create(&device_queue, sizeof(QueueData), 10, nullptr);

//   waitUntil(Serial.isConnected);
  
//   Log.trace("Connecting to mesh");
//   Mesh.on();
//   Mesh.connect();
//   Cellular.connect();
//   Particle.connect();
//   // Subscribe to the xen_ping and point to Handler
//   Mesh.subscribe("bor_ping", pingHandler); 
//   Mesh.subscribe("send_results", resultsHandler);
//   restart_time = millis();
// }

// void loop() {
//   QueueData data = {};
//   while (!os_queue_take(device_queue, &data, 0, nullptr)) { 
//     Log.trace("Sending response pong to %s", data.deviceId);
//     Mesh.publish("bor_pong", String(data.data));
//     Particle.publish("xenon-pub", data.data);
//   }

//   if(millis()-restart_time >= 600000){
//     Particle.publish("bor_online");
//     restart_time = millis();
//   }  
// }



#include "application.h"
#include "deviceid_hal.h"

SerialLogHandler dbg(LOG_LEVEL_NONE, { {"ot", LOG_LEVEL_ALL}, {"app", LOG_LEVEL_ALL} });

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
int count = 0;

void selectExternalMeshAntenna() {
  #if (PLATFORM_ID == PLATFORM_ARGON)
    digitalWrite(ANTSW1, 1);
    digitalWrite(ANTSW2, 0);
  #elif (PLATFORM_ID == PLATFORM_BORON)
    digitalWrite(ANTSW1, 0);
  #else
    digitalWrite(ANTSW1, 0);
    digitalWrite(ANTSW2, 1);
  #endif
}

STARTUP(selectExternalMeshAntenna);

void pingHandler(const char *event, const char *data) {
  Log.trace("ping received");
  count++;
}

void resultsHandler(const char *event, const char *data) {
  Log.trace("results received");
  count = 0;
  Log.trace(data);
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
  Mesh.subscribe("send_results", resultsHandler);
  restart_time = millis();
}

void loop() {
    delay(10000);
    Log.trace(String(count));
}
