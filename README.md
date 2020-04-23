# Chopeira Documentation 


1. [Button class](#Button-Class)  <br>
2. [Compressor class](#Compressor-Class) <br>
3. [Solenoid class](#Solenoid-Class) <br>
4. [Main Code](#Main-Code)

## Button Class

The button class handles both the input from the button and RGB LED indicator.


### Constructor 
The constructor takes 4 arguments:
    
    1. int data_pin (connected to digital pin);
    2. int r_pin (connected to analog pin);
    3. int g_pin (connected to analog pin);
    4. int b_pin (connected to analog pin)


Sets the pinMode for each GPIO (3 OUTPUT and on digital INPUT)

e.g: 

`button power_button(9,A0,A1,A2)`

### Methods 

##### is_pressed( )
Returns a bool, `true` if the button is pressed and `false` if it is not.

```c++
bool is_pressed(){

            // read the input pin
            bool button_state = digitalRead(input_pin);
            return button_state;
        }
```

##### set_color(char color)
Void method that changes the color of the RGB button.

Takes a character as argument - the initial of the color the LED should be.

| char | color name  |
|------|-------------|
| `R`  | `Red`       |
| `G`  | `Green`     |
| `Y`  | `Yellow`    |

```c++
void set_color(char color){

            color_name = color;

            switch (color){
                case 'R':


                    analogWrite(red_pin,255);
                    analogWrite(blue_pin,0);
                    analogWrite(green_pin,0);

                    // wait 500 milliseconds,  turn of -> so it will blink until the color changes to green
                    delay(500);

                    analogWrite(red_pin,0);
                    analogWrite(blue_pin,0);
                    analogWrite(green_pin,0);

                    break;

                
                
                case 'G':
                    analogWrite(green_pin,255);
                    analogWrite(blue_pin,0);
                    analogWrite(red_pin,0);
                    break;



                case 'Y':
                    analogWrite(green_pin,255);
                    analogWrite(blue_pin,0);
                    analogWrite(red_pin,255);
                    break;

            }
        }
```

e.g :

`power_button.set_color('R')` // Sets the color of the LED to red (and blinks it).

---






## Compressor Class 
The compressor class handles the activation of the relay connected to the compressor/pump from the counter flow cooling system.

### Constructor 
Takes one argument, the digital pin connected to the Arduino.

It sets the digital pinMode to `OUTPUT`.

e.g: 
`compressor cooling_system(9)` -> Attaches to digital pin 9 on the Arduino Board.

### Methods 
##### turn_on_cooling( )
Void method that closes the relay and activate the pump+compressor.

```c++
void turn_on_cooling(){

            // Close the relay (so the cooler turns on)
            digitalWrite(pin,HIGH);
        }
```

e.g:
`cooling_system.turn_on_cooling();`

##### turn_off_cooling( )
Void method that opens the relay and stops the pump+compressor.

```c++
void turn_off_cooling(){

            // Open the relay
            digitalWrite(pin,LOW);
        }
```

e.g:
`cooling_system.turn_off_cooling();`

---



## Solenoid Class
Handles the opening and closing of the release valve for the beer.

### Constructor 
The constructor takes one argument, the digital output pin on the Arduino.

It sets the pinMode to `OUTPUT`.

e.g: 

`solenoid valve(10)` // Attaches to pin 10 on the board.

### Methods 
##### open_valve( )
Closes the relay that controls the solenoid valve. Which opens the valve and lets liquid through.

```c++
void open_valve(){

            // Open the valve so the liquid comes out 
            digitalWrite(pin,HIGH);
        }
```

e.g: 

`valve.open_valve();` // opens the valve

##### close_valve( )
Opens the relay that controls the solenoid valve. Which closes the valve and holds the liquid.

```c++
void close_valve(){

            // Close the valve 
            digitalWrite(pin,LOW);
        }
```

e.g: 

`valve.close_valve();` // closes the valve

---

## Main Code 

Include the necessary libraries(`" "`are for files in the local directory and `< > ` are for files in the default directory):
```c++
#include "compressor.h"
#include "solenoid.h"
#include "button.h"

#include <OneWire.h>
#include <DallasTemperature.h>
```

Setup the temperature sensor library:


```c++
// Data wire is connected to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
```

Instantiate the custom classes:

```c++
// instantiate compressor to control cooling system and attach it to GPIO 9 / instantiate the selonoide class and attach it to pin 10 on the arduino  / instance the button class and Set the data pin to 13, red led to analof A0, green to analog A1, blue to analog A2
compressor cooling_system(9);
solenoid  valve(10);
button power_button(13,A0,A1,A2);
```

Set the target temperature:

```c++
// Set the target temperature for the liquid
float min_target_temperature = 0.0f;
float max_target_temperature = 2.0f;
```

Creates a boolean variable to track rather or not it's the first iteration for the machine
```c++
bool first_iteration = true;
```

Start the sensors and close the valves (prevent liquid waste): 

```c++
void setup(){
    
    // Start the emperature sensor 
    sensors.begin();

    // close the vaulve to avoid leaking
    valve.close_valve();
}
```

#### Inside the loop function


Get the temperature from the sensor: 

```c++
// Resquest the temperature for all the sensors connected to the arduino 
    sensors.requestTemperatures(); 

    // Check the temperature  - by index means it's getting the data for the first sensor (if in the future more sensores are added) -- index starts at 0
    float current_temperature = sensors.getTempCByIndex(0);
```

If the temperature is above target, turn on cooling, if it is the first iteration of the machine it means that the solenoid valve will be closed, so set the RGB color to red. If it is nor the first iteration, even though the temperature is outside the threshold the valve will not close, so set the RGB to yellow so the user knows it's still possible to get the beer, but it will not be in the right temperature and that the user should wait.

```c++
// If the temperature is higher than the target, turn on the cooling system
    if (current_temperature > max_target_temperature){
        
        // turn on the cooling system
        cooling_system.turn_on_cooling();

        // If it's the first iteration, turn the LED red so the user knows the machine won't release beer 
        if (first_iteration){

            // Turn the LED to red 
            power_button.set_color('R');
        }

        // If it's not the first iteration, the solenoid will continue to be open, but set the color to yellow so the user knows the beer is not within the temperature threshold
        if (!first_iteration){
            
            // Set the color to yellow
            power_button.set_color('Y');
        }
        
    }
```

If the temperature is equal or bellow the target, turn off the cooling and set the RGB color to solid green: 

```c++
// If the temperature is lower than the target, turn off the cooling system
    else if (current_temperature <= min_target_temperature){

        // turn off the cooling system 
        cooling_system.turn_off_cooling();

    }
```

If the temperature is within the threshold, open the valve and let the liquid flow, and set the RGB color to Green, so the user knows the machine is operating:

```c++
while (current_temperature <= max_target_temperature)
    {
        // Set the first iteration variable to false, since the timeperature already reached the threshold at least fir the first time
        first_iteration = false;

        // open the valve 
        valve.open_valve();

        // Set the button color to green, so the user knows the valve is open
        power_button.set_color('G');

    }
```