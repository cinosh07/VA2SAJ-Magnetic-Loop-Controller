//*********************************
//
//            LOOP
//
//*********************************
void loop() {

        receiveRadioCom();
        menuNavigationCheck();
        checkJoystickTuning();
        motorStop();
#ifdef NETWORK
        checkServerConnection();
#endif
#ifdef CLOUD_SAVE
        readCloudResponse();
#endif
        refreshTimer.check();
}
