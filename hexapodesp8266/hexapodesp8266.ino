#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <string.h>

//const char* ssid = "Phong 419";
//const char* password =  "phong419!@#";
//const char* ssid = "ID11_2.4G_04";
//const char* password =  "123456aA@";
const char* ssid = "Redmikhai";
const char* password =  "khaikhai";
const char* mqttServer = "m16.cloudmqtt.com";
const int mqttPort = 14886;
const char* mqttUser = "vxgdfhne";
const char* mqttPassword = "u4Z40PEVzTZQ";
char incomingByte[1] = "";
char incomingString[100] = "";
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);
  Serial.swap();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    if (client.connect("ESP8266Client", mqttUser, mqttPassword ))
    {
      //Serial.println("MQTT connected");
    } else {
      delay(2000);
    }
  }
  client.subscribe("androidcontrol");// here is where you later add a wildcard
}

void callback(char* topic, byte* payload, unsigned int length)
{
  char mqtt_msg[100] = "";
  for (int i = 0; i < length; i++) {
    mqtt_msg[i] = (char)payload[i];
  }
  int mqtt_msg_length = strlen(mqtt_msg);
  if(mqtt_msg_length < 52)
  {
    for(int i = 0; i < 51 - mqtt_msg_length; i++)
      strcat(mqtt_msg, "x");
    strcat(mqtt_msg, "\n");
  }

  Serial.print(mqtt_msg);


}
int i = 0;
boolean receiverCompleted = false;
void loop()
{
  client.loop();

  if (Serial.available()) 
  {
    incomingByte[0] = (char)(Serial.read());
    strcat(incomingString, incomingByte);
    if(incomingByte[0] != 0x0A)
    { 
      receiverCompleted = false;
    }
    else
    {
      receiverCompleted = true;      
    }
  }

  if(receiverCompleted)
  {
   client.publish("hexapodstatus", incomingString);
   strcpy(incomingString, "");
   receiverCompleted = false;
  }
  
}
