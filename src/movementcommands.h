#include <Arduino.h>

void handleForward()
{
  digitalWrite(FWD_LED_PIN, HIGH);
  Serial.println("Forward");
}

void handleReverse()
{
  digitalWrite(RVS_LED_PIN, HIGH);
  Serial.println("Reverse");
}

void handleStopAcceleration()
{
   digitalWrite(RVS_LED_PIN, LOW);
   digitalWrite(FWD_LED_PIN, LOW);
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
  digitalWrite(WATER_LED_PIN, HIGH);
  Serial.println("Water Start");
}

void handleWaterStop()
{
   digitalWrite(WATER_LED_PIN, LOW);
    Serial.println("Water Stop");
}

void handleStopAll()
{
    handleStopAcceleration();
    handleStopTurretElevationChange();
    handleStopTurretTraverseChange();
    handleWaterStop();
}