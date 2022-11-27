#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <timers.h>
TimerHandle_t autoReloadHandle1, autoReloadHandle2;
int button=2;
bool flag = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  autoReloadHandle1 = xTimerCreate("timer1", pdMS_TO_TICKS(500), pdTRUE, NULL, pattern1 ); //Once started, the call back function will execute periodically
  autoReloadHandle2 = xTimerCreate("timer2", pdMS_TO_TICKS(500), pdTRUE, NULL, pattern2 );
                                // Name, The timers period in ticks, pdTRUE will create an auto‐reload timer, NULL, The name of the call‐back function
  xTimerStart(autoReloadHandle1, 0);
  xTimerStart(autoReloadHandle2, 0);
             //The handle of the timer.0 is the time that the caller task may block on full timer command queue.
  attachInterrupt(digitalPinToInterrupt(button), ISR_, RISING);
  //digitalPinToInterrupt() converts a digital pin number to an interrupt number
  // ISR: Interrupt service routine where the interrupt is handled.
 //mode: LOW, CHANGE, RISING, FALLING
  
}

void ISR_()//Interrupt Service Routine (ISR)
{
  if(flag == 0)
  {
    xTimerStop(autoReloadHandle2, portMAX_DELAY);
    xTimerReset(autoReloadHandle1, portMAX_DELAY);
               //The handle of the timer, portMAX_DELAY): The time that the caller task may block on full command queue.
    flag = 1;
  }
  else
  {
    xTimerStop(autoReloadHandle1, portMAX_DELAY);
    xTimerReset(autoReloadHandle2, portMAX_DELAY);
    flag = 0;
  }
}

void pattern1(TimerHandle_t timerHandle)
{
  while(1)
  {
    for(int i = 5; i < 13; i++)
    {
       digitalWrite(i, HIGH);
       delay(100);
       digitalWrite(i+1, HIGH);
       digitalWrite(i, LOW);
    }
    
    for(int i = 11; i > 5; i--)
    {
       digitalWrite(i, HIGH);
       delay(100);
       digitalWrite(i-1, HIGH);
       digitalWrite(i, LOW);
    }

  }
}

void pattern2(TimerHandle_t timerHandle)
{
  while(1)
  {
    for(int i= 5; i < 9; i++)
    {
      digitalWrite(i, HIGH);
      digitalWrite(17-i, HIGH);
      delay(100);
      digitalWrite(i+1, HIGH);
      digitalWrite(17-i-1, HIGH);
      digitalWrite(i, LOW);
      digitalWrite(17-i, LOW);
    }
    for(int i= 7; i > 5; i--)
    {
      digitalWrite(i, HIGH);
      digitalWrite(17-i, HIGH);
      delay(100);
      digitalWrite(i-1, HIGH);
      digitalWrite(17-i+1, HIGH);
      digitalWrite(i, LOW);
      digitalWrite(17-i, LOW);
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
