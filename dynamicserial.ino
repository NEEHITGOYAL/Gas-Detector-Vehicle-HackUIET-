#include <SoftwareSerial.h>
SoftwareSerial s(12,14);
#include <ArduinoJson.h>
 
void setup() {
  // Initialize Serial port
  Serial.begin(115200);
  s.begin(115200);
  while (!Serial) continue;
}
 
void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  
  if (root == JsonObject::invalid())
  {
    return;
  }
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Temperature ");
  float data1=root["temp"];
  Serial.println(data1);
  Serial.print("Humidity    ");
  float data2=root["hum"];
  Serial.println(data2);
  Serial.print("Heat-index  ");
  float data3=root["hi"];
  Serial.println(data3);
  Serial.print("CO2: ");
  float co2=root["CO2"];
  Serial.println(co2);
  Serial.print("propane: ");
  float propane=root["Propane"];
  Serial.println(propane);
    Serial.print("alcohol");
  float alcohol=root["Alcohol"];
  Serial.println(alcohol);
    Serial.print("ch4: ");
  float ch4=root["CH4"];
  Serial.println(ch4);
    Serial.print("lpg: ");
  float lpg=root["LPG"];
  Serial.println(lpg);
    Serial.print("h2: ");
  float h2=root["H2"];
  Serial.println(h2);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");
}
