#include "PH.h"

PH::PH(uint8_t pin, float CO, float C_V, float A_S)
{
    this->pin = pin;
    this->COEFFICIENT = CO;
    this->CALIBRATION_VALUE = C_V;
    this->ARRAY_SIZE = A_S;
    BUFFER_ARRAY = new int[ARRAY_SIZE];
}

float PH::getCalibrationValue()
{
    return this->CALIBRATION_VALUE;
}

unsigned int PH::getArraySize()
{
    return this->ARRAY_SIZE;
}

float PH::getCoefficient()
{
    return this->COEFFICIENT;
}

unsigned long int PH::average()
{
    unsigned long int avg = 0;
    for (unsigned int i = 0; i < ARRAY_SIZE; i++)
    {
        BUFFER_ARRAY[i] = analogRead(this->pin);
        avg += BUFFER_ARRAY[i];
        delay(50);
    }
    return avg;
}

float PH::getVoltage()
{
    return (float)average() * 5.0 / 1024.0 / ARRAY_SIZE;
}

float PH::readPH()
{
    return COEFFICIENT * getVoltage() + CALIBRATION_VALUE;
}
