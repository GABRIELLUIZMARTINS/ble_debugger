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

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    nvs_flash_init();                               // 1 - Initialize NVS flash using
    init_ble_logger();
    xTaskCreate(&example_ble, "example_ble", 2048, NULL, 5, NULL);
}