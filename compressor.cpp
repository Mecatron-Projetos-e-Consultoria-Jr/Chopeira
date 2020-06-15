#include "compressor.h"


compressor::compressor(int digital_pin){

    pinMode(digital_pin,OUTPUT);
    pin = digital_pin;
}

void compressor::turn_on_cooling(){

    // Close the relay (so the cooler turns on)
    digitalWrite(pin,HIGH);
    
}

void compressor::turn_off_cooling(){

    // Open the relay
    digitalWrite(pin,LOW);
    
}