#include "freertos/queue.h"

typedef struct {
    int counter;
    time_t time_stamp;
} __attribute__((packed)) message_t;

typedef struct {
    void (*print_cb)(message_t *message);
} __attribute__((packed)) queue_ctx;

extern xQueueHandle counter_queue_handle;

#define QUEUE_SIZE (12)
#define QUEUE_TAG "QUEUE WARN" 

void dataQueueUpdate(void *ctx);
void displayQueueData(void *data);
void print_queue_data(message_t *message);
