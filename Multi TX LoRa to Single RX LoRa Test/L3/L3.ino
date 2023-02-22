#include <SPI.h>
#include <LoRa.h>
#include <elapsedMillis.h>

#define BAND  915E6
#define SS    10
#define RST   9
#define DIO0  2

String area = "L3";
String valueA  = "3@";
String valueB  = "3*";
String valueC  = "3$";
String valueD  = "3%";
String valueE  = "3^";

void setup()
{
  Serial.begin(9600);

  initLoRa();
}

void loop() 
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    while (LoRa.available()) 
    {
      String msgArea = LoRa.readStringUntil ('#');
      if (msgArea == area)
      {
        onResponse(msgArea, valueA, valueB, valueC, valueD, valueE);
      }
    }
  }
}

void initLoRa()
{
  LoRa.setPins (SS, RST, DIO0);
  if (!LoRa.begin(BAND))
  {
    while (1);
  }
}

void onResponse(String field, String sensor1, String sensor2, String sensor3, String sensor4, String sensor5)
{
  LoRa.beginPacket ();
  LoRa.print (field);
  LoRa.print ("#");
  LoRa.print (sensor1);
  LoRa.print ("#");
  LoRa.print (sensor2);
  LoRa.print ("#");
  LoRa.print (sensor3);
  LoRa.print ("#");
  LoRa.print (sensor4);
  LoRa.print ("#");
  LoRa.print (sensor5);
  LoRa.print ("#");
  LoRa.endPacket ();
}
