// Orginal code by Bryan Saunders 18/10/23
// Developed for Team Purple ENGG1100 Semester 2 2023
// Any Duplication or distribution is prohibted

#ifndef PURPLE_CONSTANTS
#define PURPLE_CONSTANTS

#define STOP_ALL 0

#define FORWARD 1
#define REVERSE 2
#define STOPACCELERATION 3
#define CREEP_FORWARD 15
#define CREEP_REVERSE 16

#define ELEVATE_TURRET_10 27 
#define ELEVATE_TURRET_5 26 
#define ELEVATE_TURRET_1 5

#define DEPRESS_TURRET_10 4
#define DEPRESS_TURRET_5 17
#define DEPRESS_TURRET_1 18

#define TRAVERSE_TURRET_ANTICLOCKWISE_10 7
#define TRAVERSE_TURRET_ANTICLOCKWISE_5 28
#define TRAVERSE_TURRET_ANTICLOCKWISE_1 29
#define TRAVERSE_TURRET_CLOCKWISE_10 8
#define TRAVERSE_TURRET_CLOCKWISE_5 19
#define TRAVERSE_TURRET_CLOCKWISE_1 20

#define WATER_START 10
#define WATER_STOP 11
#define WATER_PULSE_1 23
#define WATER_PULSE_2 24
#define WATER_PULSE_3 25

#define LINEAR_ACTUATOR_UP 12
#define LINEAR_ACTUATOR_DOWN 13
#define LINEAR_ACTUATOR_STOP 14
#define LINEAR_ACTUATOR_FULL_UP 30
#define LINEAR_ACTUATOR_FULL_DOWN 31


#define LEFT_TGT 21
#define RIGHT_TGT 22

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


const int RMD_ENABLE = 23;
const int RMD_IN_3 = 22;
const int RMD_IN_4 =21;

bool fwd = false;

const int PUMP_ON_DURATION = 750;
const int PUMP_PAUSE_DURATION = 750;

#endif