#include "Gate.h"

const int startState = 1;
int state;
const int topGateInput = A1;
const int bottomGateInput = A0;
const int topGateOutput = 2;
const int bottomGateOutput = 3;
const int topGateMinSlope = 20;
const int bottomGateMinSlope = 5;

//The max time allowed to wait for gate 2 trigger.
const int timeout = 1;

//The time increment that must pass inorder to check for a new event.
const int delayTime = 1;

const int loopDelay = 0.5;

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
        state = 2;
      }
      break;

    //wait for gate 2
    case 2:
      gateTwo->updateGate();
      if(gateTwo->checkFallingEdge()){
        endTime = micros();
        state = 3;
      }

      //Check for a timeout to revert back to gate one if false trigger.
      if(micros() - startTime > timeout * 1000000){
        state = 1;
      }

      break;

    //compute, and send it!
    case 3:{
      Serial.println(endTime - startTime);
      state = 1;
      delay(delayTime * 1000);
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
      break;

  }
  delay(loopDelay);

}