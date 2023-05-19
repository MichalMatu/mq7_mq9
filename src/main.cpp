#include <Arduino.h>

// MQ-9 wiring
#define analogMQ9 34    // Analog input pin for MQ-9 sensor
#define ledPin 2        // Device internal LED
int MQ9sensorValue = 0; // Value read from the sensor

void setup()
{
  Serial.begin(115200);
  Serial.println(F("MQ-9 Gas Sensor started"));

  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // Reading
  MQ9sensorValue = analogRead(analogMQ9);

  // Print the results to the serial monitor
  Serial.print("MQ-9 Gas Value: ");
  Serial.println(MQ9sensorValue);

  delay(1000); // Adjust the delay as needed for the desired refresh rate
}
