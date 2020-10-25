#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>

ESP8266WebServer server(80);
String page ="";
double data1,data2,data3,co2,propane,alcohol,h2,ch4,lpg;
 
void setup() {
  // Initialize Serial port
  s.begin(115200);
  const char* ssid = "hotspot";
const char* password= "password";
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("");
  while (WiFi.status()!= WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connected to");
  Serial.println(ssid);
  Serial.print("ip address:");
  Serial.println(WiFi.localIP());
  server.on("/",[](){
    page = "<h1>sensor to node mcu</h1><h3>temperature:</h3><h4>"+String(data1)+"</h4><h3>humidity:</h3><h4>"+String(data2)+"</h4><h3>heatindex:</h3><h4>"+String(data3)+"</h4><h3>Co2:</h3><h4>"+String(co2)+"</h4><h3>alcohol:</h3><h4>"+String(alcohol)+"</h4><h3>h2</h3><h4>"+String(h2)+"</h4><h3>propane:</h3><h4>"+String(propane)+"</h4><h3>ch4:</h3><h4>"+String(ch4)+"</h4><h3>lpg:</h3><h4>"+String(lpg);
    server.send(200,"text/html",page);
  });
  server.begin();
  Serial.println("Web Server Started!");
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
   data1=root["temp"];
  Serial.println(data1);
  Serial.print("Humidity    ");
   data2=root["hum"];
  Serial.println(data2);
  Serial.print("Heat-index  ");
   data3=root["hi"];
  Serial.println(data3);
  Serial.print("CO2: ");
   co2=root["CO2"];
  Serial.println(co2);
  Serial.print("propane: ");
   propane=root["Propane"];
  Serial.println(propane);
    Serial.print("alcohol");
   alcohol=root["Alcohol"];
  Serial.println(alcohol);
    Serial.print("ch4: ");
   ch4=root["CH4"];
  Serial.println(ch4);
    Serial.print("lpg: ");
   lpg=root["LPG"];
  Serial.println(lpg);
    Serial.print("h2: ");
   h2=root["H2"];
  Serial.println(h2);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");
}
