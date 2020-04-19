// #include "Particle.h"
// #include "system_threading.h"

// // Argon Master: e00fce680e945e12aabc7676
// // Xenon Slave: e00fce68fc799f116d8ffcab

// SYSTEM_MODE(SEMI_AUTOMATIC);
// uint8_t rx_buffer[64], tx_buffer[64];

// void setup() {
//   pinMode(D7, OUTPUT);
//   pinMode(A5, OUTPUT);
//   Particle.connect();

//   // SPI setup

//   for (int i = 0; i < sizeof(tx_buffer); i++){
//     tx_buffer[i] = (uint8_t)i;
//   }

//   SPI.begin(SPI_MODE_MASTER, A5);   // set the Argon as master for SPI 
//   SPI.setClockSpeed(8, MHZ);
//   SPI.setBitOrder(MSBFIRST);
//   SPI.setDataMode(SPI_MODE3);
// }

// void loop() {
//   uint8_t value = 0x5f; 
//   digitalWrite(D7, HIGH);
//   digitalWrite(A5, HIGH);
//   delay(1000);
//   SPI.transfer(value); //  A5 SS
//   delay(10);
//   digitalWrite(A5, LOW);
//   delay(10);
//   digitalWrite(D7, LOW);
//   delay(2000);
// }


SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Particle.connect();
  SPI1.setClockSpeed(8, MHZ);
  SPI1.begin(SPI_MODE_MASTER);
}

void loop() {
  digitalWrite(D5, LOW);
  SPI1.transfer(0x01);
  digitalWrite(D5, HIGH);
  delay(1000);
  digitalWrite(D5, LOW);
  SPI1.transfer(0x02);
  digitalWrite(D5, HIGH);
  delay(1000);
}