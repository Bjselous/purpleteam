#include <Arduino.h>

void handleForward()
{
  Serial.println("Forward");
}

void handleReverse()
{
  Serial.println("Reverse");
}

void handleStopAcceleration()
{
  Serial.println("Stop Acceleration");
}

void handleElevateTurret()
{
  Serial.println("Elevate Turret");
}

void handleDepressTurret()
{
  Serial.println("Depress Turret");
}

void handleStopTurretElevationChange()
{
  Serial.println("Stop Turret Elevation Change");
}

void handleTraverseTurretAnticlockwise()
{
  Serial.println("Traverse Turret Anticlockwise");
}

void handleTraverseTurretClockwise()
{
  Serial.println("Traverse Turret Clockwise");
}

void handleStopTurretTraverseChange()
{
  Serial.println("Stop Turret Traverse Change");
}

void handleWaterStart()
{
  Serial.println("Water Start");
}

void handleWaterStop()
{
  Serial.println("Water Stop");
}

void handleStopAll()
{
    handleStopAcceleration();
    handleStopTurretElevationChange();
    handleStopTurretTraverseChange();
    handleWaterStop();
}