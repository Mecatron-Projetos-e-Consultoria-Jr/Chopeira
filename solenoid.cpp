#include "solenoid.h"

solenoid::solenoid(int output_pin){

    pin = output_pin;
    pinMode(pin,OUTPUT);

}

void solenoid::open_valve(){

    // Open the valve so the liquid comes out 
    digitalWrite(pin,HIGH);
}

void solenoid::close_valve(){

    // Close the valve 
    digitalWrite(pin,LOW);
}