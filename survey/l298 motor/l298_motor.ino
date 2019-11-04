/*
Left motor is set by IN1 and IN2
Right motor is set by IN3 and IN4
*/

const int IN1 = A0;
const int IN2 = A1;
const int IN3 = A2;
const int IN4 = A3;

int const MAX_SPEED = 255;
int const MIN_SPEED = 0;

// int checkSpeed(int& speed)
// {
//     if(speed > MAX_SPEED) speed = MAX_SPEED;
//     if(speed < MIN_SPEED) speed = MIN_SPEED;
//     return speed;
// }

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

void setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);   
}

void loop()
{
    
}