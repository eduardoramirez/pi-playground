#include <stdio.h>
#include <wiringPi.h>
#include "assignment1.h"

int main(void){
    
    int x;

    if (wiringPiSetup() == -1) {
        printf("FAILED Setup\n");
        return 1;
    }


    while (1) {
        x = digitalRead(4);

        printf("%d\n", x);

    }

    return 0;
}
