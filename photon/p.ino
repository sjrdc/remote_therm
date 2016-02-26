
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

void setup() {
    second = 1000;
    minute = 60*second;
    maxit = 2;
    
    delayt = 10*second;
    sleept = 10;
    
    LED = D7;
    pinMode(LED, OUTPUT);
    
    thermostatePin = D0;
    pinMode(thermostatePin, OUTPUT);
    
    Particle.subscribe("hook-response/switch", switchResponseHandler, MY_DEVICES);
    
    Particle.publish("switch");

    delay(3*second);
    Particle.process();

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
            // safe some power
            Particle.disconnect();
            WiFi.off();
            
            delay(delayt);
        }
        else
        {
            // safe some power for real
            System.sleep(SLEEP_MODE_DEEP, sleept);
        }
    }
}

void switchResponseHandler(const char *name, const char *data)
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
        delay(d);
    }
}
