SYSTEM_MODE(SEMI_AUTOMATIC);

uint8_t globalState = 0;

// Create buffers
uint8_t tx_buffer[64];  
uint8_t rx_buffer[64];

// I2C addresses
uint8_t addr = 0x10;

// SPI Example --------------------------------------
void onSend(uint8_t state) {
   if (state) {
     globalState = 1;
   }
}
// SPI Example --------------------------------------


void setup() {
// SPI Example --------------------------------------
  Serial.begin();
  SPI1.onSelect(onSend);
  SPI1.setDataMode(SPI_MODE3); // Mode 3 means pull low to select
  SPI1.setClockSpeed(4, MHZ);
  SPI1.begin(SPI_MODE_SLAVE, D5);   // Slave device
// SPI Example --------------------------------------

// ---------------------------------------I2C Example
  Wire.begin();   // Start I2C up
// ---------------------------------------I2C Example

}

void loop() {
// SPI Example --------------------------------------
  if (globalState == 1) {
    globalState = 0;
    Serial.println("Waiting for SPI...");
    SPI1.transfer(tx_buffer, rx_buffer, sizeof(tx_buffer), NULL);
    Serial.println(rx_buffer[0]);   // Print out the values received
  }
// SPI Example --------------------------------------



}
