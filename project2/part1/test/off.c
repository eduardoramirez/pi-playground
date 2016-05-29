#include <wiringPi.h>

int main(void){

    if (wiringPiSetup()== -1)
        return 1;
    
    int i=0;
    int pins[] = {0,1,2,3,4,5,6,7,8,9,21,22,23,24,25,26,27,28,29};
    int num = 19;

    for (i=0; i < num; i++) {
        digitalWrite(pins[i], LOW);
    }

    return 0;
}

