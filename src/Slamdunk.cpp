#include "Slamdunk.h"  

Slamdunk::Slamdunk() {}

void Slamdunk::setup() {
  sensor.setup();

  BLEDevice::init("SlamDunk BLE");

  bleServer = BLEDevice::createServer();
  bleServer->setCallbacks(this);

  bleService = bleServer->createService(SERVICE_UUID);
  
  sensorCharacteristic = bleService->createCharacteristic(
    SENSOR_CHARACTERISTIC,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

  sensorCharacteristic->addDescriptor(new BLE2902());

  BLEAdvertising *bleAdverising = BLEDevice::getAdvertising();
  bleAdverising->addServiceUUID(SERVICE_UUID);
  bleAdverising->setScanResponse(true);
  bleAdverising->setMinPreferred(0x06);
  bleAdverising->setMinPreferred(0x12);
  
  bleService->start();

  advertise();
}

void Slamdunk::loop() {
  sensors_event_t accel, mag, gyro, temp;
  sensor.getEvent(&accel, &mag, &gyro, &temp);

  byte packetArray[36] = {
    ((uint8_t*)&accel.acceleration.x)[0],
    ((uint8_t*)&accel.acceleration.x)[1],
    ((uint8_t*)&accel.acceleration.x)[2],
    ((uint8_t*)&accel.acceleration.x)[3],
    ((uint8_t*)&accel.acceleration.y)[0],
    ((uint8_t*)&accel.acceleration.y)[1],
    ((uint8_t*)&accel.acceleration.y)[2],
    ((uint8_t*)&accel.acceleration.y)[3],
    ((uint8_t*)&accel.acceleration.z)[0],
    ((uint8_t*)&accel.acceleration.z)[1],
    ((uint8_t*)&accel.acceleration.z)[2],
    ((uint8_t*)&accel.acceleration.z)[3],

    ((uint8_t*)&gyro.gyro.x)[0],
    ((uint8_t*)&gyro.gyro.x)[1],
    ((uint8_t*)&gyro.gyro.x)[2],
    ((uint8_t*)&gyro.gyro.x)[3],
    ((uint8_t*)&gyro.gyro.y)[0],
    ((uint8_t*)&gyro.gyro.y)[1],
    ((uint8_t*)&gyro.gyro.y)[2],
    ((uint8_t*)&gyro.gyro.y)[3],
    ((uint8_t*)&gyro.gyro.z)[0],
    ((uint8_t*)&gyro.gyro.z)[1],
    ((uint8_t*)&gyro.gyro.z)[2],
    ((uint8_t*)&gyro.gyro.z)[3],

    ((uint8_t*)&mag.magnetic.x)[0],
    ((uint8_t*)&mag.magnetic.x)[1],
    ((uint8_t*)&mag.magnetic.x)[2],
    ((uint8_t*)&mag.magnetic.x)[3],
    ((uint8_t*)&mag.magnetic.y)[0],
    ((uint8_t*)&mag.magnetic.y)[1],
    ((uint8_t*)&mag.magnetic.y)[2],
    ((uint8_t*)&mag.magnetic.y)[3],
    ((uint8_t*)&mag.magnetic.z)[0],
    ((uint8_t*)&mag.magnetic.z)[1],
    ((uint8_t*)&mag.magnetic.z)[2],
    ((uint8_t*)&mag.magnetic.z)[3],
  };

  // printSensorData("Accel", "m/s", accel.acceleration);

  sensorCharacteristic->setValue(packetArray, sizeof(packetArray));
  sensorCharacteristic->notify();
}

void Slamdunk::advertise() {
  Serial.println("Start Advertising...");
  BLEDevice::startAdvertising();
}

void Slamdunk::onConnect(BLEServer *pServer) {
    Serial.println("New device connection.");
}

void Slamdunk::onDisconnect(BLEServer *pServer) {
  Serial.print("Device disconnected. Current active connections: "); Serial.println(pServer->getConnectedCount());
  advertise();
}

void Slamdunk::printSensorData(String name, String unit, sensors_vec_t sdata) {
  Serial.println("");
  Serial.print(name); Serial.println(": ");
  Serial.print("  \tX: "); Serial.print(sdata.x); Serial.print(" ");
  Serial.print("  \tY: "); Serial.print(sdata.y); Serial.print(" ");
  Serial.print("  \tZ: "); Serial.print(sdata.z); Serial.print("  \t"); Serial.println(unit);
  Serial.println("");
}

Slamdunk::~Slamdunk() {

}