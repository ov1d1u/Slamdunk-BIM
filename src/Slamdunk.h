
#ifndef ARDUINO_SLAMDUNK_H
#define ARDUINO_SLAMDUNK_H
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "Sensor.h"

// BLE Service
#define SERVICE_UUID			"6b685cfe-09c0-4579-aaf4-27db6ce09fcf"
#define SENSOR_CHARACTERISTIC	"d214c680-06df-4e36-a611-958769b73ca4"

class Slamdunk: public BLEServerCallbacks  
{
	private:
		BLEServer *bleServer;
		BLEService *bleService;
        BLECharacteristic *sensorCharacteristic;

		void advertise();
		void printSensorData(String name, String unit, sensors_vec_t sdata);
		void onConnect(BLEServer *pServer);
		void onDisconnect(BLEServer *pServer);
	public:
		Sensor sensor;

		Slamdunk();
		~Slamdunk();
		void setup();
		void loop();
};
#endif
