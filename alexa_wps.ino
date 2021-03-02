#include <ESP8266WiFi.h> //adicona a biboteca 
#include <Espalexa.h>

void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);

Espalexa espalexa;
EspalexaDevice* device3; //this is optional


void setup() {


  Serial.begin(115200);//velocidade da comunição
   Serial.printf("\nTente conectar-se ao WiFi com SSID'%s'\n", WiFi.SSID().c_str());//mensagem inicial

  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFi.SSID().c_str(),WiFi.psk().c_str()); // lendo dados da EEPROM, últimas credenciais salvas
  while (WiFi.status() == WL_DISCONNECTED) {  // se o estatos for desconectado enta no laço
    delay(500); // espera 1/2 segundo
    Serial.print(".");// escreve .
  }

  wl_status_t status = WiFi.status(); // verifica o estaus do wifi
  if(status == WL_CONNECTED) {// se estiver conctado eseculta
    Serial.printf("\nConectado com sucesso a SSID '%s'\n", WiFi.SSID().c_str());// mostra o nome da rede
    Serial.print("IP address: ");Serial.println(WiFi.localIP());// mostra o ip
  } else {
    Serial.printf("\nNão foi possível conectar ao WiFi. state='%d'", status); 
    Serial.println("Por favor, pressione o botão WPS no seu roteador.\n pressione qualquer tecla para continuar...");
    while(!Serial.available()) { ; }
    if(!startWPSPBC()) {
       Serial.println("Falha ao conectar com WPS :-(");  
    }
  } 


    espalexa.addDevice("Chuveiro", firstLightChanged); //simplest definition, default state off
    espalexa.addDevice("Light 2", secondLightChanged, 255); //third parameter is beginning state (here fully on)
    
    device3 = new EspalexaDevice("Light 3", thirdLightChanged); //you can also create the Device objects yourself like here
    espalexa.addDevice(device3); //and then add them
    device3->setValue(128); //this allows you to e.g. update their state value at any time!

    espalexa.begin();

}

bool startWPSPBC() {
  Serial.println("WPS config start");
  bool wpsSuccess = WiFi.beginWPSConfig();
  if(wpsSuccess) {
      // Well this means not always success :-/ in case of a timeout we have an empty ssid
      String newSSID = WiFi.SSID();
      if(newSSID.length() > 0) {
        // WPSConfig has already connected in STA mode successfully to the new station. 
        Serial.printf("WPS concluído. Conectado com sucesso ao SSID '%s'\n", newSSID.c_str());
      } else {
        wpsSuccess = false;
      }
  }
  return wpsSuccess; 
}


void loop() {

   espalexa.loop();
   delay(1);

}

void firstLightChanged(uint8_t brightness) {
    Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
    }
    else  {
      Serial.println("OFF");
    }
}

void secondLightChanged(uint8_t brightness) {
  Serial.println(brightness);
}

void thirdLightChanged(uint8_t brightness) {
  //do what you need to do here
}
