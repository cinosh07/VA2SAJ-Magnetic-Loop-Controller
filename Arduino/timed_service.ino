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
void checkFrequencyChange() {
        if (config.CURRENT_FRQ != radio.oldFrequency) {
                radio.oldFrequency = config.CURRENT_FRQ;
                checkBand(config.CURRENT_FRQ);
                toTunedPositionTimeoutCycle = 0;
                checkMemories();
                checkToAutotune();
        }
}
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
int getSWR() {
  #ifdef SWR_SENSOR
        return analogRead(swrSensorPin);
  #endif
  #ifdef SWR_RADIO
        return radio.trx_swr;
  #endif
}
void checkSWRAlarm(boolean limitReached) {
        if (CURRENT_MODE == TXMITING && limitReached == true && swrAlarm == true) {
                playAlarmSWR();
        }
}
void startSaveConfig() {
        toSavedConf = true;
        CONFIG_STATUS = PROCESSING;
        toSavedConfTimeoutCycle = 0;
}
void resetTimers() {
        toTunedPositionTimeoutCycle = 0;
        toSavedMemTimeoutCycle = 0;
        toSavedConfTimeoutCycle = 0;
        toAutotunedTimeoutCycle = 0;
        searchingCycle = 0;
        screenSaverCycle = 0;
}
