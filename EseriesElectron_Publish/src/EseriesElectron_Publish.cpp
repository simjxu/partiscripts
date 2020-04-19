#include "Particle.h"
#include "cellular_hal.h"

SerialLogHandler logHandler(LOG_LEVEL_ALL);

CellularGlobalIdentity cgi;

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

#define PUBLISH_INTERVAL_SEC (2)

// #define APP_GPS_PWR_EN_PIN         (B1) // active HIGH
#define APP_WD_FEED_PIN            (D0) // active HIGH
#define APP_MCU_CTRL_PIN           (A0) // active HIGH to keep power on

/**
 * Pet the hardware watchdog timer
 */
void petWatchdog()
{
    static unsigned long lastPet = millis();
    bool state = false;
    if (!state) {
        if (millis() - lastPet >= 50000) {
            lastPet = millis();
            digitalWriteFast(APP_WD_FEED_PIN, HIGH);
        }
    } else {
        if (millis() - lastPet >= 10000) {
            lastPet = millis();
            digitalWriteFast(APP_WD_FEED_PIN, LOW);
        }
    }
}

void setup() {
    // pinMode(APP_GPS_PWR_EN_PIN, OUTPUT);
    // digitalWrite(APP_GPS_PWR_EN_PIN, HIGH);
    pinMode(APP_WD_FEED_PIN, OUTPUT);
    pinMode(APP_MCU_CTRL_PIN, OUTPUT);
    digitalWrite(APP_MCU_CTRL_PIN, HIGH); // keep power on no matter what

    pinMode(D1, OUTPUT);
    Particle.connect();
    waitUntil(Cellular.ready);
}

uint16_t counter = 0;

void loop() {
    Serial.println("testing");
    petWatchdog();
    // cellular_result_t result = ::cellular_global_identity(&cgi, nullptr);
    // switch (result) {
    //   case SYSTEM_ERROR_NONE:
    //     Log("{\"mcc\":%d,\"mnc\":%d,\"lac\":%d,\"ci\":%d}", cgi.mobile_country_code, cgi.mobile_network_code, cgi.location_area_code, cgi.cell_id);
    //     break;
    //   default:
    //     Log("ERROR <%d>: Failed to acquire cellular global identity!", result);
    // }
    // Particle.publishVitals();
    // Particle.publish("connectivity", String(counter++), PRIVATE, NO_ACK);

    // 123 bytes NO_ACK
    // Particle.publish("connectivity", String::format("%d; xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", counter++), PRIVATE, NO_ACK);

    // 192 bytes NO_ACK
    Particle.publish("connectivity", String::format("%d xxxxxx", counter++), PRIVATE, NO_ACK);

    // 192 bytes WITH_ACK
    // Particle.publish("connectivity", String::format("%d; xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", counter++), PRIVATE, WITH_ACK);

    delay(PUBLISH_INTERVAL_SEC * 1000);

    if (!Particle.connected()) {
        static uint32_t s = millis();
        if (millis() - s >= PUBLISH_INTERVAL_SEC * 1000 * 2) {
            s = millis();
            digitalWrite(D1, HIGH);
            delay(30);
            digitalWrite(D1, LOW);
        }
    }
}