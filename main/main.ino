#include <AFMotor.h> //L293D
#include <SoftwareSerial.h> //HC06
#include <virtuabotixRTC.h> // DS1320
#include <string.h>

#define CLK 6
#define DAT 7
#define RST 8
//ultrasonic sensor1 in front
#define TRIG1 12
#define ECHO1 13
//ultra sensor 2 behind
#define TRIG2 10
#define ECHO2 11

#define rxPin 5
#define txPin 4

// #define BUTTON 3

//motor
#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3

#define buzzer 9

// const int rxPin = 5;
// const int txPin = 4;

int startTime = 0;

virtuabotixRTC Clock(6, 7, 8);

SoftwareSerial hc06(rxPin, txPin);

//bật chuông báo
void onBuzzer()
{
    digitalWrite(buzzer,HIGH);
}

// 
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

/*
    Hàm check có nhiệm vụ so sánh sâu s(giờ đặt báo thức) với hai giá trị hour(giờ), và minutes(phút) ở hiện tại
    trả vể True nếu thời điểm hiện tại bằng s
    ngc lại trả về False
*/
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

//Hàm distance2Object trả về khoảng cách từ sensor tới vật cản gần nhất
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

int changeSpeed(int speed)
{
    long int time = millis() - startTime;

    if(time > 5000)
    {
        speed = speedRandom();
        startTime   = millis();
    }
    return speed;
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

    //set time for clock module with (seconds, minutes, hours, dayofweek, dayofmonth, month, years)
    Clock.setDS1302Time(00, 02, 18, 5, 24, 10, 2019); 
}

bool ans = false;

void loop() {
    //update time
    Clock.updateTime();

    int hou = Clock.hours;
    int minut = Clock.minutes;

    String msg;
    if(hc06.available())
    {
        msg = hc06.readString();
        Serial.print("Message: ");
        Serial.println(msg);//print message from phone
        ans = check(msg, hou, minut);
    } 

    //print hour and minutes
    Serial.print(hou);
    Serial.print(":");
    Serial.println(minut);
 
    // on/off buzzer
//    if(ans == true)
    if(1)
    {
//        onBuzzer();
        
        float dis1 = distance2Object(TRIG1, ECHO1);
        Serial.print("Distance1 = ");
        Serial.println(dis1);
        float dis2 = distance2Object(TRIG2, ECHO2);
        Serial.print("Distance2 = ");
        Serial.println(dis2);

        if(dis1 < 30)
        {
            moveDown(255, IN1, IN2);
            moveDown(255, IN3, IN4);
        }
        
        if(dis2 < 30)
        {
            moveUp(255, IN1, IN2);
            moveUp(255, IN3, IN4);
        }
    }
        delay(1000);
}
