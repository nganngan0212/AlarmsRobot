/*
Software used: Arduino Remote LITE (Bluetooth & Wifi)
Connect Arudino with Bluetooth module
    HC-06     Arduino
     +5V        5V
     GND        GND
     TX         5
     RX         4
*/

#include <SoftwareSerial.h>

const int RXPIN = 5;
const int TXPIN = 4;

SoftwareSerial hc06(RXPIN, TXPIN);

void setupHC06()
{
    hc06.begin(9600);
}

void setup()
{
    Serial.begin(9600);
    setupHC06();
}

void loop()
{
    if(hc06.available())
    {
        int msg = hc06.read();
        Serial.write(msg);
    }
}
