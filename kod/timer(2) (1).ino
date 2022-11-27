#include <Arduino_FreeRTOS.h>
#include <timers.h>
int led1 = 9, led2 = 12;

TimerHandle_t oneShotHandle, autoReloadHandle;
void oneShotCallBackFunc(TimerHandle_t timerHandle)
{
  static bool togel = 0;
  if(togel == 0){
    digitalWrite(led1, HIGH);
  togel = 1;
  }
  else{
    digitalWrite(led1, LOW);
    togel = 0;
  }    
}

void autoReloadCallBackFunc(TimerHandle_t timerHandle)
{
  static bool togel = 0;
  static int i = 0;
  i++;
  if(i > 5){
    xTimerStart(oneShotHandle, 0);
    i = 0;
  }
  if(togel == 0){
    digitalWrite(led2, HIGH);
  togel = 1;
  }
  else{
    digitalWrite(led2, LOW);
    togel = 0;
  }    
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  
  oneShotHandle = xTimerCreate("OneShot", pdMS_TO_TICKS(500), pdFALSE, NULL, oneShotCallBackFunc );
  autoReloadHandle = xTimerCreate("AutoReload", pdMS_TO_TICKS(500), pdTRUE, NULL, autoReloadCallBackFunc );

  if(oneShotHandle != NULL && autoReloadHandle != NULL){
    xTimerStart(oneShotHandle, 0);
    xTimerStart(autoReloadHandle, 0);
  }
}

void loop() {

}
