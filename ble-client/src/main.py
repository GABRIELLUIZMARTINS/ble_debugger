from BleClient import BLEClient

# Endereço MAC do dispositivo BLE
mac_address = "12:34:56:78:9A:BE"

# UUID do serviço GATT desejado
servico_uuid = 0x180

# UUID da característica desejada
caracteristica_uuid_send = 0xDEAD
caracteristica_uuid_received = 0xFEF4

if __name__ == "__main__":

    # Criando uma instância da classe BLEClient
    cliente_ble = BLEClient(mac_address)

    # Conectando ao dispositivo BLE
    cliente_ble.connect()

    # Enviando a mensagem
    #mensagem_enviada = "Comunicação com Servidor estabelecida."
    #cliente_ble.send_message(mensagem_enviada, servico_uuid, caracteristica_uuid_send)

    # Recebendo a mensagem
    while True:
        try:
            mensagem_recebida = cliente_ble.receive_message(servico_uuid, caracteristica_uuid_received)
            if mensagem_recebida is None:
                raise Exception("Mensagem recebida é None")
            print("Mensagem recebida:", mensagem_recebida)
        except Exception as e:
            print("Ocorreu um erro ao receber a mensagem:", str(e))
            cliente_ble.disconnect()
            cliente_ble.connect()

    # Desconectando do dispositivo
    cliente_ble.disconnect()
