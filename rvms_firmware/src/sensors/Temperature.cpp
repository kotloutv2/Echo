//
// Created by mia2b.
// TODO: Write description
//

#include "Temperature.hpp"
#include "Debug.hpp"
#include "Config.hpp"

Temperature AirTemp;
Temperature BodyTemp;

Temperature::Temperature() = default;

void Temperature::setup(uint8_t address) {
    if (!sensor.begin(address)) {
        debugC("Failed to connect to temperature sensor:");
        debugC(address);
        debugC("Check connection");
    }
    sensor.setResolution(TEMP_RESOLUTION);
}

void Temperature::update() {
    sensor.wake();
    temperatureC = (int16_t) (sensor.readTempC() * 1000);
    sensor.shutdown();
}

int16_t Temperature::getTemp() const {
    return temperatureC;
}


