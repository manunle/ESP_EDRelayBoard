#include <Arduino.h>
#include <PubSubClient.h>

#include "ESPBASE.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);
const byte mqttDebug = 1;
//const int ESP_BUILTIN_LED = 1;
#define RELAY1_PIN 12
#define RELAY2_PIN 13
#define STATUS_LED 16
byte relay1state = 0;
byte relay2state = 0;
String sChipID;
long lastReconnectAttempt = 0;
int rbver = 0;
String verstr = "ESP_EDRelayBoard ver 1.0";


ESPBASE Esp;

void setup() {
  Serial.begin(115200);
  char cChipID[10];
  sprintf(cChipID,"%08X",ESP.getChipId());
  sChipID = String(cChipID);

  Esp.initialize();

  customWatchdog = millis();
  setupMQTTClient();
  customWatchdog = millis();

  pinMode(RELAY1_PIN,OUTPUT);
  pinMode(RELAY2_PIN,OUTPUT);
 
  Serial.println("Done with setup");
  Serial.println(config.ssid);
}

void loop() {
  // OTA request handling
  ArduinoOTA.handle();

  //  WebServer requests handling
  server.handleClient();

   //  feed de DOG :)
  customWatchdog = millis();
  if(Esp.WIFI_connected)
  {
    if(config.MQTTServer != "")
    {
      if (!mqttClient.connected()) 
      {
        Serial.println("mqtt NOT connected");
        long now = millis();
        if (now - lastReconnectAttempt > 5000) 
        {
          lastReconnectAttempt = now;
          // Attempt to reconnect
          if (mqttClient.connect(config.MQTTServer.c_str())) 
          {
            String recon = "Recon";
            mqttSend(recon,config.DeviceName,": Reconnected");
            lastReconnectAttempt = 0;
          }
        }
      } else {
        // Client connected
        mqttClient.loop();
      }
    
      if(cHeartbeat >= config.HeartbeatEvery and config.HeartbeatEvery > 0)
      {
        cHeartbeat = 0;
        mqttSend(config.HeartbeatTopic,config.DeviceName," Still Here");
      }
    }
  }
  yield();
}

String getSignalString()
{
  String signalstring = "";
  byte available_networks = WiFi.scanNetworks();
  signalstring = signalstring + sChipID + ":";
 
  for (int network = 0; network < available_networks; network++) {
    String sSSID = WiFi.SSID(network);
    if(network > 0)
      signalstring = signalstring + ",";
    signalstring = signalstring + WiFi.SSID(network) + "=" + String(WiFi.RSSI(network));
  }
  return signalstring;    
}

void setupMQTTClient() {
  int connectResult;
  
  if (config.MQTTServer != "") {
    mqttClient.setServer(config.MQTTServer.c_str(), config.MQTTPort);
//    mqttClient.setServer("192.168.1.6", config.MQTTPort);
    mqttClient.setCallback(mqttCallback);
    Serial.println("MQTT Connecting");
      connectResult = mqttClient.connect(config.DeviceName.c_str());
//        connectResult = mqttClient.connect("ME");
    if (connectResult) {
      Serial.println("MQTT Connected");
    }
    else{
      Serial.println("Didn't connect");
    }
    
    if (mqttClient.connected()) {
      if (mqttClient.subscribe(config.StatusTopic.c_str())) {
        Serial.println("Subscribed to " + config.StatusTopic);
        mqttSend(config.RelayTopic,config.DeviceName+" ",Esp.MyIP());
      }
      if (mqttClient.subscribe(config.RelayTopic.c_str())) {
        Serial.println("Subscribed to " + config.RelayTopic);
        mqttSend(config.RelayTopic,config.DeviceName+" ","Subscribed to " + config.RelayTopic);
        String startstr = "start";
        mqttSend(startstr,config.DeviceName+" ",verstr);
      }
    }
  }
}

void mqttSend(String& topic,String msg)
{
  String preface = ""; 
  Serial.println(topic);
  Serial.println(msg);
  mqttSend(topic,preface,msg);
}

void mqttSend(String& topic,String& preface,String msg)
{
  Serial.println(topic);
  Serial.println(preface);
  Serial.println(msg);
  String soutput=preface+msg;
  char mybytes[soutput.length()+1];
  char topicbytes[topic.length()+1];
  topic.toCharArray(topicbytes,topic.length()+1);  
  soutput.toCharArray(mybytes,soutput.length()+1);
//  mqttClient.publish(topicbytes,mybytes);
  mqttClient.publish(topic.c_str(),soutput.c_str());
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  char c_payload[length];
  memcpy(c_payload, payload, length);
  c_payload[length] = '\0';
  
  String s_topic = String(topic);
  String s_payload = String(c_payload);
  
  if (s_topic == config.StatusTopic) {
    Serial.println("Got Status: ");
    Serial.println(s_payload);
    char dname[20];
    String DeviceName;
    char *p = c_payload;
    char *str;
    str = strtok_r(p,";",&p);
    strncpy(dname,str,20);
    Serial.print("device name: ");
    DeviceName = String(dname);
    Serial.println(DeviceName);
    if(DeviceName == String(config.DeviceName))
    {
      Serial.println("This is for me");
//      mqttSend(config.StatusTopic,formatConfig());
        mqttSend(config.RelayTopic,config.DeviceName+" ",formatConfig());
    }
  }
  if (s_topic == config.RelayTopic) 
  {
    if(s_payload == "STAT")
    {
      mqttSend(config.RelayTopic,sChipID," WiFi: " + getSignalString());
    }
    if(s_payload == config.Relay1ToggleMessage)
    {
      if(relay1state == 1)
      {
        s_payload = config.Relay1OffMessage;
      }
      else
      {
        s_payload = config.Relay1OnMessage;
      }
    }
    if(s_payload == config.Relay1OnMessage)
    {
      relay1state = 1;
      digitalWrite(RELAY1_PIN,HIGH);
    }
    if(s_payload == config.Relay1OffMessage)
    {
      relay1state = 0;
      digitalWrite(RELAY1_PIN,LOW);
    }
    if(s_payload == config.Relay2ToggleMessage)
    {
      if(relay2state == 1)
      {
        s_payload = config.Relay2OffMessage;
      }
      else
      {
        s_payload = config.Relay2OnMessage;
      }
    }
    if(s_payload == config.Relay2OnMessage)
    {
      relay2state = 1;
      digitalWrite(RELAY2_PIN,HIGH);
    }
    if(s_payload == config.Relay2OffMessage)
    {
      relay2state = 0;
      digitalWrite(RELAY2_PIN,LOW);
    }
    String RelayState = " Relay 1: ";
    if(relay1state == 1)
      RelayState = RelayState + "On ";
    else
      RelayState = RelayState + "Off ";
    RelayState = RelayState + " Relay 2: ";
    if(relay2state == 1)
      RelayState = RelayState + "On ";
    else
      RelayState = RelayState + "Off ";
    mqttSend(config.StatusTopic,config.DeviceName,RelayState);
  }
//  else {
//    if (mqttDebug) { Serial.println(" [unknown message]"); }
//  }
}


