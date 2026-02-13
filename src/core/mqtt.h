#ifndef mqtt_h
#define mqtt_h

#ifdef MQTT_ENABLE // ============================== Everything ignored if not defined ==============================
#include <AsyncMqttClient.h>

void connectToMqtt();
void mqttInit();
void zeroBuffer();
void onMqttConnect(bool sessionPresent);
void mqttPublishStatus();
void mqttPublishPlaylist();
void mqttPublishVolume();
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

#endif // #ifdef MQTT_ENABLE

#endif