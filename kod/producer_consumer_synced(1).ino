#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t binarySem = NULL;

void task1 (void *arg)
{  
  for(;;)
  { 
    Serial.println(configTICK_RATE_HZ);

   /*to avoid overflow in pdMS_TO_TICKS (defined in projdefs.h) either change configUSE_16_BIT_TICKS (in FreeRTOSConfig.h)to 0 
     * or override pdMS_TO_TICKS in FreeRTOSConfig.h as following:
     * #define pdMS_TO_TICKS( xTimeInMs ) ( ( TickType_t ) ( ( ( unsigned long ) ( xTimeInMs ) * ( TickType_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000 ) )
     * Notice: unsigned long replaces TickType_t
    */
    vTaskDelay(pdMS_TO_TICKS(2000));
    xSemaphoreGive( binarySem );
  }
      
  vTaskDelete(NULL);
}

void task2 (void *arg)
{
  for(;;)
  { 
    xSemaphoreTake( binarySem, portMAX_DELAY );
    Serial.println("Task2 woke up!");
  }
      
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(9600);
  binarySem = xSemaphoreCreateBinary();
  if(binarySem != NULL){
    xTaskCreate(task1, (const portCHAR *)"producer", 128, NULL, 0, NULL);
    xTaskCreate(task2, (const portCHAR *)"consumer", 128, NULL, 0, NULL);
  }
}

void loop() {
}
