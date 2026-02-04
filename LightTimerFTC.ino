#include "Gate.h"

const int startState = 1;
int state;
const int topGateInput = A1;
const int bottomGateInput = A0;
const int topGateOutput = 2;
const int bottomGateOutput = 3;
const int topGateMinSlope = 50;
const int bottomGateMinSlope = 10;

unsigned long startTime;
unsigned long endTime;

Gate topGate(topGateInput, topGateOutput, topGateMinSlope);
Gate bottomGate(bottomGateInput, bottomGateOutput, bottomGateMinSlope);

Gate* gateOne = &bottomGate;
Gate* gateTwo = &topGate;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Welcome to the Calabrtron 2000!\nI hope it works!\n\nTime: u sec");
  state = startState;
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state){

    //wait for gate 1
    case 1:
      gateOne->updateGate();
      if(gateOne->checkFallingEdge()){
        startTime = micros();
        //Serial.println("/1");
        state = 2;
      }
      break;

    //wait for gate 2
    case 2:
      gateTwo->updateGate();
      //Serial.println(gateTwo.getGateVal());
      if(gateTwo->checkFallingEdge()){
        endTime = micros();
        //Serial.println("/2");
        state = 3;
      }
      break;

    //compute, and send it!
    case 3:{
      Serial.println(endTime - startTime);
      state = 1;
      break;
    }

    //Debug Case. This will turn on the IR
    //leds for there to be some signal
    case 4:
      gateOne->turnOnLed();
      gateTwo->turnOnLed();
      state = 5;
      break;

    //debug case. Set Case to 5 on build to debug inputs.
    case 5:
      Serial.print(analogRead(topGateInput));
      Serial.print(",");
      Serial.println(analogRead(bottomGateInput));
      delay(25);
      break;

  }
  delay(10);

}