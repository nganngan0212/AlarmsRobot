   /*
Software used: Arduino Remote LITE (Bluetooth & Wifi)
Connect Arudino with Bluetooth module
    HC-06     Arduino
     +5V        5V
     GND        GND
     TX         5
     RX         4


     DS1302     Arduino
     Vcc        5V
     GND        GND
     CLK        6
     DAT        7
     RST        8
*/

#include <AFMotor.h> //L293D
#include <SoftwareSerial.h> //HC06
#include <virtuabotixRTC.h> // DS1320
#include <string.h>

#define CLK 6
#define DAT 7
#define RST 8
#define SPEEDMOTOR1 255
#define SPEEDMOTOR2 180

const int buzzer = 10;

const int rxPin = 5;
const int txPin = 4;

AF_DCMotor motor1(2);
AF_DCMotor motor2(3);

virtuabotixRTC Clock(6, 7, 8);

SoftwareSerial hc06(rxPin, txPin);

void onBuzzer()
{
    digitalWrite(buzzer,HIGH);
}

void offBuzzer()
{
  digitalWrite(buzzer, LOW);
}

void setupHC06()
{
    hc06.begin(9600);   
}

void Roleft()
{
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
}

void Roright()
{
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
}

void Up()
{
    motor1.run(FORWARD);
    motor2.run(FORWARD);
}

//void Down()
//{
//    motor1.run(BACKWARD);
//    motor2.run(BACKWARD);
//}
//
//void Left()
//{
//    motor1.run(FORWARD);
//    motor2.run(FORWARD);
//}

void Stop()
{
    motor1.run(BRAKE);
    motor2.run(BRAKE);
}

void setup() {
  // put your setup code here, to run once:
    motor1.setSpeed(SPEEDMOTOR1);
    motor1.run(RELEASE);

    motor2.setSpeed(SPEEDMOTOR2);
    motor2.run(RELEASE);

    pinMode(buzzer, OUTPUT);
    
    Serial.begin(9600);
    setupHC06();
}

void loop() {
  // put your main code here, to run repeatedly:
    String msg;
    
    if(hc06.available())
    {
        msg = hc06.readString();
        Serial.println(msg);
    }

}
