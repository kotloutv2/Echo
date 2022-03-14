//
// Created by mia2b.
// TODO: Write description
//
#ifndef ECHO_DEBUG_HPP
#define ECHO_DEBUG_HPP

#include "Config.hpp"
#include <Arduino.h>

#if DEBUG_LEVEL > 0
#define debugC(...)    Serial.println(__VA_ARGS__)
#else
#define debugC(...)    nullptr
#endif

#if DEBUG_LEVEL > 1
#define debugI(...)    Serial.println(__VA_ARGS__)
#else
#define debugI(...)    nullptr
#endif

#if DEBUG_LEVEL > 2
#define debugV(...)   Serial.println(__VA_ARGS__)
#else
#define debugV(...)   nullptr
#endif

#endif //ECHO_DEBUG_HPP
