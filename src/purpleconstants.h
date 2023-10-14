#ifndef PURPLE_CONSTANTS
#define PURPLE_CONSTANTS

#define STOP_ALL 0

#define FORWARD 1
#define REVERSE 2
#define STOPACCELERATION 3
#define CREEP_FORWARD 15
#define CREEP_REVERSE 16

#define ELEVATE_TURRET 4
#define DEPRESS_TURRET 5
#define STOP_TURRET_ELEVATION_CHANGE 6
#define SLOW_ELEVATE_TURRET 17
#define SLOW_DEPRESS_TURRET 18

#define TRAVERSE_TURRET_ANTICLOCKWISE 7
#define TRAVERSE_TURRET_CLOCKWISE 8
#define STOP_TURRET_TRAVERSE_CHANGE 9
#define SLOW_TRAVERSE_TURRET_ANTICLOCKWISE 19
#define SLOW_TRAVERSE_TURRET_CLOCKWISE 20

#define WATER_START 10
#define WATER_STOP 11
#define WATER_PULSE_1 23
#define WATER_PULSE_2 24
#define WATER_PULSE_3 25

#define LINEAR_ACTUATOR_UP 12
#define LINEAR_ACTUATOR_DOWN 13
#define LINEAR_ACTUATOR_STOP 14

#define LASER_ON 21
#define LASER_OFF 22

// WiFi network name and password:
const char * networkName = "PurpleT";
const char * networkPswd = "1qaz2wsx";

//LED
const int SERVO_ELEVATION_PIN = 33;
const int SERVO_TRAVERSE_PIN = 32;

const int PD_ENABLE = 14;
const int PD_IN_1 = 27;
const int PD_IN_2 = 26;

const int MD_ENABLE = 12;
const int MD_IN_3 = 25;
const int MD_IN_4 = 13;


const int LA_ENABLE = 05;
const int LA_IN_1 = 18;
const int LA_IN_2 = 19;

const int LASER_PIN = 23;

bool fwd = false;

#endif