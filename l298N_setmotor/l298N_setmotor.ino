#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3

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

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //tien
  int dis = 25;
  if(dis < 30)
  {
    moveDown(255, IN3, IN4);
  }
  delay(200);
  moveUp(255, IN1, IN2);
}
