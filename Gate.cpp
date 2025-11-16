#include "Gate.h"

Gate::Gate(int threshIn, int gatePinInputIn, int gatePinOutputIn)
  : threshold(threshIn), gatePinInput(gatePinInputIn), gatePinOutput(gatePinOutputIn) {
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