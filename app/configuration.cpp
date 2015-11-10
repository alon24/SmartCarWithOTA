/*
 * configuration.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: ilan
 */
#include "../include/configuration.h"

#include <SmingCore/SmingCore.h>

SmartCarConfig ActiveConfig;

SmartCarConfig loadConfig()
{
	DynamicJsonBuffer jsonBuffer;
	SmartCarConfig cfg;
	if (fileExist(SMARTCAR_CONFIG_FILE))
	{
		Serial.printf("loadConfig::dumping file %s:\r\n", SMARTCAR_CONFIG_FILE);
		Serial.println(fileGetContent(SMARTCAR_CONFIG_FILE));

		int size = fileGetSize(SMARTCAR_CONFIG_FILE);
		char* jsonString = new char[size + 1];
		fileGetContent(SMARTCAR_CONFIG_FILE, jsonString, size + 1);
		JsonObject& root = jsonBuffer.parseObject(jsonString);

		JsonObject& network = root["network"];
		cfg.NetworkSSID = String((const char*)network["ssid"]);
		cfg.NetworkPassword = String((const char*)network["password"]);
		cfg.otaServer = String((const char*)network["otaServer"]);

		delete[] jsonString;
	}
	else
	{
		cfg.NetworkSSID = WIFI_SSID;
		cfg.NetworkPassword = WIFI_PWD;
	}
	return cfg;
}

void saveConfig(SmartCarConfig& cfg)
{
	ActiveConfig = cfg;

	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	JsonObject& network = jsonBuffer.createObject();
	root["network"] = network;
	network["ssid"] = cfg.NetworkSSID.c_str();
	network["password"] = cfg.NetworkPassword.c_str();
	network["otaServer"] = cfg.otaServer.c_str();

	char buf[3048];
	root.prettyPrintTo(buf, sizeof(buf));
	fileSetContent(SMARTCAR_CONFIG_FILE, buf);

	Serial.printf("saveConfig::dumping file %s:\r\n", SMARTCAR_CONFIG_FILE);
	Serial.println(fileGetContent(SMARTCAR_CONFIG_FILE));
}
