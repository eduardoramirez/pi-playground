#include <wiringPi.h>
#include <stdio.h>

#define RPIN 0
#define GPIN 2
#define BPIN 3
#define LED_MAX 2048 


int main(void) {
    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed");
        return 1;
    }

    softPwmCreate(RPIN, 0, LED_MAX);
    softPwmCreate(GPIN, 0, LED_MAX);
    softPwmCreate(BPIN, 0, LED_MAX);
    softPwmWrite(RPIN, 0);
    softPwmWrite(GPIN, 0);
    softPwmWrite(BPIN, 0);


    while (1) {
        softPwmWrite(RPIN, 0x76);
        softPwmWrite(BPIN, 0xee);
        printf("Magenta ON ... ");
        delay(500);

        softPwmWrite(RPIN, 0);
        softPwmWrite(BPIN, 0);
        printf(" ... Magenta Off\n");
        delay(500);
    }
    return 0;
}

