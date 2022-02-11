#ifndef ZMPT_H
#define ZMPT_H

#include <Arduino.h>
// Initialize zmpt module
void zmptInit(float maxRmsVolt, float minRmsVolt, int maxADC, int minADC, uint8_t connectedPin);
//This function can be run in a while loop indefinitely to see the waveform and adjust potentiometer according to it
void zmptTester(int time, int delayTime);
// Get AC Voltage -> Output is RMS Voltage
float getVoltageAC(int frequency);
//Get DC Voltage -> Output is RMS Voltage
float getVoltageDC();

#endif