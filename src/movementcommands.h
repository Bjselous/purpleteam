#include <Arduino.h>
#include <ESP32Servo.h>
#include "purpleconstants.h"

int _turret_elevation_postion = 90;
int _turret_traverse_postion = 90;
bool _can_traverse = false;
bool _can_elevate = false;
Servo elevation_servo;
Servo traverse_servo;
TaskHandle_t _elevate_turret_task;
TaskHandle_t _traverse_turret_task;

void handleForward()
{ 
  digitalWrite(MD_ENABLE, HIGH);
  digitalWrite(MD_IN_3, HIGH);
  digitalWrite(MD_IN_4, LOW);
  Serial.println("Forward");
}

void handleCreepForward()
{ 
  digitalWrite(MD_ENABLE, HIGH);
  digitalWrite(MD_IN_3, HIGH);
  digitalWrite(MD_IN_4, LOW);
  Serial.println("Creep Forward");
}

void handleReverse()
{
  digitalWrite(MD_ENABLE, HIGH);
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, HIGH);
  Serial.println("Reverse");
}

void handleCreepReverse()
{
  digitalWrite(MD_ENABLE, HIGH);
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, HIGH);
  Serial.println("Creep Reverse");
}

void handleStopAcceleration()
{
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, LOW);
  digitalWrite(MD_ENABLE, LOW);
  Serial.println("Stop Acceleration");
}

void elevateTurret(void* pvParameters)
{
  while(_turret_elevation_postion < 170)
   {    
    if(_can_elevate)
    {
      elevation_servo.write(_turret_elevation_postion+1);
      _turret_elevation_postion++;
      Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
    }
    delay(20);
   }
    _elevate_turret_task = NULL;
   vTaskDelete(NULL);
}

void slowElevateTurret(void* pvParameters)
{
  while(_turret_elevation_postion < 170)
   {    
    if(_can_elevate)
      {
      elevation_servo.write(_turret_elevation_postion+1);
      _turret_elevation_postion++;
      Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
      }
    delay(200);
   }
    _elevate_turret_task = NULL;
   vTaskDelete(NULL);
}

void depressTurret(void* pvParameters)
{
  while(_turret_elevation_postion > 10)
   {
    if(_can_elevate)
    {
    elevation_servo.write(_turret_elevation_postion-1);
    _turret_elevation_postion--;
    Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
    }
    delay(20);
   }
   _elevate_turret_task = NULL;
   vTaskDelete(NULL);
}

void slowDepressTurret(void* pvParameters)
{
  while(_turret_elevation_postion > 10)
   {
    if(_can_elevate)
    {
    elevation_servo.write(_turret_elevation_postion-1);
    _turret_elevation_postion--;
    Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
    }
    delay(200);
   }
   _elevate_turret_task = NULL;
   vTaskDelete(NULL);
}

void handleElevateTurret()
{ 
  _can_elevate = true;

   xTaskCreatePinnedToCore(
                    elevateTurret,   /* Task function. */
                    "ElevateTurretTasks",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    3,           /* priority of the task */
                    &_elevate_turret_task,      /* Task handle to keep track of created task */
                    1); 
  Serial.println("Elevate Turret");
}

void handleSlowElevateTurret()
{
   _can_elevate = true;

   xTaskCreatePinnedToCore(
                    slowElevateTurret,   /* Task function. */
                    "SlowElevateTurretTasks",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_elevate_turret_task,      /* Task handle to keep track of created task */
                    1); 
  Serial.println("Slow Elevate Turret");
}

void handleDepressTurret()
{     
    _can_elevate = true;

    xTaskCreatePinnedToCore(
                    depressTurret,   /* Task function. */
                    "DepressTurretTasks",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    3,           /* priority of the task */
                    &_elevate_turret_task,      /* Task handle to keep track of created task */
                    1); 
    Serial.println("Depress Turret");
}

void handleSlowDepressTurret()
{   
    _can_elevate = true;

    xTaskCreatePinnedToCore(
                    slowDepressTurret,   /* Task function. */
                    "SlowDepressTurretTasks",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_elevate_turret_task,      /* Task handle to keep track of created task */
                    1); 
    Serial.println("Slow Depress Turret");
}

void handleStopTurretElevationChange()
{
  _can_elevate = false;

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
    if(_can_traverse)
    {
    traverse_servo.write(_turret_traverse_postion+1);    
    _turret_traverse_postion++;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
    delay(10);
   }
    
    _traverse_turret_task = NULL;
    vTaskDelete(NULL);  
}

void slowTraverseTurretClockwise(void* pvParameters)
{
  while(_turret_traverse_postion < 170)
   {    
    if(_can_traverse)
    {
    traverse_servo.write(_turret_traverse_postion+1);    
    _turret_traverse_postion++;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
    delay(200);
   }
    
    _traverse_turret_task = NULL;
    vTaskDelete(NULL);  
}

void traverseTurretAntiClockwise(void* pvParameters)
{
  while(_turret_traverse_postion > 10)
   {
    if(_can_traverse)
    {
    traverse_servo.write(_turret_traverse_postion-1);
    _turret_traverse_postion--;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
    delay(10);
   }

   _traverse_turret_task = NULL;   
   vTaskDelete(NULL);   
}

void slowTraverseTurretAntiClockwise(void* pvParameters)
{
  while(_turret_traverse_postion > 10)
   {
    if(_can_traverse)
    {
    traverse_servo.write(_turret_traverse_postion-1);
    _turret_traverse_postion--;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
    delay(200);
   }

   _traverse_turret_task = NULL;   
   vTaskDelete(NULL);   
}

void handleTraverseTurretAnticlockwise()
{
  _can_traverse = true;
   xTaskCreatePinnedToCore(
                    traverseTurretAntiClockwise,   /* Task function. */
                    "TraverseTurretTask",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_traverse_turret_task,      /* Task handle to keep track of created task */
                    0); 
  Serial.println("Traverse Turret Anticlockwise");
}

void handleSlowTraverseTurretAnticlockwise()
{
  _can_traverse = true;
   xTaskCreatePinnedToCore(
                    slowTraverseTurretAntiClockwise,   /* Task function. */
                    "SlowTraverseTurretTask",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_traverse_turret_task,      /* Task handle to keep track of created task */
                    1); 
  Serial.println("Slow Traverse Turret Anticlockwise");
}

void handleTraverseTurretClockwise()
{
  _can_traverse = true;
  xTaskCreatePinnedToCore(
                    traverseTurretClockwise,   /* Task function. */
                    "TraverseTurretTask",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    3,           /* priority of the task */
                    &_traverse_turret_task,      /* Task handle to keep track of created task */
                    1); 
  Serial.println("Traverse Turret Clockwise");
}

void handleSlowTraverseTurretClockwise()
{
  _can_traverse = true;
  xTaskCreatePinnedToCore(
                    slowTraverseTurretClockwise,   /* Task function. */
                    "SlowTraverseTurretTask",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &_traverse_turret_task,      /* Task handle to keep track of created task */
                    1); 
  Serial.println("Traverse Turret Clockwise");
}

void handleStopTurretTraverseChange()
{
  _can_traverse = false;
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
  Serial.println("Water Start");
}

void handleWaterPulse1()
{
  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);

  delay(1000);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  Serial.println("Water Pulse 1");
}

void handleWaterPulse2()
{
  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);

  delay(1000);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  delay(800);

  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);

  delay(1000);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  Serial.println("Water Pulse 2");
}

void handleWaterPulse3()
{
  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);

  delay(1000);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  delay(800);

  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);

  delay(1000);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  delay(800);

  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);
  
  delay(1000);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  Serial.println("Water Pulse 3");
}

void handleWaterStop()
{
  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);
  Serial.println("Water Stop");
}

void handleLaserOn()
{
  digitalWrite(LASER_PIN, HIGH);
  Serial.println("Laser On");
}

void handleLaserOff()
{
  digitalWrite(LASER_PIN, LOW);
  Serial.println("Laser Off");
}

void handleStopAll()
{
    handleStopAcceleration();
    handleStopTurretElevationChange();
    handleStopTurretTraverseChange();
    handleWaterStop();
    handleLinearActuatorStop();
}