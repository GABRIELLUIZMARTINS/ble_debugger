#ifndef BLE_LOGGER_H
#define BLE_LOGGER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "nvs_flash.h"
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

#define DISCONNECT_TIMEOUT_MS 12000  // 120000 = 120 seconds

/* Check if the parameter is not NULL */
#define IS_VALID(parameter) ((parameter) != (NULL) ? (true) : (false))

typedef struct ble_data
{
    char data[100];
    uint16_t size;
    uint8_t ble_addr_type;
} ble_data_t;
ble_data_t my_ble_data;

void ble_update_data(char *data);
esp_err_t init_ble_logger();
void app_main();

#endif