
#include "Arduino.h"
#include <engineLibrary.h>

int RPWM_PIN;
int LPWM_PIN;

void initializeEngine(int RPWM_PIN_new, int LPWM_PIN_new){
    RPWM_PIN = RPWM_PIN_new;
    LPWM_PIN = LPWM_PIN_new;
    pinMode(RPWM_PIN, OUTPUT);
    pinMode(LPWM_PIN, OUTPUT);
    analogWrite(RPWM_PIN, 0);
    analogWrite(LPWM_PIN, 0);
};
void stop(){
    analogWrite(RPWM_PIN, 0);
    analogWrite(LPWM_PIN, 0);
};
void rotate(char direction, int value){
    if(direction == 'r'){
        analogWrite(RPWM_PIN, value);
        analogWrite(LPWM_PIN, 0);

    }
    else{
        analogWrite(LPWM_PIN, value);
        analogWrite(RPWM_PIN, 0);

    }
};