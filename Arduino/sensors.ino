/*
   Mag loop antenna auto tuner

   Created 30 March. 2019
   Updated september 26th 2019
   by Carl Tremblay - VA2SAJ AKA cinosh07

   Attribution-NonCommercial 2.0 Generic (CC BY-NC 2.0) License
   https://creativecommons.org/licenses/by-nc/2.0/

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
   OR OTHER DEALINGS IN THE SOFTWARE.

   code and circuitry inspired from
   https://create.arduino.cc/editor/JMardling/67243a05-af85-4b7b-832c-b67a56f8b77c/preview
   www.ve1zac.com/Simple%20Loop%20Automatic%20Tuner.pdf
   https://sites.google.com/site/lofturj/to-automatically-tune-a-magnetic-loop-antenna
 */
//***************************************
//
//  Check if limit switch is reached
//
//***************************************
int checkLimitSwitch() {
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
                updateDisplay(0,"");
                gotoPositionLock = false;
        }
}
//***************************************************************************
//
//    Sampling an average swr sensor value from numSamples(int) readings
//
//***************************************************************************
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
//************************************************
//
//      Check if SWR limit has been reached
//
//************************************************
int getRFSignal() {
        int rfValue = 0;
  #ifdef RF_SENSOR
        //TODO Get RF Received Strengh via external sensor

  #else
  #ifdef ICOM
        icom_request_signal();
        delay(10);
        getRadioStatus();
        rfvalue = rfAverage(5);

  #endif
  #ifdef YEASU
        //TODO
  #endif
  #ifdef KENWOOD
        //TODO
  #endif
  #ifdef ELECCRAFT
        //TODO
  #endif
  #ifdef OTHER
        //TODO
  #endif
  #endif
        return rfValue;
}

//***************************************************************************
//
//    Sampling an average swr sensor value from numSamples(int) readings
//
//***************************************************************************
int rfAverage(int 5) {

        //returns averaged value of numsamples swrValue samples
        icom_request_signal();
        delay(10);
        getRadioStatus();
        int rfValue = 0;
        for (int i = 0; i < numSamples; i++)
        {
          #ifdef ICOM
                rfValue += radio.trx_signal;
                icom_request_signal();
                delay(10);
                getRadioStatus();

          #endif
          #ifdef YEASU
                //TODO
          #endif
          #ifdef KENWOOD
                //TODO
          #endif
          #ifdef ELECCRAFT
                //TODO
          #endif
          #ifdef OTHER
                //TODO
          #endif

        }
        //average swrvalue
        return rfValue / numSamples;
}
