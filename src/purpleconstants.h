#ifndef PURPLE_CONSTANTS
#define PURPLE_CONSTANTS

#define STOP_ALL 0

#define FORWARD 1
#define REVERSE 2
#define STOPACCELERATION 3

#define ELEVATE_TURRET 4
#define DEPRESS_TURRET 5
#define STOP_TURRET_ELEVATION_CHANGE 6

#define TRAVERSE_TURRET_ANTICLOCKWISE 7
#define TRAVERSE_TURRET_CLOCKWISE 8
#define STOP_TURRET_TRAVERSE_CHANGE 9

#define WATER_START 10
#define WATER_STOP 11

// WiFi network name and password:
const char * networkName = "PurpleT";
const char * networkPswd = "1qaz2wsx";

//LED
const int REDLED_PIN = 27;
const int GREENLED_PIN = 26;

const int SERVO_ELEVATION_PIN = 33;
const int SERVO_TRAVERSE_PIN = 32;
const int WATER_LED_PIN = 12;

bool fwd = false;

#endif