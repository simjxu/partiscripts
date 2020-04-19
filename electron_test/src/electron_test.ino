#include "Particle.h"

SerialLogHandler logHandler(115200, LOG_LEVEL_ALL);

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

void setup()
{
    Serial.begin(115200);
    waitFor(Serial.isConnected, 10000);

    SPI.setDataMode(SPI_MODE0);
    SPI.setClockSpeed(100 * 1000);
    SPI.begin();

    delay(5000); // because ???

    uint8_t buf[8]; // contents don't matter, garbage from the stack is OK!

    SPI.transfer(buf, NULL, sizeof(buf), NULL);

    Log.info("auto buf tx success!");

    delay(1000);

    // // following line does not compile
    // SPI.transfer("ABC", NULL, sizeof("ABC"), NULL);
    // // Hard faults on Gen 3
    // SPI.transfer((uint8_t*) "ABC", NULL, sizeof("ABC"), NULL);

    // Log.info("const buf tx success!");
}

void loop()
{
}