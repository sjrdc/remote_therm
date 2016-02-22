

bool debu = true;

const int second = 1000;
const int minute = 60*second;
int lonpause;

const int LED = D7;

void flash(int ntimes = 2, int delay = 200);

void setup() {
    if (debu)
    {
        lonpause = 10*second;
        Serial.begin(9600);
    }
    else
        lonpause = 5*minute;
    
    pinMode(LED, OUTPUT);
    flash();
    // Lets listen for the hook response
    Particle.subscribe("hook-response/switch", switchThermostate, MY_DEVICES);

    // Lets give ourselves 10 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<10;i++) {
        if (debu)
            Serial.println("waiting " + String(10-i) + " seconds before we publish");
        delay(1000);
        flash();
    }
}

void loop() 
{
    // Let's request the weather, but no more than once every 60 seconds.
    Particle.connect();
    
    if (debu)
        Serial.println("requestin' confi'uration!");

    Particle.process();
    delay(1*second);    
    Particle.publish("switch");
    delay(1*second);
    Particle.process();
    
    Particle.disconnect();
    WiFi.off();
    
    delay(lonpause);
    flash();
}

void switchThermostate(const char *name, const char *data)
{
    if (debu)
        Serial.println(data);
        
    if (strcmp(data, "true") == 0)
    {
        if (debu)
            Serial.println("Switch ON");
        else {}
    }
    else
    {
        if (debu)
            Serial.println("Switch OFF");
        else {}
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
