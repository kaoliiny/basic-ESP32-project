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
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "dataQueue.h"

#define TASK_STACK_SIZE (1024)

static xTaskHandle dataQueueUpdate_handle = NULL;
static xTaskHandle displayData_handle = NULL;

void all_tasks_shutdown(void) {
	if (dataQueueUpdate_handle) {
		vTaskDelete(dataQueueUpdate_handle);
		dataQueueUpdate_handle = NULL;
	}

	if (displayData_handle) {
		vTaskDelete(displayData_handle);
		displayData_handle = NULL;
	}
}

void tasks_start_up(void) {
	xTaskCreate(dataQueueUpdate, "put data", TASK_STACK_SIZE, NULL, configMAX_PRIORITIES - 3, &dataQueueUpdate_handle);
	xTaskCreate(displayQueueData, "get data", TASK_STACK_SIZE, NULL, configMAX_PRIORITIES - 3, &displayData_handle);
}

void app_main(void) {
	printf("Hello Guys!\n");
	tasks_start_up();
}
