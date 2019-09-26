//****************************************************
//
//            Menus and Buttons Navigation
//
//****************************************************
void menuNavigationCheck() {
        int switchState = digitalRead(switchPin);
        // Si le screensaver est present, afficher le menu home
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
                //Bouton Menu (Navigation)
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
                //Bouton Joystick Mode Home (Tests)
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
                //Bouton A Mode Home ( Autotune this frequecy )
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
                //Bouton B Mode Home ( Follow this frequency )
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
                //Bouton Joystick Mode Settings (Afficher le Mode Reset des positions par default des Bandes)
                while (digitalRead(buttonJoystickPin) == LOW && CURRENT_MODE == SETTINGS)
                {
                        CURRENT_MODE = RESETONE;
                        resetScreenSaver();
                        playShortBeep();
                }

                //Bouton A Mode Settings ( Set Auto Tune Mode )
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == SETTINGS )
                {
                        config.AUTO_TUNE = !config.AUTO_TUNE;
                        refreshTimer.check();
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
                        startSaveConfig();

                }
                //Bouton B Mode Settings ( Set Auto Follow Mode)
                while (digitalRead(buttonBPin) == LOW && CURRENT_MODE == SETTINGS)
                {
                        config.AUTO_FOLLOW = !config.AUTO_FOLLOW;
                        playBeepBeep();
                        resetScreenSaver();
                        returnToHomeMenu();
                        startSaveConfig();
                        refreshTimer.check();
                }
                //Bouton C Mode Settings ( Calibration Mode )
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
                //Bouton Joystick Mode GOTOONE ( Return to home - Zero)
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
                //Bouton A Mode GOTOONE ( Goto 10M position)
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
                //Bouton B Mode GOTOONE ( Goto 12M position )
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
                //Bouton C Mode GOTOONE ( Goto 15M position )
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
                //Bouton Joystick Mode GOTOTWO ( Goto 17M position )
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
                //Bouton A Mode GOTOTWO ( Goto 20M position)
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
                //Bouton B Mode GOTOTWO ( Goto 30M position)
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
                //Bouton C Mode GOTOTWO ( Goto 40M position)
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
                //Bouton A Mode GOTOTHREE ( Goto 60M position)
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
                //Bouton B Mode GOTOTHREE ( Goto 80M position)
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
                //Bouton C Mode GOTOTHREE ( Goto 160M position)
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
                //Bouton A Mode Coarse (Goto Fine Tune Menu)
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == COARSE_TUNE )
                {
                        CURRENT_MODE = FINE_TUNE;
                        highSpeed = highSpeedFine;
                        refreshJoystickRange();
                        playShortBeep();
                        resetScreenSaver();
                }
                //Bouton B Mode Coarse (AutoTune current Frenquency and save)
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
                //Bouton C Mode Coarse (Save current Frequency position)
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
                //Bouton A Mode Fine (Goto Coarse Tune Menu)
                while (digitalRead(buttonAPin) == LOW && CURRENT_MODE == FINE_TUNE )
                {
                        CURRENT_MODE = COARSE_TUNE;
                        highSpeed = highSpeedCoarse;
                        refreshJoystickRange();
                        playShortBeep();
                        resetScreenSaver();
                }

                //Bouton B Mode Fine (AutoTune current Frenquency and save)
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

                //Bouton C Mode Fine (Save current Frequency position)
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
                //Bouton Joystick Mode RESETONE ( Return to home - Zero)
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
                //Bouton A Mode RESETONE ( Reset 10M )
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
                //Bouton B Mode RESETONE ( Reset 12M )
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
                //Bouton C Mode RESETONE ( Reset 15M )
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
                //Bouton Joystick Mode RESETTWO (  Reset 17M )
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
                //Bouton A Mode RESETTWO ( Reset 20M )
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
                //Bouton B Mode RESETTWO ( Reset 30M )
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
                //Bouton C Mode RESETTWO ( Reset 40M )
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
                //Bouton A Mode RESETTHREE ( Reset 60M )
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
                //Bouton B Mode RESETTHREE ( Reset 80M )
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
                //Bouton C Mode RESETTHREE ( Reset 160M )
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
