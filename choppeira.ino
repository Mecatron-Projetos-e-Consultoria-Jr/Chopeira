#include "temperature_sensor.h"
#include "compressor.h"
#include "solenoid.h"

// instantiate temperature_sensor and attach the signal pin to the analog GPIO A0 and instantiate compressor to control cooling system and attach it to GPIO 9 / instantiate the selonoide class and attach it to pin 10 on the arduino 
temperature_sensor sensor(A0);
compressor cooling_system(9);
solenoid  valve(10);

// Set the target temperature for the liquid
float target_temperature = 0.0f;

// Set the pin in which the button will be wired to
int button = 11;

void setup(){
    
    // Set the pin mode for the button 
    pinMode(button,INPUT);

    // close the vaulve to avoid leaking
    valve.close_valve();
}

void loop(){

    // Check the temperature 
    float current_temperature = sensor.get_current_temperature();

    // If the temperature is higher than the target, turn on the cooling system
    if (current_temperature > target_temperature){
        
        // turn on the cooling system
        cooling_system.turn_on_cooling();
    }

    // If the temperature is lower than the target, turn off the cooling system
    else if (current_temperature <= target_temperature){

        // turn off the cooling system 
        cooling_system.turn_off_cooling();
    }
    
    // Check to see if the button is pressed 
    bool button_pressed = digitalRead(button);

    while (button_pressed)
    {
        // open the valve 
        valve.open_valve();

        // update the button state 
        button_pressed = digitalRead(button);

        // if the button stopped being pressed, close the valve 
        if(!button_pressed){

            // close the valve 
            valve.close_valve();
        }

    }
    
}
