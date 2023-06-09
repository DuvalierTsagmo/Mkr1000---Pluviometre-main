/*
  Titre      : Pluviometrie
  Auteur     : Duvalier Tsagmo
  Date       : 24/03/2023
  Description: Envoie le nombre de bascule du à une quantité de pluie provenant du Anemometre
  Version    : 0.0.1
*/

// librairie pour le framework
#include <Arduino.h>
#include <SPI.h>

// Librairie de branchement
// #include "WIFIConnector_MKR1000.h"
// #include "MQTTConnector.h"

// Definition des pin
const int PinReedSwitch = 1; // Reedswitch pour le decompteur
volatile int Compteur = 0;   // Compteur de basculement de l'auget

// Variables de gestions du temps
unsigned int tempsActuel = 0;
unsigned int tempsPasse = 0;
unsigned int tempsNecessaire = 5000; // 1 min

// Interrupt pour compter le nombre de bascule
void compteurBascule()
{
    Compteur++;
    Serial.print(Compteur);
    Compteur = 0;
}

void setup()
{

    Serial.begin(9600);
    // Definition des pinMode
    pinMode(PinReedSwitch, INPUT);

    // Lien interrupt pour compter les bascules à chaque changement d'etat du haut vers le bas
    attachInterrupt(digitalPinToInterrupt(PinReedSwitch), compteurBascule, FALLING);
}

void loop()
{
    // Sauvegarde du temps en cours
    tempsActuel = millis();

    //Envoie du decompte sur thingsboard  après chaque 01 min
    if ((tempsActuel - tempsPasse) >  tempsNecessaire){

      Serial.println(Compteur);
      Compteur = 0;
      tempsPasse = tempsActuel;
    } 
}