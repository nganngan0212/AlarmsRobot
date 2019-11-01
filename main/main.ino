   /*
Software used: Arduino Remote LITE (Bluetooth & Wifi)
Connect Arudino with Bluetooth module
    HC-06     Arduino
     +5V        5V
     GND        GND
     TX         5
     RX         4

Connect Arduino with DS1302 module
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
#define TRIG 12
#define ECHO 13
#define BUTTON 3

const int buzzer = 10;

const int rxPin = 5;
const int txPin = 4;

AF_DCMotor motor1(2);
AF_DCMotor motor2(3);

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

// dừng động cơ
void Stop()
{
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor1.run(BRAKE);
    motor2.run(BRAKE);
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
        if(h == hour && m == minutes)
        {
            return  true;
        } 
        else{
            return false;
        }
    }
}

/*
    Hàm offBuzzer đọc giá trị của nút bấm
    nếu nút đc bấm, giá trị đọc vào lớn hơn 0, tắt chuông báo
*/
void offBuzzer()
{
        digitalWrite(buzzer, LOW);
}

void setup()
{
    motor1.setSpeed(SPEEDMOTOR1);
    motor1.run(RELEASE);

    motor2.setSpeed(SPEEDMOTOR2);
    motor2.run(RELEASE);

    pinMode(buzzer, OUTPUT);
    
    Serial.begin(9600);
    setupHC06();

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    pinMode(BUTTON,INPUT);

    //set time for clock module with (seconds, minutes, hours, dayofweek, dayofmonth, month, years)
    Clock.setDS1302Time(00, 02, 18, 5, 24, 10, 2019); 

}

//Hàm distance trả về khoảng cách từ sensor tới vật cản gần nhất 
float distance()
{
    int startTime = 0, finishTime = 0, duration = 0;
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    while(digitalRead(ECHO) == 0){;}
    startTime = micros(); 
    while(digitalRead(ECHO) == 1){;}
    finishTime = micros();

    duration = -startTime + finishTime;
    float dis =(duration / 2.0) * (34300.0/1000000);
    return dis;
}

bool ans = false;
void loop() {
  // put your main code here, to run repeatedly:
    Clock.updateTime();

    int hou = Clock.hours;
    int minut = Clock.minutes;

    String msg;
    if(hc06.available())
    {
        msg = hc06.readString();
        Serial.println(msg);
        ans = check(msg, hou, minut);
    } 
    Serial.print(hou);
    Serial.print(":");
    Serial.println(minut);

    // on/off buzzer
    if(ans == true)
    {
        onBuzzer();
        int a = digitalRead(BUTTON);
        if(a > 0)
        {
            offBuzzer();
            ans = false;
            msg = " ";
        }
    }
  
    delay(500);
}
