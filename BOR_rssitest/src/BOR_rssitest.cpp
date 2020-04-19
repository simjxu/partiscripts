// Track connection health by periodically publishing a message to the Particle
// Cloud while simultaneously subscribing to that same message to validate
// application-level round-trip. The message will include metrics including
// total TX since start, total RX since start, round trip duration of the last
// TX/RX pair, and current cellular RSSI and Signal Quality. See
// https://docs.particle.io/reference/device-os/firmware/electron/#rssi-
// for details on the RSSI and Signal Quality measurements.
// Sample publish event
// {device_id}/heartbeat
// TX=6,RX=6,RT=1060,RSSI=-95,QUAL=13
#include "Particle.h"
#include "system_threading.h"
SerialLogHandler logHandler(Serial, LOG_LEVEL_ALL);
String last_event;
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);
#define HEARTBEAT_TX_INTERVAL_MS (5l * 1000l)
struct {
    Timer *timer;
    uint32_t tx_count;
    uint32_t rx_count;
    uint32_t tx_start_ms;
    uint32_t roundtrip_ms;
} heartbeat;

int pind7= D7;
void sub_handler(const char *event, const char *data)
{
    heartbeat.rx_count++;
    heartbeat.roundtrip_ms = millis() - heartbeat.tx_start_ms;
    Log.info("Round-trip time for Heartbeat Event Publish is %lums",
        heartbeat.roundtrip_ms);
}
/**
 * Cellular.command() callback to retrive RSSI signal strength directly from
 * the cellular modem due to observed behavior where Cellular.RSSI() sometimes
 * provides incorrect values.
 */
typedef struct {
    int rssi;
    int qual;
} csq_rssi_param_t;
int cesq_rssi_callback(int type, const char *cbuf, int len, csq_rssi_param_t *param)
{
    if((type == TYPE_PLUS) && param)
    {
        if(sscanf(cbuf, "\r\n+CESQ: %*d,%*d,%*d,%*d,%d,%d", &param->qual,  &param->rssi) != 2)
        {
            param->rssi = -1;
            param->qual = -1;
        }
    }
    return WAIT;
}
void send_heartbeat()
{
    // CellularSignal signal = Cellular.RSSI();
    csq_rssi_param_t param = {-1, -1};
    int cell_rssi = 0;
    int cell_qual = 0;
    if(Cellular.command(cesq_rssi_callback, &param, 1000, "AT+CESQ\r\n") == RESP_OK)
    {
        if(param.rssi != -1 && param.qual != -1)
        {   
            if(param.rssi >= 0 && param.rssi <= 97)
            {
                cell_rssi = -141 + param.rssi;
            }
            else
            {
                cell_rssi = 1;
            }
        }
    }
    String data = String::format("TX=%d,RX=%d,RT=%d,RSSI=%d,QUAL=%d",
            heartbeat.tx_count,
            heartbeat.rx_count,
            heartbeat.roundtrip_ms,
            cell_rssi,
            cell_qual);
    last_event = data;    
    heartbeat.tx_start_ms = millis();
    heartbeat.tx_count++;
    if(Particle.connected())
    {
        Particle.publish(Particle.deviceID() + "/heartbeat/", data, PRIVATE, NO_ACK);
    }
    else
    {
        Log.info("Particle not connected! Skipping publish (still printing).");
    }    
    Log.info("%s: %s", Time.format().c_str(), data.c_str());
}
void setup()
{  
    Serial.begin(115200);
    waitFor(Serial.isConnected, 5000);
    Particle.subscribe(Particle.deviceID() + "/heartbeat", sub_handler, MY_DEVICES);
    Particle.variable("last_event", last_event);
    Particle.connect();
    memset(&heartbeat, 0, sizeof(heartbeat));
    heartbeat.tx_start_ms = millis() - HEARTBEAT_TX_INTERVAL_MS;
		pinMode(pind7, INPUT);
}
void loop()
{
    static bool connected = false;
    static auto sec = System.uptime();
		bool connectStatus = false;
		connectStatus = Cellular.ready();
		if(digitalRead(pind7)==HIGH && connectStatus==false){
			Log.info("resetting");
			Cellular.off();
      delay(1000);
      Cellular.on();
      Cellular.connect();
		}
    if(sec != System.uptime())
    {
        Log.info("heartbeat");
        sec = System.uptime();
    }
    // wait to be connected at least once before starting the test
    if(!(connected || Particle.connected()))
    {
        return;
    }
    connected = true;
    if(millis() - heartbeat.tx_start_ms > HEARTBEAT_TX_INTERVAL_MS)
    {
        send_heartbeat();
    }

		
}