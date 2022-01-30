
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dataQueue.h"

void displayQueueData(void *cb) {
	while (1) {
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}
