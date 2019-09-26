//*************************************************************************
//
// Verification si le step motor doit aller automatiquement a sa position
//
//*************************************************************************
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
//*********************************
//
//    Controle of Step Moteur
//
//*********************************
void stepMotor(int direction)
{
  motorStart();
  capacitorStepper.step(direction);
  config.CURRENT_POSITION = config.CURRENT_POSITION + direction;
}
//*********************************
//
//      Step Motor Stop
//
//*********************************
//This is needed to prevent driver from running current through a stationary winding and preventing noise in the rf signal
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
//Move capacitor step motor quickly to the provided position
void goToCapacitorPosition(uint32_t position, int mode, String MESSAGE)
{
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
    while (config.CURRENT_POSITION != position)
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
//*********************************
//
//  Calibration Procedure
//
//*********************************
void calibrate() {
  //TODO Calibration Mode
  playBeepBeep();
  resetScreenSaver();
  startSaveConfig();
  returnToHomeMenu();
  refreshTimer.check();
}
