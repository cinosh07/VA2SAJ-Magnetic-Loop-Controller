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
//****************************************************
//
//            Menus and Buttons Navigation
//
//****************************************************
void menuNavigationCheck() {
        int switchState = digitalRead(switchPin);
        // If screesaver is present, clear it and display home
        if (CURRENT_MODE == HOME && screensaver == true) {
                if (switchState != lastSwitchState) {
                        if (switchState == HIGH) {
                                resetScreenSaver();
                                blanckLCD();
                        }
                }
                // save switch state for next comparison:
                lastSwitchState = switchState;
        } else {
                // Menu button(Navigation)
                if (switchState != lastSwitchState) {
                        if (switchState == HIGH) {
                                if (CURRENT_MODE == HOME) {
                                        CURRENT_MODE = COARSE_TUNE;
                                        highSpeed = highSpeedCoarse;
                                        refreshJoystickRange();
                                } else if (CURRENT_MODE == COARSE_TUNE) {
                                        CURRENT_MODE = GOTOONE;
                                } else if (CURRENT_MODE == FINE_TUNE) {
                                        CURRENT_MODE = GOTOONE;
                                }
                                else if (CURRENT_MODE == GOTOONE) {
                                        CURRENT_MODE = GOTOTWO;
                                }
                                else if (CURRENT_MODE == GOTOTWO) {
                                        CURRENT_MODE = GOTOTHREE;
                                }
                                else if (CURRENT_MODE == GOTOTHREE) {
                                        CURRENT_MODE = SETTINGS;
                                }
                                else if (CURRENT_MODE == SETTINGS) {
                                        CURRENT_MODE = HOME;
                                }
                                else if (CURRENT_MODE == RESETONE) {
                                        CURRENT_MODE = RESETTWO;
                                }
                                else if (CURRENT_MODE == RESETTWO) {
                                        CURRENT_MODE = RESETTHREE;
                                }
                                else if (CURRENT_MODE == RESETTHREE) {
                                        CURRENT_MODE = HOME;
                                }
                                resetScreenSaver();
                                playShortBeep();
                        }
                }
                // save switch state for next comparison:
                lastSwitchState = switchState;
                //****************************************************
                //                   HOME Page
                //****************************************************
                //Joystick button Mode Home (Tests)
                while (digitalRead(buttonJoystickPin) == LOW && CURRENT_MODE == HOME)
                {
                        if (txmiting == false) {
                                txmiting = true;
                                startRadioAutotune();
                        } else {
                                txmiting = false;
                                stopRadioAutotune();
                        }
                        playShortBeep();
                }
                //A Button Mode Home ( Autotune this frequecy )
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == HOME )
                {
                        CURRENT_MODE == TUNING;
                        resetScreenSaver();
                        if (config.AUTO_FOLLOW == false) {
                                startAutoTune(CURRENT_POSITION_TYPE);
                        } else {
                                startAutoTune(FOLLOW_TYPE);
                        }
                        playBeepBeep();

                }
                //B Button Mode Home ( Follow this frequency )
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == HOME)
                {

                        resetScreenSaver();
                        if (config.AUTO_FOLLOW == false && TUNED_STATUS == WRONG_POSITION) {
                                CURRENT_MODE == SEARCHING;
                                resetScreenSaver();
                                toTunedPositionChange == false;
                                toTunedPositionTimeoutCycle = 0;
                                playBeep();
                                capacitorStepper.setSpeed(ultraHighSpeed);
                                motorStart();
                                goToCapacitorPosition(toTunedPosition, SEARCHING, "");
                                motorStop();
                                checkMemories();
                                toTunedPositionChange = false;
                                toTunedPositionTimeoutCycle = 0;
                                refreshTimer.check();
                                playBeepBeep();
                                returnToHomeMenu();
                        }


                }
                //****************************************************
                //                   SETTINGS Page
                //****************************************************
                //Joystick Button Mode Settings (Afficher le Mode Reset des positions par default des Bandes)
                while (digitalRead(buttonJoystickPin) == LOW && CURRENT_MODE == SETTINGS)
                {
                        CURRENT_MODE = RESETONE;
                        resetScreenSaver();
                        playShortBeep();
                }

                //A Button Mode Settings ( Set Auto Tune Mode )
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == SETTINGS )
                {
                        config.AUTO_TUNE = !config.AUTO_TUNE;
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
                        startSaveConfig();

                }
                //B Button Mode Settings ( Set Auto Follow Mode)
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == SETTINGS)
                {
                        config.AUTO_FOLLOW = !config.AUTO_FOLLOW;
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
                        startSaveConfig();
                        refreshTimer.check();
                }
                //C Button Mode Settings ( Calibration Mode )
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == SETTINGS)
                {
                        playBeep();
                        CURRENT_MODE = RETURN_HOME;
                        updateDisplay(0,"");
                        returnToHome();
                        CURRENT_MODE = CALIBRATION;
                        updateDisplay(0,SCANNING_MESSAGE);
                        calibrate();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
                        startSaveConfig();
                        refreshTimer.check();
                }
                //****************************************************
                //                      GOTO Page 1
                //****************************************************
                //Joystick Button Mode GOTOONE ( Return to home - Zero)
                while (digitalRead(buttonJoystickPin) == LOW && CURRENT_MODE == GOTOONE)
                {
                        playBeep();
                        returnToHome();
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();

                }
                //A Button Mode GOTOONE ( Goto 10M position)
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == GOTOONE )
                {
      #ifdef ANTENNA_BAND_10M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS10M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //B Button Mode GOTOONE ( Goto 12M position )
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == GOTOONE)
                {
      #ifdef ANTENNA_BAND_12M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS12M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //C Button Mode GOTOONE ( Goto 15M position )
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == GOTOONE)
                {
      #ifdef ANTENNA_BAND_15M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS15M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //****************************************************
                //                      GOTO Page 2
                //****************************************************
                //Joystick Button Mode GOTOTWO ( Goto 17M position )
                while (digitalRead(buttonJoystickPin) == LOW && CURRENT_MODE == GOTOTWO)
                {

#ifdef ANTENNA_BAND_17M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS17M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //A Button Mode GOTOTWO ( Goto 20M position)
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == GOTOTWO )
                {
      #ifdef ANTENNA_BAND_20M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS20M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //B Button Mode GOTOTWO ( Goto 30M position)
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == GOTOTWO )
                {
      #ifdef ANTENNA_BAND_30M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS30M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //C Button Mode GOTOTWO ( Goto 40M position)
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == GOTOTWO )
                {
      #ifdef ANTENNA_BAND_40M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS40M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //****************************************************
                //                      GOTO Page 3
                //****************************************************
                //A Button Mode GOTOTHREE ( Goto 60M position)
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == GOTOTHREE )
                {
      #ifdef ANTENNA_BAND_60M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS60M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //B Button Mode GOTOTHREE ( Goto 80M position)
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == GOTOTHREE )
                {
      #ifdef ANTENNA_BAND_80M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS80M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //C Button Mode GOTOTHREE ( Goto 160M position)
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == GOTOTHREE )
                {
      #ifdef ANTENNA_BAND_160M
                        playBeep();
                        capacitorStepper.setSpeed(ultraHighSpeed);
                        motorStart();
                        goToCapacitorPosition(config.POS160M, SEARCHING, "");
                        motorStop();
                        TUNED_STATUS = STATUS_ERROR;
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #endif
                }
                //****************************************************
                //              Manual Coarse Tune Page
                //****************************************************
                //A Button Mode Coarse (Goto Fine Tune Menu)
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == COARSE_TUNE )
                {
                        CURRENT_MODE = FINE_TUNE;
                        highSpeed = highSpeedFine;
                        refreshJoystickRange();
                        playShortBeep();
                        resetScreenSaver();
                }
                //B Button Mode Coarse (AutoTune current Frenquency and save)
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == COARSE_TUNE )
                {
                        if (config.AUTO_FOLLOW == false) {
                                startAutoTune(CURRENT_POSITION_TYPE);
                        } else {
                                startAutoTune(FOLLOW_TYPE);
                        }
                        resetScreenSaver();
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();

                }
                //C Button Mode Coarse (Save current Frequency position)
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == COARSE_TUNE )
                {
                        saveCurrentMemory();
                        resetScreenSaver();
                        TUNED_STATUS = OK;
                        returnToHomeMenu();
                        playBeepBeep();
                }
                //****************************************************
                //              Manual Fine Tune Page
                //****************************************************
                //A Button Mode Fine (Goto Coarse Tune Menu)
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == FINE_TUNE )
                {
                        CURRENT_MODE = COARSE_TUNE;
                        highSpeed = highSpeedCoarse;
                        refreshJoystickRange();
                        playShortBeep();
                        resetScreenSaver();
                }

                //B Button Mode Fine (AutoTune current Frenquency and save)
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == FINE_TUNE )
                {
                        if (config.AUTO_FOLLOW == false) {
                                startAutoTune(CURRENT_POSITION_TYPE);
                        } else {
                                startAutoTune(FOLLOW_TYPE);
                        }
                        resetScreenSaver();
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                }

                //C Button Mode Fine (Save current Frequency position)
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == FINE_TUNE )
                {
                        saveCurrentMemory();
                        resetScreenSaver();
                        TUNED_STATUS = OK;
                        returnToHomeMenu();
                        playBeepBeep();
                }
                //****************************************************
                //                     Reset Page One
                //****************************************************
                //Joystick Button Mode RESETONE ( Return to home - Zero)
                while (digitalRead(buttonJoystickPin) == LOW && CURRENT_MODE == RESETONE)
                {

      #ifdef LIMIT_SWITCH
                        playBeep();
                        returnToHome();
                        checkMemories();
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
      #else
                        config.CURRENT_POSITION = 0;
                        config.ISCALIB = true;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //A Button Mode RESETONE ( Reset 10M )
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == RESETONE)
                {
      #ifdef ANTENNA_BAND_10M
                        config.POS10M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //B Button Mode RESETONE ( Reset 12M )
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == RESETONE)
                {
      #ifdef ANTENNA_BAND_12M
                        config.POS12M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //C Button Mode RESETONE ( Reset 15M )
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == RESETONE)
                {
      #ifdef ANTENNA_BAND_15M
                        config.POS15M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //****************************************************
                //                     Reset Page Two
                //****************************************************
                //Joystick Button Mode RESETTWO (  Reset 17M )
                while (digitalRead(buttonJoystickPin) == LOW && CURRENT_MODE == RESETTWO)
                {

#ifdef ANTENNA_BAND_17M
                        config.POS17M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif

                }
                //A Button Mode RESETTWO ( Reset 20M )
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == RESETTWO)
                {
      #ifdef ANTENNA_BAND_20M
                        config.POS20M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //B Button Mode RESETTWO ( Reset 30M )
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == RESETTWO)
                {
      #ifdef ANTENNA_BAND_30M
                        config.POS30M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //C Button Mode RESETTWO ( Reset 40M )
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == RESETTWO)
                {
      #ifdef ANTENNA_BAND_40M
                        config.POS40M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //****************************************************
                //                 Reset Page Three
                //****************************************************
                //A Button Mode RESETTHREE ( Reset 60M )
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == RESETTHREE)
                {
      #ifdef ANTENNA_BAND_60M
                        config.POS60M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //B Button Mode RESETTHREE ( Reset 80M )
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == RESETTHREE)
                {
      #ifdef ANTENNA_BAND_80M
                        config.POS80M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
                //C Button Mode RESETTHREE ( Reset 160M )
                while (digitalRead(buttonCPin) == LOW && CURRENT_MODE == RESETTHREE)
                {
      #ifdef ANTENNA_BAND_160M
                        config.POS160M = config.CURRENT_POSITION;
                        returnToHomeMenu();
                        startSaveConfig();
                        playBeepBeep();
                        resetScreenSaver();
      #endif
                }
        }
}
void returnToHomeMenu() {
        CURRENT_MODE = HOME;
}
