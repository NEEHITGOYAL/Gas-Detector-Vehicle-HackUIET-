//this is for arduino json version 5
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT11  
#define RL 20
#define ro135 89.41
#define ro8 25.07
#define ro6 45.16
#define ro4 32.19
#define ro3 70.63
#define ro2 63.51 
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  s.begin(115200);
  Serial.begin(9600);
  
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
  dht.begin();
}
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
void loop() {
 
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  float mq135=analogRead(A0);
  float mq8=analogRead(A1);
  float mq6=analogRead(A2);
  float mq4=analogRead(A3);
  float mq3=analogRead(A4);
  float mq2=analogRead(A5);
  float vrl135 = (mq135*5)/1023;
  float vrl8 = (mq8*5)/1023;
  float vrl6 = (mq6*5)/1023;
  float vrl4 = (mq4*5)/1023;
  float vrl3 = (mq3*5)/1023;
  float vrl2 = (mq2*5)/1023;
  float rs135 = ((5-vrl135)*RL)/vrl135;
  float rs8 = ((5-vrl8)*RL)/vrl8;
  float rs6 = ((5-vrl6)*RL)/vrl6;
  float rs4 = ((5-vrl4)*RL)/vrl4;
  float rs3 = ((5-vrl3)*RL)/vrl3;
  float rs2 = ((5-vrl2)*RL)/vrl2;
 /* Serial.print("rs135 ");
  Serial.println(rs135);
  Serial.print("rs8 ");
  Serial.println(rs8);
  Serial.print("rs6 ");
  Serial.println(rs6);
  Serial.print("rs4 ");
  Serial.println(rs4);
  Serial.print("rs3 ");
  Serial.println(rs3);
  Serial.print("rs2 ");
  Serial.println(rs2);*/
  
  float ratio135 = rs135/ro135;
  float ratio8 = rs8/ro8;
  float ratio6 = rs6/ro6;
  float ratio4 = rs4/ro4;
  float ratio3 = rs3/ro3;
  float ratio2 = rs2/ro2;
  float co2 = 110.47*(pow(ratio135,-2.862));
  float propane = 652.71*(pow(ratio2,-2.168));
  float alcohol = 0.3934*(pow(ratio3,-1.504));
  float ch4 = 1012.7*(pow(ratio4,-2.786));
  float lpg = 1009.2*(pow(ratio6,-2.35));
  float h2 = 976.97*(pow(ratio8,-0.688));
  
  Serial.print("CO2 in ppm ");
  Serial.println(co2);
  Serial.print("Propane in ppm ");
  Serial.println(propane);
  Serial.print("Alcohol in ppm ");
  Serial.println(alcohol);
  Serial.print("CH4 in ppm ");
  Serial.println(ch4);
  Serial.print("LPG in ppm ");
  Serial.println(lpg);
  Serial.print("H2 in ppm ");
  Serial.println(h2);
  delay(2000);
 
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
if (isnan(h) || isnan(t) || isnan(f)) {
    return;
  }
  // If the DHT-11 is not connected to correct pin or if it doesnot
//work no data will be sent
  root["temp"] = t;
  root["hum"] = h;
  root["hi"] = hic;
  root["CO2"]= co2;
  root["Propane"]= propane;
  root["Alcohol"]= alcohol;
  root["CH4"]= ch4;
  root["lpg"]= lpg;
  root["H2"]= h2;
 
if(s.available()>0)
{
 root.printTo(s);
}
}
