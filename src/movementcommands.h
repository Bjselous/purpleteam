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
  analogWrite(MD_ENABLE, 250);
  digitalWrite(MD_IN_3, HIGH);
  digitalWrite(MD_IN_4, LOW);
  Serial.println("Forward");
}

void handleCreepForward()
{ 
  analogWrite(MD_ENABLE, 125);
  digitalWrite(MD_IN_3, HIGH);
  digitalWrite(MD_IN_4, LOW);
  Serial.println("Creep Forward");
}

void handleReverse()
{
  analogWrite(MD_ENABLE, 250);
  digitalWrite(MD_IN_3, LOW);
  digitalWrite(MD_IN_4, HIGH);
  Serial.println("Reverse");
}

void handleCreepReverse()
{
  analogWrite(MD_ENABLE, 125);
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
  if(_turret_traverse_postion>10)
    {
    traverse_servo.write(_turret_traverse_postion-10);
    _turret_traverse_postion-=10;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Anticlockwise 10");
}

void handleTraverseTurretAnticlockwise5()
{
  if(_turret_traverse_postion>10)
    {
    traverse_servo.write(_turret_traverse_postion-5);
    _turret_traverse_postion-=5;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Anticlockwise 5");
}

void handleTraverseTurretAnticlockwise1()
{
  if(_turret_traverse_postion>10)
    {
    traverse_servo.write(_turret_traverse_postion-1);
    _turret_traverse_postion--;
    Serial.println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Anticlockwise 1");
}


void handleTraverseTurretClockwise10()
{
  if(_turret_traverse_postion < 170)
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
  if(_turret_traverse_postion < 170)
    {
    traverse_servo.write(_turret_traverse_postion+5);    
    _turret_traverse_postion+=5;
    Serial.
    println("_turret_traverse_position = " + String(_turret_traverse_postion));
    }
  Serial.println("Traverse Turret Clockwise 5 ");
}

void handleTraverseTurretClockwise1()
{
  if(_turret_traverse_postion < 170)
    {
    traverse_servo.write(_turret_traverse_postion+1);    
    _turret_traverse_postion++;
    Serial.
    println("_turret_traverse_position = " + String(_turret_traverse_postion));
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
    handleWaterStop();
    handleLinearActuatorStop();
}