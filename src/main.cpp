#include <Arduino.h>
#include "RFMotionLightSensorNode.h"

RFMotionLightSensorNode node;

void setup() 
{     
  Serial.begin(38400);
  node.setup();
}

void loop() 
{
  node.loop();
}