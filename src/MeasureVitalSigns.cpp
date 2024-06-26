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
#include <../lib/utils/ReferenceRanges.h>

std::list<Measurement> measurements;
std::string communications = "";
std::map<std::string, ReferenceValues> referenceRanges;

// DS18B20
#define ONE_WIRE_BUS 4
#define TEMPERATURE_REPORTING_PERIOD_MS 20000
#define TEMPERATURE_MEAN_SAMPLES 4
#define DS18B20_RESOLUTION 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;

unsigned long lastTempRequest = 0;
float temperature = 0.0;
float sumTemperature = 0.0;
int countTemperature = 0;

// MAX30100
#define OXIMETER_REPORTING_PERIOD_MS 20000
#define OXIMETER_MEAN_SAMPLES 4

PulseOximeter pox;
uint32_t lastOximeterReport = 0;
uint32_t lastBeat = 0;
float bpm, SpO2;
float sumBpm = 0.0;
float sumSpO2 = 0.0;
int countOximeter = 0;

void onBeatDetected() {
  Serial.println("Beat!");
  lastBeat = millis();
}

void configureMax30100() {
  pox.setIRLedCurrent(MAX30100_LED_CURR_27_1MA);
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
    xSemaphoreTake(xSemaphoreCommunications, (TickType_t) 10);
    if (communications == "") {
      communications = "Paciente apresenta: ";
    }
    communications.append("\n").append(payload);
    xSemaphoreGive(xSemaphoreCommunications);
}

std::string formatValue(float value, int precision) {
  std::string valueText = std::to_string(value);
  return valueText.substr(0, valueText.find(".") + precision);
}

void validateTemperature(Measurement measurement) {
  if (isNotNormal(measurement.value, referenceRanges[TEMPERATURE_CODE])) {
    std::string payload = "Temperatura corporal anormal: ";
    payload += formatValue(measurement.value, 2);
    payload += " °C";
    Serial.println(payload.c_str());
    addCommunication(payload);
  }
}

void validateHeartRate(Measurement measurement) {
  if (isNotNormal(measurement.value, referenceRanges[HEART_RATE_CODE])) {
    std::string payload = "Frequência cardíaca anormal: ";
    payload += formatValue(measurement.value, 0);
    payload += " bpm";
    Serial.println(payload.c_str());
    addCommunication(payload);
  }
}

void validateOximetry(Measurement measurement) {
  if (isNotNormal(measurement.value,  referenceRanges[OXIMETRY_CODE])) {
    std::string payload = "Saturação de oxigênio anormal: ";
    payload += formatValue(measurement.value, 0);
    payload += " %";
    Serial.println(payload.c_str());
    addCommunication(payload);
  }
}

void measureTemperature() {
  if (millis() - lastTempRequest >= TEMPERATURE_REPORTING_PERIOD_MS) {
    temperature = sensors.getTempCByIndex(0);
    Serial.printf("Temperature: %f °C\n", temperature);
    if (isValid(temperature, referenceRanges[TEMPERATURE_CODE])) {
      sumTemperature += temperature; 
      countTemperature++;
      Serial.printf("[COUNT] - Temperature: %d \n", countTemperature);
      if (countTemperature >= TEMPERATURE_MEAN_SAMPLES) {
        float media = sumTemperature/countTemperature;
        Serial.printf("[MÉDIA] - Temperature: %f °C\n", media);
        Measurement m = {media, getDateTime(time(NULL)), VitalSign::TEMPERATURE};
        xSemaphoreTake(xSemaphoreMeasurements, (TickType_t) 10);
        measurements.push_back(m);
        xSemaphoreGive(xSemaphoreMeasurements);
        validateTemperature(m);
        sumTemperature = 0.0;
        countTemperature = 0;
      }
    } else {
      Serial.println("Medição inválida do termômetro");
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
    Serial.printf("Heart rate: %f bpm SpO2: %f %\n", bpm, SpO2);
    if (isValid(bpm, referenceRanges[HEART_RATE_CODE]) && isValid(SpO2, referenceRanges[OXIMETRY_CODE])) {
      sumBpm += bpm;
      sumSpO2 += SpO2;
      countOximeter++;
      Serial.printf("[COUNT] - Oximetro: %d \n", countOximeter);
      if (countOximeter >= OXIMETER_MEAN_SAMPLES) {
        float mediaBpm = sumBpm/countOximeter;
        float mediaSpO2 = sumSpO2/countOximeter;
        Serial.printf("[MÉDIA] - Heart rate: %f bpm SpO2: %f %\n", mediaBpm, mediaSpO2);
        String dateTime = getDateTime(time(NULL));
        Measurement m = {mediaBpm, dateTime, VitalSign::HEART_RATE};
        Measurement n = {mediaSpO2, dateTime, VitalSign::OXIMETRY};
        xSemaphoreTake(xSemaphoreMeasurements, (TickType_t) 10);
        measurements.push_back(m);
        measurements.push_back(n);
        xSemaphoreGive(xSemaphoreMeasurements);
        validateHeartRate(m);
        validateOximetry(n);
        sumBpm = 0.0;
        sumSpO2 = 0.0;
        countOximeter = 0;
      }

    } else {
      Serial.println("Medição inválida do oxímetro");
    }
  }
}

void measureVitalSigns() {
  measureTemperature();
  measureHeartRateAndOximetry();
}