namespace debug{
        
    inline void log_message(String x){

        Serial.println(x);
    }

    template <typename T>
    inline void log_number(T x){

        Serial.println(x);
    }
}