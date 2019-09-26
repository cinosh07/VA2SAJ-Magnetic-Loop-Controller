
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
