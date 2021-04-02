
//#include <TheThingsNetwork.h>
#include <LoRaWan.h>
#include "DHT.h"

#define DHTPIN            2   // pin de la carte utilisee pour les donnees
#define DHTTYPE           DHT22 //type de capteur 

DHT dht(DHTPIN, DHTTYPE);
unsigned char data[4]; 
char buffer[256];


void setup(void)
{
    dht.begin(); 
    SerialUSB.begin(9600);          
    lora.init();// init lora
    
    memset(buffer, 0, 256);
    lora.getVersion(buffer, 256, 1);
    SerialUSB.print(buffer); 

   // identification du device sur la Gateway
    
    lora.setId(NULL, "00BB716C0F5B3E34", "70B3D57ED001E4CE");// 00BB716C0F5B3E34 : devEUI (la passerelle)
                                                             // 70B3D57ED001E4CE : AppKey (l'application)
    lora.setKey(NULL, NULL, "6E3AFC33722CBBB842506C6E0A62DC95");
    
    lora.setDeciveMode(LWOTAA);   // choix mode OTAA
    lora.setDataRate(DR0, EU868); //emission sur la bande des 868MHz
    
    lora.setChannel(0, 868.1);//configuration des canaux
    lora.setChannel(1, 868.3);//configuration des canaux
    lora.setChannel(2, 868.5);//configuration des canaux
    
    lora.setDutyCycle(false);
    lora.setJoinDutyCycle(false);
    
    lora.setPower(14); //puissance du device
    
    while(!lora.setOTAAJoin(JOIN)); // test de connexion
}

void loop(void)
{   
    bool result = false;
    //On récupère le taux de charge de notre batterie grâce à notre fonction créée précédemment
    int batterie = getValBattery(); 

    data[0] = 0x02; //Numéro de channel TTN
    data[1] = 0x67; //Type de donnee TTN
    data[2] = highByte(batterie); //Extraction du bit de point fort du taux de charge
    data[3] = lowByte(batterie); //Extraction du bit de point faible du taux de charge
    
    SerialUSB.print("batterie ");//affichage sur le moniteur serie
    SerialUSB.println(batterie*1.0/10); //affichage sur le moniteur serie
    
    result = lora.transferPacket(data, 4, 30); //transmission 4 packets (octets) toutes les 30s
}