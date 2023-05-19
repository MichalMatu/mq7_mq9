#include <Arduino.h>

// MQ-7 wiring
#define analogMQ7 34    // Analog input pin for MQ-7 sensor
#define ledPin 2        // Device internal LED
int MQ7sensorValue = 0; // Value read from the sensor

void setup()
{
  Serial.begin(115200);
  Serial.println(F("MQ-7 Gas Sensor Flying-Fish started"));

  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // A) preparation
  // turn the heater fully on
  ledcWrite(analogMQ7, 255);
  // heat for 1 min
  delay(60000);
  // now reducing the heating power: turn the heater to approx 1.4V
  ledcWrite(analogMQ7, 71); // 255x1400/5000
  // heat for 90 sec
  delay(90000);

  // B) reading
  // CO2 via MQ7: we need to read the sensor at 5V, but must not let it heat up. So hurry!
  ledcWrite(analogMQ7, 255);
  delay(50); // Getting an analog read apparently takes 100uSec
  MQ7sensorValue = analogRead(analogMQ7);

  // C) print the results to the serial monitor
  Serial.print("MQ-7 PPM: ");
  Serial.println(MQ7sensorValue);

  // D) interpretation
  // Detecting range: 20ppm-2000ppm carbon monoxide
  // air quality-cases: < 200 perfect, 200 - 800 normal, > 800 - 1800 high, > 1800 abnormal

  if (MQ7sensorValue <= 200)
  {
    Serial.println("Air-Quality: CO perfect");
  }
  else if (MQ7sensorValue <= 800)
  {
    Serial.println("Air-Quality: CO normal");
  }
  else if (MQ7sensorValue <= 1800)
  {
    Serial.println("Air-Quality: CO high");
  }
  else if (MQ7sensorValue > 1800)
  {
    digitalWrite(ledPin, HIGH); // optical information in case of emergency
    Serial.println("Air-Quality: ALARM CO very high");
    delay(3000);
    digitalWrite(ledPin, LOW);
  }
  else
  {
    Serial.println("MQ-7 - can't read any value - check the sensor!");
  }
}
