const int IN1 = A0;
const int IN2 = A1;
const int IN3 = A2;
const int IN4 = A3;

int const MAX_SPEED = 255;
int const MIN_SPEED = 0;

void setupMotorLeft();
void setupMotorRight();

void motorLeftUp(int speed);
void motorLeftDown(int speed);
void motorRightUp(int speed);
void motorRightDown(int speed);

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