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

            // Set the default color to red 
            set_color('R');
        }

        bool is_pressed(){

            // read the input pin
            bool button_state = digitalRead(input_pin);
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
};