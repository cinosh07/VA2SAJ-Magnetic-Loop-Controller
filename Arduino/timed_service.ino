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
//****************************************************
//
//            Timed Services update
//
//****************************************************
void RefreshServices() {
        if (HRD_PRESENT == false) {
                getRadioStatus();
        }
        checkTimeout();
        checkScreenSaver();
        checkFrequencyChange();
        checkToFollowTimer();
        if (screensaver == true) {
                RunScreenSaver();
        } else {
                updateDisplay(0,"");
        }
}
//******************************************************
//
//  Check if the current radio frequency has changed
//
//******************************************************
void checkFrequencyChange() {
        if (config.CURRENT_FRQ != radio.oldFrequency) {
                radio.oldFrequency = config.CURRENT_FRQ;
                checkBand(config.CURRENT_FRQ);
                toTunedPositionTimeoutCycle = 0;
                checkMemories();
                checkToAutotune();
        }
}
//*******************************************************************************
//
//  Check if display refressh timer is over and display needed to be refreshed
//
//*******************************************************************************
void checkTimeout() {
        if (timeoutCycle < returnToMenutimeout ) {
                timeoutCycle = timeoutCycle + 1;
        } else {
                timeoutCycle = 0;
                if (CURRENT_MODE != HOME) {
                        CURRENT_MODE = HOME;
                        playShortBeep();
                }
        }
        if (toSavedConf == true && confLocked == false) {
                if (toSavedConfTimeoutCycle < toSavedConfTimeout ) {
                        toSavedConfTimeoutCycle = toSavedConfTimeoutCycle + 1;
                } else {
                        toSavedConfTimeoutCycle = 0;
                        saveConfiguration(filename, config);
                }
        }
        if (toSavedMem == true && memLocked == false) {
                if (toSavedMemTimeoutCycle < toSavedMemTimeout ) {
                        toSavedMemTimeoutCycle = toSavedMemTimeoutCycle + 1;
                } else {
                        toSavedMemTimeoutCycle = 0;
                        saveMemory();
                }
        }
}
//***************************************************************
//
//  Check if auto follow timer is over and ready to be executed
//
//***************************************************************
void checkToFollowTimer() {
        if (toTunedPositionChange == true && gotoPositionLock == false) {
                if (toTunedPositionTimeoutCycle < toSavedMemTimeout ) {
                        toTunedPositionTimeoutCycle = toTunedPositionTimeoutCycle + 1;
                } else {
                        toTunedPositionTimeoutCycle = 0;
                        checkToFollow();
                }
        }
}
//*******************************************
//
//  Check if screensaver is to be displayed
//
//*******************************************
void checkScreenSaver() {
        if (CURRENT_MODE == WAITING || CURRENT_MODE == TXMITING || CURRENT_MODE == SEARCHING || CURRENT_MODE == TUNING || radio.trx_signal == 0) {
                resetScreenSaver();
        }
        if (screenSaverCycle < screenSaverTimeout ) {
                screenSaverCycle = screenSaverCycle + 1;
        } else {
                screenSaverCycle = 0;
                if (CURRENT_MODE == HOME && screensaver == false) {
                        screensaver = true;
                        playShortBeep();
                }
        }
}
//***************************************
//
//  Start the save configuration timer
//
//***************************************
void startSaveConfig() {
        toSavedConf = true;
        CONFIG_STATUS = PROCESSING;
        toSavedConfTimeoutCycle = 0;
}
//***************************************
//
//      Reset all the timers to 0
//
//***************************************
void resetTimers() {
        toTunedPositionTimeoutCycle = 0;
        toSavedMemTimeoutCycle = 0;
        toSavedConfTimeoutCycle = 0;
        toAutotunedTimeoutCycle = 0;
        searchingCycle = 0;
        screenSaverCycle = 0;
}
