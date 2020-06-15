#include "button.h"

button::button(int r_pin, int g_pin, int b_pin){

        red_pin = r_pin;
        blue_pin = b_pin;
        green_pin = g_pin;

        // set the pin mode to output
        pinMode(red_pin,OUTPUT);
        pinMode(blue_pin,OUTPUT);
        pinMode(green_pin,OUTPUT);

}

void button::set_color(char color){

            color_name = color;

            switch (color){
                case 'R':


                    analogWrite(red_pin,255);
                    analogWrite(blue_pin,0);
                    analogWrite(green_pin,0);

                    // wait 500 milliseconds,  turn of -> so it will blink until the color changes to green
                    delay(250);

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
                    analogWrite(green_pin,50);
                    analogWrite(blue_pin,0);
                    analogWrite(red_pin,255);

                    break;
            }
        }

void button::turn_led_off(){

    // Turn the LED off
    analogWrite(red_pin,0);
    analogWrite(blue_pin,0);
    analogWrite(green_pin,0);
}

void button::boot_routine(){

    // blink 3 times the led with the green color, to let the user know the boot sequence is starting
    for (int i = 0; i < 3; i++){

        button::set_color('G');
        delay(1000);
        button::turn_led_off();
        delay(1000);
    }
    
}