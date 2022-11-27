#include <FreeRTOS.h>
#include <Task.h>
#include <semp.h>

int temp=25;
int des=25;

SemaphoreHandle_t mutex1,mutex2;

void setup(){

    serial.begin(9600);

    mutex1= xSemaphoreCreateMutex(  ); 
    mutex2= xSemaphoreCreateMutex(); 

    xTaskCreate(task1,"t1",128,NULL,0,NULL);
    xTaskCreate(task2,"t2",128,NULL,0,NULL);
    xTaskCreate(task3,"t3",128,NULL,0,NULL);        
}

void task1(){

  while(1){
      
    vTaskDelay(pdMS_TO_TICKS(30000));

  }
}


void task2(){

   vTaskDelay(pdMS_TO_TICKS(6000));
}


void task3(){

    vTaskDelay(pdMS_TO_TICKS(5000));
}



void loop(){


}
