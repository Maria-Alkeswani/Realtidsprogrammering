#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t mutex1 = NULL;
volatile int sharedRes = 0;
void producer(void *arg)
{  
  for(;;)
  { 
    xSemaphoreTake(mutex1, portMAX_DELAY);
    if(sharedRes > 30000){
      sharedRes = 0;
    } 
    else{
      sharedRes++;
    }
    xSemaphoreGive(mutex1);

    vTaskDelay(pdMS_TO_TICKS(1));
  }
      
  vTaskDelete(NULL);
}

void consumer(void *arg)
{
  for(;;)
  { 
    xSemaphoreTake(mutex1, portMAX_DELAY);
    if(sharedRes % 2 != 0){
      //delay(10);
      Serial.println(sharedRes);
    } 
    xSemaphoreGive(mutex1);
    
    vTaskDelay(pdMS_TO_TICKS(1));
  }
      
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(9600);
  mutex1 = xSemaphoreCreateMutex();
  if(mutex1 != NULL){
    xTaskCreate(producer, (const portCHAR *)"producer", 128, NULL, 0, NULL);
    xTaskCreate(consumer, (const portCHAR *)"consumer", 128, NULL, 0, NULL);
  }
}

void loop() {
}
