#ifndef common_h
#define common_h
#include <Arduino.h>
#define one 16753245
#define two 16736925
#define three 16769565
#define four 16720605
#define five  16712445
#define six 16761405
#define seven 16769055
#define eight 16754775
#define nine 16748655
#define zero 16750695
#define UP 16718055
#define DOWN 16730805
#define OK 16726215
#define LEFT 16726215
#define RIGHT 16734885
unsigned long timer_ledblink;
typedef struct led{
    char pin;
    char brightness;
    int type;
    bool is_turnOn;
}led;

#endif