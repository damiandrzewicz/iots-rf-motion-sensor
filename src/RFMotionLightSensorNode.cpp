#include "RFMotionLightSensorNode.h"
#include <Wire.h>

void RFMotionLightSensorNode::setup()
{
    //setPeriodicalWakeupMode(1000U);
    //RFTemplateNode::setup();
    RFTemplateNode::initAdcReference();
    initLightSensor();

}

int RFMotionLightSensorNode::sensorRawToPhys(int raw){
  // Conversion rule
  float Vout = float(raw) * (1.1 / float(1023));// Conversion analog to voltage
  float RLDR = (10000 * (1.1 - Vout))/Vout; // Conversion voltage to resistance
  int phys=500/(RLDR/1000); // Conversion resitance to lumen
  return phys;
}

void RFMotionLightSensorNode::work()
{
    //RFTemplateNode::work();

    auto lidhtADC = readLightADC();
    PRINTD1F("light adc:"); PRINTLND1(lidhtADC);
    auto lux = sensorRawToPhys(lidhtADC);
    PRINTD1F("lux:"); PRINTLND1(lux);

    delay(500);

    //appendSendBufferInt(lidhtADC, true);
}

void RFMotionLightSensorNode::loop()
{
    work();
}

void RFMotionLightSensorNode::initMotionSensor()
{

}

void RFMotionLightSensorNode::initLightSensor()
{
    pinMode(lightSensorPin_, OUTPUT);
    pinMode(lightSensorAdcPin_, INPUT);
    digitalWrite(lightSensorPin_, LOW);

}


uint16_t RFMotionLightSensorNode::readLightADC()
{
    digitalWrite(lightSensorPin_, HIGH);
    uint16_t temp = 0;
    uint8_t repeats = 8;
    for(uint8_t i = 0; i < repeats; i++){
        temp += analogRead(lightSensorAdcPin_);
    }
    digitalWrite(lightSensorPin_, LOW);
    return temp / repeats;
}