#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include "LowPower.h"

#define PHS         5   // photosensor output pin 5
#define PHS1        6
int analogPin = 5;
int analogPin1 = 6;
int PHSREAD = 0;
int PHSREAD1 = 0;

#define NODEID      1
#define NETWORKID   55
#define GATEWAYID   2
#define FREQUENCY   RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9
#define SERIAL_BAUD 115200


RFM69 radio;

typedef struct {		
  float         temp1;
  float         temp2;
  float         analog3;
  int           counter;
} Payload;
Payload theData;

void setup() {
  Serial.begin(SERIAL_BAUD);
  pinMode(PHS, OUTPUT);
  pinMode(PHS1, OUTPUT);
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  //radio.setHighPower(); //uncomment only for RFM69HW!
  radio.encrypt(KEY);
  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  //Serial.println(buff);
}


void loop() {

    byte temperature =  radio.readTemperature(-4); // -1 = user cal factor, adjust for correct ambient
    theData.temp1 = 1.8 * temperature + 32; // 9/5=1.8
    digitalWrite(PHS1, HIGH);
    delay(50);
    PHSREAD1 = analogRead(analogPin1);
   
    int Vo; // Integer value of voltage reading
    float R = 9890.0; // Fixed resistance in the voltage divider
    float logRt,Rt,T,TF;
    float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
    PHSREAD1 = analogRead(analogPin1);
    Rt = R*( 1023.0 / (float)PHSREAD1 - 1.0 );
    logRt = log(Rt);
    T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;
    TF = ((T*1.8)+32);
    digitalWrite(PHS1, LOW);
    theData.temp2 = TF;
    Serial.print(theData.temp1);
    Serial.print(" , ");
    Serial.print(theData.temp2);
    Serial.print(" , ");
    digitalWrite(PHS, HIGH);
    delay(50);
    PHSREAD = analogRead(analogPin);
    PHSREAD = map(PHSREAD,77,284, 0, 100);
    theData.analog3 = PHSREAD;
    Serial.print(theData.analog3);
    digitalWrite(PHS, LOW);

    radio.send(GATEWAYID, (const void*)(&theData), sizeof(theData));

    Serial.println();
    Blink(LED,3);
    

    radio.sleep();
    //for(int x = 0; x < 1; x++){
    for(int x = 0; x < 90; x++){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
    }

  }


void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
