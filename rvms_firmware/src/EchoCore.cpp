//
// Created by mia2b.
//
// References:
// https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/master/cores/nRF5/main.cpp
//

#include <Arduino.h>
#include <rtos.h>
#include "Debug.hpp"
#include "com/BluetoothLE.hpp"
#include "sensors/Sensors.hpp"

TaskHandle_t btleTaskHandle;
TaskHandle_t bTask;

[[noreturn]] void taskBtle(void *pvParameters);

[[noreturn]] void TaskB(void *pvParameters);

// Tasks

[[noreturn]] void taskBtle(void *pvParameters) {
    Serial.println("Thread A Started");
    Btle.setup();
    Btle.startAdvertising();
    Btle.setBatteryPercent(50);
//    uint32_t counter = 0;
    char charBuf[21];
    while (true) {
        if (Btle.isConnected()){
            sprintf(charBuf, "ABCDEFGHIJKLMNOPQRST");
            Serial.print(charBuf);
            Btle.sendMsg(charBuf);
        } else {
            vTaskDelay(1000);
            Serial.println("Disconnected");
        }
    }
}

[[noreturn]] void TaskB(void *pvParameters) {
    Serial.println("Thread B Started");

    while (true) {
//        Serial.println("------ Task B");
        vTaskDelay(600);
    }
}


int main() {
    init();
    Serial.begin(115200);
    // Note: Don't call any interrupt related statements outside the tasks.
    xTaskCreate(taskBtle, "Task A", 256, nullptr, tskIDLE_PRIORITY + 2, &btleTaskHandle);
    xTaskCreate(TaskB, "Task B", 256, nullptr, tskIDLE_PRIORITY + 1, &bTask);

    vTaskStartScheduler(); // Start the RTOS
    return 0;
}