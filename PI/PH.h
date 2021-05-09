#ifndef PH_H
#define PH_H

#include "Arduino.h"

class PH
{
private:
    float CALIBRATION_VALUE, COEFFICIENT;
    unsigned int ARRAY_SIZE;
    int *BUFFER_ARRAY;
    uint8_t pin;

public:
    PH(uint8_t pin, float CO = -5.7, float C_V = 21.33, float A_S = 10);
    unsigned int getArraySize();
    float getCalibrationValue();
    float getVoltage();
    float getCoefficient();
    float readPH();
    unsigned long int average();
};

#endif