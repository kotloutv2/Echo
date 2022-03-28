//
// Created by mia2b.
// TODO: Write description
//

#include "Photoplethysmogram.hpp"
#include "Config.hpp"
#include "Debug.hpp"
Photoplethysmogram Ppg;

Photoplethysmogram::Photoplethysmogram() = default;

void Photoplethysmogram::setup() {
    if (max86150Sensor.begin(Wire, I2C_SPEED_FAST, I2C_ADDR_PPG)) {
        debugC("Failed to connect to temperature sensor:");
        debugC(I2C_ADDR_PPG);
        debugC("Check connection");
    }
    max86150Sensor.setup();
    max86150Sensor.wakeUp();
}

void Photoplethysmogram::update() {
    if (max86150Sensor.check() > 0) {
        ppg = (uint32_t) (max86150Sensor.getFIFORed());
    }
}

uint32_t Photoplethysmogram::getPpg() const {
    return ppg;
}


