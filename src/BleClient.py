from bluepy import btle
from time import sleep

class BLEClient:
    def __init__(self, mac_address):
        self.mac_address = mac_address
        self.dispositivo = None

    def connect(self):
        try:
            self.dispositivo = btle.Peripheral(self.mac_address)
            print("Conectado ao dispositivo BLE com sucesso!")
        except Exception as e:
            print("Ocorreu um erro ao conectar ao dispositivo:", str(e))

    def disconnect(self):
        try:
            self.dispositivo.disconnect()
            print("Desconectado do dispositivo BLE com sucesso!")
        except Exception as e:
            print("Ocorreu um erro ao desconectar do dispositivo:", str(e))

    def send_message(self, mensagem, servico_uuid, caracteristica_uuid):
        try:
            servico_gatt = self.dispositivo.getServiceByUUID(servico_uuid)
            caracteristica = servico_gatt.getCharacteristics(caracteristica_uuid)[0]
            caracteristica.write(bytes(mensagem, "utf-8"))
            print("Mensagem enviada com sucesso!")
        except Exception as e:
            print("Ocorreu um erro ao enviar a mensagem:", str(e))

    def receive_message(self, servico_uuid, caracteristica_uuid):
        try:
            servico_gatt = self.dispositivo.getServiceByUUID(servico_uuid)
            caracteristica = servico_gatt.getCharacteristics(caracteristica_uuid)[0]
            data = caracteristica.read()
            mensagem = data.decode("utf-8")
            print("Mensagem recebida:", mensagem)
            return mensagem
        except Exception as e:
            print("Ocorreu um erro ao receber a mensagem:", str(e))
            return None
