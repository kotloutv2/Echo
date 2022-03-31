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
#include "sensors/Temperature.hpp"
#include "sensors/Photoplethysmogram.hpp"

TaskHandle_t btleTaskHandle;
TaskHandle_t tempTaskHandle;
TaskHandle_t ppgTaskHandle;

[[noreturn]] void taskBtle(void *pvParameters);
[[noreturn]] void taskTemp(void *pvParameters);
[[noreturn]] void taskPpg(void *pvParameters);
// Tasks

[[noreturn]] void taskBtle(void *pvParameters) {
    Serial.println("Bluetooth Started");
    Btle.setup();
    Btle.startAdvertising();
    Btle.setBatteryPercent(50);
//    uint32_t counter = 0;
    char charBuf[8];
    while (true) {
        if (Btle.isConnected()){
//            sprintf(charBuf, "A%f B%f\n", AirTemp.getTemp(), BodyTemp.getTemp());
            sprintf(charBuf, "%lx %x %x\n", Ppg.getPpg(), AirTemp.getTemp(), BodyTemp.getTemp());
            Serial.print(charBuf);
            Btle.sendMsg(charBuf);
        } else {
            vTaskDelay(1000);
            Serial.println(".");
        }
    }
}

[[noreturn]] void taskTemp(void *pvParameters) {
    Serial.println("Temperature Monitoring Started");
    AirTemp.setup(I2C_ADDR_AIR_TEMP);
    BodyTemp.setup(I2C_ADDR_BODY_TEMP);
    vTaskPrioritySet(tempTaskHandle,tskIDLE_PRIORITY + 1);
    while (true) {
        AirTemp.update();
        BodyTemp.update();
        vTaskDelay(1000);
    }
}


[[noreturn]] void taskPpg(void *pvParameters) {
    Serial.println("PPG Monitoring Started");
    Ppg.setup();
    vTaskPrioritySet(ppgTaskHandle,tskIDLE_PRIORITY + 1);
    while (true) {
        if (Ppg.check() > 0) {
            Ppg.update();
            vTaskDelay(5);
        } else {
            vTaskDelay(10);
        }
    }
}


int main() {
    init();
    Serial.begin(115200);
    // Note: Don't call any interrupt related statements outside the tasks.
    xTaskCreate(taskBtle, "Task Btle", 512, nullptr, tskIDLE_PRIORITY + 3, &btleTaskHandle);
    xTaskCreate(taskPpg, "Task Ppg", 512, nullptr, tskIDLE_PRIORITY + 5, &ppgTaskHandle);
    xTaskCreate(taskTemp, "Task Temp", 256, nullptr, tskIDLE_PRIORITY + 5, &tempTaskHandle);


    vTaskStartScheduler(); // Start the RTOS
    return 0;
}