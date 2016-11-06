#include <Homie.h>
#include <DHT.h>

#define FW_NAME       "roomsensor"
#define FW_VERSION    "0.0.1"

const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";

#define DHT_PIN       2
#define DHT_TYPE      DHT22
#define PUB_INTERVAL  15

HomieNode temperatureNode("temperature", "temperature");
HomieNode humidityNode("humidity", "humidity");

DHT dht(DHT_PIN, DHT_TYPE);

unsigned long lastPublish = 0;

void setupHandler() {
  Homie.setNodeProperty(temperatureNode, "unit", "c", true);
  Homie.setNodeProperty(humidityNode, "unit", "%", true);
  
  dht.begin();
}

void loopHandler() {
  if (millis() - lastPublish >= PUB_INTERVAL * 1000UL) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    
    if (!isnan(t) && Homie.setNodeProperty(temperatureNode, "degrees", String(t), true)) {
      lastPublish = millis();
    }
    if (!isnan(h) && Homie.setNodeProperty(humidityNode, "relative", String(h), true)) {
      lastPublish = millis();
    }
  }
}

void setup() {
  Homie.setFirmware(FW_NAME, FW_VERSION);

  Homie.registerNode(temperatureNode);
  Homie.registerNode(humidityNode);
  
  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);

  Homie.enableBuiltInLedIndicator(false);  
  Homie.setup();
}

void loop() {
  Homie.loop();
}
