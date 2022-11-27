#include <Arduino_FreeRTOS.h>

volatile int sharedRes = 0;
void producer(void *arg)
{  
  for(;;)
  { 
    if(sharedRes > 30000){
      sharedRes = 0;
    } 
    else{
      sharedRes++;
    }
  }
      
  vTaskDelete(NULL);
}

void consumer(void *arg)
{
  for(;;)
  { 
    if(sharedRes % 2 != 0){
      delay(10);
      Serial.println(sharedRes);
    } 
  }
      
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(9600);

  xTaskCreate(producer, (const portCHAR *)"producer", 128, NULL, 0, NULL);
  xTaskCreate(consumer, (const portCHAR *)"consumer", 128, NULL, 0, NULL);
}

void loop() {
}
