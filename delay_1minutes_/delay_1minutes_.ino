void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
long int time = 0;
void loop() {
  // put your main code here, to run repeatedly:
  
  long int t = millis() - time;
  if(t > 1000){
      Serial.println(t);
      time = millis();
  }
}
