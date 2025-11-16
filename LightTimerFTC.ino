#include "Gate.h"

const int startState = 1;
int state;
const int gateOneInput = A0;
const int gateTwoInput = A1;
const int gateOneOutput = 2;
const int gateTwoOutput = 3;
int gateOneThreshold = 440;
int gateTwoThreshold = 440;

unsigned long startTime;
unsigned long endTime;

const double gateDist = 2.0; //10 cm

Gate gateOne(gateOneThreshold, gateOneInput, gateOneOutput);
Gate gateTwo(gateTwoThreshold, gateTwoInput, gateTwoOutput);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  state = startState;
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state){

    //wait for gate 1
    case 1:
    gateOne.updateGate();
      if(gateOne.checkFallingEdge()){
        startTime = micros();
        state = 2;
      }
      break;

    //wait for gate 2
    case 2:
      gateTwo.updateGate();
      if(gateTwo.checkFallingEdge()){
        endTime = micros();
        state = 3;
      }
      break;

    //compute, and send it!
    case 3:{
      double speed = gateDist/((endTime - startTime)/(1000000.0));
      Serial.println(speed);
      delay(10); //give ADC time to settle after read.
      state = 1;
      break;
    }

    case 4:
      gateOne.turnOnLed();
      gateTwo.turnOnLed();
      state = 5;
      break;

    case 5:
      Serial.print(analogRead(gateOneInput));
      Serial.print(",");
      Serial.println(analogRead(gateTwoInput));
      delay(25);
      break;

  }

}