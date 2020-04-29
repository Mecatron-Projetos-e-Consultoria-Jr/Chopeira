// #define log(x) Serial.println(x)

class solenoid {

    private:
        int pin;

    public:

        solenoid(int output_pin){
            pin = output_pin;
            pinMode(pin,OUTPUT);
        }

        void open_valve(){

            // Open the valve so the liquid comes out 
            digitalWrite(pin,HIGH);
            Serial.println("[solenoid.h]Setting solenoid to HIGH");
        }

        void close_valve(){

            // Close the valve 
            digitalWrite(pin,LOW);
            Serial.println("[solenoid.h]Setting solenoid to LOW");
        }

};
