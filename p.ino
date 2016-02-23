
int second;
int minute;
int longpause;

int LED;
int thermostatePin;

void flash(int ntimes = 2, int delay = 200);

bool switchOn = false;
int idx;
int maxit;
int sleept;
int delayt;

void setup() 
{
    second = 1000;
    minute = 60*second;
    
    maxit = 2;
    
    delayt = 5*second;
    sleept = 5;
    
    LED = D7;
    pinMode(LED, OUTPUT);
    
    thermostatePin = D0;
    pinMode(thermostatePin, OUTPUT);
    
    Particle.subscribe("hook-response/switch", switchHandler, MY_DEVICES);

    flash(1, 1000);
}

void loop() 
{
    Particle.connect();
    delay(1*second);
    
    if (switchOn) flash(2, 300);
    else flash(5, 75);
    
    idx ++;
    if (idx == maxit)
    {
        idx = 0;
        Particle.publish("switch");
        
        delay(3*second);
        Particle.process();
        
        if (switchOn)
        {
            digitalWrite(thermostatePin, HIGH);
            
            Particle.disconnect();
            WiFi.off();
            
            delay(delayt);
        }
        else
        {
            System.sleep(SLEEP_MODE_DEEP, sleept);
        }
    }
}

void switchHandler(const char *name, const char *data)
{
    if (strcmp(data, "true") == 0) switchOn = true;
    else switchOn = false;
}

void flash(int ntimes, int d)
{
    for (int i = 0; i < ntimes; ++i)
    {
        digitalWrite(LED, HIGH);
        delay(d);
        digitalWrite(LED, LOW);
        if (i != ntimes - 1) delay(d);
    }
}
