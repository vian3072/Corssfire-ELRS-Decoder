#include "CRSF.h"


#define DEBUG // if not commented out, Serial.print() is active! For debugging only!!
  
const bool testAutoSendMode = false;
#define FRESH_TIME_US 4000  // Update every 4ms
unsigned long int currentMicros = 0;

int packetPerSec;
unsigned long int currentMillis;

#define SECOND 1000


CRSF crsf;

void setup(){
  crsf.begin();

  #ifdef DEBUG
    Serial.begin(115200);
    packetPerSec = 0;
    currentMillis = 0;
  #endif

}

void loop(){
  //delay(5);
  
  if (micros() - currentMicros >= FRESH_TIME_US) {
    crsf.GetCrsfPacket();
    //if(crsf.crsfData[1]==24){ //data packet
      #ifdef DEBUG
        packetPerSec++;
      #endif
      // Turn indicator light on.
      if(crsf.failsafe_status == 0){
        digitalWrite(LED_BUILTIN, 1);
      }else{
        digitalWrite(LED_BUILTIN, 0);
      }
    if(millis()-currentMillis > SECOND ){
      //Serial.println(packetPerSec); 
      currentMillis=millis();
      packetPerSec=0;
    }
    Serial.print("t:");
    Serial.println(crsf.channels[1]); 
    //Serial.print(crsf.channels[0]); 
    //Serial.print(crsf.channels[1]); 
    Serial.print("x:");
    Serial.println(map((crsf.channels[2]),175,1805,0,180)); 

    if(crsf.connected==false){
      Serial.print("disconnected");
    }
    //Serial.println();
    //Serial<<crsf.channels[0]<<","<<crsf.channels[1]<<","<<crsf.channels[2]<<","<<crsf.channels[3]<<"\r\n";
   // Serial<<crsf.crsfData[0]<<","<<crsf.crsfData[1]<<","<<crsf.crsfData[2]<<","<<crsf.crsfData[3]<<"\r\n";
   // Serial<<crsf.channels[0]<<","<<crsf.channels[1]<<","<<crsf.channels[2]<<","<<crsf.channels[3]<<","<<crsf.inBuffer[4]<<","<<crsf.inBuffer[5]<<","<<crsf.inBuffer[24]<<","<<crsf.inBuffer[25]<<"\r\n";
    //Serial.println(startMillis);
    //Serial.println(crsf.GetBufferIndex());      

      crsf.UpdateChannels();
 // }
    currentMicros = micros();
  }
}
