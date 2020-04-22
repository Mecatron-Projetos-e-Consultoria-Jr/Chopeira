#include "compressor.h"
#include "solenoid.h"
#include "button.h"

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// instantiate compressor to control cooling system and attach it to GPIO 9 / instantiate the selonoide class and attach it to pin 10 on the arduino  / instance the button class and Set the data pin to 13, red led to analof A0, green to analog A1, blue to analog A2
compressor cooling_system(9);
solenoid  valve(10);
button power_button(13,A0,A1,A2);

// Set the target temperature for the liquid
float min_target_temperature = 0.0f;
float max_target_temperature = 2.0f;

void setup(){
    
    // Start the emperature sensor 
    sensors.begin();

    // close the vaulve to avoid leaking
    valve.close_valve();
}

void loop(){

    // Resquest the temperature for all the sensors connected to the arduino 
    sensors.requestTemperatures(); 

    // Check the temperature  - by index means it's getting the data for the first sensor (if in the future more sensores are added) -- index starts at 0
    float current_temperature = sensors.getTempCByIndex(0);

    // If the temperature is higher than the target, turn on the cooling system
    if (current_temperature > max_target_temperature){
        
        // turn on the cooling system
        cooling_system.turn_on_cooling();

        // Turn the LED to red 
        power_button.set_color('R');
    }

    // If the temperature is lower than the min_target, turn off the cooling system
    else if (current_temperature <= min_target_temperature){

        // turn off the cooling system 
        cooling_system.turn_off_cooling();

    }
    
    // if the temperature is lower or equal to the max temperature allowed in the threshold, open the solenoid valve
    if (current_temperature <= max_target_temperature)
    {
        // open the valve 
        valve.open_valve();

        // Set the button color to green, so the user knows the valve is open
        power_button.set_color('G');

    }
    
}
