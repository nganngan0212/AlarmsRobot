#define BUTTON 3
void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(BUTTON);
  Serial.println(a);
  delay(200);
}
