
class button{

    private:

        int red_pin;
        int blue_pin;
        int green_pin;
        int input_pin;
        
        char color_name;

    public:
        button(int data_pin,int r_pin, int g_pin, int b_pin){

             red_pin = r_pin;
             blue_pin = b_pin;
             green_pin = g_pin;
             input_pin = data_pin;

             // set the pin mode to output
             pinMode(red_pin,OUTPUT);
             pinMode(blue_pin,OUTPUT);
             pinMode(green_pin,OUTPUT);

             // set the pin mode for the button to input
             pinMode(input_pin,INPUT);
        }

        bool is_pressed(){

            // read the input pin
            bool button_state = digitalRead(input_pin);
            log_message(F("[button.h]Button Pressed"));

            return button_state;
        }

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
                    
                    log_message(F("[button.h]Setting LED color to RED"));
                    break;

                
                
                case 'G':
                    analogWrite(green_pin,255);
                    analogWrite(blue_pin,0);
                    analogWrite(red_pin,0);

                    log_message(F("[button.h]Setting LED color to GREEN"));
                    break;



                case 'Y':
                    analogWrite(green_pin,255);
                    analogWrite(blue_pin,0);
                    analogWrite(red_pin,255);

                    log_message(F("[button.h]Setting LED color to YELLOW"));
                    break;
            }
        }

         void turn_led_off(){

            // Turn the LED off
            analogWrite(red_pin,0);
            analogWrite(blue_pin,0);
            analogWrite(green_pin,0);
            log_message(F("[button.h]Turning LED off"));
        }
        
        void boot_routine(){

            // blink 3 times the led with the green color, to let the user know the boot sequence is starting
            for (int i = 0; i < 3; i++){

                button::set_color('G');
                log_message(F("[button.h]Turning on the LED - GREEN"));
                delay(1000);
                button::turn_led_off();
                log_message(F("[button.h]Turning LED off"));
                delay(1000);
            }
            
        }
};
