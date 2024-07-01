from bluepy import btle
from time import sleep

class BleSender:
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

    def send_message(self, message, uuid_service, characteristic_uuid):
        try:
            servico_gatt = self.device.getServiceByUUID(uuid_service)
            characteristic = servico_gatt.getCharacteristics(characteristic_uuid)[0]
            characteristic.write(bytes(message, "utf-8"))
            print("Message sent succesfully!")
        except Exception as e:
            print("An error occurred while sending the massage:", str(e))
