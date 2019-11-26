#include <SoftwareSerial.h> //HC06
#include <virtuabotixRTC.h> // DS1320
#include <string.h>

#define UNSET -1

#define CLK 6
#define DAT 7
#define RST 8
//ultrasonic sensor1 in front
#define TRIG2 12
#define ECHO2 13
//ultra sensor 2 behind
#define TRIG1 10
#define ECHO1 11

#define rxPin 5
#define txPin 4

// #define BUTTON 3

//motor
#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3

#define buzzer 9

virtuabotixRTC Clock(6, 7, 8);

SoftwareSerial hc06(rxPin, txPin);

// turn on Buzzer
void onBuzzer()
{
    digitalWrite(buzzer,HIGH);
}

// setup HC06
void setupHC06()
{
    hc06.begin(9600);   
}

void setupMotor1()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
}

void setupMotor2()
{
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void moveUp(int speed, int pin1, int pin2)
{
    // speed = checkSpeed(speed);
    analogWrite(pin1, speed);
    analogWrite(pin2, 0);
}

void moveDown(int speed, int pin1, int pin2)
{
    // speed = checkSpeed(speed);
    analogWrite(pin1, 0);
    analogWrite(pin2, speed);
}

int speedRandom() 
{
    // random speed motor in range of 180-255
    return random(180,255);
}

// check is alarm time
bool check(String s, int hour, int minutes)
{
    int len = s.length();
    if(len != 5)
    {
        Serial.println("Error!");
        return false;
    }
    else{
        int h = (s[0]-48)*10 + (s[1]-48);
        int m = (s[3]-48)*10 + (s[4]-48);
        return (h == hour && m == minutes);
        }
}

// Return distance from robot to objects
float distance2Object(int trigPin, int echoPin)
{
    // signaling from TRIG
    digitalWrite(trigPin, 0);  // turn off TRIG
    delayMicroseconds(2);
    digitalWrite(trigPin,1);   // turn on TRIG
    delayMicroseconds(10);  // signal pulse has length 10 micro secs
    digitalWrite(trigPin, 0);

    // measure time
    while(!digitalRead(echoPin)) {;}
    unsigned long start = micros();
    while(digitalRead(echoPin)) {;}
    unsigned long finish = micros();

    // compute distance to object
    float distance = (finish - start)/2.0*0.03432;
    return distance;
}

bool isChangeSpeed(virtuabotixRTC rtc, int &start_time)
{
    rtc.updateTime();
    if(start_time == UNSET)
    {
        start_time = rtc.hours*3600 + rtc.minutes*60 + rtc.seconds;
        return true;
    }
    else
    {
        int cur_time = rtc.hours*3600 + rtc.minutes*60 + rtc.seconds;
        if(cur_time - start_time >= 5)
        {
            start_time = cur_time;
            return true;
        }
        return false;
    }
}

void setup()
{
    pinMode(buzzer, OUTPUT);
    
    Serial.begin(9600);

    setupHC06();

    pinMode(TRIG1, OUTPUT);
    pinMode(ECHO1, INPUT);

    pinMode(TRIG2, OUTPUT);
    pinMode(ECHO2, INPUT);

    setupMotor1();
    setupMotor2();

//    set time for clock module with (seconds, minutes, hours, dayofweek, dayofmonth, month, years)
//    Clock.setDS1302Time(00, 51, 7, 4, 27, 11, 2019); 
}

bool ans = false;
int start_time = UNSET;
String msg;
bool is_set = false;

void loop() {
    //update time
    Clock.updateTime();

    int hou = Clock.hours;
    int minut = Clock.minutes;

    if(hc06.available())
    {
        msg = hc06.readString();
        is_set = true;
        Serial.print("Message: ");
        Serial.println(msg); //print message from phone
    } 
    
    if(is_set)
    {
        ans = check(msg, hou, minut);
        if(ans) is_set = false;
    }
    //print hour and minutes
    Serial.print(hou);
    Serial.print(":");
    Serial.println(minut);
 
    // robot active
    if(ans)
    {
        onBuzzer();
        
        float dis1 = distance2Object(TRIG1, ECHO1);
        Serial.print("Distance1 = ");
        Serial.println(dis1);
        float dis2 = distance2Object(TRIG2, ECHO2);
        Serial.print("Distance2 = ");
        Serial.println(dis2);

        int speed1, speed2;

        if(isChangeSpeed(Clock, start_time))
        {
            speed1 = speedRandom();
            speed2 = speedRandom();
            Serial.print("Speed1: ");
            Serial.println(speed1);
            Serial.print("Speed2: ");
            Serial.println(speed2);
        }

        if(dis1 < 50 && dis2 < 50)
        {
            moveUp(speed1, IN1, IN2);
            moveDown(speed2, IN3, IN4);
            Serial.println("Left up, Right down.");
        }
        else
        { 
            if(dis1 < 50)
            {
                moveDown(speed1, IN1, IN2);
                moveDown(speed2, IN3, IN4);
                Serial.println("Move Up.");
            }
            
            if(dis2 < 50)
            {
                moveUp(speed1, IN1, IN2);
                moveUp(speed2, IN3, IN4);
                Serial.println("Move Down.");
            }
        }
    }
//    delay(500);
}
