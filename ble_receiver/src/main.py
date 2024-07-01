from ble_receiver import BleReceiver

# MAC address of the BLE device
mac_address = "12:34:56:78:9A:BE"

# UUID of the desired GATT service
uuid_service = 0x180

# UUID of the desired characteristic
characteristic_uuid_send = 0xDEAD
characteristic_uuid_received = 0xFEF4

if __name__ == "__main__":

    # Creating a class BleReceiver instance 
    receiver_ble = BleReceiver(mac_address)

    # Connecting to BLE device
    receiver_ble.connect()

    # Receiving messages
    while True:
        try:
            received_message = receiver_ble.receive_message(uuid_service, characteristic_uuid_received)
            if received_message is None:
                raise Exception("Received message is None")
            print("Received message: ", received_message)
        except Exception as e:
            print("An error occurred while receiving the message:", str(e))
            receiver_ble.disconnect()
            receiver_ble.connect()

    # Desconectando do device
    receiver_ble.disconnect()
