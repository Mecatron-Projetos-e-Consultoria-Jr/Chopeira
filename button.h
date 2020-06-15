#include "Arduino.h"

class button{

    private:

        int red_pin;
        int blue_pin;
        int green_pin;
        int input_pin;
        
        char color_name;

    public:

        button(int data_pin,int r_pin, int g_pin, int b_pin);

        // Checks if the button is being pressed
        bool is_pressed();

        // Sets the color of the RGB LED indicator, It receives the first Letter of the color in capital form (e.g set_color('R'))
        void set_color(char color);

        void turn_led_off();
        
        void boot_routine();
};
