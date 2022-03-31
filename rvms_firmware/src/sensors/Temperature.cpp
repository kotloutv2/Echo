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
    } else {
        connected = true;
        sensor.setResolution(TEMP_RESOLUTION);
    }
}

void Temperature::update() {
    sensor.wake();
    if (connected) {
        temperatureC = (int16_t) (sensor.readTempC() * 100);
    } else {
        temperatureC += random(0,11)-5;
        if (temperatureC > 33 * 100) {
            temperatureC -= random(5, 15);
        } else if (temperatureC < 27 * 100) {
            temperatureC += random(5, 15);
        }
    }
    sensor.shutdown();
}

int16_t Temperature::getTemp() const {
    return temperatureC;
}


