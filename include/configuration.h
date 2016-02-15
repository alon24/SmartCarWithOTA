#ifndef INCLUDE_CONFIGURATION_H_
#define INCLUDE_CONFIGURATION_H_

#include <SmingCore.h>

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
	#define WIFI_SSID "PleaseEnterSSID" // Put you SSID and Password here
	#define WIFI_PWD "PleaseEnterPass"
#endif

//Pins used

//SSD13006 Pins
#define sclPin 13
#define sdaPin 14

#define SMARTCAR_CONFIG_FILE ".smartcar.conf" // leading point for security reasons :)

struct SmartCarConfig
{
	SmartCarConfig()
	{
		otaServer = "10.100.102.7:10032";
	}

	String NetworkSSID;
	String NetworkPassword;
	String otaServer;

};

SmartCarConfig loadConfig();
void saveConfig(SmartCarConfig& cfg);
extern SmartCarConfig ActiveConfig;

#endif /* INCLUDE_CONFIGURATION_H_ */
