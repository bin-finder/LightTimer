#ifndef Gate_h
#define Gate_h

#include <Arduino.h>

/**
* This class handles an LED and a photoresistor,
* and checks if the gate has been blocked.
*/

class Gate{
  private:
    const int threshold;
    const int gatePinInput;
    const int gatePinOutput;
    int gateVal;
    int prevGateVal;
    const int minSlope = 50 ;//to be an edge, a line must have a slope bigger then 100.
  
  public:

    /**
    * @brief Initiliser.
    * @param threshIn The threshold of the photosister to return true or false.
    * @param gatePinInputIn The photosistor analog input pin.
    * @param gatePinOutputIn The LED output pin. cooper was here :D
    */
    Gate(int threshIn,int gatePinInputIn, int gatePinOutputIn);

    /**
    * @brief This checks for rising edge.
    * @return True if the gate is blocked, and False if not. (obviously).
    */
    bool checkRisingEdge();

    /**
    * @brief This checks for falling edge.
    * @return True if the gate is blocked, and False if not. (obviously).
    */
    bool checkFallingEdge();

    /**
    * @brief reads the values from the analog inputs.
    */
    void updateGate();

    /**
    * @brief Turns on the led
    */
    void turnOnLed();

    void turnOffLed();
};

#endif