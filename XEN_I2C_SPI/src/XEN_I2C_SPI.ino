// #include "Particle.h"

// // Argon Master: e00fce680e945e12aabc7676
// // Xenon Slave: e00fce68fc799f116d8ffcab
// // stty -f /dev/cu.usbmodem14301 14400

// SYSTEM_MODE(SEMI_AUTOMATIC);
// uint8_t rx_buffer[64], tx_buffer[64];
// uint32_t select_state = 0x00;
// uint32_t transfer_state = 0x00;

// void onTransferFinished() {
//     transfer_state = 1;
// }

// void onSelect(uint8_t state){
//   if (state){
//     select_state = state;
//   }
// }

// void setup() {
//   // SPI setup
//   SPI.setClockSpeed(4, MHZ);
//   for (int i = 0; i < sizeof(tx_buffer); i++){
//     tx_buffer[i] = (uint8_t)i;
//   }
//   SPI.onSelect(onSelect);
//   SPI.begin(SPI_MODE_SLAVE, A5);   // set the Argon as master for SPI 
// }

// void loop() {
//   delay(2000);
//   Serial.println("Starting loop");
//   while (1){
//     Serial.println("Select state 0");
//     while(select_state == 0);
//     Serial.println("Select state not 0");
//     select_state = 0;
//     transfer_state = 0;
//     SPI.transfer(tx_buffer, rx_buffer, sizeof(rx_buffer), onTransferFinished);
//     while(transfer_state ==0);
//     Serial.println("Transfer state not 0");
//     if (SPI.available() > 0) {
//       Serial.printf("received %d bytes", SPI.available());
//       Serial.println();
//       for (int i = 0; i < SPI.available(); i++) {
//         Serial.printf("%02x ", rx_buffer[i]);
//       }
//       Serial.println();
//     }
//   }

  

// }

// //-------------------------------------------------
// // SPI slave example
// static uint8_t rx_buffer[64];
// static uint8_t tx_buffer[64];
// static uint32_t select_state = 0x00;
// static uint32_t transfer_state = 0x00;

// void onTransferFinished() {
//     transfer_state = 1;
// }

// void onSelect(uint8_t state) {
//     if (state)
//         select_state = state;
// }

// void setup() {
//     Serial.begin(9600);
//     pinMode(D5, INPUT);

//     for (int i = 0; i < sizeof(tx_buffer); i++)
//       tx_buffer[i] = (uint8_t)i;
//     SPI1.onSelect(onSelect);

//     SPI1.begin(SPI_MODE_SLAVE, D5);
//     SPI1.setClockSpeed(8, MHZ);
//     SPI1.setBitOrder(MSBFIRST);
//     SPI1.setDataMode(SPI_MODE3);
// }

// /* executes continuously after setup() runs */
// void loop() {
//     delay(10000);
//     Serial.println("started");
//     while (1) {
//         Serial.println("Select state 0");
//         while(select_state == 0);
//         select_state = 0;

//         transfer_state = 0;
//         SPI1.transfer(tx_buffer, rx_buffer, sizeof(rx_buffer), onTransferFinished);
//         while(transfer_state == 0);
//         if (SPI1.available() > 0) {
//             Serial.printf("Received %d bytes", SPI1.available());
//             Serial.println();
//             for (int i = 0; i < SPI1.available(); i++) {
//                 Serial.printf("%02x ", rx_buffer[i]);
//             }
//             Serial.println();
//         }
//     }
// }


SYSTEM_MODE(MANUAL);

uint8_t globalState = 0;

byte sending[1];
byte receive[1];

void onSend(uint8_t state) {
   if (state) {
     globalState = 1;
   }
}

void setup() {
  Serial.begin();
  SPI1.onSelect(onSend);
  SPI1.setClockSpeed(8, MHZ);
  SPI1.begin(SPI_MODE_SLAVE, D5);
  pinMode(D5, INPUT);
}

void loop() {
  if (globalState == 1) {
    globalState = 0;
    Serial.println("READING...");
    SPI1.transfer(sending, receive, 1, NULL);
    Serial.println(receive[0], HEX);
    if (receive[0] == 0) {
      Serial.println("LOW");
    } else {
      Serial.println("HIGH");
    }
  }
}