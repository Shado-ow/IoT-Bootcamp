//fire alarm using mqtt

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <DHT.h>
#include <DHTesp.h>

const char *ssid ="Anvesha";
const char *pass ="pinkcity15";

#define channelID 2389132
const char mqttUserName[] ="IS0rKjoRJAsmEwAGOzcaOR8";
const char clientID[] = "IS0rKjoRJAsmEwAGOzcaOR8";
const char mqttPass[] = "CPv9si+QxdyNLjpXMCFChfH1";

#define ESP8266wifi
#define DHTPIN 2
DHT dht(D4, DHT11);

const char* PROGMEM thingspeak_cert_thumbprint = "271892dda426c30709b97ae6c521b95b48f716e1";

#define mqttPort 1883
WiFiClient client;

const char* server = "mqtt3.thingspeak.com";
int status = WL_IDLE_STATUS;
long lastPublishMillis = 0;
int connectionDelay = 1;
int updateInterval = 8;
PubSubClient mqttClient( client );

void mqttSubscribe( long subChannelID ){
  String myTopic = "channels/"+String( subChannelID )+"/subscribe";
  mqttClient.subscribe(myTopic.c_str());
}

void mqttPublish(long pubChannelID, String message) {
  String topicString ="channels/" + String( pubChannelID ) + "/publish";
  mqttClient.publish( topicString.c_str(), message.c_str() );
}

void mqttSubscriptionCallback( char* topic, byte* payload, unsigned int length ) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
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
  while ( !mqttClient.connected() ) {
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

const int Temperature = D4;
const int Buzzer = D5;
const int Gas = A0; 

void setup() {
  Serial.begin(9600);
  delay(500);
  connectWifi();
  mqttClient.setServer( server, mqttPort );
  mqttClient.setCallback( mqttSubscriptionCallback );
  mqttClient.setBufferSize( 2048 );
  pinMode(Temperature, INPUT);
  pinMode(Gas, INPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWifi();
  }
  if (!mqttClient.connected()) {
    mqttConnect();
    mqttSubscribe(channelID);
  }
  mqttClient.loop();
  digitalWrite(Buzzer, LOW);
  float gas = analogRead(A0);
  mqttPublish( channelID, (String("field2=")+String(gas)) );
  Serial.print("Gas: ");
  Serial.println(gas);
  /* if ((temp > ) && (gas > )) {
    digitalWrite(Buzzer, HIGH);
  } */
  // float temp_receive = mqttSubscribe(channelID);
  // Serial.println(temp_receive);
  // Serial.println( "State= " + String( mqttClient.state() ) );
  delay(1000);
}
