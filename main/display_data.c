
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
	printf("time between receipts in the message queue: %ld sec\n\n", message->time_stamp / CLOCKS_PER_SEC);
}

void displayQueueData(void *data) {
	message_t *msg_queue = NULL;
	queue_ctx *q_data = NULL;
	if (data) {
		q_data = (queue_ctx *)data;
	}

	/* Nothig to receive yet */
	vTaskDelay(DELAY_MS * 5 / portTICK_PERIOD_MS);

	while (1) {
		if (uxQueueMessagesWaiting(counter_queue_handle) > 0) {
			if (xQueueReceive(counter_queue_handle, (void *)&msg_queue, (TickType_t)0) != pdPASS) {
				ESP_LOGW(QUEUE_TAG, "Queue receive error!");
			} else {
				if (q_data && q_data->print_cb) {
					q_data->print_cb(msg_queue);
				}
			}
		}
		vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
	}
}
