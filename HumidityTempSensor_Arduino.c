//uses thingspeak to store info, connects to wifi, uses humidity and temp sensor 

//#include <DHTesp.h>

#include <ESP8266WiFi.h>
//#include <DHT.h>
#include <ThingSpeak.h>
 
const char *ssid =  "Sanya mobile";  
const char *pass =  "9902833110";
 
 
DHT dht(D4, DHT11);

WiFiClient client;
 
long myChannelNumber = 2389130;
const char myWriteAPIKey[] = "5XI6KJZ8SSLHB28Y";
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  //dht.begin();
  ThingSpeak.begin(client);

  float g = analogRead(A0);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float g = analogRead(A0);
  Serial.println("Gas: " + (String) g);
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  // ThingSpeak.writeField(myChannelNumber, 2, t, myWriteAPIKey);
  // ThingSpeak.writeField(myChannelNumber, 1, h, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3, g, myWriteAPIKey);
  delay(2000);
}

/*
#include <DHTesp.h>

#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
 
const char *ssid =  "Dhanwin";  
const char *pass =  "Rikkula402";
 
 
DHT dht(D5, DHT11);
 
WiFiClient client;
 
long myChannelNumber = 2389130;
const char myWriteAPIKey[] = "5XI6KJZ8SSLHB28Y";
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  ThingSpeak.writeField(myChannelNumber, 2, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 1, h, myWriteAPIKey);
  delay(2000);
}


*/
