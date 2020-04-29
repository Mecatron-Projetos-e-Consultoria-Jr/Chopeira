#define log(x) Serial.println(x)

class compressor {

    private:
        int pin;
    
    public:
    
        compressor(int digital_pin){

            pinMode(digital_pin,OUTPUT);
            pin = digital_pin;
        }

        void turn_on_cooling(){

            // Close the relay (so the cooler turns on)
            digitalWrite(pin,HIGH);
            log("[compressor.h]Setting cooling to HIGH");
        }

        void turn_off_cooling(){

            // Open the relay
            digitalWrite(pin,LOW);
            log("[compressor.h]Setting cooling to LOW");
        }

};
