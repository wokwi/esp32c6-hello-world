#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "esp_chip_info.h"

#define LED_RED GPIO_NUM_9

void app_main(void)
{
  gpio_reset_pin(LED_RED);
  gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);

  printf("Hello, Wokwi!\n");

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  printf("This is %s chip with %d CPU core(s), WiFi%s%s%s\n",
          CONFIG_IDF_TARGET,
          chip_info.cores,
          (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
          (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
          (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

  while (1)
  {
    gpio_set_level(LED_RED, 0);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    gpio_set_level(LED_RED, 1);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
