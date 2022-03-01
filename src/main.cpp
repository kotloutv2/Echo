#include <Arduino.h>
#include <rtos.h>

TaskHandle_t aTask;
TaskHandle_t bTask;

[[noreturn]] void TaskA(void *pvParameters);

[[noreturn]] void TaskB(void *pvParameters);

// Tasks

[[noreturn]] void TaskA(void *pvParameters) {
    Serial.println("Thread A Started");

    while (true) {
        Serial.println("Task A ------");
        vTaskDelay(200);
    }
}

[[noreturn]] void TaskB(void *pvParameters) {
    Serial.println("Thread B Started");

    while (true) {
        Serial.println("------ Task B");
        vTaskDelay(600);
    }
}


int main() {
    init();
    Serial.begin(115200);

    xTaskCreate(TaskA, "Task A", 256, nullptr, tskIDLE_PRIORITY + 2, &aTask);
    xTaskCreate(TaskB, "Task B", 256, nullptr, tskIDLE_PRIORITY + 1, &bTask);

    vTaskStartScheduler(); // Start the RTOS
    return 0;
}