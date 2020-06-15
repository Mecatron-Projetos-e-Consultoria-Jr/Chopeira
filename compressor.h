#include "Arduino.h"

class compressor {

    private:
        int pin;
    
    public:
    
        // Constructor for the compressor class
        compressor(int digital_pin);

        // Turn on the cooling system by closing the relay circuit that controls the compressor
        void turn_on_cooling();

        // Turn off the cooling system by oppening the relay circuit that controls the compressor
        void turn_off_cooling();

};
