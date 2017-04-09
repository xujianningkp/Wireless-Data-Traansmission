#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

#define NODEID      99
#define NETWORKID   55
#define GATEWAYID   77  //send to test monitor
#define FREQUENCY   RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9
#define SERIAL_BAUD 115200

int counter = 0;

RFM69 radio;
SPIFlash flash(8, 0xEF30); //EF40 for 16mbit windbond chip
bool promiscuousMode = false; //set to 'true' to sniff all packets on the same network

typedef struct {		
  float         temp1;   //temperature maybe?
  float         temp2;
  float         analog3;
  int           counter;
} Payload;
Payload theData;

void setup() {
  Serial.begin(SERIAL_BAUD);
  Wire.begin();
  RTC.begin();
  // following line sets the RTC to the date & time this sketch was compiled
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  delay(10);
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  //radio.setHighPower(); //uncomment only for RFM69HW!
  radio.encrypt(KEY);
  radio.promiscuous(promiscuousMode);
  char buff[50];
  sprintf(buff, "\nListening at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  //Serial.println(buff);
}

byte ackCount=0;
void loop() {
  
  
  
  if (radio.receiveDone())
  {
    
    if (radio.DATALEN != sizeof(Payload))
      Serial.print("Invalid payload received, not matching Payload struct!");
    else
    {
      theData = *(Payload*)radio.DATA; //assume radio.DATA actually contains our struct and not something else
      
      DateTime now = RTC.now();
      Serial.print(now.year(), DEC);
      Serial.print('/');
      if(now.month() < 10)Serial.print('0');
      Serial.print(now.month(), DEC);
      Serial.print('/');
      if(now.day() < 10){Serial.print('0');}
      Serial.print(now.day(), DEC);
      Serial.print(" , ");
      if(now.hour() < 10){Serial.print('0');}
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      if(now.minute() < 10){Serial.print('0');}
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      if(now.second() < 10){Serial.print('0');}
      Serial.print(now.second(), DEC);
      
      Serial.print(" , ");
      Serial.print(theData.temp1);
      Serial.print(" , ");
      Serial.print(theData.temp2);
      Serial.print(" , ");
      Serial.print(theData.analog3);
      delay(100);
      
      counter = counter + 1;
      theData.counter = counter;
      if (counter > 99){
      counter = 1;
      }
      
      radio.send(GATEWAYID, (const void*)(&theData), sizeof(theData));
    }
    
    Serial.println();
    Blink(LED,3);
    
  }
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
