#include <RFM69.h>
#include <SPI.h>
#include "LowPower.h"

#define NODEID      2
#define NETWORKID   55
#define GATEWAYID   99
#define FREQUENCY   RF69_915MHZ
#define KEY         "thisIsEncryptKey"
#define LED         9
#define SERIAL_BAUD 115200

RFM69 radio;

bool promiscuousMode = false; //set to 'true' to sniff all packets on the same network

typedef struct {		
  float         temp1;   //RFM69W Build-in Temp
  float         temp2;   //Analog Temp (Outside)
  float         analog3; //Moister Sensor
  int           counter; //Numbers of Testing data
} Payload;
Payload theData;


void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(10);
  Blink(LED,1000);

  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.encrypt(KEY);
  radio.promiscuous(promiscuousMode);
  char buff[50];
  sprintf(buff, "\nListening at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
}

void loop() {
      radio.receiveDone(); //Put RFM69W in RX mode (listening mode) 
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      
      if (radio.receiveDone()){
      if (radio.DATALEN != sizeof(Payload))
            Serial.print("Invalid payload received, not matching Payload struct!");
      else
          {
            theData = *(Payload*)radio.DATA; //assume radio.DATA actually contains our struct and not something else

            Serial.print(theData.temp1);
            Serial.print(" , ");
            Serial.print(theData.temp2);
            Serial.print(" , ");
            Serial.print(theData.analog3);
            delay(100);
            radio.send(GATEWAYID, (const void*)(&theData), sizeof(theData));
          }
      Serial.println();
      Blink(LED,3);
      radio.sleep();
      //Put Moteino to sleep mode for 14mins 50secs
      for(int x = 0; x <89; x++){
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
      LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
      } 
     }      
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}

