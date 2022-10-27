
#ifndef ARDUINO_SENSOR_H
#define ARDUINO_SENSOR_H
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>

#define LSM9DS0_XM_CS 10
#define LSM9DS0_GYRO_CS 9
#define LSM9DS0_SCLK 13
#define LSM9DS0_MISO 12
#define LSM9DS0_MOSI 11

class Sensor  
{
	private:
		Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);
	public:
		Sensor();
		~Sensor();
		void setup();
		void displaySensorDetails();
		void getEvent(sensors_event_t *accelEvent, sensors_event_t *magEvent, sensors_event_t *gyroEvent, sensors_event_t *tempEvent);
};
#endif
