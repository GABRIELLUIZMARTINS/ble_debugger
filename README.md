# _BLE DEBUGGER_

An example to how debug your projets with esp32 using bluetooth low energy. For this there is an esp32 component called `ble_sender` that sends the data and an implementation in a python file to receive the data, called `ble_receiver`.

The component is available in the [ble_sender](ble_sender/src/ble_sender/), with an example task in the [main](ble_sender/src/main/main.c) file.
To get messages from esp32 run [ble_receiver](ble_receiver/src/main.py).
