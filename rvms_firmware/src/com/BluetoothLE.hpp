//
// Created by mia2b.
// TODO: Write description
//

#ifndef ECHO_BLUETOOTHLE_HPP
#define ECHO_BLUETOOTHLE_HPP

#include <bluefruit.h>

class BluetoothLE {
public:
    BluetoothLE(void);
    void setup();
    void startAdvertising();
    void sendMsg(const char[]);
    void setBatteryPercent(int percent);

    bool isConnected();

private:
    BLEBas  ble_battery_service;
    BLEDis  ble_information_service;
    BLEUart ble_uart_service;

    static void connectCallback(uint16_t conn_handle);
    static void disconnectCallback(uint16_t conn_handle, uint8_t reason);

};

extern BluetoothLE Btle;

#endif //ECHO_BLUETOOTHLE_HPP
