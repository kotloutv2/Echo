#include <Arduino.h>
#include <rtos.h>

TaskHandle_t aTask;
TaskHandle_t bTask;

void TaskA(void *pvParameters);

void TaskB(void *pvParameters);

void setup() {
    Serial.begin(115200);

    xTaskCreate(TaskA, "Task A", 256, NULL, tskIDLE_PRIORITY + 2, &aTask);
    xTaskCreate(TaskB, "Task B", 256, NULL, tskIDLE_PRIORITY + 1, &bTask);

    vTaskStartScheduler(); // Start the RTOS
}

void loop() {
    // Don't use this, do things in tasks
}

// Tasks

void TaskA(void *pvParameters) {
    Serial.println("Thread A Started");

    while (true) {
        Serial.println("Task A ------");
        vTaskDelay(200);
    }
}

void TaskB(void *pvParameters) {
    Serial.println("Thread B Started");

    while (true) {
        Serial.println("------ Task B");
        vTaskDelay(600);
    }
}
