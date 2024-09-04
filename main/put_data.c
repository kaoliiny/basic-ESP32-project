
#include <stdio.h>
#include <time.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "data_queue.h"

/* 5s = 5000ms */
#define DELAY_MS    5000

static time_t time_stamp_prev;

void dataQueueUpdate(void *data) {
	message_t msg_queue = {0};
	message_t *msg = &msg_queue;

	while (1) {
		if (uxQueueSpacesAvailable(counter_queue_handle) > 0) {
			/* Don't update counter and time_stamp when the queue is already full. */
			msg->counter++;
			if (msg->counter < 0) {
				msg->counter = 0;
			}
			msg->time_stamp = clock() - time_stamp_prev;
			time_stamp_prev += msg->time_stamp;

			/* Don't block if the queue is already full. */
			if (xQueueSend(counter_queue_handle, (void *)&msg, (TickType_t)0) != pdPASS) {
				ESP_LOGW(QUEUE_TAG, "Queue send error!");
			}
		}
		/* (￣o￣) zzZzzZ */
		vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
	}
}
