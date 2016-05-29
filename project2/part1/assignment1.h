#ifndef _ASSIGNMENT_BODY_
#define _ASSIGNMENT_BODY_

#define uchar unsigned char

// A. Pin number definitions (DO NOT MODIFY)
// Important! USE the pin numbers and WIRE.
// We use 8 sensors.
//
// 1. Button
#define PIN_BUTTON 0

// 2. 2-Color LED
#define PIN_YELLOW 1

// 3. Temperature
#define PIN_TEMP 4

// 4. Tracking Sensor
#define PIN_TRACK 5

// 5. Shock Sensor
#define PIN_SHOCK 6

// 6. RGB(3-Color) LED
#define PIN_RED 7
#define PIN_GREEN 8
#define PIN_BLUE 9

// 7. Auto-flash Red
#define PIN_ALED 12

// 8. Buzzer
#define PIN_BUZZER 13

// B. Shared structure
// All thread fuctions get a shared variable of the structure
// as the function parameter.
// If needed, you can add anything in this structure.
typedef struct shared_variable {
	int bProgramExit; // Once it is set to 1, the program will be terminated.
    int active; // Has the button been pressed? If so we are in running mode
    int b_pressed;
    int temp;
    int shock;
    int track;
} SharedVariable;


// C. Functions
// You need to implement following functions.
// Do not change any function name here.
void init_shared_variable(SharedVariable* sv);
void init_sensors(SharedVariable* sv);

void body_button(SharedVariable* sv);
void body_twocolor(SharedVariable* sv);
void body_temp(SharedVariable* sv);
void body_track(SharedVariable* sv);
void body_shock(SharedVariable* sv);
void body_rgbcolor(SharedVariable* sv);
void body_aled(SharedVariable* sv);
void body_buzzer(SharedVariable* sv);

void ledColorSet(uchar r_val, uchar g_val, uchar b_val);

#endif
