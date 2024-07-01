#ifndef BLE_LOGGER_H
#define BLE_LOGGER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_nimble_hci.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_eth.h"
#include "esp_netif.h"
#include "freertos/timers.h"

/* Check if the parameter is not NULL */
#define IS_VALID(parameter) ((parameter) != (NULL) ? (true) : (false))

typedef struct ble_data
{
    char data[CONFIG_DATA_BUFFER_SIZE];
    uint16_t size;
    uint8_t ble_addr_type;
} ble_data_t;

void ble_update_data(char *data);
esp_err_t init_ble_server();

#endif
