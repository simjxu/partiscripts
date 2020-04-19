
// SPI Example --------------------------------------

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

// Create buffers
uint8_t rx_buffer[64], tx_buffer[64];

void setup() {
  Particle.connect();
  pinMode(D7, OUTPUT);

  // SPI Example --------------------------------------
  SPI1.setDataMode(SPI_MODE3); // Mode 3 means pull low to select
  SPI1.setClockSpeed(4, MHZ);
  SPI1.begin(SPI_MODE_MASTER);    
  // SPI Example --------------------------------------

  // ---------------------------------------I2C Example


  // tx_buffer contains all the data that you want to transfer, currently setting some random data to it
  tx_buffer[0] = 0x02;
  tx_buffer[1] = 0x0A;
}

void loop() {
  digitalWrite(D7, HIGH); // Indicate when data is being sent via LED
  digitalWrite(D5, LOW);  // pull SS pin low to begin transfer
  SPI1.transfer(tx_buffer, rx_buffer, sizeof(tx_buffer), NULL);
  digitalWrite(D5, HIGH); // pull SS pin high to deselect slave
  delay(500);
  digitalWrite(D7, LOW); // Indicate when data has stopped being sent
  delay(2000);

  // Another example transfer: single byte
  digitalWrite(D7, HIGH); // Indicate when data is being sent
  digitalWrite(D5, LOW);
  SPI1.transfer(0x0D);
  digitalWrite(D5, HIGH);
  delay(500);
  digitalWrite(D7, LOW); // Indicate when data has stopped being sent
  delay(2000);
}
// SPI Example --------------------------------------