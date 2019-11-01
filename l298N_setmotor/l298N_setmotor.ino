#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3
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
  analogWrite(IN1, 255);
  analogWrite(IN2, 0);
  
  analogWrite(IN3, 255);
  analogWrite(IN4 , 0);
}
