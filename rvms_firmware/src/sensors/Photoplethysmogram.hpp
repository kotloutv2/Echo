//
// Created by mia2b.
// TODO: Write description
//

#ifndef ECHO_PHOTOPLETHYSMOGRAM_HPP
#define ECHO_PHOTOPLETHYSMOGRAM_HPP


#include "max86150.h"

class Photoplethysmogram {
public:
    Photoplethysmogram();
    void setup();
    void update();
    uint32_t getPpg() const;

    uint16_t check();

private:
    MAX86150 max86150Sensor;
    volatile uint32_t ppg = 310000;
    bool connected = false;

};


extern Photoplethysmogram Ppg;

#endif //ECHO_PHOTOPLETHYSMOGRAM_HPP
