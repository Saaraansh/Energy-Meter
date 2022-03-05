#include <sct.h>

const float FACTOR = 30; //30A/1V
const float VMIN = 0.18;
const float VMAX = 3.02;
const float ADCV = 3.3;

float getCurrent()
{
    float voltage;
    float current;
    float sum = 0;
    long time = millis();
    int counter = 0;

    while(millis() - time < 500)
    {
        voltage = analogRead(A0) * ADCV /1023.0;
        current = fmap(voltage, VMIN, VMAX, -FACTOR, FACTOR);

        sum += sq(current);
        counter ++;
        delay(1);
    }
    current = sqrt(sum / counter);
    return(current);
}

float fmap(float voltage, float in_min, float in_max, float out_min, float out_max)
{
    return(((voltage - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min); 
}