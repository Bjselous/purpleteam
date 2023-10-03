#include <Arduino.h>
#include <ESP32Servo.h>
#include "purpleconstants.h"

int _turret_elevation_postion = 90;
int _turret_traverse_postion = 90;
Servo elevation_servo;
Servo traverse_servo;
TaskHandle_t _elevate_turret_task;
TaskHandle_t _traverse_turret_task;

void handleForward()
{ 
  digitalWrite(MD_ENABLE, HIGH);
  //digitalWrite(MD_IN_1, HIGH);
  //digitalWrite(MD_IN_2, LOW);
  digitalWrite(MD_IN_3, HIGH);
  digitalWrite(MD_IN_4, LOW);
  Serial.println("Forward");
}

void handleReverse()
{
  digitalWrite(MD_ENABLE, HIGH);
  //digitalWrite(MD_IN_1, LOW);
  //digitalWrite(MD_IN_2, HIGH);
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, HIGH);
  Serial.println("Reverse");
}

void handleStopAcceleration()
{
  //digitalWrite(MD_IN_1, LOW);
  //digitalWrite(MD_IN_2, LOW);
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, LOW);
  digitalWrite(MD_ENABLE, LOW);
  Serial.println("Stop Acceleration");
}

void elevateTurret(void* pvParameters)
{
  while(_turret_elevation_postion < 170)
   {    
    elevation_servo.write(_turret_elevation_postion+1);
    delay(20);
    _turret_elevation_postion++;
    Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
   }
    _elevate_turret_task = NULL;
   vTaskDelete(NULL);
}

void depressTurret(void* pvParameters)
{
  while(_turret_elevation_postion > 10)
   {
    elevation_servo.write(_turret_elevation_postion-1);
    delay(20);
    _turret_elevation_postion--;
    Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
   }
   _elevate_turret_task = NULL;
   vTaskDelete(NULL);
}

void handleElevateTurret()
{
   xTaskCreatePinnedToCore(
                    elevateTurret,   /* Task function. */
                    "ElevateTurretTasks",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_elevate_turret_task,      /* Task handle to keep track of created task */
                    0); 
  Serial.println("Elevate Turret");
}

void handleDepressTurret()
{     
    xTaskCreatePinnedToCore(
                    depressTurret,   /* Task function. */
                    "DepressTurretTasks",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_elevate_turret_task,      /* Task handle to keep track of created task */
                    0); 
    Serial.println("Depress Turret");
}

void handleStopTurretElevationChange()
{
   if(_elevate_turret_task != NULL) 
   {
    vTaskDelete(_elevate_turret_task);
   }
  Serial.println("Stop Turret Elevation Change");
}

void traverseTurretClockwise(void* pvParameters)
{
  while(_turret_traverse_postion < 170)
   {    
    traverse_servo.write(_turret_traverse_postion+1);
    delay(20);
    _turret_traverse_postion++;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
   }
    _traverse_turret_task = NULL;
   vTaskDelete(NULL);
}

void traverseTurretAntiClockwise(void* pvParameters)
{
  while(_turret_traverse_postion > 10)
   {
    traverse_servo.write(_turret_traverse_postion-1);
    delay(20);
    _turret_traverse_postion--;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
   }
   _traverse_turret_task = NULL;
   vTaskDelete(NULL);
}

void handleTraverseTurretAnticlockwise()
{
   xTaskCreatePinnedToCore(
                    traverseTurretClockwise,   /* Task function. */
                    "TraverseTurretTask",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_traverse_turret_task,      /* Task handle to keep track of created task */
                    0); 
  Serial.println("Traverse Turret Anticlockwise");
}

void handleTraverseTurretClockwise()
{
  xTaskCreatePinnedToCore(
                    traverseTurretAntiClockwise,   /* Task function. */
                    "TraverseTurretTask",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_traverse_turret_task,      /* Task handle to keep track of created task */
                    0); 
  Serial.println("Traverse Turret Clockwise");
}

void handleStopTurretTraverseChange()
{
  if(_traverse_turret_task != NULL) 
   {
    vTaskDelete(_traverse_turret_task);
   }
  Serial.println("Stop Turret Traverse Change");
}

void handleLinearActuatorUp()
{  
  digitalWrite(LA_ENABLE, HIGH);
  digitalWrite(LA_IN_1, LOW);
  digitalWrite(LA_IN_2, HIGH);
  Serial.println("Linear Actuator Up");
}

void handleLinearActuatorDown()
{ 
  digitalWrite(LA_ENABLE, HIGH);
  digitalWrite(LA_IN_1, HIGH);
  digitalWrite(LA_IN_2, LOW);
  Serial.println("Linear Actuator Down");
}

void handleLinearActuatorStop()
{
  digitalWrite(LA_IN_1, LOW);
  digitalWrite(LA_IN_2, LOW);
  digitalWrite(LA_ENABLE, LOW);
  Serial.println("Linear Actuator Stop");
}

void handleWaterStart()
{
  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);
  //digitalWrite(WATER_RELAY_PIN, HIGH);
  Serial.println("Water Start");
}

void handleWaterStop()
{
  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);
  //digitalWrite(WATER_RELAY_PIN, LOW);
  Serial.println("Water Stop");
}

void handleStopAll()
{
    handleStopAcceleration();
    handleStopTurretElevationChange();
    handleStopTurretTraverseChange();
    handleWaterStop();
    handleLinearActuatorStop();
}