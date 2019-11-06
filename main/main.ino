#include <SoftwareSerial.h> // HC06
#include <virtuabotixRTC.h> // DS1320
#include <string.h>

// Motors
const int IN1 = A0;
const int IN2 = A1;
const int IN3 = A2;
const int IN4 = A3;
const int MAX_SPEED = 255;
const int MIN_SPEED = 0;
void setupL298();
void moveUp(int& speed, const int& pin1, const int& pin2);
void moveDown(int& speed, const int& pin1, const int& pin2);
int speedRandom();

// Bluetooth
const int TXPIN = 4;
const int RXPIN = 5;
SoftwareSerial hc06(RXPIN, TXPIN);
void setupHC06();

// Real time DS1302
virtuabotixRTC myRTC(6, 7, 8);// CLK, DAT, RST
bool isTimeUp(virtuabotixRTC rtc, int& start_time);
void printCurrentTime(virtuabotixRTC rtc);
bool checkTime(string msg, int hour, int minutes);

// US015
const int TRIG1 = 10;
const int ECHO1 = 11;
const int TRIG2 = 12;
const int ECHO2 = 13;
void setupUltraSonic(int trig_pin, int echo_pin);
float distance2Object(int trig_pin, int echo_pin)

// Buzzer
const int BUZZER = 9;
void turnOnBuzzer(int buzzer_pin);

void setup()
{
    setupL298(); // Motor
    setupHC06(); // Bluetooth
    myRTC.setDS1302Time(00, 11, 17, 4, 23, 10, 2019); // ds1302
    setupUltraSonic(TRIG1, ECHO1); // Ultrasonic
    setupUltraSonic(TRIG2, ECHO2);
    pinMode(BUZZER, OUTPUT); // Buzzer
}

int start_time = NULL;
string msg;
bool is_time = false;

// Main function
void loop()
{
    // Get time from Bluetooth
    myRTC.updateTime();
    h = myRTC.hours;
    m = myRTC.minutes;
    if(hc06.available())
    {
        msg = hc06.readString();
        is_time = checkTime(msg, h, m);
    }

    // Alarm
    if(is_time)
    {
        // Turn on buzzer if is alarm clock
        turnOnBuzzer(BUZZER);

        // Run motor
        float dis1 = distance2Object(TRIG1, ECHO1);
        float dis2 = distance2Object(TRIG2, ECHO2);
        while(isNearObject(TRIG1, ECHO2) && isNearObject(TRIG2, ECHO2))
        {
            // Rotate until one of them false
            moveDown(180, IN1, IN2);
            moveUp(180, IN3, IN4);
        }
        
        if(isTimeUp(myRTC, start_time))
        {
            int speed_left = speedRandom();
            int speed_right = speedRandom();
        }

        if(isNearObject(TRIG1, ECHO1))
        {
            // Run backward
            moveDown(speed_left, IN1, IN2);
            moveDown(speed_right, IN3, IN4);

        }
        if(isNearObject(TRIG2, ECHO2))
        {
            // Run forward
            moveUp(speed_left, IN1, IN2);
            moveUp(speed_right, IN3, IN4);
        }
    }
}

/************************
* Motor 
************************/
void moveUp(int& speed, const int& pin1, const int& pin2)
{
    // speed = checkSpeed(speed);
    analogWrite(pin1, speed);
    analogWrite(pin2, MIN_SPEED);
}

void moveDown(int& speed, const int& pin1, const int& pin2)
{
    // speed = checkSpeed(speed);
    analogWrite(pin1, MIN_SPEED);
    analogWrite(pin2, speed);
}

int speedRandom()
{
    // random speed motor in range of 180-255
    return random(180,255);
}

void setupL298()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);  
}

/************************
* Bluetooth
************************/
void setupHC06()
{
    hc06.begin(9600);
}

/************************
* DS1302
************************/
bool isTimeUp(virtuabotixRTC rtc, int& start_time)
{
    rtc.updateTime();
    if(start_time == NULL)
    {
        start_time = rtc.hours*3600 + rtc.minutes*60 + rtc.seconds;
        return true;
    }
    else
    {
        int cur_time = rtc.hours*3600 + rtc.minutes*60 + rtc.seconds;
        if(cur_time - start_time > 5)
        {
            start_time = cur_time;
            return true;
        }
        return false;
    }
}

void printCurrentTime(virtuabotixRTC rtc)
{
    // This allows for the update of variables for time or accessing the individual elements.
    rtc.updateTime();

    // Print
    Serial.print("Current Date / Time: ");
    Serial.print(rtc.dayofmonth);
    Serial.print("/");
    Serial.print(rtc.month);
    Serial.print("/");
    Serial.print(rtc.year);
    Serial.print("  ");
    Serial.print(rtc.hours);
    Serial.print(":");
    Serial.print(rtc.minutes);
    Serial.print(":");
    Serial.println(rtc.seconds);
}

bool checkTime(string msg, int hour, int minutes)
{
    int len = msg.length();
    if(len != 5) return false;
    else
    {
        int h = msg[0]*10 + msg[1];
        int m = msg[3]*10 + msg[4];
        
        if(h == hour && m == minutes) return true; 
        else return false;
    }
}

/************************
* US015
************************/
void setupUltraSonic(int trig_pin, int echo_pin)
{
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
}

// compute distance from Sensor to Object
float distance2Object(int trig_pin, int echo_pin)
{
    // signaling from TRIG
    digitalWrite(trig_pin, 0);  // turn off TRIG
    delayMicroseconds(2);
    digitalWrite(trig_pin,1);   // turn on TRIG
    delayMicroseconds(10);  // signal pulse has length 10 micro secs
    digitalWrite(trig_pin, 0);

    // measure time
    while(!digitalRead(echo_pin)) {;}
    unsigned long start = micros();
    while(digitalRead(echo_pin)) {;}
    unsigned long finish = micros();

    // compute distance to object
    float distance = (finish - start)/2.0*0.03432;
    return distance;
}

bool isNearObject(int trig_pin, int echo_pin)
{
    return (distance2Object(trig_pin, echo_pin) < 20)
}

/************************
* Buzzer
************************/
void turnOnBuzzer(int buzzer_pin)
{
    digitalWrite(buzzer_pin, HIGH);
}