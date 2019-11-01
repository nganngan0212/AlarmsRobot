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
#include<string.h>

const int rxPin = 5;
const int txPin = 4;

SoftwareSerial hc06(rxPin, txPin);

void setupHC06()
{
    hc06.begin(9600);   
    pinMode(10, OUTPUT);
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
        String msg = hc06.readString();
        Serial.println(msg);
        if(msg == "on") {
          digitalWrite(10, HIGH);
        }
        if(msg == "off")
        {
          digitalWrite(10, LOW);
        }
    }
}
