//The second exam:
#include <FreeRTOS.h>
#include <Task.h>
#include <semp.h>

int desired = 25;
int temp=0;

SemaphoreHandle_t mutex1, mutex2; 


void setup(){
   serial.begin(9600);
   mutex1= xSemaphoreCreateMutex();
   mutex2= xSemaphoreCreateMutex();
   xTaskCreat(task_1, "T1",128,NULL,0,NULL);
   xTaskCreat(task_2, "T2",128,NULL,0,NULL);
   xTaskCreat(task_3, "T3",128,NULL,0,NULL);

}

void task_1(){

  while(1){
    xSemaphoreTake(mutex1,portMaxDelay);
    desired = receiveDesired();
    xSemaphoreGive(mutes1);
   vTaskDelay(pdMS_TO_TICKS(30000));
  }

}

void task_2(){

  while(1){
    xSemaphoreTake(mutex2,portMaxDelay);
    temp = readTemperature(); 
    xSemaphoreGive(mutes2);
    vTaskDelay(pdMS_TO_TICKS(6000)); 
  }


}

void task_3(){

  while(1){
    xSemaphoreTake(mutex1,maxporttime);
   xSemaphoreTake(mutex2,maxporttime);
    if (temp > desired+2 )
      turnCooler(1);
      turnHeater(0);
    else if (temp < desired-2 )
      turnCooler(0);
      turnHeater(1);    
    else (){
      turnCooler(0);
      turnHeater(0);
    }
   xSemaphoreGive(mutes1);
   xSemaphoreGive(mutes2);
   vTaskDelay(pdMS_TO_TICKS(5000));
  }


}

void loop(){

}

//The second exam:

#include <FreeRTOS.h>
#include <Task.h>
#include <semp.h>

int fire = 0;
int motion = 0;
int door = 0;

SemaphoreHandle_t mutex1, mutex2, mutex3;

void setup(){
  serial.begin(9600);

  mutex1=xSemaphoreCreateMutex();
  mutex2=xSemaphoreCreateMutex();
  mutex3=xSemaphoreCreateMutex();

  xTaskCreate(t1, "task_1",128, NULL, 0,NULL)
  xTaskCreate(t2, "task_2",128, NULL, 0,NULL)
  xTaskCreate(t3, "task_3",128, NULL, 0,NULL)
  xTaskCreate(t4, "task_4",128, NULL, 0,NULL)

}

void t1(){

  while(1){

   xSemaphoreTake(mutex1,portMaxDelay);
   if (fireSignal())
    fire = 1
    else 
    fire = 0
   xSemaphoreGive(mutes1);  
   

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
void t2(){

  while(1){

    xSemaphoreTake(mutex2,portMaxDelay);
   if (motionSignal())
    motion = 1
    else 
    motion = 0
   xSemaphoreGive(mutes2);  

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
void t3(){

  while(1){
   xSemaphoreTake(mutex3,portMaxDelay);
   if (doorSignal)
    door = 1
    else 
    door = 0
  
   xSemaphoreGive(mutes3);
    vTaskDelay(pdMS_TO_TICKS(400));
  }
}
void t4(){

  while(1){
  xSemaphoreTake(mutex1,portMaxDelay);
  xSemaphoreTake(mutex2,portMaxDelay);
  xSemaphoreTake(mutex3,portMaxDelay);

if( fire == 1 || motion == 1 || door==1)
 sendMessage(fire,motion,door)

 xSemaphoreGive(mutes1);
 xSemaphoreGive(mutes2);
 xSemaphoreGive(mutes3);

  vTaskDelay(pdMS_TO_TICKS(5000));
  }
}
void loop (){

}


//Task with parameter to print task2 every 4 second

void setup(){
 serial.begin(9600);
 vTaskCreate(task1,"t1",128,NULL,0,NULL);
}

void task1(void *param){
   const char *out = "task1\n";

   for (;;)
   serial.println(out);
    vTaskDelay(pdMS_TO_TICKS(4000));

}

//OR

void setup(){
 serial.begin(9600);
 vTaskCreate(task1,"t1",128,(void*)"task1\n",0,NULL);
}

void task1(void *param){
   const char *out = (const char * ) param;

   for (;;)
   serial.println(out);
    vTaskDelay(pdMS_TO_TICKS(4000));

}
void loop() {

}

// We need the task handle to delet the task 

TaskHandle_t task2Handle;
BaseType_t task2Deleted = pdFALSE; 

void task1(void *param)
{
  const char *out = "Task1 is running\n";
  uint32_t i = 0;
  for(;;)
  {
    Serial.print(out);
    vTaskDelay(pdMS_TO_TICKS(400));
    if (i++ > 10 && !task2Deleted)
    {
      vTaskDelete(task2Handle);
      task2Deleted = pdTRUE;
    }
  } 
  vTaskDelete(NULL);  
}

void task2(void *param)
{
  const char *out = "Task2 is running\n";
  uint32_t i;
  for(;;)
  {
    Serial.print(out);
    vTaskDelay(pdMS_TO_TICKS(400));
  }   
}

void setup() {

  Serial.begin(9600);
  xTaskCreate(task1, "T1", 128, NULL, 0, NULL);
  xTaskCreate(task2, "T2", 128, NULL, 0, &task2Handle);
}

void loop() {

}
