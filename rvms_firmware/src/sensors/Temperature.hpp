//
// Created by mia2b.
// TODO: Write description
//

#ifndef ECHO_TEMPERATURE_HPP
#define ECHO_TEMPERATURE_HPP


#include "Adafruit_MCP9808.h"

class Temperature {
public:
    Temperature();
    void setup(uint8_t address);
    void update();
    int16_t getTemp() const;
private:
    Adafruit_MCP9808 sensor = Adafruit_MCP9808();
    volatile int16_t temperatureC = 0;


};

extern Temperature AirTemp;
extern Temperature BodyTemp;

#endif //ECHO_TEMPERATURE_HPP
