/*
Setup connection:
        US-015      Arduino
        VCC         3.3V
        GND         GND
        TRIG        8
        ECHO        7
*/

const int TRIG = 8;
const int ECHO = 7;

// setup UltraSonic US-015
void setupUltraSonic()
{
    pinMode(TRIG, OUTPUT);  // TRIG using for signaling
    pinMode(ECHO, INPUT);   // ECHO using for receiver
}

// compute distance from Sensor to Object
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

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);     // communicate Seirial with baudrate 9600
    setupUltraSonic();
}

void loop()
{
    float distance = distance2Object(TRIG, ECHO);
    // print on Serial screen
    Serial.println(distance);     // cm
    delay(500); 
}
