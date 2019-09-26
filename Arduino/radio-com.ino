//*********************************
//
//  Initialize Radio Serial Com
//
//*********************************
void initRadioCom() {
#ifdef ICOM
  initCat();
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
//*********************************
//
//  Receive Radio Serial Com
//
//*********************************
void receiveRadioCom() {
#ifdef ICOM
  processCatMessages();
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
//**************************************************
//
//     Radio - Put in AUTO_TUNE Mode
//
//       -Change the power level to a safe value
//       -Chage the mode to MODE_TYPE_RTTY-
//       -Start Transmitting
//
//**************************************************
void startRadioAutotune() {
#ifdef ICOM
  startIcomAutotune();
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
  //Let the time to tranission to stabilise before taking readings
  delay(500);
}
//************************************************************
//
//     Radio - Stop AUTO_TUNE Mode
//
//       -Stop Transmitting
//       -Change the power level to the original value
//       -Chage the mode to the original value
//
//************************************************************
void stopRadioAutotune() {
#ifdef ICOM
  resetDisplay();
  stopIcomAutotune();
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
//*******************************************
//
//     Radio - Get Radio Power
//
//*******************************************
void getRadioPower() {
#ifdef ICOM
  icom_request_pwr();
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
//*******************************************
//
//  Radio - Get Radio Transmitting Status
//
//*******************************************
int getRadioTxmitStatus() {
#ifdef ICOM
  return icom_getRadioTxmitStatus();//nalogRead(swrSensorPin) != 0
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
//*******************************************
//
//     Radio - Get Radio Status
//
//*******************************************
void getRadioStatus() {
#ifdef ICOM
  getIcomRadioStatus();
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
//*******************************************
//
//     Radio - Get Radio Frequency
//
//*******************************************
void getRadioFrequency() {
#ifdef ICOM
  icom_request_frequency();
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
//*******************************************
//
//     Radio - Get Radio Band
//
//*******************************************
void getRadioBand() {
#ifdef ICOM
  icom_request_mode();
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
//*******************************************
//
//     Radio - Set Radio Band
//
//*******************************************
void setRadioBand(uint8_t modeid) {
#ifdef ICOM
  radioIcomSetMode(modeid, MODE_FILTER_DEFAULT);
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
//*******************************************
//
// Verification de la bande Freq. en cours
//
//*******************************************
void checkBand(int32_t frq) {

  int32_t f1;
  f1 = frq / 1000000;
  if (f1 == 1 && CURRENT_BAND != BAND_160M) {
    CURRENT_BAND = BAND_160M;
  }
  if (f1 == 3 && CURRENT_BAND != BAND_80M) {
    CURRENT_BAND = BAND_80M;
  }
  if (f1 == 5 && CURRENT_BAND != BAND_60M) {
    CURRENT_BAND = BAND_60M;
  }
  if (f1 == 7 && CURRENT_BAND != BAND_40M) {
    CURRENT_BAND = BAND_40M;
  }
  if (f1 == 10 && CURRENT_BAND != BAND_30M) {
    CURRENT_BAND = BAND_30M;
  }
  if (f1 == 14 && CURRENT_BAND != BAND_20M) {
    CURRENT_BAND = BAND_20M;
  }
  if (f1 == 18 && CURRENT_BAND != BAND_17M) {
    CURRENT_BAND = BAND_17M;
  }
  if (f1 == 21 && CURRENT_BAND != BAND_15M) {
    CURRENT_BAND = BAND_15M;
  }
  if (f1 == 24 && CURRENT_BAND != BAND_12M) {
    CURRENT_BAND = BAND_12M;
  }
  if (f1 == 28 && CURRENT_BAND != BAND_10M) {
    CURRENT_BAND = BAND_10M;
  }
}
