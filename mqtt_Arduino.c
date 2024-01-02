#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>


const char *ssid ="Sanya mobile";
const char *pass ="9902833110";

#define channelID 2390761
const char mqttUserName[] ="FjwbBzc9FTYLKiwqBAkNIyM";
const char clientID[] = "FjwbBzc9FTYLKiwqBAkNIyM";
const char mqttPass[] = "wMG4ezjFlt56Yjr7wR4Ek2iD";

#define ESP8266wifi

const char* PROGMEM thingspeak_cert_thumbprint =
"271892dda426c30709b97ae6c521b95b48f716e1";

#define mqttPort 1883
WiFiClient client;

const char* server = "mqtt3.thingspeak.com";
int status = WL_IDLE_STATUS;
long lastPublishMillis = 0;
int connectionDelay = 1;
int updateInterval = 15;
PubSubClient mqttClient( client );

void mqttSubscribe( long subChannelID ){
String myTopic = "channels/"+String( subChannelID )+"/subscribe";
mqttClient.subscribe(myTopic.c_str());
}

void mqttPublish(long pubChannelID, String message) {
String topicString ="channels/" + String( pubChannelID ) + "/publish";
mqttClient.publish( topicString.c_str(), message.c_str() );
}

void mqttSubscriptionCallback( char* topic, byte* payload, unsigned int
length ) {
Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
for (int i = 0; i < length; i++) {
Serial.print((char)payload[i]);
}
Serial.println();
}

void connectWifi() {
WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
}

void mqttConnect() {
while ( !mqttClient.connected() )
{
if ( mqttClient.connect( clientID, mqttUserName, mqttPass ) ) {
Serial.print( "MQTT to " );
Serial.print( server );
Serial.print (" at port ");
Serial.print( mqttPort );
Serial.println( " successful." );
} else {
Serial.print( "MQTT connection failed, rc = " );
Serial.print( mqttClient.state() );
Serial.println( " Will try again in a few seconds" );
delay( connectionDelay*1000 );
}
}
}

const int echo = D2;  
const int trigger = D1; 
int distance = 0; 

void setup() {
Serial.begin( 9600 );
delay(1000);
pinMode(echo, INPUT); 
  pinMode(trigger, OUTPUT);
connectWifi();
mqttClient.setServer( server, mqttPort );
mqttClient.setCallback( mqttSubscriptionCallback );
mqttClient.setBufferSize( 2048 );

}

void loop() {


if (WiFi.status() != WL_CONNECTED) {
connectWifi();
}

if (!mqttClient.connected()) {
mqttConnect();
mqttSubscribe(channelID );
}

mqttClient.loop();

digitalWrite(echo, LOW);
delayMicroseconds(2);

digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

float duration = pulseIn(echo,HIGH);
  //Serial.print("duration: ");
  //Serial.println(duration);
float speed = 0.0343;
float distance = (duration * speed) / 2; 
Serial.print("Distance: ");
Serial.println(distance);

mqttPublish( channelID, (String("field1=")+String(distance)) );
//lastPublishMillis = millis();

delay(1000);

}

/*
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>


const char *ssid ="jagan";
const char *pass ="12345678";

#define channelID 452134
const char mqttUserName[] ="FjwbBzc9FTYLKiwqBAkNIyM";
const char clientID[] = "FjwbBzc9FTYLKiwqBAkNIyM";
const char mqttPass[] = "wMG4ezjFlt56Yjr7wR4Ek2iD";

#define ESP8266wifi

const char* PROGMEM thingspeak_cert_thumbprint =
"271892dda426c30709b97ae6c521b95b48f716e1";

#define mqttPort 1883
WiFiClient client;

const char* server = "mqtt3.thingspeak.com";
int status = WL_IDLE_STATUS;
long lastPublishMillis = 0;
int connectionDelay = 1;
int updateInterval = 15;
PubSubClient mqttClient( client );

void mqttSubscribe( long subChannelID ){
String myTopic = "channels/"+String( subChannelID )+"/subscribe";
mqttClient.subscribe(myTopic.c_str());
}

void mqttPublish(long pubChannelID, String message) {
String topicString ="channels/" + String( pubChannelID ) + "/publish";
mqttClient.publish( topicString.c_str(), message.c_str() );
}

void mqttSubscriptionCallback( char* topic, byte* payload, unsigned int
length ) {
Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
for (int i = 0; i < length; i++) {
Serial.print((char)payload[i]);
}
Serial.println();
}

void connectWifi() {
WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
}

void mqttConnect() {
while ( !mqttClient.connected() )
{
if ( mqttClient.connect( clientID, mqttUserName, mqttPass ) ) {
Serial.print( "MQTT to " );
Serial.print( server );
Serial.print (" at port ");
Serial.print( mqttPort );
Serial.println( " successful." );
} else {
Serial.print( "MQTT connection failed, rc = " );
Serial.print( mqttClient.state() );
Serial.println( " Will try again in a few seconds" );
delay( connectionDelay*1000 );
}
}
}

const int LevelSensorPin = A0;  
int WaterLevelValue = 0; 

void setup() {
Serial.begin( 9600 );
delay(3000);
connectWifi();
mqttClient.setServer( server, mqttPort );
mqttClient.setCallback( mqttSubscriptionCallback );
mqttClient.setBufferSize( 2048 );

}

void loop() {


if (WiFi.status() != WL_CONNECTED) {
connectWifi();
}

if (!mqttClient.connected()) {
mqttConnect();
mqttSubscribe(channelID );
}

mqttClient.loop();

if ( (millis() - lastPublishMillis) > updateInterval*1000) {
WaterLevelValue = analogRead(LevelSensorPin);
Serial.println(WaterLevelValue);

mqttPublish( channelID, (String("field1=")+String(WaterLevelValue)) );
lastPublishMillis = millis();
}

}
*/
