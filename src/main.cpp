#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define BUFFER_SIZE 100
// GV
const char *ssid = "xxxxxx";       // Имя роутера
const char *pass = "xxxxxx";       // Пароль роутера
const char *mqtt_server = "xxxxx"; // Имя сервера MQTT
const int mqtt_port = 00000;       // Порт для подключения к серверу MQTT
const char *mqtt_user = "xxxxxx";  // Логи для подключения к серверу MQTT
const char *mqtt_pass = "xxxxxx";  // Пароль для подключения к серверу MQTT
const char *topic = "test";
const int pause = 1000; //пауза между отправками
int tm = 300;

WiFiClient wifiC;

PubSubClient client(mqtt_server, 1883, wifiC);
// PFP
void refreshData();

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  if (client.connect("esp32", mqtt_user, mqtt_pass))
  {
    client.publish(topic, "hello world");
  }
}

void loop()
{
  client.loop();
  refreshData();
}

void refreshData()
{
  if (tm == 0)
  {
    unsigned long int t = millis();
    client.publish(topic, String(t).c_str());
    tm = pause; // пауза меду отправками 3 секунды
  }
  tm--;
  delay(1);
}