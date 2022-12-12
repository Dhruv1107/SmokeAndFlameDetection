/******************************************
*
 * This example works for both Industrial and STEM users.
 *
 * Developed by Jose Garcia, https://github.com/jotathebest/
 *
 * ****************************************/

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsEsp32Mqtt.h"
#include <WiFi.h>
#include <WiFiClient.h>


/****************************************
 * Define Constants
 ****************************************/
const char *UBIDOTS_TOKEN = "BBFF-ANKqMHdKjg7CEzs6JrlkHxpGI7Zxvn";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "Pixel7";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "helloworld1";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "esp32";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "flame-sensor"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL2 = "relay";
// const char *VARIABLE_LABEL3 = "";

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;
uint8_t analogPin = 32; // Pin used to read data from GPIO34 ADC_CH6.
int flameSensor = 13;
int LED = 2;
int relayPin = 18;
char str_sensor[10];



Ubidots ubidots(UBIDOTS_TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  pinMode(flameSensor,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(relayPin,OUTPUT);

  timer = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  
    // float value = analogRead(analogPin);
    int output = digitalRead(flameSensor);
    if(output)
    {
      // dtostrf(output,4,2,str_sensor);
      Serial.println(output);
      digitalWrite(LED,HIGH);
      digitalWrite(relayPin,HIGH);
      ubidots.add(VARIABLE_LABEL, output);
      ubidots.publish(DEVICE_LABEL);
      delay(1000);
    }
    else{
    digitalWrite(LED,LOW);
    digitalWrite(relayPin,LOW);
    }

    timer = millis();
  
  ubidots.loop();
  // delay(1000);
}

