#ifndef PARAMETERS_H
#define PARAMETERS_H
#define CFGVER "R1.0"

struct strConfig {
  boolean dhcp;                         // 1 Byte - EEPROM 16
  boolean isDayLightSaving;             // 1 Byte - EEPROM 17
  long Update_Time_Via_NTP_Every;       // 4 Byte - EEPROM 18
  long timeZone;                        // 4 Byte - EEPROM 22
  byte  IP[4];                          // 4 Byte - EEPROM 32
  byte  Netmask[4];                     // 4 Byte - EEPROM 36
  byte  Gateway[4];                     // 4 Byte - EEPROM 40
  String ssid;                          // up to 32 Byte - EEPROM 64
  String password;                      // up to 32 Byte - EEPROM 96
  String ntpServerName;                 // up to 32 Byte - EEPROM 128
  String DeviceName;                    // up to 32 Byte - EEPROM 160
  String OTApwd;                         // up to 32 Byte - EEPROM 192
  String MQTTServer;                    // up to 32 Byte - EEPROM 224
  long MQTTPort;                        // 4 Byte - EEPROM 256
  String RelayTopic;                   // up to 32 Byte - EEPROM 260
  String Relay1OnMessage;                 // up to 16 Byte - EEPROM 292
  String Relay2OnMessage;                 // up to 16 Byte - EEPROM 308
  String Relay1OffMessage;                 // up to 16 Byte - EEPROM 324
  String Relay2OffMessage;                 // up to 16 Byte - EEPROM 340
  String Relay1ToggleMessage;                 // up to 16 Byte - EEPROM 356
  String Relay2ToggleMessage;                 // up to 16 Byte - EEPROM 372
  String StatusTopic;                   // up to 32 Byte - EEPROM 388
  String HeartbeatTopic;                // up to 32 Byte - EEPROM 420
  long HeartbeatEvery;                  // 4 Byte - EEPROM 452
  // Application Settings here... from EEPROM 456 up to 511 (0 - 511)

} config;



#ifdef ARDUINO_ESP32_DEV

  #include <Preferences.h>

  Preferences EEPROM;

  void WriteConfig(){

    Serial.println("Writing Config");
    EEPROM.putString("head", CFGVER);


    EEPROM.putUChar("dhcp", config.dhcp);
    EEPROM.putUChar("isDayLight", config.isDayLightSaving);

    EEPROM.putULong("NTPrate", config.Update_Time_Via_NTP_Every); // 4 Byte
    EEPROM.putULong("timeZone", config.timeZone); // 4 Byte

    EEPROM.putUChar("ip0", config.IP[0]);
    EEPROM.putUChar("ip1", config.IP[1]);
    EEPROM.putUChar("ip2", config.IP[2]);
    EEPROM.putUChar("ip3", config.IP[3]);

    EEPROM.putUChar("nm0", config.Netmask[0]);
    EEPROM.putUChar("nm1", config.Netmask[1]);
    EEPROM.putUChar("nm2", config.Netmask[2]);
    EEPROM.putUChar("nm3", config.Netmask[3]);

    EEPROM.putUChar("gw0", config.Gateway[0]);
    EEPROM.putUChar("gw1", config.Gateway[1]);
    EEPROM.putUChar("gw2", config.Gateway[2]);
    EEPROM.putUChar("gw3", config.Gateway[3]);

    EEPROM.putString("ssid", config.ssid);
    EEPROM.putString("pwd", config.password);
    EEPROM.putString("ntpSN", config.ntpServerName);
    EEPROM.putString("DevN", config.DeviceName);
    EEPROM.putString("OTApwd", config.OTApwd);
    EEPROM.putString("MQTTServer",config.MQTTServer);
    EEPROM.putULong("MQTTPort",config.MQTTPort);
    EEPROM.putString("ToggleTopic",config.ToggleTopic);
    EEPROM.putString("ToggleMessage",config.ToggleMessage);
    EEPROM.putString("StatusTopic",config.StatusTopic);
    EEPROM.putString("HeartbeatTopic",config.HeartbeatTopic);
    EEPROM.putULong("HeartbeatEvery",config.HeartbeatEvery);
  }
  boolean ReadConfig(){
    Serial.println("Reading Configuration");
    if (EEPROM.getString("head") == CFGVER )
    {
      Serial.println("Configurarion Found!" + CFGVER);
      config.dhcp = EEPROM.getUChar("dhcp",0);
      config.isDayLightSaving = EEPROM.getUChar("isDayLight");
      config.Update_Time_Via_NTP_Every = EEPROM.getULong("NTPrate"); // 4 Byte
      config.timeZone = EEPROM.getULong("timeZone"); // 4 Byte
      config.IP[0] = EEPROM.getUChar("ip0");
      config.IP[1] = EEPROM.getUChar("ip1");
      config.IP[2] = EEPROM.getUChar("ip2");
      config.IP[3] = EEPROM.getUChar("ip3");
      config.Netmask[0] = EEPROM.getUChar("nm0");
      config.Netmask[1] = EEPROM.getUChar("nm1");
      config.Netmask[2] = EEPROM.getUChar("nm2");
      config.Netmask[3] = EEPROM.getUChar("nm3");
      config.Gateway[0] = EEPROM.getUChar("gw0");
      config.Gateway[1] = EEPROM.getUChar("gw1");
      config.Gateway[2] = EEPROM.getUChar("gw2");
      config.Gateway[3] = EEPROM.getUChar("gw3");
      config.ssid = EEPROM.getString("ssid");
      config.password = EEPROM.getString("pwd");
      config.ntpServerName = EEPROM.getString("ntpSN");
      config.DeviceName = EEPROM.getString("DevN");
      config.OTApwd = EEPROM.getString("OTApwd");
      config.MQTTServer = EEPROM.getString("MQTTServer");
      config.MQTTPort = EEPROM.getULong("MQTTPort");
      config.ToggleTopic = EEPROM.getString("ToggleTopic");
      config.ToggleMessage = EEPROM.GetString("ToggleMessage");
      config.StatusTopic = EEPROM.GetString("StatusTopic");
      config.HeartbeatTopic = EEPROM.GetString("HeartbeatTopic");
      config.HeartbeatEvery = EEPROM.GetULong("HeartbeatEvery");
      // Application parameters here ... from EEPROM 356 to 511

      return true;

    }
    else
    {
      Serial.println("Configurarion NOT FOUND!!!!");
      return false;
    }
  }



#elif ARDUINO_ESP8266_ESP01 || ARDUINO_ESP8266_NODEMCU
  //  Auxiliar function to handle EEPROM
  // EEPROM-parameters

  void EEPROMWritelong(int address, long value){
    byte four = (value & 0xFF);
    byte three = ((value >> 8) & 0xFF);
    byte two = ((value >> 16) & 0xFF);
    byte one = ((value >> 24) & 0xFF);

    //Write the 4 bytes into the eeprom memory.
    EEPROM.write(address, four);
    EEPROM.write(address + 1, three);
    EEPROM.write(address + 2, two);
    EEPROM.write(address + 3, one);
  }

  long EEPROMReadlong(long address){
    //Read the 4 bytes from the eeprom memory.
    long four = EEPROM.read(address);
    long three = EEPROM.read(address + 1);
    long two = EEPROM.read(address + 2);
    long one = EEPROM.read(address + 3);

    //Return the recomposed long by using bitshift.
    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
  }

  void WriteStringToEEPROM(int beginaddress, String string){
    char  charBuf[string.length() + 1];
    string.toCharArray(charBuf, string.length() + 1);
    for (int t =  0; t < sizeof(charBuf); t++)
    {
      EEPROM.write(beginaddress + t, charBuf[t]);
    }
  }

  String  ReadStringFromEEPROM(int beginaddress){
    volatile byte counter = 0;
    char rChar;
    String retString = "";
    while (1)
    {
      rChar = EEPROM.read(beginaddress + counter);
      if (rChar == 0) break;
      if (counter > 31) break;
      counter++;
      retString.concat(rChar);

    }
    return retString;
  }

  void WriteConfig(){
    String cfgver = CFGVER;
    char ccfgver[5];
    cfgver.toCharArray(ccfgver,5);

    Serial.print("Writing Config ");
    Serial.println(ccfgver);
    EEPROM.write(0, ccfgver[0]);
    EEPROM.write(1, ccfgver[1]);
    EEPROM.write(2, ccfgver[2]);
    EEPROM.write(3, ccfgver[3]);

    EEPROM.write(16, config.dhcp);
    EEPROM.write(17, config.isDayLightSaving);

    EEPROMWritelong(18, config.Update_Time_Via_NTP_Every); // 4 Byte
    EEPROMWritelong(22, config.timeZone); // 4 Byte

    EEPROM.write(32, config.IP[0]);
    EEPROM.write(33, config.IP[1]);
    EEPROM.write(34, config.IP[2]);
    EEPROM.write(35, config.IP[3]);

    EEPROM.write(36, config.Netmask[0]);
    EEPROM.write(37, config.Netmask[1]);
    EEPROM.write(38, config.Netmask[2]);
    EEPROM.write(39, config.Netmask[3]);

    EEPROM.write(40, config.Gateway[0]);
    EEPROM.write(41, config.Gateway[1]);
    EEPROM.write(42, config.Gateway[2]);
    EEPROM.write(43, config.Gateway[3]);

    WriteStringToEEPROM(64, config.ssid);
    WriteStringToEEPROM(96, config.password);
    WriteStringToEEPROM(128, config.ntpServerName);
    WriteStringToEEPROM(160, config.DeviceName);
    WriteStringToEEPROM(192, config.OTApwd);
    WriteStringToEEPROM(224, config.MQTTServer);
    EEPROMWritelong(256, config.MQTTPort);
    WriteStringToEEPROM(260, config.RelayTopic);                 // up to 32 Byte - EEPROM 260
    WriteStringToEEPROM(292, config.Relay1OnMessage);                 // up to 16 Byte - EEPROM 292
    WriteStringToEEPROM(308, config.Relay2OnMessage);                 // up to 16 Byte - EEPROM 308
    WriteStringToEEPROM(324, config.Relay1OffMessage);                 // up to 16 Byte - EEPROM 324
    WriteStringToEEPROM(340, config.Relay2OffMessage);                 // up to 16 Byte - EEPROM 340
    WriteStringToEEPROM(356, config.Relay1ToggleMessage);                 // up to 16 Byte - EEPROM 356
    WriteStringToEEPROM(372, config.Relay2ToggleMessage);                 // up to 16 Byte - EEPROM 372
    WriteStringToEEPROM(388, config.StatusTopic);
    WriteStringToEEPROM(420, config.HeartbeatTopic);
    EEPROMWritelong(452, config.HeartbeatEvery);

      // Application Settings here... from EEPROM 392 up to 511 (0 - 511)

    EEPROM.commit();

  }

  boolean ReadConfig(){
    Serial.println("Reading Configuration");
    String cfgver = CFGVER;
    char ccfgver[5];
    cfgver.toCharArray(ccfgver,5);
    if (EEPROM.read(0) == cfgver[0] && EEPROM.read(1) == cfgver[1] && EEPROM.read(2) == cfgver[2] && EEPROM.read(3) == cfgver[3] )
    {
      Serial.println("Configurarion Found!");
      config.dhcp = 	EEPROM.read(16);
      config.isDayLightSaving = EEPROM.read(17);
      config.Update_Time_Via_NTP_Every = EEPROMReadlong(18); // 4 Byte
      config.timeZone = EEPROMReadlong(22); // 4 Byte
      config.IP[0] = EEPROM.read(32);
      config.IP[1] = EEPROM.read(33);
      config.IP[2] = EEPROM.read(34);
      config.IP[3] = EEPROM.read(35);
      config.Netmask[0] = EEPROM.read(36);
      config.Netmask[1] = EEPROM.read(37);
      config.Netmask[2] = EEPROM.read(38);
      config.Netmask[3] = EEPROM.read(39);
      config.Gateway[0] = EEPROM.read(40);
      config.Gateway[1] = EEPROM.read(41);
      config.Gateway[2] = EEPROM.read(42);
      config.Gateway[3] = EEPROM.read(43);
      config.ssid = ReadStringFromEEPROM(64);
      config.password = ReadStringFromEEPROM(96);
      config.ntpServerName = ReadStringFromEEPROM(128);
      config.DeviceName = ReadStringFromEEPROM(160);
      config.OTApwd = ReadStringFromEEPROM(192);
      config.MQTTServer = ReadStringFromEEPROM(224);
      config.MQTTPort = EEPROMReadlong(256);
      config.RelayTopic = ReadStringFromEEPROM(260);                 // up to 32 Byte - EEPROM 260
      config.Relay1OnMessage = ReadStringFromEEPROM(292);                 // up to 16 Byte - EEPROM 292
      config.Relay2OnMessage = ReadStringFromEEPROM(308);                 // up to 16 Byte - EEPROM 308
      config.Relay1OffMessage = ReadStringFromEEPROM(324);                 // up to 16 Byte - EEPROM 324
      config.Relay2OffMessage = ReadStringFromEEPROM(340);                 // up to 16 Byte - EEPROM 340
      config.Relay1ToggleMessage = ReadStringFromEEPROM(356);                 // up to 16 Byte - EEPROM 356
      config.Relay2ToggleMessage = ReadStringFromEEPROM(372);                 // up to 16 Byte - EEPROM 372
      config.StatusTopic = ReadStringFromEEPROM(388);
      config.HeartbeatTopic = ReadStringFromEEPROM(420);
      config.HeartbeatEvery = EEPROMReadlong(452);
      // Application parameters here ... from EEPROM 456 to 511

      return true;

    }
    else
    {
      Serial.println("Configurarion NOT FOUND!!!!");
      return false;
    }
  }


#endif  // ESP8266

void printConfig(){

  Serial.println("Printing Config");

  Serial.printf("DHCP:%d\n", config.dhcp);
  Serial.printf("DayLight:%d\n", config.isDayLightSaving);

  Serial.printf("NTP update every %ld sec\n", config.Update_Time_Via_NTP_Every); // 4 Byte
  Serial.printf("Timezone %ld\n", config.timeZone); // 4 Byte

  Serial.printf("IP:%d.%d.%d.%d\n", config.IP[0],config.IP[1],config.IP[2],config.IP[3]);
  Serial.printf("Mask:%d.%d.%d.%d\n", config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3]);
  Serial.printf("Gateway:%d.%d.%d.%d\n", config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3]);


  Serial.printf("SSID:%s\n", config.ssid.c_str());
  Serial.printf("PWD:%s\n", config.password.c_str());
  Serial.printf("ntp ServerName:%s\n", config.ntpServerName.c_str());
  Serial.printf("Device Name:%s\n", config.DeviceName.c_str());
  Serial.printf("OTA password:%s\n", config.OTApwd.c_str());
  Serial.printf("MQTT Server:%s\n", config.MQTTServer.c_str());
  Serial.printf("MQTT Port:%ld\n", config.MQTTPort);
  Serial.printf("Relay Topic:%s\n", config.RelayTopic.c_str());                 // up to 32 Byte - EEPROM 260
  Serial.printf("Relay 1 On Message:%s\n", config.Relay1OnMessage.c_str());                 // up to 16 Byte - EEPROM 292
  Serial.printf("Relay 2 On Message:%s\n", config.Relay2OnMessage.c_str());                 // up to 16 Byte - EEPROM 308
  Serial.printf("Relay 1 Off Message:%s\n", config.Relay1OffMessage.c_str());                 // up to 16 Byte - EEPROM 324
  Serial.printf("Relay 2 Off Message:%s\n", config.Relay2OffMessage.c_str());                 // up to 16 Byte - EEPROM 340
  Serial.printf("Relay 1 Toggle Message:%s\n", config.Relay1ToggleMessage.c_str());                 // up to 16 Byte - EEPROM 356
  Serial.printf("Relay 2 Toggle Message:%s\n", config.Relay2ToggleMessage.c_str());                 // up to 16 Byte - EEPROM 372
  Serial.printf("Status Topic:%s\n", config.StatusTopic.c_str());
  Serial.printf("Heartbeat Topic:%s\n", config.HeartbeatTopic.c_str());
  Serial.printf("Heartbeat Every %ld seconds",config.HeartbeatEvery);
    // Application Settings here... from EEPROM 456 up to 511 (0 - 511)

}

String formatConfig(){
  String outstring = "";
  outstring = outstring + "DHCP:"+String(config.dhcp) + "|";
  outstring = outstring + "DayLight:" + String(config.isDayLightSaving) + "|";
  outstring = outstring + "NTP update every " + String(config.Update_Time_Via_NTP_Every) + " sec" + "|";
  outstring = outstring + "Timezone:" + String(config.timeZone) + "|";
  outstring = outstring + "IP:" + String(config.IP[0]) + "." + String(config.IP[1]) + "." + String(config.IP[2]) + "." + String(config.IP[3]) + "|";
  outstring = outstring + "Mask:" + String(config.Netmask[0]) + "." + String(config.Netmask[1]) + "." + String(config.Netmask[2]) + "." + String(config.Netmask[3]) + "|";
  outstring = outstring + "Gateway:" + String(config.Gateway[0]) + "." + String(config.Gateway[1]) + "." + String(config.Gateway[2]) + "." + String(config.Gateway[3]) + "|";
  outstring = outstring + "SSID:" + config.ssid + "|";
  outstring = outstring + "PWD:" + config.password + "|";
  outstring = outstring + "ntp ServerName:" + config.ntpServerName + "|";
  outstring = outstring + "Device Name:" + config.DeviceName + "|";
  outstring = outstring + "OTA password" + config.OTApwd + "|";
  outstring = outstring + "MQTT Server:" + config.MQTTServer + "|";
  outstring = outstring + "MQTT Port:" + String(config.MQTTPort) + "|";
  outstring = outstring + "Relay Topic:" + config.RelayTopic + "|";                 // up to 32 Byte - EEPROM 260
  outstring = outstring + "Relay 1 On Message:" + config.Relay1OnMessage + "|";                 // up to 16 Byte - EEPROM 292
  outstring = outstring + "Relay 2 On Message:" + config.Relay2OnMessage + "|";                 // up to 16 Byte - EEPROM 308
  outstring = outstring + "Relay 1 Off Message:" + config.Relay1OffMessage + "|";                 // up to 16 Byte - EEPROM 324
  outstring = outstring + "Relay 2 Off Message:" + config.Relay2OffMessage + "|";                 // up to 16 Byte - EEPROM 340
  outstring = outstring + "Relay 1 Toggle Message:" + config.Relay1ToggleMessage + "|";                 // up to 16 Byte - EEPROM 356
  outstring = outstring + "Relay 2 Toggle Message:" + config.Relay2ToggleMessage + "|";                 // up to 16 Byte - EEPROM 372
  outstring = outstring + "Status Topic:" + config.StatusTopic + "|";
  outstring = outstring + "Heartbeat Topic:" + config.HeartbeatTopic + "|";
  outstring = outstring + "Heartbeat every " + String(config.HeartbeatEvery);
  return outstring;
}

void configLoadDefaults(uint16_t ChipId){

  #ifdef ARDUINO_ESP32_DEV
    config.ssid = "ESP32-" + String(ChipId,HEX);       // SSID of access point
  #elif ARDUINO_ESP8266_ESP01 || ARDUINO_ESP8266_NODEMCU
    config.ssid = "ESP8266-" + String(ChipId,HEX);       // SSID of access point
  #endif
  config.password = "" ;   // password of access point
  config.dhcp = true;
  config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 1; config.IP[3] = 100;
  config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;
  config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 254;
  config.ntpServerName = "0.ch.pool.ntp.org"; //"0.ch.pool.ntp.org"; // to be adjusted to PT ntp.ist.utl.pt
  config.Update_Time_Via_NTP_Every =  5;
  config.timeZone = 1;
  config.isDayLightSaving = true;
  config.DeviceName = "Not Named";
  config.OTApwd = "";
  config.MQTTServer = "";
  config.MQTTPort = 0;
  config.RelayTopic = "";                 // up to 32 Byte - EEPROM 260
  config.Relay1OnMessage = "";                 // up to 16 Byte - EEPROM 292
  config.Relay2OnMessage = "";                 // up to 16 Byte - EEPROM 308
  config.Relay1OffMessage = "";                 // up to 16 Byte - EEPROM 324
  config.Relay2OffMessage = "";                 // up to 16 Byte - EEPROM 340
  config.Relay1ToggleMessage = "";                 // up to 16 Byte - EEPROM 356
  config.Relay2ToggleMessage = "";                 // up to 16 Byte - EEPROM 372
  config.StatusTopic = "";
  config.HeartbeatTopic = "";
  config.HeartbeatEvery = 0;

  return;
}


#endif
