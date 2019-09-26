//***************************************
//
//  Check if limit switch is reached
//
//***************************************
void checkLimitSwitch() {
  #ifdef LIMIT_SWITCH
        return digitalRead(limitSwitch);
  #else
        return HIGH;
  #endif
}
//*************************************************************************
//
//             Step Motor Return to home with a limit switch
//  Don't use this function directly. Use returnToHome() function instead
//
//*************************************************************************
void returnToHomeLimitSwitch() {
        //zeroing with limit switch
        if (gotoPositionLock == false) {
                gotoPositionLock = true;
                //Definning the absolute start position from the current position


                resetScreenSaver();
                int tempMode = CURRENT_MODE;
                CURRENT_MODE = mode;
                updateDisplay(0,"");
                int direction = ccw;

                //While the goal position is not reached, continue to move
                while (checkLimitSwitch() == HIGH)
                {
                        capacitorStepper.step(direction);
                        resetScreenSaver();
                        config.CURRENT_POSITION = config.CURRENT_POSITION + direction;
                }
                CURRENT_MODE = tempMode;

                config.CURRENT_POSITION = 0;
                updateDisplay(position,"");
                gotoPositionLock = false;
        }
}
//************************************************
//
//   Echantillonnage de la valeur du SWR Sensor
//
//************************************************
uint32_t swrAverage(int numSamples) {

        //returns averaged value of numsamples swrValue samples
        uint32_t swrValue = 0;
        for (int i = 0; i < numSamples; i++)
        {
                swrValue += (uint32_t) getSWR();
                delay(5);//wait 5ms between samples
        }
        //average swrvalue
        return swrValue / (uint32_t) numSamples;
}
//************************************************
//
//        Get the SWR Value of the sensor
//
//************************************************
int getSWR() {
  #ifdef SWR_SENSOR
        return analogRead(swrSensorPin);
  #endif
  #ifdef SWR_RADIO
        return (int) radio.trx_swr;
  #endif
}
//************************************************
//
//   Check if SWR limit Alarm is needed to play
//
//************************************************
void checkSWRAlarm(boolean limitReached) {
        if (CURRENT_MODE == TXMITING && limitReached == true && swrAlarm == true) {
                playAlarmSWR();
        }
}
//************************************************
//
//      Check if SWR limit has been reached
//
//************************************************
boolean checkSWRLimit() {
  #ifdef SWR_SENSOR
        if ( analogRead(swrSensorPin) > swrThreshod[CURRENT_BAND]) {
                return true;
        } else {
                return false;
        }
  #endif
  #ifdef SWR_RADIO
        if (radio.trx_swr > (uint8_t) swrThreshod[CURRENT_BAND]) {
                return true;
        } else {
                return false;
        }
  #endif
}