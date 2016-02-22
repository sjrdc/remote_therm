
const int second = 1000;
const int lonpause = 60*second;
const int LED = D7;

void flash(int ntimes = 2, int delay = 200);

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    flash();
    // Lets listen for the hook response
    Particle.subscribe("hook-response/piet", gotWeatherData, MY_DEVICES);

    // Lets give ourselves 10 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<10;i++) {
        Serial.println("waiting " + String(10-i) + " seconds before we publish");
        delay(1000);
        flash();
    }
}

bool debu = true;

void loop() 
{
    // Let's request the weather, but no more than once every 60 seconds.
    Particle.connect();
    
    if (debu)
        Serial.println("requestin' confi'uration!");

    Particle.process();
    delay(5*second);    
    Particle.publish("piet");
    delay(5*second);
    Particle.process();
    
    Particle.disconnect();
    WiFi.off();
    
    delay(lonpause);
    flash();
}

void gotWeatherData(const char *name, const char *data)
{
    if (debu)
        Serial.println(data);
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