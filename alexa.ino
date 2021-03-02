
#include <ESP8266WiFi.h>
#include <Espalexa.h>
#define D3 16

const char* ssid = "Netvirtua3619";
const char* password = "f0dase123";


Espalexa espAlexa; 
//void Funcion DO(uint8_t brightness); 
//void Funcion D1 (uint8_t brightness); 
//void Funcion_D2 (uint8_t brightness);
 void Funcion_D3 (uint8_t brightness);


void setup() {
Serial.begin(9500);

pinMode (D3, OUTPUT);
digitalWrite(D3, HIGH);
ConectarWifi(); 

espAlexa. addDevice ("luz", Funcion_D3);
espAlexa.begin();
}


void loop() {
  ConectarWifi();
  espAlexa.loop();
  delay(1);
}


void ConectarWifi () 
{
    if (WiFi.status() != WL_CONNECTED) 
    {
     WiFi.mode (WIFI_STA);
     WiFi.begin(ssid, password);
     Serial.println(""); 
     Serial.println("Connecting to WiFi");
        while (WiFi.status() != WL_CONNECTED) 
        {
        delay(500); 
        Serial.print(".");
        }
     Serial.print("Connected to "); 
     Serial.println(ssid); 
     Serial.print("IP address: "); 
     Serial.println (WiFi.localIP());
     }
}
 void Funcion_D0(uint8_t brightness) 
 { 
    if (brightness) 
    {
    digitalWrite(D3, LOW);
    }

    else
    {
    digitalWrite (D3, HIGH);
    }
 }
