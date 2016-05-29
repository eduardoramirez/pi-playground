#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>



void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
	sv->bProgramExit = 0;
    sv->b_pressed = 0;
    sv->active = 0;
    sv->temp = 0;
    sv->shock = 0;
    sv->track = 0;
    int i=0;
    for (i=0;i<8;i++){
        sv->last_run[i] = 0;
    }
}

void init_sensors(SharedVariable* sv) {

    // ACTUATORS
    softPwmCreate(PIN_RED, 0, 100);
    softPwmCreate(PIN_GREEN,0, 100);
    softPwmCreate(PIN_BLUE, 0, 100);
    pinMode(PIN_YELLOW, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_ALED, OUTPUT);
    // SENSORS
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_TEMP, INPUT);
    pinMode(PIN_TRACK, INPUT);
    pinMode(PIN_SHOCK, INPUT);

    // ~~~~~ INITIALIZE ACTUATORS TO STARTING VALUES ~~~~  
    // 2-Color LED
    digitalWrite(PIN_YELLOW, LOW);
    // RGB(3-Color) LED
    ledColorSet(0x00, 0x00, 0x00);
    // AutoFlash LED
    digitalWrite(PIN_ALED, LOW);
    // Buzzer
    digitalWrite(PIN_BUZZER, LOW);


}

// DONE
void body_button(SharedVariable* sv) {
    int x = digitalRead(PIN_BUTTON);

    if ( !x && !(sv->b_pressed) ){
        //printf("Button Pressed\n");
        sv->b_pressed = 1;
        return;
    }
    if (x && (sv->b_pressed) ) {
        //printf("button released\n");
        sv->b_pressed=0;
        if ( sv->active ){
            // if it goes from active to inactive RESET EVERYTHING
            sv->active=0; 
            //printf("Deactivating!\n");
        }
        else{
	        sv->active = !(sv->active);
            //printf("Activating\n");
        }
        return;
    }
}

void body_temp(SharedVariable* sv) {
    int x = digitalRead(PIN_TEMP);

    if (  sv->active && !sv->track && !sv->shock){
        sv->temp = x;
    }
    else
        sv->temp = 0;
}

void body_track(SharedVariable* sv) {
    int x = digitalRead(PIN_TRACK);

    if (sv->active && !sv->shock) { 

        if (!x) {
            //printf("TRACKING MODE ENABLED\n");
            sv->track = 1;
        }
    }
    else 
        sv->track = 0;
}

void body_shock(SharedVariable* sv) {
    int x = digitalRead(PIN_SHOCK);

    if (sv->active && !sv->track) { 
        //printf("Shock: %d\n",x);
        if (!x)
            sv->shock = 1;
    }
    else 
        sv->shock = 0;
}


//DONE
void body_twocolor(SharedVariable* sv) {
    if (sv->active) {
        digitalWrite(PIN_YELLOW, HIGH);
    }
    else {
        digitalWrite(PIN_YELLOW, LOW);
    }

}


void body_rgbcolor(SharedVariable* sv) {
    if (sv->active) {
        if (sv->shock){
            // SET RGB TO RED
            ledColorSet(0xff, 0x00, 0x00);
        }
        else if(sv->track){
            // SET RGB TO MAGENTA
            ledColorSet(0x76, 0x00, 0xee);
        }
        else {
            // SET RGB TO GREEN
            ledColorSet(0x00, 0xff, 0x00);
        }
    }
    else {
        // INACTIVE
        ledColorSet(0x00, 0x00, 0xff);
    }
}

void body_aled(SharedVariable* sv) {
    if (sv->temp && sv->active) {
        digitalWrite(PIN_ALED, HIGH);
    }
    else{
        digitalWrite(PIN_ALED, LOW);
    }
}

void body_buzzer(SharedVariable* sv) {
    if (sv->temp) {
        digitalWrite(PIN_BUZZER, HIGH);
    }
    else{
        digitalWrite(PIN_BUZZER, LOW);
    }
}


void ledColorSet(uchar r_val, uchar g_val, uchar b_val) {
    softPwmWrite(PIN_RED, r_val);
    softPwmWrite(PIN_GREEN, g_val);
    softPwmWrite(PIN_BLUE, b_val);
}
