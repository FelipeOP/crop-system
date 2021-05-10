#include <DHT.h>
#include <DHT_U.h>
#include <PH.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleSerialBLE.h>

#define DHT_TYPE DHT11
#define PH_pin A5
#define DHT_pin 3

SoftwareSerial SwSerial(10, 11); // RX, TX
PH ph(PH_pin);
DHT dht(DHT_pin, DHT_TYPE);
BlynkTimer timer;

//Auth token in Blynk App
char auth[] = "nn2BAm1jbkhYYdcsazgDxVib_a_ND3Z0";

void sendSensor()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
    float p = ph.readPH();

    if (isnan(h) || isnan(t) || isnan(p))
    {
        Serial.println("Failed to read from DHT sensor or PH!");
        return;
    }
    // You can send any value at any time.
    // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V5, h);
    Blynk.virtualWrite(V6, t);
    Blynk.virtualWrite(V7, p);
}

void setup()
{
    //Debug console
    Serial.begin(9600);
    //USB connection
    SwSerial.begin(9600);
    //Bluetooth connection
    Blynk.begin(SwSerial, auth);
    dht.begin();
    //Time between read
    timer.setInterval(1000L, sendSensor);
}

void loop()
{
    Blynk.run();
    timer.run();
}
