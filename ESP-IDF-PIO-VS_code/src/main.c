#include <stdio.h>
#include <stdbool.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <esp_system.h>
#include <esp_event.h>
#include <esp_log.h>
#include <nvs_flash.h>

//#include <freertos/event_groups.h>
#include "esp_rom_gpio.h"

#include "onewire_bus.h"
#include "ds18b20.h"

static const char *TAG = "example";

#define EXAMPLE_ONEWIRE_BUS_GPIO    2
#define EXAMPLE_ONEWIRE_MAX_DS18B20 8

static const bool chatty = true;

// LED ========================================

static const gpio_num_t blink_led = GPIO_NUM_2;

void setup_LED(gpio_num_t gpio)
{
    esp_rom_gpio_pad_select_gpio(gpio);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(gpio, GPIO_MODE_OUTPUT);
}
void blink_led_task(void *param)
{
    setup_LED(blink_led);

    while (1)
    {
        /* Blink off (output low) */
        if (chatty)
            printf("Turning off the LED\n");
        gpio_set_level(blink_led, 0);
        vTaskDelay(995 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
        if (chatty)
            printf("Turning on the LED\n");
        gpio_set_level(blink_led, 1);
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // Note: 512 is insufficient stack for blink_led_task
    xTaskCreate(&blink_led_task, "blink_led_task", 1024, NULL, 5, NULL);
    while(true)
    {
        if (chatty)
            printf("hello world\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}