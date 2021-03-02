#include <ESP8266WiFi.h> //adicona a biboteca 
#include <Espalexa.h>

#define A 16
#define B 5
#define C 4
#define D 0
#define NUMBER_OF_STEPS_PER_REV 512

int q;
int f;
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);

Espalexa espalexa;
EspalexaDevice* device2; //this is optional


void setup() {

pinMode(A,OUTPUT);
pinMode(B,OUTPUT);
pinMode(C,OUTPUT);
pinMode(D,OUTPUT);

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


    espalexa.addDevice("agua fria", firstLightChanged, 255); //simplest definition, default state off
    espalexa.addDevice("agua quente", secondLightChanged, 255); //third parameter is beginning state (here fully on)
    espalexa.addDevice(device2); //and then add them

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



void write(int a,int b,int c,int d){
digitalWrite(A,a);
digitalWrite(B,b);
digitalWrite(C,c);
digitalWrite(D,d);
}

void loop() {

   espalexa.loop();
   delay(1);

}


void direita(){
write(1,0,0,0);
delay(5);
write(1,1,0,0);
delay(5);
write(0,1,0,0);
delay(5);
write(0,1,1,0);
delay(5);
write(0,0,1,0);
delay(5);
write(0,0,1,1);
delay(5);
write(0,0,0,1);
delay(5);
write(1,0,0,1);
delay(5);
}


void esquerda(){
write(0,0,0,1);
delay(5);
write(0,0,1,1);
delay(5);
write(0,0,1,0);
delay(5);
write(0,1,1,0);
delay(5);
write(0,1,0,0);
delay(5);
write(1,1,0,0);
delay(5);
write(1,0,0,0);
delay(5);
write(1,0,0,1);
delay(5);
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
if (f<=brightness)
{
    while(f=!brightness)
    {
    direita();
    f++;
    Serial.println(f);
    }
}

if (f>=brightness)
{
    while(f=!brightness)
    {
    esquerda();
    f--;
    Serial.println(f);
    }
}

}

void thirdLightChanged(uint8_t brightness) {
  //do what you need to do here
}
