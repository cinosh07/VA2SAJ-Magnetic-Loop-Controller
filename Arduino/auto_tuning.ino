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
//*****************************************
//
//    Trigger Start Auto Tuning Process
//
//*****************************************
void startAutoTune(int type) {

        if (type == CURRENT_POSITION_TYPE) {
                if (TUNED_STATUS == WRONG_POSITION) {
                        tuningProcess(getMemoryPosition(config.CURRENT_FRQ));
                } else if (TUNED_STATUS == STATUS_ERROR) {
                        //TODO TUNING STATUS_ERROR
                } else if (TUNED_STATUS == OK) {
                        tuningProcess(config.CURRENT_POSITION);
                }
        } else if (type == FOLLOW_TYPE) {
                //TODO TUNING FOLLOW_TYPE
        } else if (type == AUTO_TYPE) {
                //TODO TUNING AUTO_TYPE
        }
}
//*******************************************************************************
//
//     Check if capacitor stepper motor need to start an autotune process
//
//*******************************************************************************
void checkToAutotune() {
        if (config.AUTO_TUNE == true) {
                //TODO startAutoTune(type) if neededggg
                //TODO Check if current frequency has saved memory
        } else if (toAutotuned) {
                //toAutotuned
        }
}
//*********************************
//
//      Auto Tuning Process
//
//*********************************
void tuningProcess(uint32_t position) {
        goalSearchSteps = searchSteps[CURRENT_BAND];
        //uint32_t goalSearchSteps = searchSteps[CURRENT_BAND];
        int swrSamplingDelay = swrWaitDelay;
        int swrSamplingTreshold = tuningThreshold[CURRENT_BAND];
        boolean CWScanObsolete = false;
        boolean tunedPositionFound = false;
        uint32_t currentMinPosition = 0;
        int currentMinSWR = 0;
        //index 0 holds the value
        int currentSWR = 0;
        int wrongDirectionCounter = 0;
        boolean wrongDirection = false;

        resetTimers();
        motorStart();
        capacitorStepper.setSpeed(ultraHighSpeed);
        playBeep();
        //Begins the tuning procedure for the currently selected frequency
        TUNED_STATUS = WRONG_POSITION;
        int tempMode = CURRENT_MODE;
        CURRENT_MODE = TUNING;

        //Goes to the correct starting position of the current frequency
        blanckLCD();
        updateDisplay(position,STARTING_TUNING_MESSAGE);
        capacitorStepper.setSpeed(ultraHighSpeed);
        goToCapacitorPosition(position, TUNING, STARTING_TUNING_MESSAGE);
        playBeep();
        //Start Radio transmission at safe power level in RTTY Mode for tuning
        updateDisplay(position,WAITING_RADIO_TUNING_MESSAGE);
        delay(10);
        startRadioAutotune();

        currentMinPosition = config.CURRENT_POSITION;
        //read in the averaged swr sensor value here
        currentMinSWR = swrAverage(swrAverageSample);//averaging 10 samples

        //Search down counter clockwise, then return to middle and then search clockwise
        //Start search down counter clockwise
        while ((config.CURRENT_POSITION > position - goalSearchSteps) && config.CURRENT_POSITION > 0 && wrongDirection == false && checkLimitSwitch() == HIGH)
        {

                capacitorStepper.setSpeed(ultraHighSpeed);
                uint32_t goalPosition = 0;
                if (getSWR() < tuningThreshold[CURRENT_BAND]) {
                        goalPosition = config.CURRENT_POSITION+(ccw*SEARCH_FACTOR_FINE[CURRENT_BAND]);
                        goalSearchSteps = searchStepsFine[CURRENT_BAND];
                        swrSamplingDelay = swrWaitDelayFine;
                        swrSamplingTreshold = tuningThresholdFine[CURRENT_BAND];
                } else {
                        goalPosition = config.CURRENT_POSITION+(ccw*SEARCH_FACTOR[CURRENT_BAND]);
                        goalSearchSteps = searchSteps[CURRENT_BAND];
                        swrSamplingDelay = swrWaitDelay;
                        swrSamplingTreshold = tuningThreshold[CURRENT_BAND];
                }
                goToCapacitorPosition(goalPosition, TUNING, SCANNING_MESSAGE);
                delay(swrSamplingDelay);
                currentSWR = swrAverage(swrAverageSample); //delay time needed is >10*5ms = 50ms
                if (currentSWR < currentMinSWR)
                {
                        currentMinSWR = currentSWR;
                        if ( currentMinSWR < tuningThreshold[CURRENT_BAND]) {
                                tunedPositionFound = true;
                        }
                        currentMinPosition = config.CURRENT_POSITION;
                } else {

                        //Check if we are going in the wrong direction or bypassed the tuned point
                        //If true, stop scanning in this direction by setting wrongDirection variable to true
                        //This is done by checking if swr value in increasing more than the tuningThreshold over the last four reading
                        // (tuningThreshold contains value per band stored in an array. It is the minimum difference between
                        // currentSWR and currentMinSWR that is needed to trigger a wrong position counter increase  )
                        if (wrongDirectionCounter < 4 && currentSWR - currentMinSWR > swrSamplingTreshold) {
                                wrongDirectionCounter = wrongDirectionCounter + 1;
                        } else if (wrongDirectionCounter == 4) {
                                //Check if second step is obsolete to do. i.e. The scan has bypassed the lowest swr tuned point.
                                //Then set CWScanObsolete=true; So the clockwise scan will be bypassed
                                wrongDirection = true;
                        }
                }
        }

        //Check if we bypassed the tuned point and found a tuned position. If true the scan in ccw direction is obsolete
        if (wrongDirection == true && tunedPositionFound == true) {
                CWScanObsolete = true;
        }
        //Reset to default value before starting the scan in the oposite direction
        wrongDirection = false;
        wrongDirectionCounter = 0;
        goalSearchSteps = searchSteps[CURRENT_BAND];
        swrSamplingDelay = swrWaitDelay;
        swrSamplingTreshold = tuningThreshold[CURRENT_BAND];
        //Stop Radio transmission
        updateDisplay(position,WAITING_RADIO_TUNING_MESSAGE);
        delay(10);
        stopRadioAutotune();
        if (CWScanObsolete == true) {
                updateDisplay(position,FINISH_TUNING_MESSAGE);
        } else {
                updateDisplay(position,MIDPOINT_TUNING_MESSAGE);
        }

        playBeep();

        //Start search clockwise if needed
        if (CWScanObsolete == false) {
                //return to middle position
                capacitorStepper.setSpeed(ultraHighSpeed);
                goToCapacitorPosition(position, TUNING, MIDPOINT_TUNING_MESSAGE);
                //Start Radio transmission at safe power level in RTTY Mode for tuning
                updateDisplay(position,WAITING_RADIO_TUNING_MESSAGE);
                delay(10);
                startRadioAutotune();
        }
        while ((config.CURRENT_POSITION < position + goalSearchSteps) && config.CURRENT_POSITION < maxSteps && wrongDirection == false && CWScanObsolete == false && checkLimitSwitch() == HIGH)
        {
                capacitorStepper.setSpeed(ultraHighSpeed);
                uint32_t goalPosition = 0;
                if (getSWR() < tuningThreshold[CURRENT_BAND]) {
                        goalPosition = config.CURRENT_POSITION+(cw*SEARCH_FACTOR_FINE[CURRENT_BAND]);
                        goalSearchSteps = searchStepsFine[CURRENT_BAND];
                        swrSamplingDelay = swrWaitDelayFine;
                        swrSamplingTreshold = tuningThresholdFine[CURRENT_BAND];
                } else {
                        goalPosition = config.CURRENT_POSITION+(cw*SEARCH_FACTOR[CURRENT_BAND]);
                        goalSearchSteps = searchSteps[CURRENT_BAND];
                        swrSamplingDelay = swrWaitDelay;
                        swrSamplingTreshold = tuningThreshold[CURRENT_BAND];
                }
                goToCapacitorPosition(goalPosition, TUNING, SCANNING_MESSAGE);
                delay(swrSamplingDelay);
                currentSWR = swrAverage(swrAverageSample);
                if (currentSWR < currentMinSWR)
                {
                        currentMinSWR = currentSWR;
                        currentMinPosition = config.CURRENT_POSITION;
                } else {
                        //Check if we are going in the wrong direction or bypassed the tuned point
                        //If true, stop scanning in this direction by setting wrongDirection variable to true
                        //This is done by checking if swr value in increasing more than the tuningThreshold over the last four reading
                        // (tuningThreshold contains value per band stored in an array. It is the minimum difference between
                        // currentSWR and currentMinSWR that is needed to trigger a wrong position counter increase  )
                        if (wrongDirectionCounter < 4 && currentSWR - currentMinSWR > swrSamplingTreshold) {
                                wrongDirectionCounter = wrongDirectionCounter + 1;
                        } else if (wrongDirectionCounter == 4 )  {
                                wrongDirection = true;
                        }
                }
        }
        if (CWScanObsolete == false) {
                //Stop Radio transmission
                updateDisplay(position,WAITING_RADIO_TUNING_MESSAGE);
                delay(10);
                stopRadioAutotune();
        }
        capacitorStepper.setSpeed(ultraHighSpeed);
        updateDisplay(position,FINISH_TUNING_MESSAGE);
        goToCapacitorPosition(currentMinPosition, TUNING, FINISH_TUNING_MESSAGE);
        motorStop();

        //Check if the tuned frequency meet the maximum swr limit.
        //If it reached the limit it will not save the memory and notify swr error
        if (currentMinSWR > swrThreshod[CURRENT_BAND]) {
                updateDisplay(position,SWR_ERROR_TUNING_MESSAGE);
                playAlarmSWR();
                delay(2000);
                CURRENT_MODE = tempMode;
                startSaveConfig();
        } else {
                CURRENT_MODE = tempMode;
                startSaveConfig();
                saveCurrentMemory();
        }
        checkMemories();
        blanckLCD();
        updateDisplay(position,"");
}
//*************************************************************
//
//   Get the stepper position offset for Side band Operation
//
//*************************************************************
uint32_t getModePositionOffset() {
        if (radio.trx_mode == MODE_TYPE_LSB ) {
                return LSB_POSITION_OFFSET[CURRENT_BAND];
        } else if (radio.trx_mode == MODE_TYPE_USB  ) {
                return USB_POSITION_OFFSET[CURRENT_BAND];
        } else {
                return 0;
        }
}
