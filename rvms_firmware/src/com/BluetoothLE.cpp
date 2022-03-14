//
// Created by mia2b.
//
// Reference on how to use the Adafruit Bluefruit Lib:
// https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/bluefruit-nrf52-api
//

#include "BluetoothLE.hpp"

#include <Arduino.h>
#include <bluefruit.h>
#include "Config.hpp"
#include "Debug.hpp"

BluetoothLE Btle;

BluetoothLE::BluetoothLE() = default;

void BluetoothLE::setup() {
    Serial.println("???");
    debugI("Initializing BluetoothLE");
    debugV("Bluefruit.begin()");
    Bluefruit.begin();
    debugV("Bluefruit.setName(RVMS)");
    Bluefruit.setName(BOARD_NAME);
    debugV("Bluefruit.setTxPower(0)");
    Bluefruit.setTxPower(0);

    debugV("Set callbacks");
    Bluefruit.Periph.setConnectCallback(BluetoothLE::connectCallback);
    Bluefruit.Periph.setDisconnectCallback(BluetoothLE::disconnectCallback);

    debugV("Begin Services");

    ble_information_service.setManufacturer(BOARD_MANUFACTURER);
    ble_information_service.setSoftwareRev(BOARD_MIN_SOFTWARE_VERSION);
    ble_information_service.setFirmwareRev(BOARD_FIRMWARE_VERSION);
    ble_information_service.setHardwareRev(BOARD_HARDWARE_VERSION);
    ble_information_service.setModel(BOARD_MODEL);
    ble_information_service.setSerialNum(BOARD_SERIAL_NUM);


    ble_battery_service.begin();
    ble_battery_service.write(100);
    ble_information_service.begin();
    ble_uart_service.begin();

    debugI("Finished setting up bluetooth");
}

void BluetoothLE::startAdvertising() {
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();

    // Include the BLE UART (AKA 'NUS') 128-bit UUID
    Bluefruit.Advertising.addService(ble_uart_service);

    // Secondary Scan Response packet (optional)
    // Since there is no room for 'Name' in Advertising packet

    Bluefruit.ScanResponse.addName();
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
    Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

}

void BluetoothLE::sendMsg(const char str[]) {
    ble_uart_service.write(str);
}

void BluetoothLE::connectCallback(uint16_t conn_handle) {
    // Get the reference to current connection
    BLEConnection* connection = Bluefruit.Connection(conn_handle);

    char central_name[32] = { 0 };
    connection->getPeerName(central_name, sizeof(central_name));

    Serial.print("Connected to ");
    Serial.println(central_name);
}

void BluetoothLE::disconnectCallback(uint16_t conn_handle, uint8_t reason)
{
    (void) conn_handle;
    (void) reason;

    Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
    Serial.println("Advertising!");
}

void BluetoothLE::setBatteryPercent(int percent) {
    ble_battery_service.write(percent);
}

bool BluetoothLE::isConnected() {
    return (bool)Bluefruit.connected();
}

