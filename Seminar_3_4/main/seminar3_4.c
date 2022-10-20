

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "led_strip.h"
#include <stdio.h>
#include <stdlib.h>
/* Note: ESP32 don't support temperature sensor */

#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32S3
#include "driver/temp_sensor.h"
#define RMT_TX_CHANNEL RMT_CHANNEL_0

static const char *TAG = "TempLedSensor";
static led_strip_t *pStrip_a;

void led_decider(float tsenes_out)
{
	if(tsenes_out < 30.0){
		 ESP_ERROR_CHECK(pStrip_a->set_pixel(pStrip_a, 0, 0, 255, 0));
		 ESP_LOGE(TAG,"Green");
	 }else{
		 ESP_ERROR_CHECK(pStrip_a->set_pixel(pStrip_a, 0, 255, 0, 0));
		 ESP_LOGE(TAG,"Red");
	 }
	pStrip_a->refresh(pStrip_a, 100);
}
void init_led_strip(){

	rmt_config_t config = RMT_DEFAULT_CONFIG_TX(18, RMT_TX_CHANNEL);
	// set counter clock to 40MHz
	config.clk_div = 2;

	ESP_ERROR_CHECK(rmt_config(&config));
	ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

	// install ws2812 driver
	led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(24, (led_strip_dev_t)config.channel);
	pStrip_a = led_strip_new_rmt_ws2812(&strip_config);
	if (!pStrip_a) {
	    ESP_LOGE(TAG, "install WS2812 driver failed");
	 }
	 // Clear LED strip (turn off all LEDs)
	 ESP_ERROR_CHECK(pStrip_a->clear(pStrip_a, 100));
}
void tempsensor_example(void *arg)
{
	// Initialize touch pad peripheral, it will start a timer to run a filter
    ESP_LOGI(TAG, "Initializing Temperature sensor");
    float tsens_out;
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor_get_config(&temp_sensor);
    ESP_LOGI(TAG, "default dac %d, clk_div %d", temp_sensor.dac_offset, temp_sensor.clk_div);
    temp_sensor.dac_offset = TSENS_DAC_DEFAULT; // DEFAULT: range:-10℃ ~  80℃, error < 1℃.
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
    ESP_LOGI(TAG, "Temperature sensor started");
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        temp_sensor_read_celsius(&tsens_out);
        ESP_LOGI(TAG, "Temperature out celsius %fC", tsens_out);
        led_decider(tsens_out);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
	init_led_strip();
    xTaskCreate(tempsensor_example, "temp", 2048, NULL, 5, NULL);
}

#elif CONFIG_IDF_TARGET_ESP32

void app_main(void)
{
    printf("ESP32 don't support temperature sensor\n");
}

#endif
