# Chopeira Documentation 


1. [Button class](#Button-Class)  <br>
2. [Compressor class](#Compressor-Class) <br>
3. [Solenoid class](#Solenoid-Class)

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