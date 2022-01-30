
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dataQueue.h"

/* 5s = 5000ms */
#define DELAY_MS    5000

void dataQueueUpdate(void *cb) {
	while (1) {
		vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
	}
}
