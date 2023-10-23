// Orginal code by Bryan Saunders 18/10/23
// Developed for Team Purple ENGG1100 Semester 2 2023
// Any Duplication or distribution is prohibted

#include <Arduino.h>
#include <ESP32Servo.h>
#include "purpleconstants.h"

int _turret_elevation_postion = 90;
int _turret_traverse_postion = 90;
bool _can_traverse = false;
bool _can_elevate = false;
Servo elevation_servo;
Servo traverse_servo;
TaskHandle_t _elevate_LA_task;

void handleForward()
{ 
  analogWrite(MD_ENABLE, 255);
  digitalWrite(MD_IN_3, HIGH);
  digitalWrite(MD_IN_4, LOW);

  analogWrite(RMD_ENABLE, 255);
  digitalWrite(RMD_IN_3, HIGH);
  digitalWrite(RMD_IN_4, LOW);

  Serial.println("Forward");
}

void handleCreepForward()
{ 
  analogWrite(MD_ENABLE, 200);
  digitalWrite(MD_IN_3, HIGH);
  digitalWrite(MD_IN_4, LOW);

  analogWrite(RMD_ENABLE, 200);
  digitalWrite(RMD_IN_3, HIGH);
  digitalWrite(RMD_IN_4, LOW);

  Serial.println("Creep Forward");
}

void handleReverse()
{
  analogWrite(MD_ENABLE, 255);
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, HIGH);

  analogWrite(RMD_ENABLE, 255);
  digitalWrite(RMD_IN_3, LOW);
  digitalWrite(RMD_IN_4, HIGH);

  Serial.println("Reverse");
}

void handleCreepReverse()
{
  analogWrite(MD_ENABLE, 125);
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, HIGH);

  analogWrite(RMD_ENABLE, 125);
  digitalWrite(RMD_IN_3, LOW);
  digitalWrite(RMD_IN_4, HIGH);
  Serial.println("Creep Reverse");
}

void handleStopAcceleration()
{
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, LOW);
  digitalWrite(MD_ENABLE, LOW);

  digitalWrite(RMD_IN_3, LOW);
  digitalWrite(RMD_IN_4, LOW);
  digitalWrite(RMD_ENABLE, LOW);
  Serial.println("Stop Acceleration");
}

void handleElevateTurret10()
{ 
  if(_turret_elevation_postion < 175)
  {
      elevation_servo.write(_turret_elevation_postion+10);
      _turret_elevation_postion+=10;
      Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
   }
  Serial.println("Elevate Turret 10");
}

void handleElevateTurret5()
{ 
   if(_turret_elevation_postion < 175)
  {
  elevation_servo.write(_turret_elevation_postion+5);
  _turret_elevation_postion+=5;
  Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
  }
  Serial.println("Elevate Turret 5 ");
}

void handleElevateTurret1()
{ 
  if(_turret_elevation_postion < 175)
  {
    elevation_servo.write(_turret_elevation_postion+1);
    _turret_elevation_postion++;
    Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
  } 
  Serial.println("Elevate Turret 1");
}

void handleDepressTurret10()
{     
  if(_turret_elevation_postion > 20 )
  {
  elevation_servo.write(_turret_elevation_postion-10);
  _turret_elevation_postion-=10;
  Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
  }
  Serial.println("Depress Turret 10");
}

void handleDepressTurret5()
{     
     if(_turret_elevation_postion > 20 )
  {
  elevation_servo.write(_turret_elevation_postion-5);
  _turret_elevation_postion-=5;
  Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
  }
  Serial.println("Depress Turret 5");
}

void handleDepressTurret1()
{     
     if(_turret_elevation_postion > 20 )
  {
    elevation_servo.write(_turret_elevation_postion-1);
    _turret_elevation_postion--;
    Serial.println("_turret_elevation = " + String(_turret_elevation_postion));
  }
    Serial.println("Depress Turret 1");
}

void handleTraverseTurretAnticlockwise10()
{
  if(_turret_traverse_postion>0)
    {
    traverse_servo.write(_turret_traverse_postion-10);
    _turret_traverse_postion-=10;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Anticlockwise 10");
}

void handleTraverseTurretAnticlockwise5()
{
  if(_turret_traverse_postion>0)
    {
    traverse_servo.write(_turret_traverse_postion-5);
    _turret_traverse_postion-=5;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Anticlockwise 5");
}

void handleTraverseTurretAnticlockwise1()
{
  if(_turret_traverse_postion>0)
    {
    traverse_servo.write(_turret_traverse_postion-1);
    _turret_traverse_postion--;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Anticlockwise 1");
}


void handleTraverseTurretClockwise10()
{
  if(_turret_traverse_postion < 180)
    {
    traverse_servo.write(_turret_traverse_postion+10);    
    _turret_traverse_postion+=10;
    Serial.
    println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Clockwise 10");
}

void handleTraverseTurretClockwise5()
{
  if(_turret_traverse_postion < 180)
    {
    traverse_servo.write(_turret_traverse_postion+5);    
    _turret_traverse_postion+=5;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Clockwise 5 ");
}

void handleTraverseTurretClockwise1()
{
  if(_turret_traverse_postion < 180)
    {
    traverse_servo.write(_turret_traverse_postion+1);    
    _turret_traverse_postion++;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Clockwise 1 ");
}

void handleLinearActuatorUp()
{  
  digitalWrite(LA_ENABLE, HIGH);
  digitalWrite(LA_IN_1, LOW);
  digitalWrite(LA_IN_2, HIGH);
  Serial.println("Linear Actuator Up");
}

void handleLinearActuatorStop()
{
  digitalWrite(LA_IN_1, LOW);
  digitalWrite(LA_IN_2, LOW);
  digitalWrite(LA_ENABLE, LOW);
  Serial.println("Linear Actuator Stop");
}

void elevateLA(void* pvParameters)
{
  digitalWrite(LA_ENABLE, HIGH);
  digitalWrite(LA_IN_1, LOW);
  digitalWrite(LA_IN_2, HIGH);
  delay(25000);
  handleLinearActuatorStop();
  _elevate_LA_task = NULL;
  vTaskDelete(NULL);
}

void handleLinearActuatorFullUp()
{    
    xTaskCreatePinnedToCore(
                    elevateLA,   /* Task function. */
                    "ElevateLATasks",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &_elevate_LA_task,      /* Task handle to keep track of created task */
                    1); 
  Serial.println("Linear Actuator full up");
}

void handleLinearActuatorDown()
{ 
  digitalWrite(LA_ENABLE, HIGH);
  digitalWrite(LA_IN_1, HIGH);
  digitalWrite(LA_IN_2, LOW);
  Serial.println("Linear Actuator Down");
}

void drepressLA(void* pvParameters)
{
  digitalWrite(LA_ENABLE, HIGH);
  digitalWrite(LA_IN_1, HIGH);
  digitalWrite(LA_IN_2, LOW);
  delay(25000);
  handleLinearActuatorStop();
  _elevate_LA_task = NULL;
  vTaskDelete(NULL);
}

void handleLinearActuatorFullDown()
{ 
   xTaskCreatePinnedToCore(
                    drepressLA,   /* Task function. */
                    "ElevateLATasks",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &_elevate_LA_task,      /* Task handle to keep track of created task */
                    1);  
  Serial.println("Linear Actuator full Down");
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

  delay(PUMP_ON_DURATION);

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

  delay(PUMP_ON_DURATION);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  delay(PUMP_PAUSE_DURATION);

  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);

  delay(PUMP_ON_DURATION);

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

  delay(PUMP_ON_DURATION);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  delay(PUMP_PAUSE_DURATION);

  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);

  delay(PUMP_ON_DURATION);

  digitalWrite(PD_IN_1, LOW);
  digitalWrite(PD_IN_2, LOW);
  digitalWrite(PD_ENABLE, LOW);

  delay(PUMP_PAUSE_DURATION);

  digitalWrite(PD_ENABLE, HIGH);
  digitalWrite(PD_IN_1, HIGH);
  digitalWrite(PD_IN_2, LOW);
  
  delay(PUMP_ON_DURATION);

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

void handleLeftTGT()
{
  elevation_servo.write(160);
  _turret_elevation_postion=160;
  Serial.println("_turret_elevation = " + String(_turret_elevation_postion));

  traverse_servo.write(165);    
  _turret_traverse_postion=165;
  Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));

  Serial.println("Left TGT");
}

void handleRightTGT()
{
  elevation_servo.write(160);
  _turret_elevation_postion=160;
  Serial.println("_turret_elevation = " + String(_turret_elevation_postion));

  traverse_servo.write(15);    
  _turret_traverse_postion=15;
  Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));


  Serial.println("Right TGT");
}

void handleStopAll()
{
    handleStopAcceleration();
    handleWaterStop();
    handleLinearActuatorStop();
}