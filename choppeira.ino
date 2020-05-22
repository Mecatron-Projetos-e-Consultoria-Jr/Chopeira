#include "debug.h"
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
button power_button(5,6,7,8);

// Set the target temperature for the liquid
const float min_target_temperature PROGMEM = 0.0f;
const float max_target_temperature PROGMEM = 2.0f;

// bool to know if it's the first iteration for the machine
bool first_iteration  = true;


void setup(){
    
    // Start the serial communication 
    Serial.begin(19200);
    debug::log_message(F("                         .sssssssss.\n                   .sssssssssssssssssss\n                 sssssssssssssssssssssssss\n                ssssssssssssssssssssssssssss\n                 @@sssssssssssssssssssssss@ss\n                 |s@@@@sssssssssssssss@@@@s|s\n          _______|sssss@@@@@sssss@@@@@sssss|s\n        /         sssssssss@sssss@sssssssss|s\n       /  .------+.ssssssss@sssss@ssssssss.|\n      /  /       |...sssssss@sss@sssssss...|\n     |  |        |.......sss@sss@ssss......|\n     |  |        |..........s@ss@sss.......|\n     |  |        |...........@ss@..........|\n      \\  \\       |............ss@..........|\n       \\  '------+...........ss@...........|\n        \\________ .........................|\n                 |.........................|\n                /...........................\n                  |.......................|\n                      |...............|\n\n"));
    
    debug::log_message(F(""));
    debug::log_message(F(""));
    
    debug::log_message(F("[choppeira.ino]Serial communicate started[9600 bound rate] "));

    // Start the emperature sensor 
    sensors.begin();
    debug::log_message(F("[choppeira.ino]Temperature Sensor Initialized"));

    // close the vaulve to avoid leaking
    valve.close_valve();
    debug::log_message(F("[choppeira.ino]Valve Closed"));

    // Set the LED color to RED
    power_button.set_color('R');

    // Start the boot sequence for the LED, to let the user know that it's starting
    debug::log_message(F("[choppeira.ino]Initializing the boot sequence for the LED"));
    power_button.boot_routine();

}

void loop(){

    // Resquest the temperature for all the sensors connected to the arduino 
    sensors.requestTemperatures(); 

    // Check the temperature  - by index means it's getting the data for the first sensor (if in the future more sensores are added) -- index starts at 0
    float current_temperature = sensors.getTempCByIndex(0);
    // float current_temperature = 5.0f;
    
    debug::log_message(F("[choppeira.ino]Current Temperature: "));
    debug::log_number<float>(current_temperature);
    
    // If the temperature is higher than the target, turn on the cooling system
    if (current_temperature > max_target_temperature){
        
        // turn on the cooling system
        cooling_system.turn_on_cooling();
        debug::log_message(F("[choppeira.ino]Temperature Above Threshold. Turning Cooling system on ..."));

        // If it's the first iteration, turn the LED red so the user knows the machine won't release beer 
        if (first_iteration){

            // Turn the LED to red 
            power_button.set_color('R');
            debug::log_message(F("[choppeira.ino]First iteration not finished... Setting LED color to RED"));
        }

        // If it's not the first iteration, the solenoid will continue to be open, but set the color to yellow so the user knows the beer is not within the temperature threshold
        else if (!first_iteration){
            
            // Set the color to yellow
            power_button.set_color('Y');
            debug::log_message(F("[choppeira.ino]First iteration previously reached... Setting LED color to YELLOW"));
        }
        
    }

    // If the temperature is lower than the min_target, turn off the cooling system
    else if (current_temperature <= min_target_temperature){

        // turn off the cooling system 
        cooling_system.turn_off_cooling();
        debug::log_message(F("[choppeira.ino]Temperature below the threshold. Turning Cooling off ..."));

    }
    
    // if the temperature is lower or equal to the max temperature allowed in the threshold, open the solenoid valve and leave it open. The only moment the valve is closed is at the first iteration 
    else if (current_temperature <= max_target_temperature)
    {
        // Set the first iteration variable to false, since the timeperature already reached the threshold at least for the first time
        first_iteration = false;
        debug::log_message(F("[choppeira.ino]Temperature below the max threshold, setting the first_iteration variable to false ... "));
        
        // open the valve 
        valve.open_valve();
        debug::log_message(F("[choppeira.ino]Open the valve (and leave it open)"));

        // Set the button color to green, so the user knows the valve is open
        power_button.set_color('G');
        debug::log_message(F("[choppeira.ino]Set the LED color to GREEN (since the valve is open)"));
    
    }

    // wait for one second before next iteration (1000 ms) ----- time between measurements for the temperature sensor 
    delay(3000);
    debug::log_message(F("[choppeira.ino]Wait 1000ms before next iteration"));

    debug::log_message(F(""));
    debug::log_message(F(""));
    debug::log_message(F(""));
}
