from bluepy import btle
from time import sleep

class BleReceiver:
    def __init__(self, mac_address):
        self.mac_address = mac_address
        self.device = None

    def connect(self):
        try:
            self.device = btle.Peripheral(self.mac_address)
            print("Connected to BLE device sucessfully!")
        except Exception as e:
            print("An error occurred while connecting to the device:", str(e))

    def disconnect(self):
        try:
            self.device.disconnect()
            print("Sucessfully disconnected from BLE device!")
        except Exception as e:
            print("An error occurred while disconnecting from the device:", str(e))

    def receive_message(self, uuid_service, characteristic_uuid):
        try:
            servico_gatt = self.device.getServiceByUUID(uuid_service)
            characteristic = servico_gatt.getCharacteristics(characteristic_uuid)[0]
            data = characteristic.read()
            message = data.decode("utf-8")
            print("Received message:", message)
            return message
        except Exception as e:
            print("An error occurred while receiving the message:", str(e))
            return None
