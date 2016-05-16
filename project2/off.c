#include <wiringPi.h>

int main(void){

    if (wiringPiSetup()== -1)
        return 1;
    
    int i=0;
    int pins[] = {0,1,4,5,6,7,8,9,12,13};
    int num = 10;

    for (i=0; i < num; i++) {
        digitalWrite(pins[i], LOW);
    }

    return 0;
}

