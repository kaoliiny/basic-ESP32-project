/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spi_flash.h"
#include "esp_log.h"
#include "data_queue.h"

#define TASK_STACK_SIZE 2048

static xTaskHandle dataQueueUpdate_handle = NULL;
static xTaskHandle displayData_handle = NULL;
static queue_ctx q_data = {0}; 

xQueueHandle counter_queue_handle = NULL;

void shutdown(void) {
	if (dataQueueUpdate_handle) {
		vTaskDelete(dataQueueUpdate_handle);
		dataQueueUpdate_handle = NULL;
	}

	if (displayData_handle) {
		vTaskDelete(displayData_handle);
		displayData_handle = NULL;
	}

	if (counter_queue_handle) {
        vQueueDelete(counter_queue_handle);
        counter_queue_handle = NULL;
    }
}

void tasks_start_up(void) {
	q_data.print_cb = print_queue_data;

	xTaskCreate(dataQueueUpdate, "put data", TASK_STACK_SIZE, NULL, configMAX_PRIORITIES - 3, &dataQueueUpdate_handle);
	xTaskCreate(displayQueueData, "get data", TASK_STACK_SIZE, (void *)&q_data, configMAX_PRIORITIES - 3, &displayData_handle);
}

int counter_queue_init(void) {
	counter_queue_handle = xQueueCreate(QUEUE_SIZE, sizeof(message_t *));
	if (counter_queue_handle == NULL) {
		ESP_LOGE(QUEUE_TAG, "Queue init error!");
		return -1;
	}
	return 0;
}

void app_main(void) {
	printf("Hello Guys!\n");

	if (!counter_queue_init()) {
		tasks_start_up();
		while(1) {
			vTaskDelay(500 / portTICK_PERIOD_MS);
		}
		shutdown();
	}
}
