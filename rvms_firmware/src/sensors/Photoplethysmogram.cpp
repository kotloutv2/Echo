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
    if (!max86150Sensor.begin(Wire, I2C_SPEED_FAST, I2C_ADDR_PPG)) {
        debugC("Failed to connect to ppg sensor:");
        debugC(I2C_ADDR_PPG);
        debugC("Check connection");
    } else {
        connected = true;
        max86150Sensor.setup();
        max86150Sensor.wakeUp();
    }
}

void Photoplethysmogram::update() {
    if (connected) {

        ppg = (uint32_t) (max86150Sensor.getFIFORed());
    } else {
        ppg += (uint32_t) random(10, 40);
        if (ppg > 312000) {
            ppg = 309000;
        }
    }
}

uint16_t Photoplethysmogram::check() {
    if (connected) {
        return max86150Sensor.check();
    } else {
        return random(0, 5);
    }
}

uint32_t Photoplethysmogram::getPpg() const {
    return ppg;
}


