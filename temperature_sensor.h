// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
//  Estarei utilizando o sensor ts-m6 como base. Link para datasheet abaixo                                                // 
//  https://www.autosportlabs.com/wp-content/uploads/2014/01/texense-TS-103.pdf                                            // 
//                                                                                                                         // 
//  red - supply (5v)                                                                                                      // 
//  white - signal (analog input)                                                                                          // 
//  blue/black - GND                
//    
// 
//  -50ºC ------- 0.225v
// 
//  +0.0225 V para cada 1ºC de aumento
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 


// Create class to use the liquid temperature sensor 
class temperature_sensor
{
    private:
        int pin;
        float base_voltage = 0.225;

    public:

        // Constructor 
        temperature_sensor(int signal_pin){

            // declare the pin as input
            pin = signal_pin;
            pinMode(pin, INPUT);
            
        }

        // function to read the temp 
        float get_current_temperature(){

            // Get the analog input
            int raw_input = analogRead(pin);

            // Convert the analog input to voltage         
            float input_voltage = map(raw_input,0,255,0,5); // map(value, fromLow, fromHigh, toLow, toHigh)

            // Get difference in voltage and calculate the current temperature
            float difference_in_voltage = input_voltage - base_voltage;

            // For every 0.0225v  there is an increase of 1 C 
            float current_temp = (difference_in_voltage/0.0225) - 50;

            // return the value
            return current_temp;
        }

};
