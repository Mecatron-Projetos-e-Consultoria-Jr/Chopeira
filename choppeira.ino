#include "temperature_sensor.h"
#include "compressor.h"


// instantiate temperature_sensor and attach the signal pin to the analog GPIO A0 and instantiate compressor to control cooling system and attach it to GPIO 9
temperature_sensor sensor(A0);
compressor cooling_system(9);

// Set the target temperature for the liquid
float target_temperature = 0.0f;


void setup(){
    // 
}

void loop(){

    // Check the temperature 
    float current_temperature = sensor.get_current_temperature();

    // If the temperature is higher than the target, turn on the cooling system
    if (current_temperature > target_temperature){
        
        // turn on the cooling system
        cooling_system.turn_on_cooling();
    }
    else if (current_temperature < target_temperature){

        // turn off the cooling system 
        cooling_system.turn_off_cooling();
    }
    
}