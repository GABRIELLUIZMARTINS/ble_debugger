#include "ble_logger.h"
#include "nvs_flash.h"

void example_ble(void *pvParameters) {
    int i = 0;
    char buffer[20];

    for(;;)
    {
        sprintf(buffer, "%d", i++);
        printf("Tarefa em execução: %s\n",buffer);
        ble_update_data(buffer);

        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}

void app_main()
{
    nvs_flash_init();                                               // 1 - Initialize NVS flash 
    init_ble_server();                                              // 2 - Initialize BLE server
    xTaskCreate(&example_ble, "Example BLE", 2048, NULL, 5, NULL);  // 3 - Create task example
}
