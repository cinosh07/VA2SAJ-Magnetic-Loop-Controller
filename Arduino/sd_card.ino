/*
   Mag loop antenna auto tuner

   Created 30 March. 2019
   Updated september 26th 2019
   by Carl Tremblay - VA2SAJ AKA cinosh07

   Attribution-NonCommercial 2.0 Generic (CC BY-NC 2.0) License

   code and circuitry inspired from
   https://create.arduino.cc/editor/JMardling/67243a05-af85-4b7b-832c-b67a56f8b77c/preview
   www.ve1zac.com/Simple%20Loop%20Automatic%20Tuner.pdf
   https://sites.google.com/site/lofturj/to-automatically-tune-a-magnetic-loop-antenna
 */
//*******************************************
//
//     Initialization of SD Card Reader
//
//*******************************************
void initSDCard() {

        pinMode( networkShieldCSPin, OUTPUT);
        digitalWrite( networkShieldCSPin, HIGH  );
        pinMode(sdCardCSPin, OUTPUT);
        digitalWrite(sdCardCSPin, HIGH);
        if (!SD.begin(sdCardCSPin)) {
                playAlarmNOSD();;
                sdCardPresent = false;
#ifdef DEBUG
                Serial.println("initialization failed!");
#endif
                return;
        } else {
                sdCardPresent = true;
        }
        loadConfiguration(filename, config);
}
//******************************************************
//
//      Switch SPI interface to use SD Card Shield
//
//******************************************************
void activateSDCard() {
        digitalWrite( networkShieldCSPin, HIGH  );
        digitalWrite(sdCardCSPin, LOW);
        delay(50);
}
