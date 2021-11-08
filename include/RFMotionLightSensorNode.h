#pragma once

#include "RFBaseNode.h"

class RFMotionLightSensorNode : public RFBaseNode
{
public:
    RFMotionLightSensorNode() = default;

    virtual void setup() override;
    virtual void work() override;
    virtual void loop() override;

protected:

    void initMotionSensor();
    void initLightSensor();
    int sensorRawToPhys(int raw);

    uint16_t readLightADC();

private:
    const uint8_t lightSensorPin_ = 7;
    const uint8_t lightSensorAdcPin_ = A1;
};