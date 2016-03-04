
int second;
int minute;
int longpause;

int LED;
int thermostatPin;

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
    maxit = 3;
    idx = 0;
    
    // debu settins
    /*
    delayt = 20*second;
    sleept = 20;
    */
    delayt = 5*60*second;
    sleept = 5*60;
    
    LED = D7;
    pinMode(LED, OUTPUT);
    
    thermostatPin = D0;
    pinMode(thermostatPin, OUTPUT);
    
    Particle.subscribe("hook-response/thermostat", switchResponseHandler, MY_DEVICES);
    
    Particle.publish("thermostat");

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
    
    Particle.publish("thermostat");
    
    idx ++;
    if (idx == maxit)
    {
        idx = 0;
        
        delay(3*second);
        Particle.process();
        
        if (switchOn)
        {
            // turn the thermostate on
            digitalWrite(thermostatPin, HIGH);
            
            // safe some power
            Particle.disconnect();
            WiFi.off();
            
            delay(delayt);
        }
        else
        {
            // turn the thermostat off
            digitalWrite(thermostatPin, LOW);
            
            // safe some power for real
            System.sleep(SLEEP_MODE_DEEP, sleept);
        }
    }
}

void switchResponseHandler(const char *name, const char *data)
{
    if (strcmp(data, "true") == 0) 
    {
        switchOn = true;
        Particle.publish("active-true");
    }
    else
    {
        switchOn = false;
        Particle.publish("active-false");
    }
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
