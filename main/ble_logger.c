#include "../include/ble_logger.h"

char *TAG = "BLE-Logger";
ble_data_t ble_data;
TimerHandle_t disconnect_timer;

static int device_write(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt,
                        void *arg);
static int device_read(uint16_t con_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt,
                       void *arg);

static void disconnect_timer_callback(TimerHandle_t xTimer);
static void stop_disconnect_timer();
static void start_disconnect_timer();
static int ble_gap_event(struct ble_gap_event *event, void *arg);
static void ble_app_advertise(void);
static void ble_app_on_sync(void);
static void host_task(void *param);
static void set_base_mac_address();

// Array of pointers to other service definitions
// UUID - Universal Unique Identifier
static const struct ble_gatt_svc_def gatt_svcs[] = {
    {.type = BLE_GATT_SVC_TYPE_PRIMARY,
     .uuid = BLE_UUID16_DECLARE(0x180),  // Define UUID for device type
     .characteristics =
         (struct ble_gatt_chr_def[]){{.uuid = BLE_UUID16_DECLARE(0xFEF4),  // Define UUID for reading
                                      .flags = BLE_GATT_CHR_F_READ,
                                      .access_cb = device_read},
                                     {.uuid = BLE_UUID16_DECLARE(0xDEAD),  // Define UUID for writing
                                      .flags = BLE_GATT_CHR_F_WRITE,
                                      .access_cb = device_write},
                                     {0}}},
    {0}};

void ble_update_data(char *data)
{
    strcpy(ble_data.data, data);
    ble_data.size = strlen(ble_data.data);
}

// Write data to ESP32 defined as server
static int device_write(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt,
                        void *arg)
{
    printf("Data from the client: %.*s\n", ctxt->om->om_len, ctxt->om->om_data);
    return 0;
}

// Read data from ESP32 defined as server
static int device_read(uint16_t con_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt,
                       void *arg)
{
    os_mbuf_append(ctxt->om, ble_data.data, ble_data.size);
    return 0;
}

// Timer callback function to handle disconnection after a timeout
static void disconnect_timer_callback(TimerHandle_t xTimer)
{
    ESP_LOGI(TAG, "Disconnecting due to timeout.");
    ble_hs_id_infer_auto(0, &ble_data.ble_addr_type);
    ble_gap_terminate(0, BLE_ERR_REM_USER_CONN_TERM);
}

// Function to start the disconnection timer
static void start_disconnect_timer()
{
    disconnect_timer = xTimerCreate("DisconnectTimer", pdMS_TO_TICKS(DISCONNECT_TIMEOUT_MS), pdFALSE,
                                    (void *)0, disconnect_timer_callback);
    if (disconnect_timer != NULL)
    {
        xTimerStart(disconnect_timer, 0);
    }
}

// Function to stop the disconnection timer
static void stop_disconnect_timer()
{
    if (disconnect_timer != NULL)
    {
        xTimerStop(disconnect_timer, 0);
    }
}

// BLE event handling
static int ble_gap_event(struct ble_gap_event *event, void *arg)
{
    switch (event->type)
    {
        // Advertise if connected
        case BLE_GAP_EVENT_CONNECT:
            ESP_LOGI(TAG, "BLE GAP EVENT CONNECT %s", event->connect.status == 0 ? "OK!" : "FAILED!");

            if (event->connect.status != 0)
            {
                ble_app_advertise();
            }
            else
            {
                // Start the disconnection timer upon successful connection
                start_disconnect_timer();
            }
            break;

        // Advertise again after completion of the event
        case BLE_GAP_EVENT_ADV_COMPLETE:
            ESP_LOGI(TAG, "BLE GAP EVENT");
            ble_app_advertise();
            break;

        // Disconnection event
        case BLE_GAP_EVENT_DISCONNECT:
            ESP_LOGI(TAG, "BLE GAP EVENT DISCONNECT");
            // Stop the disconnection timer upon disconnection
            stop_disconnect_timer();
            // Start advertising again to allow for reconnection
            ble_app_advertise();
            break;

        default:
            break;
    }

    return 0;
}
// Define the BLE connection
static void ble_app_advertise(void)
{
    // GAP - device name definition
    struct ble_hs_adv_fields fields;
    const char *device_name;
    memset(&fields, 0, sizeof(fields));
    device_name = ble_svc_gap_device_name();  // Read the BLE device name
    fields.name = (uint8_t *)device_name;
    fields.name_len = strlen(device_name);
    fields.name_is_complete = 1;
    ble_gap_adv_set_fields(&fields);

    // GAP - device connectivity definition
    struct ble_gap_adv_params adv_params;
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;  // connectable or non-connectable
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;  // discoverable or non-discoverable
    ble_gap_adv_start(ble_data.ble_addr_type, NULL, BLE_HS_FOREVER, &adv_params, ble_gap_event, NULL);
}

// The application
static void ble_app_on_sync(void)
{
    ble_hs_id_infer_auto(0, &ble_data.ble_addr_type);  // Determines the best address type automatically
    ble_app_advertise();                               // Define the BLE connection
}

// The infinite task
static void host_task(void *param)
{
    nimble_port_run();  // This function will return only when nimble_port_stop() is executed
}

static void set_base_mac_address()
{
    uint8_t mac[6] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
    esp_base_mac_addr_set(mac);
}

esp_err_t init_ble_logger()
{
    esp_err_t ret_code = ESP_OK;

    set_base_mac_address();                     // Configurar o endereço MAC base
    esp_nimble_hci_and_controller_init();       // Initialize ESP controller
    nimble_port_init();                         // Initialize the host stack
    ble_svc_gap_device_name_set("Ble-Server");  // Initialize NimBLE configuration - server name
    ble_svc_gap_init();                         // Initialize NimBLE configuration - gap service
    ble_svc_gatt_init();                        // Initialize NimBLE configuration - gatt service
    ble_gatts_count_cfg(gatt_svcs);             // Initialize NimBLE configuration - config gatt services
    ble_gatts_add_svcs(gatt_svcs);              // Initialize NimBLE configuration - queues gatt services.
    ble_hs_cfg.sync_cb = ble_app_on_sync;       // Initialize application
    nimble_port_freertos_init(host_task);       // Run the thread

    return ret_code;
}
