#include <mutex>
#include <list>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <../lib/measurements/MeasureVitalSigns.h>
#include <../lib/utils/DateUtils.h>
#include <../lib/utils/Constants.h>
#include <../lib/fhir/ResourceModels.h>

std::mutex measurementsMutex;
std::list<Measurement> measurements;

std::string communications = "";
std::mutex communicationsMutex;

// DS18B20
#define ONE_WIRE_BUS 4
#define TEMPERATURE_REPORTING_PERIOD_MS 20000
#define DS18B20_RESOLUTION 12
#define MIN_VALID_TEMPERATURE 30
#define MIN_VALID_HEART_RATE 0
#define MIN_VALID_OXIMETRY 0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;

unsigned long lastTempRequest = 0;
float temperature = 0.0;

// MAX30100
#define OXIMETER_REPORTING_PERIOD_MS 20000

PulseOximeter pox;
uint32_t lastOximeterReport = 0;
uint32_t lastBeat = 0;
float bpm, SpO2;

void onBeatDetected() {
  Serial.println("Beat!");
  lastBeat = millis();
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

void initializeSensors() {
  initializeDS18B20();
  measureAsyncTemperature();
  initializeMAX30100();
  configureMax30100();
}

void addCommunication(std::string payload) {
    communicationsMutex.lock();
    if (communications == "") {
      communications = "Paciente apresenta: ";
    }
    communications.append("\n").append(payload);
    communicationsMutex.unlock();
}

void validateTemperature(Measurement measurement) {
  if (measurement.value <= TEMPERATURE_LOW || measurement.value >= TEMPERATURE_HIGH) {
    std::string payload = "Temperatura corporal anormal: ";
    payload += std::to_string(measurement.value);
    payload += " °C em ";
    payload += measurement.dateTime.c_str(); 
    payload += ".";
    Serial.println(payload.c_str());
    addCommunication(payload);
  }
}

void validateHeartRate(Measurement measurement) {
  if (measurement.value <= HEART_RATE_LOW || measurement.value >= HEART_RATE_HIGH) {
    std::string payload = "Frequência cardíaca anormal: ";
    payload += std::to_string(measurement.value);
    payload += " bpm em ";
    payload += measurement.dateTime.c_str(); 
    payload += ".";
    Serial.println(payload.c_str());
    addCommunication(payload);
  }
}

void validateOximetry(Measurement measurement) {
  if (measurement.value < OXIMETRY_LOW) {
    std::string payload = "Saturação de oxigênio anormal: ";
    payload += std::to_string(measurement.value);
    payload += " SpO2 em ";
    payload += measurement.dateTime.c_str(); 
    payload += ".";
    Serial.println(payload.c_str());
    addCommunication(payload);
  }
}

void measureTemperature() {
  if (millis() - lastTempRequest >= TEMPERATURE_REPORTING_PERIOD_MS) {
    temperature = sensors.getTempCByIndex(0);
    Serial.printf("Temperature: %f °C\n", temperature);
    if (temperature > MIN_VALID_TEMPERATURE) {
      Measurement m = {temperature, getDateTime(time(NULL)), VitalSign::TEMPERATURE};
      measurementsMutex.lock();
      measurements.push_back(m);
      measurementsMutex.unlock();
      validateTemperature(m);
    }
    measureAsyncTemperature();
  }
}

void measureHeartRateAndOximetry() {

  if (millis() - lastBeat > OXIMETER_REPORTING_PERIOD_MS) {
    initializeMAX30100();
    lastBeat = millis();
  } else {
    pox.update();
  }

  if (millis() - lastOximeterReport > OXIMETER_REPORTING_PERIOD_MS) {
    bpm = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    lastOximeterReport = millis();
    String dateTime = getDateTime(time(NULL));
    Serial.printf("Heart rate: %f bpm SpO2: %f %\n", bpm, SpO2);
    if (bpm > MIN_VALID_HEART_RATE && SpO2 > MIN_VALID_OXIMETRY) {
      Measurement m = {bpm, dateTime, VitalSign::HEART_RATE};
      Measurement n = {SpO2, dateTime, VitalSign::OXIMETRY};
      measurementsMutex.lock();
      measurements.push_back(m);
      measurements.push_back(n);
      measurementsMutex.unlock();
      validateHeartRate(m);
      validateOximetry(n);
    }
  }
}

void measureVitalSigns() {
  measureTemperature();
  measureHeartRateAndOximetry();
}