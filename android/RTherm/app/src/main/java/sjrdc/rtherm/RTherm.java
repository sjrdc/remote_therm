package sjrdc.rtherm;

/**
 * Created by scrijns on 2/25/16.
 */
public class RTherm {

    private boolean thermostat;

    private boolean active;
    private int temperature;

    public RTherm() {
    }

    public RTherm(boolean s, boolean a, int t) {
        thermostat = s;
        active = a;
        temperature = t;
    }

    public boolean getThermostat()
    {
        return thermostat;
    }

    public boolean getActive()
    {
        return active;
    }

    public int getTemperature() {
        return temperature;
    }
}
