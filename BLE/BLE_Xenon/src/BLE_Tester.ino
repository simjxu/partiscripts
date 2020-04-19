#include "Particle.h"

SYSTEM_MODE(MANUAL);

// BLE TX power in dBm.
#define TX_POWER                   (8)

// Adjust this value to measure the average power consumption for different advertising interval.
#define ADVERTISING_INTERVAL_MS    20

// Adjust this value to measure the average power consumption for different connection interval.
// To measure the power consumption during connected,uses mobile App to connect to this device once it starts advertising.
#define CONENCTION_INTERVAL_MS     20

void setup() {
    BleAdvertisingParams params = {};
    params.size = sizeof(BleAdvertisingParams);
    params.interval = BLE_MSEC_TO_UNITS(ADVERTISING_INTERVAL_MS, BLE_UNIT_0_625_MS);
    params.timeout = 0;
    params.type = BLE_ADV_CONNECTABLE_SCANNABLE_UNDIRECRED_EVT;
    params.filter_policy = BLE_ADV_FP_ANY;
    params.inc_tx_power = false;
    BLE.setAdvertisingParameters(&params);

    BLE.setPPCP(BLE_MSEC_TO_UNITS(CONENCTION_INTERVAL_MS, BLE_UNIT_1_25_MS),
                BLE_MSEC_TO_UNITS(CONENCTION_INTERVAL_MS + 20, BLE_UNIT_1_25_MS),
                0,
                BLE_MSEC_TO_UNITS(6000, BLE_UNIT_10_MS));

    BLE.setTxPower(TX_POWER);

    iBeacon beacon(1, 2, "9c1b8bdc-5548-4e32-8a78-b9f524131206", -55);
    BLE.advertise(beacon);
    BLE.setAdvertisingType(BleAdvertisingEventType::CONNECTABLE_SCANNABLE_UNDIRECRED);

    // After 15 seconds, device enters sleep mode.
    delay(15000);

    // We usually measure the power consumption during device in sleep mode.
    System.sleep(D8, FALLING, 30, SLEEP_NETWORK_STANDBY); // Sleep for 30 seconds
}

void loop() {

}


