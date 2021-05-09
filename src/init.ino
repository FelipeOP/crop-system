#include <DHT.h>
#include <DHT_U.h>
#include <PH.h>
#include <BlynkSimpleStream.h>
#include <SoftwareSerial.h>

#define PH_pin A5
#define DHT_pin 3

SoftwareSerial SwSerial(10, 11); // RX, TX
PH ph(PH_pin);
DHT dht(DHT_pin, DHT11);
BlynkTimer timer;

char auth[] = "04NBYveCfAJ3HLTW_CwMVkBE9tHP7t9D";

void sendSensor()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
    float p = ph.readPH();

    if (isnan(h) || isnan(t) || isnan(p))
    {
        SwSerial.println("Failed to read from DHT sensor or PH!");
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
    SwSerial.begin(9600);
    Serial.begin(9600);
    Blynk.begin(Serial, auth);
    dht.begin();
    //Time between read
    timer.setInterval(1000L, sendSensor);
}

void loop()
{
    Blynk.run();
    timer.run();
}
