#include <Arduino.h>
#include <zmpt.h>

float slope = 0.122;
float intercept = 249.734;
uint8_t usingPin = A0;
float lowADC = 2047;

void zmptInit(float maxRmsVolt, float minRmsVolt, int maxADC, int minADC, uint8_t connectedPin)
{
    lowADC = minADC;
    maxRmsVolt = maxRmsVolt * sqrt(2);
    minRmsVolt = minRmsVolt * sqrt(2);
    slope = (maxRmsVolt - minRmsVolt) / (maxADC - minADC);
    intercept = ((slope * minADC) - minRmsVolt);
    usingPin = connectedPin;
    pinMode(usingPin, INPUT);
    return;
}

void zmptTester(int time, int delayTime)
{
    int i = 0;
    while (i < (time / delayTime))
    {
        Serial.println(analogRead(usingPin));
        delay(delayTime);
        i++;
    }
    return;
}

float getVoltageDC()
{
    int sensVal = 0;
    int maxVal = 0;
    for (int i = 0; i < 100; i++)
    {
        sensVal = analogRead(usingPin);
        if (maxVal < sensVal)
        {
            maxVal = sensVal;
        }
    }
    float vFinal = 0;
    if (maxVal != lowADC)
    {
        vFinal = (slope * maxVal) - intercept;
        vFinal = vFinal / sqrt(2);
    }
    else
    {
        vFinal = 0;
    }
    return vFinal;
}

float getVoltageAC(int frequency)
{
    int sensVal = 0;
    int maxVal = 0;
    int time = 1000000 / frequency;
    int currTime = micros();
    while ((micros() - currTime) <= time)
    {
        sensVal = analogRead(usingPin);
        if (maxVal < sensVal)
        {
            maxVal = sensVal;
        }
    }
    float vFinal = 0;
    if (maxVal != lowADC)
    {
        vFinal = (slope * maxVal) - intercept;
        vFinal = vFinal / sqrt(2);
    }
    else
    {
        vFinal = 0;
    }
    return vFinal;
}