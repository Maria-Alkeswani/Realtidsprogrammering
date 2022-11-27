
#include "Arduino_FreeRTOS.h"
#include "queue.h"


void sender(void *pvParameters);
void receiver(void *pvParameters);
QueueHandle_t qu;

void setup() {
  Serial.begin(9600);
  qu = xQueueCreate(5, sizeof(int16_t));
  if (qu != NULL) {
      xTaskCreate(sender, "Sender 1", 128, (void *)1, 0, NULL);
      xTaskCreate(sender, "Sender 2", 128, (void *)2, 0, NULL);
      xTaskCreate(receiver, "Receiver", 128, NULL, 1, NULL);
  }
}

void sender(void *pvParameters)
{
    volatile int16_t msg = (int16_t) pvParameters;
    BaseType_t xStatus;

    for (;; )
    {
        xStatus = xQueueSendToBack(qu, &msg, 0);

        if (xStatus != pdPASS){
            Serial.println("Could not send to the queue.");
        }
    }
}
/*-----------------------------------------------------------*/

void receiver(void *pvParameters)
{
    int16_t msg;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100UL);

    for (;; )
    {
        if (uxQueueMessagesWaiting(qu) != 0)
        {
            Serial.println("Queue should have been empty!");
        }

        xStatus = xQueueReceive(qu, &msg, xTicksToWait);

        if (xStatus == pdPASS)
        {
            Serial.println(msg);
        }
        else
        {
            Serial.println("Could not receive from the queue.");
        }
    }
}

void loop() {
 
}
