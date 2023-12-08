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

typedef struct ble_data
{
    char data[100];
    uint16_t size;
    uint8_t ble_addr_type;
}ble_data_t;
ble_data_t my_ble_data;



void ble_update_data(char *data);
void ble_app_advertise(void);
static int ble_gap_event(struct ble_gap_event *event, void *arg);
void ble_app_advertise(void);
void ble_app_on_sync(void);
void host_task(void *param);
void set_base_mac_address() ;
void test_ble(void *pvParameters);
void init_ble_logger();
void app_main();

#endif