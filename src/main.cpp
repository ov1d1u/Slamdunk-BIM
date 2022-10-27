#include <Arduino.h>
#include "Slamdunk.h"

Slamdunk slamdunk;

void setup(void)  {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.println("-------------");
  Serial.println("Slamdunk v0.1");
  Serial.println("-------------");
  Serial.println("");
  
  slamdunk.setup();

  /* Display some basic information on this sensor */
  slamdunk.sensor.displaySensorDetails();
  
  /* We're ready to go! */
  Serial.println("");
}

void loop(void)  {
  slamdunk.loop();
}