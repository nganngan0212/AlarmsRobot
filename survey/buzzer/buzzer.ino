const int BUTTON = 3;
const int BUZZER = 10;

void setup()
{
    pinMode(BUTTON, INPUT);
    pinMode(BUZZER, OUTPUT);
}

void turnOnBuzzer(int buzzer_pin)
{
    digitalWrite(buzzer_pin, HIGH);
}

void turnOffBuzzer(int buzzer_pin)
{
    digitalWrite(buzzer_pin, LOW);
}
    
bool checkButton(int button_pin)
{
    return digitalRead(button_pin);
}

bool is_time = false;

void loop()
{
    // is_time = check_time(sth);
    if(is_time) turnOnBuzzer(BUTTON);

    if(checkButton(BUTTON)) turnOffBuzzer(BUTTON);
}