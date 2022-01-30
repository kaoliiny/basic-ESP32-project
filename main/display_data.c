
#include <stdio.h>
#include <time.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "data_queue.h"

/* 1s = 1000ms */
#define DELAY_MS    1000

void print_queue_data(message_t *message) {
	if (message == NULL) {
		return ;
	}

	printf("counter value: %d\n", message->counter);
	printf("timestamp: %s\n", ctime((const long int *)&message->time_stamp));
}

void displayQueueData(void *data) {
	message_t *msg_queue = NULL;

	/* Nothig to receiv yet */
	vTaskDelay(DELAY_MS * 5 / portTICK_PERIOD_MS);

	while (1) {
		if (xQueueReceive(counter_queue_handle, (void *)&msg_queue, (TickType_t)0) != pdPASS) {
			ESP_LOGW(QUEUE_TAG, "Queue receive error!");
		} else {
			print_queue_data(msg_queue);
		}
		vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
	}
}
