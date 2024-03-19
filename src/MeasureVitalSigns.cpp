#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <../lib/MeasureVitalSigns.h>

// DS18B20
#define ONE_WIRE_BUS 4
#define TEMPERATURE_REPORTING_PERIOD_MS 2000
#define DS18B20_RESOLUTION 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;

unsigned long lastTempRequest = 0;
float temperature = 0.0;

// MAX30100
#define OXIMETER_REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t lastOximeterReport = 0;

void onBeatDetected() {
  Serial.println("Beat!");
}

void configureMax30100() {
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void initializeMAX30100() {
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
}

void initializeDS18B20() {
  sensors.begin();
  sensors.getAddress(tempDeviceAddress, 0);
  sensors.setResolution(tempDeviceAddress, DS18B20_RESOLUTION);
  sensors.setWaitForConversion(false);
}

void measureAsyncTemperature() {
  sensors.requestTemperatures();
  lastTempRequest = millis();
}

void initializateSensors() {
  initializeDS18B20();
  measureAsyncTemperature();
  initializeMAX30100();
  configureMax30100();
}

void measureTemperature() {
  if (millis() - lastTempRequest >= TEMPERATURE_REPORTING_PERIOD_MS) {
    temperature = sensors.getTempCByIndex(0);
    Serial.println("Temperature: " + String(temperature) + " °C");
    measureAsyncTemperature();
  }
}

void measureHeartRateAndOximetry() {
  pox.update();

  if (millis() - lastOximeterReport > OXIMETER_REPORTING_PERIOD_MS) {
    Serial.print("Heart rate: ");
    Serial.print(pox.getHeartRate());
    Serial.println("bpm");
    Serial.print("SpO2: ");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    lastOximeterReport = millis();
  }
}

void measureVitalSigns() {
  measureTemperature();
  measureHeartRateAndOximetry();
}