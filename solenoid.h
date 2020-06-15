#include "Arduino.h"

class solenoid {

    private:
        int pin;

    public:

        // Constructor for the solenoid class, It takes the arduino Pin number as a parameter
        solenoid(int output_pin);

        // Open the solenoid valve 
        void open_valve();

        // Close the solenoid valve 
        void close_valve();

};
