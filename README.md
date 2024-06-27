# _BLE LOGGER_

This is an example of how to use bluetooth as a logger to debug applications.

## Configuration

You needs configure NimBLE in menuconfig:

Component config --> Bluetooth --> Bluetooth Host (NimBLE - BLE only) --> NimBLE - BLE only

## BLE Server

In this implementation it is possible to send strings through the `ble_update_data()` function that updates the value that is sent.

Firmware files are distributed as follows:

```pre
.
├── .vscode         # Visual Studio Code Workspace files
├── build           # Firmware build files (automatically generated)
└──  src            # Source code
    ├── main                            # Application example
    └── espnow_sender/espnow_receiver   # Implementation 
```
