#include "Gate.h"

Gate::Gate(int gatePinInputIn, int gatePinOutputIn, int minSlopeIn)
  : gatePinInput(gatePinInputIn), gatePinOutput(gatePinOutputIn), minSlope(minSlopeIn) {
  pinMode(gatePinOutput, OUTPUT);
  digitalWrite(gatePinOutput, LOW);
  prevGateVal = analogRead(gatePinInput);
}

void Gate::updateGate() {
  prevGateVal = gateVal;
  turnOnLed();
  gateVal = analogRead(gatePinInput);
  turnOffLed();
}

bool Gate::checkRisingEdge() {
  if (gateVal - prevGateVal > minSlope) {
    return true;
  } else {
    return false;
  }
}

bool Gate::checkFallingEdge() {
  if (prevGateVal - gateVal > minSlope) {
    return true;
  } else {
    return false;
  }
}

void Gate::turnOnLed() {
  digitalWrite(gatePinOutput, HIGH);
}

void Gate::turnOffLed() {
  digitalWrite(gatePinOutput, LOW);
}

int Gate::getGateVal(){
  return gateVal;
}