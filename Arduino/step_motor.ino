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
//**************************************************************************************
//
// Check if capacitor stepper is needed to move to the current radio frequency position
//
//**************************************************************************************
void checkToFollow() {
        if (config.AUTO_FOLLOW == true && TUNED_STATUS == WRONG_POSITION && toTunedPositionChange == true) {
                toTunedPositionChange == false;
                toTunedPositionTimeoutCycle = 0;
                playBeep();
                capacitorStepper.setSpeed(ultraHighSpeed);
                motorStart();
                goToCapacitorPosition(toTunedPosition, SEARCHING, "");
                motorStop();
                TUNED_STATUS = OK;
                toTunedPositionChange = false;
                toTunedPositionTimeoutCycle = 0;
                refreshTimer.check();
                playBeepBeep();
                resetScreenSaver();
                returnToHomeMenu();
        }
}
//*******************************************************
//
//                  Step Motor Stop
//
//    This is needed to prevent driver from running
// current through a stationary winding and preventing
//              noise in the rf signal
//
//*******************************************************

void motorStop()
{
        digitalWrite(sleeppin, LOW);
        digitalWrite(resetpin, LOW);
}
//*********************************
//
//        Step Motor Start
//
//*********************************
void motorStart()
{
        digitalWrite(sleeppin, HIGH);
        digitalWrite(resetpin, HIGH);
}
//***************************************
//
//  Step Motor Go To Capacitor Position
//
//***************************************
void goToCapacitorPosition(uint32_t position, int mode, String MESSAGE)
{
        //Move capacitor step motor quickly to the provided position
        if (gotoPositionLock == false) {
                gotoPositionLock = true;
                //Definning the absolute start position from the current position
                uint32_t startPosition = config.CURRENT_POSITION;

                resetScreenSaver();
                int tempMode = CURRENT_MODE;
                CURRENT_MODE = mode;
                updateDisplay(position,MESSAGE);
                int direction;
                if (config.CURRENT_POSITION < position)
                {
                        direction = cw; // Clockwise direction
                } else {
                        direction = ccw; // Counter Clockwise direction
                }
                //While the goal position is not reached, continue to move
                while (config.CURRENT_POSITION != position && config.CURRENT_POSITION < maxSteps && config.CURRENT_POSITION > 0 && checkLimitSwitch() == HIGH)
                {
                        capacitorStepper.step(direction);
                        resetScreenSaver();
                        config.CURRENT_POSITION = config.CURRENT_POSITION + direction;
                }
                CURRENT_MODE = tempMode;
                if (mode != TUNING) {
                        updateDisplay(position,"");
                        startSaveConfig();
                }


                gotoPositionLock = false;
        }
}
//***************************************
//
//      Return to Home comnmand
//
//***************************************
void returnToHome() {
        TUNED_STATUS = STATUS_ERROR;
        updateDisplay(0,"");
  #ifdef LIMIT_SWITCH
        returnToHomeLimitSwitch();
  #else
        capacitorStepper.setSpeed(ultraHighSpeed);
        motorStart();
        goToCapacitorPosition(0, SEARCHING, "");
        motorStop();
        #endif
}
