#include "../include/ble_logger.h"

void test_ble(void *pvParameters) {
    int i = 0;
    char buffer[20];
    while (true) {
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
    xTaskCreate(&test_ble, "test_ble", 2048, NULL, 5, NULL);

}