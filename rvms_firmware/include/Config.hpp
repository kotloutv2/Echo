//
// Created by mia2b.
// TODO: Write description
//

#ifndef ECHO_CONFIG_HPP
#define ECHO_CONFIG_HPP

// Adafruit Bluefruit Feather nrf52832
#define BOARD_NAME "Echo RVMS"
#define BOARD_HARDWARE_VERSION "Bread 22.3.13"
#define BOARD_FIRMWARE_VERSION "Echo 22.3.13"
#define BOARD_MANUFACTURER "Rvms Capstone Group"
#define BOARD_MODEL "Feather nrf52832"
#define BOARD_MIN_SOFTWARE_VERSION "Tracer 22.3.13"
#define BOARD_SERIAL_NUM "0000-0001"


#define I2C_ADDR_AIR_TEMP 0x18
#define I2C_ADDR_BODY_TEMP 0x19
#define I2C_ADDR_PPG MAX86150_ADDRESS

//  0    0.5°C       30 ms
//  1    0.25°C      65 ms
//  2    0.125°C     130 ms
//  3    0.0625°C    250 ms
#define TEMP_RESOLUTION 3

// TODO: Define Bluetooth and sensor modules and versions

// 0 - No Debug
// 1 - Critical
// 2 - Info
// 3 - Verbose
#define DEBUG_LEVEL 3

#endif //ECHO_CONFIG_HPP
