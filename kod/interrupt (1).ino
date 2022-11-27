#include <Arduino_FreeRTOS.h>
#include <queue.h>

int intr1Pin = 2, intr2Pin = 3, led1 = 9, led2 = 12;
volatile int toggel1 = 0, toggel2 = 0;
QueueHandle_t queue;

void ISR1(void)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE; 
  volatile int16_t msg = 1;
  xQueueSendToBackFromISR( queue, &msg, &xHigherPriorityTaskWoken );
}

void ISR2(void)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE; 
  volatile int16_t msg = 2;
  xQueueSendToBackFromISR( queue, &msg, &xHigherPriorityTaskWoken );
}

void handlerTask(void *pvParameters)
{
  BaseType_t xStatus;
  int16_t msg;
  for (;; )
    {
      xStatus = xQueueReceive(queue, &msg, portMAX_DELAY);
  
      if (xStatus == pdPASS){
        Serial.println("I'm awake!");
      }

      if(msg == 1){
        if(toggel1 == 0){
          digitalWrite(led1, HIGH);
          toggel1 = 1;
        }
        else{
          digitalWrite(led1, LOW);
          toggel1 = 0;
        }
      }
      else if (msg == 2){
        if(toggel2 == 0){
          digitalWrite(led2, HIGH);
          toggel2 = 1;
        }
        else{
          digitalWrite(led2, LOW);
          toggel2 = 0;
        }
      }
    }
}

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(intr1Pin, INPUT_PULLUP);
  pinMode(intr2Pin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(intr1Pin), ISR1, RISING);
  attachInterrupt(digitalPinToInterrupt(intr2Pin), ISR2, RISING);
  
  queue = xQueueCreate(5, sizeof(int16_t));
  if (queue != NULL) {
      xTaskCreate(handlerTask, "Handler Task", 256, NULL, 0, NULL);      
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
