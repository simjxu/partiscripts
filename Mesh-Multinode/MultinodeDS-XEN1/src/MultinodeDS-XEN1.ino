// SYSTEM_MODE(SEMI_AUTOMATIC);
// SYSTEM_THREAD(ENABLED);

// bool bor_resp = false;
// bool notConnected = true;
// int attempts = 0;
// int starttime = 0;
// int timecheck = 0;
// String datastring = "123456789012345678901234567890";
// float average_time;
// int count = 0;

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

// // STARTUP(selectExternalMeshAntenna);

// void pongHandler(const char *event, const char *data) {
//   Serial.println("ack received");
//   bor_resp = true;
// }

// void updateHandler(const char *event, const char *data) {
//   Serial.println("getting update...");
//   Particle.connect();
//   while(Particle.connected()!=true) {
//     delay(1000);
//   }
//   Serial.println("connected!");
// }

// void resetHandler(const char *event, const char *data) {
//   System.reset();
// }

// void setup() {
//   Mesh.subscribe("bor_pong:"+System.deviceID(), pongHandler);
//   Mesh.subscribe("flash_update", updateHandler);
//   Mesh.subscribe("reset", resetHandler);
// }

// void loop() {
//   starttime = millis();
//   Mesh.on();
//   Mesh.connect();
//   waitFor(Mesh.ready,4000);
//   Serial.println("turning on Mesh");

//   // Check to see if the Mesh is connected
//   while(notConnected) {
//     for(int i=0;i<10;i++){
//       Mesh.publish("cxn_check", String(i));
//     }
//     delay(2000);
//   }
 
  


//   timecheck = millis()-starttime;
//   Mesh.publish("bor_ping", System.deviceID() + " : " + String(attempts) + " : " + String(timecheck));
//   delay(8000-timecheck);
//   Serial.println("turning off Mesh");
//   Mesh.disconnect();
//   // System.sleep(SLEEP_MODE_DEEP);

//   // Serial.println("sent message");
//   // while(bor_resp==false && attempts<5) {
//   //   delay(2000);
//   //   if(bor_resp==false){
//   //     Serial.println("retrying ping...");
//   //     attempts += 1;
//   //     Mesh.publish("bor_ping", System.deviceID() + " : " + datastring + " : " + String(attempts) + " : " + String(timecheck));
//   //   }
//   // }
//   // Serial.println(timecheck);
//   // System.sleep(SLEEP_MODE_DEEP);
// }



#include "application.h"
#include "deviceid_hal.h"

SerialLogHandler dbg(LOG_LEVEL_NONE, { {"ot", LOG_LEVEL_ALL}, {"app", LOG_LEVEL_ALL} });

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

bool bor_resp = false;
int count = 0;
bool netready = false;
int starttime = 0;
int timecheck = 0;
int attempts = 0;
int pongcount = 0;
int receivedcount = 0;

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

void pongHandler(const char *event, const char *data) {
  Log.trace("ack received");
  pongcount++;
}

void receivedHandler(const char *event, const char *data) {
  bor_resp = true;
}

void setup(){
  // waitUntil(Serial.isConnected);
  Mesh.on();
  Mesh.subscribe("bor_pong", pongHandler);
  Mesh.subscribe("bor_data_received", receivedHandler);
}

void loop(){
  bor_resp = false;
  count = 0;
  pongcount = 0;
  Log.trace("turning on Mesh");
  Mesh.connect();
  waitFor(Network.ready, 120000);
  starttime = millis();
  
  Log.trace("Sending mesh publishes");
  while(count<=30) {
    Mesh.publish("bor_ping", String(count));
    count++;
    delay(2000);
    timecheck = millis()-starttime;
  }

  delay(10000);

  while(bor_resp==false){
    Mesh.publish("send_results", String(pongcount));
    delay(2000);
  }

  bor_resp = false;

  Log.trace("total time: "+String(timecheck));
  Log.trace("turning off Mesh");
  System.sleep(600000);
  delay(600000);
}