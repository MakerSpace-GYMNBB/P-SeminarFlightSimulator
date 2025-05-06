#ifndef ENGINELIBRARY_H
#define ENGINELIBRARY_H

#include "Arduino.h"

extern int RPWM_PIN;
extern int LPWM_PIN;

void initializeEngine(int RPWM_PIN_new, int LPWM_PIN_new);
void stop();
void rotate(char direction, int value);

#endif