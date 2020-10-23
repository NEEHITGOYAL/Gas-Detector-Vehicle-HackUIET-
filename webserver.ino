#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
/*#define RL 20
#define ro135 89.41
#define ro8 25.07
#define ro6 45.16
#define ro4 32.19
#define ro3 70.63
#define ro2 63.51

*/
const char* ssid = "hotspot";
const char* password= "password";
ESP8266WebServer server(80);
String page ="";
double data=0;
void setup(void){
/*Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
  delay(1000);
 */ Serial.begin(115200);
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
    page = "<h1>sensor to node mcu</h1><h3>data:</h3><h4>"+String(data);
    server.send(200,"text/html",page);
  });
  server.begin();
  Serial.println("Web Server Started!");
}
void loop(void)
{
  
  // put your main code here, to run repeatedly:
 /* float mq135=analogRead(A0);
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
/*  Serial.print("rs135 ");
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
  Serial.println(rs2);
  */
 /* float ratio135 = rs135/ro135;
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
  float nh3 = 102.2*(pow(ratio135,-2.473));
  
  Serial.print("CO2 ");
  Serial.println(co2);
  Serial.print("Propane ");
  Serial.println(propane);
  Serial.print("Alcohol ");
  Serial.println(alcohol);
  Serial.print("CH4 ");
  Serial.println(ch4);
  Serial.print("LPG ");
  Serial.println(lpg);
  Serial.print("H2 ");
  Serial.println(h2);
  Serial.print("nh3 ");
  Serial.println(nh3);  
  delay(2000);
 

 */ 
}
