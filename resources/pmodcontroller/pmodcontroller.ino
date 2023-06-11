#include <ArduinoJson.h>
#include <dht.h>
#define dht11pin 21
StaticJsonDocument<128> doc;
JsonObject pmod_data = doc.createNestedObject("pmod_data");
String input;
int zybo_power = 10;
int pmod_pin1 = 2;
int pmod_pin2 = 3;
int pmod_pin3 = 4;
int pmod_pin4 = 5;
int pmod_pin7 = 6;
int pmod_pin8 = 7;
int pmod_pin9 = 8;
int pmod_pin10 = 9;

dht DHT;

void setup() {
  Serial.begin(9600);
  pinMode(pmod_pin1, OUTPUT);
  pinMode(pmod_pin2, OUTPUT);
  pinMode(pmod_pin3, OUTPUT);
  pinMode(pmod_pin4, OUTPUT);
  pinMode(pmod_pin7, OUTPUT);
  pinMode(pmod_pin8, OUTPUT);
  pinMode(pmod_pin9, OUTPUT);
  pinMode(pmod_pin10, OUTPUT);
  pinMode(zybo_power, OUTPUT);
  //Serial.println("initialized");
  delay(1000);

  // jsonData();
  //Serial.println();
}

void loop() {

  if (Serial.available()) {
    input = Serial.readStringUntil('\n');

    if (input == "pmod_pin1") {
      digitalWrite(pmod_pin1, HIGH);
      jsonData();
    }
    if (input == "pmod_pin1_o") {
      digitalWrite(pmod_pin1, LOW);
      jsonData();
    }
    if (input == "pmod_pin2") {
      digitalWrite(pmod_pin2, HIGH);
      jsonData();
    }
    if (input == "pmod_pin2_o") {
      digitalWrite(pmod_pin2, LOW);
      jsonData();
    }
    if (input == "pmod_pin3") {
      digitalWrite(pmod_pin3, HIGH);
      jsonData();
    }
    if (input == "pmod_pin3_o") {
      digitalWrite(pmod_pin3, LOW);
      jsonData();
    }
    if (input == "pmod_pin4") {
      digitalWrite(pmod_pin4, HIGH);
      jsonData();
    }
    if (input == "pmod_pin4_o") {
      digitalWrite(pmod_pin4, LOW);
      jsonData();
    }
    if (input == "pmod_pin7") {
      digitalWrite(pmod_pin7, HIGH);
      jsonData();
    }
    if (input == "pmod_pin7_o") {
      digitalWrite(pmod_pin7, LOW);
      jsonData();
    }
    if (input == "pmod_pin8") {
      digitalWrite(pmod_pin8, HIGH);
      jsonData();
    }
    if (input == "pmod_pin8_o") {
      digitalWrite(pmod_pin8, LOW);
      jsonData();
    }
    if (input == "pmod_pin9") {
      digitalWrite(pmod_pin9, HIGH);
      jsonData();
    }
    if (input == "pmod_pin9_o") {
      digitalWrite(pmod_pin9, LOW);
      jsonData();
    }
    if (input == "pmod_pin10") {
      digitalWrite(pmod_pin10, HIGH);
      jsonData();
    }
    if (input == "pmod_pin10_o") {
      digitalWrite(pmod_pin10, LOW);
      jsonData();
    }
    if (input == "jsonData") {
      jsonData();
    }
    if (input == "zybo_power") {
      digitalWrite(zybo_power, HIGH);
      jsonData();
    }
    if (input == "zybo_power_o") {
      digitalWrite(zybo_power, LOW);
      jsonData();
    }
    if (input == "sensor_data") {
      sensorData();
    }
  }
}

void jsonData() {
  doc["sensor_data"] = false;
  // doc["time"] = 1351824120;


  pmod_data["pmod_pin1"] = digitalRead(pmod_pin1);
  pmod_data["pmod_pin2"] = digitalRead(pmod_pin2);
  pmod_data["pmod_pin3"] = digitalRead(pmod_pin3);
  pmod_data["pmod_pin4"] = digitalRead(pmod_pin4);
  pmod_data["pmod_pin7"] = digitalRead(pmod_pin7);
  pmod_data["pmod_pin8"] = digitalRead(pmod_pin8);
  pmod_data["pmod_pin9"] = digitalRead(pmod_pin9);
  pmod_data["pmod_pin10"] = digitalRead(pmod_pin10);
  pmod_data["zybo_power"] = digitalRead(zybo_power);

  serializeJson(doc, Serial);
  Serial.println();
  // serializeJsonPretty(doc, Serial);
}

void sensorData() {
  int photoResistor = analogRead(A6);
  int readDHT = DHT.read11(dht11pin);
  float t = DHT.temperature;  // Read temperature
  float h = DHT.humidity;     // Read humidity
  doc["temperature_c"] = t;
  doc["temperature_f"] = (t * 9.0) / 5.0 + 32.0;
  doc["humidity"] = h;
  doc["photo_resistor"] = photoResistor;
  doc["sensor_data"] = true;
  serializeJson(doc, Serial);
  Serial.println();
}
