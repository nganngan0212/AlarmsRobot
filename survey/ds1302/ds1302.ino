#include <virtuabotixRTC.h>

// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);// CLK, DAT, RST

// Check time for another action
bool isTimeUp(virtuabotixRTC rtc, int& start_time)
{
    rtc.updateTime();
    if(start_time == NULL) start_time = rtc.hours*3600 + rtc.minutes*60 + rtc.seconds;
    int cur_time = rtc.hours*3600 + rtc.minutes*60 + rtc.seconds;
    if(cur_time - start_time > 5)
    {
        start_time = cur_time;
        return true;
    }
    return false;
}

// Print current time
void printCurrentTime(virtuabotixRTC rtc)
{
    // This allows for the update of variables for time or accessing the individual elements.
    myRTC.updateTime();

    // Print
    Serial.print("Current Date / Time: ");
    Serial.print(myRTC.dayofmonth);
    Serial.print("/");
    Serial.print(myRTC.month);
    Serial.print("/");
    Serial.print(myRTC.year);
    Serial.print("  ");
    Serial.print(myRTC.hours);
    Serial.print(":");
    Serial.print(myRTC.minutes);
    Serial.print(":");
    Serial.println(myRTC.seconds);
}

void setup() 
{
    Serial.begin(9600);
    // Set time: seconds, minutes, hours, dayofweek, dayofmonth, month, years
    // Set time once
    myRTC.setDS1302Time(00, 11, 17, 4, 23, 10, 2019);
    int start_time = NULL;
}

void loop() 
{                                                                                           

}
