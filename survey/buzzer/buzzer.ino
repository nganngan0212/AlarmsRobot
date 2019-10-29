const int BUTTON = 3;

void setup()
{
    pinMode(BUTTON, INPUT);
    bool is_time = false;
}

void turnOnBuzzer(int button_pin)
{
    digitalWrite(button_pin, HIGH);
}

void turnOffBuzzer(int button_pin)
{
    digitalWrite(button_pin, LOW);
}

void loop()
{
    
}