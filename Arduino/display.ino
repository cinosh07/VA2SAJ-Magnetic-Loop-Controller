//*********************************
//
// Initialisation de l Affichage LCD
//
//*********************************
void initDisplay() {
        display.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab
        display.fillScreen(ST7735_BLACK);
        display.setRotation(display.getRotation() + 1);
}
//*********************************
//
//     Update Affichage LCD
//
//*********************************
void updateDisplay( uint32_t ORIGIN_POSITION, String MESSAGE )
{
        if ((radio.trx_signal != 0 && CURRENT_MODE != TUNING && CURRENT_MODE != CALIBRATION) || CURRENT_MODE == COARSE_TUNE || CURRENT_MODE == FINE_TUNE ) {

                resetDisplay();
                PREVIOUS_MODE = CURRENT_MODE;
                refreshDisplay(1);

                if (CURRENT_MODE == HOME) {
                        //Display Home menu
                        displayHome();
                } else if (CURRENT_MODE == SETTINGS) {
                        //Display Settings
                        displaySettings();
                } else if (CURRENT_MODE == COARSE_TUNE) {
                        //Display Coarse tune
                        displayCoarseTune();
                } else if (CURRENT_MODE == FINE_TUNE) {
                        //Display Fine Tune
                        displayFineTune();
                }
                else if (CURRENT_MODE == GOTOONE) {
                        //Display goto page 1
                        displayGOTOONE();
                }
                else if (CURRENT_MODE == GOTOTWO) {
                        //Display goto page 2
                        displayGOTOTWO();
                }
                else if (CURRENT_MODE == GOTOTHREE) {
                        //Display goto page 3
                        displayGOTOTHREE();
                }
                else if (CURRENT_MODE == RESETONE) {
                        //Display Reset page 1
                        displayRESETONE();
                }
                else if (CURRENT_MODE == RESETTWO) {
                        //Display Reset page 2
                        displayRESETTWO();
                }
                else if (CURRENT_MODE == RESETTHREE) {
                        //Display Reset page 3
                        displayRESETTHREE();
                }
                else if (CURRENT_MODE == SEARCHING) {
                        //Display Searching
                        displaySearchingBand();
                }
                else if (CURRENT_MODE == RETURN_HOME) {
                        //Display Searching
                        displayReturnToHome();
                }
        } else {

                if (CURRENT_MODE == TUNING) {
                        displayTuning(ORIGIN_POSITION, MESSAGE);
                }
                if (CURRENT_MODE == CALIBRATION) {
                        displayCalibration(ORIGIN_POSITION, MESSAGE);
                }
                if (radio.radioIsPresent == 1 && CURRENT_MODE != TUNING) {
                        // Display Transmitting SWR
                        displayTxmiting();
                } else if (CURRENT_MODE != TUNING && CURRENT_MODE != CALIBRATION ) {
                        //Display Waiting Radio
                        displaySearchingRadio();
                }
        }
}
//*********************************
//
// Remisse a zero de l'affichage
//
//*********************************
void resetDisplay() {

        if (PREVIOUS_MODE != CURRENT_MODE || radio.txmit == true) {
                radio.txmit = false;
                display.fillScreen(ST7735_BLACK);
        }
}
//*********************************
//
// Rafrashissement de l'affichage
//
//*********************************
void refreshDisplay(int size) {

        display.setTextColor( ST7735_GREEN, ST7735_BLACK );
        display.setCursor( 4, 4 );
        display.setTextSize( size );
}
//*********************************
//
//     Affichage du menu home
//
//*********************************
void displayHome() {

        display.println( MENU_STRING[CURRENT_MODE] );
        display.setTextSize( 2 );
        display.setTextColor( ST7735_YELLOW, ST7735_BLACK );
        display.setCursor( 4, 20 );
        display.println( RADIO_MODEL );
        display.setTextColor( ST7735_WHITE, ST7735_BLACK );
        display.setCursor( 4, 45 );
        display.print( "  " );
        int pwr = radio.trx_pwr * 100 / 285;
        if (pwr < 10) {
                display.print( "00" );
        } else if (pwr > 9 && pwr < 100) {
                display.print( "0" );
        }
        display.print( pwr );
        display.print( "W " );
        String mode = "N/A   ";
        if (radio.trx_mode == MODE_TYPE_LSB) {
                mode = "LSB   ";
        } else if (radio.trx_mode == MODE_TYPE_USB) {
                mode = "USB   ";
        } else if (radio.trx_mode == MODE_TYPE_AM) {
                mode = "AM    ";
        } else if (radio.trx_mode == MODE_TYPE_CW) {
                mode = "CW    ";
        } else if (radio.trx_mode == MODE_TYPE_RTTY) {
                mode = "RTTY  ";
        } else if (radio.trx_mode == MODE_TYPE_CWR) {
                mode = "CW-R  ";
        } else if (radio.trx_mode == MODE_TYPE_RTTYR) {
                mode = "RTTY-R";
        }
        display.print( mode );
        display_frq(config.CURRENT_FRQ);
        displaySettingsGrid(GRID_BOTTOM);
}
//*********************************************
//
// Affichage Status Icons Grid - TOP ou BOTTOM
//
//*********************************************
void displaySettingsGrid(int position) {
        int firstLine;
        int secondLine;
        if (position == GRID_BOTTOM) {
                //Affichage de grille au bas de l'ecran
                firstLine = 90;
                secondLine = 110;
        } else if (position == GRID_TOP) {
                //Affichage de grille au haut de l'ecran
                firstLine = 20;
                secondLine = 40;
        }
        display.setTextSize( 1 );

        //*****************************************
        //Display Status Icons Grid - First line

        //Icon SD Card
        if (sdCardPresent == false) {
                display.drawBitmap(5, firstLine, icon_sd, 16, 16, ST7735_RED);
        } else {
                display.drawBitmap(5, firstLine, icon_sd, 16, 16, ST7735_GREEN);
        }
        //Icon Config Saved
        if (CONFIG_STATUS == OK) {
                display.drawBitmap(30, firstLine, icon_disk, 16, 16, ST7735_GREEN);
        } else if (CONFIG_STATUS == PROCESSING) {
                display.drawBitmap(30, firstLine, icon_disk, 16, 16, ST7735_YELLOW);
        } else if (CONFIG_STATUS == STATUS_ERROR) {
                display.drawBitmap(30, firstLine, icon_disk, 16, 16, ST7735_RED);
        }
        //Icon Memory saved
        if (MEM_STATUS == OK) {
                display.drawBitmap(55, firstLine, icon_mem, 16, 16, ST7735_GREEN);
        } else if (MEM_STATUS == PROCESSING) {
                display.drawBitmap(55, firstLine, icon_mem, 16, 16, ST7735_YELLOW);
        } else if (MEM_STATUS == STATUS_ERROR) {
                display.drawBitmap(55, firstLine, icon_mem, 16, 16, ST7735_RED);
        }
        //Icon calibrated
        if (config.ISCALIB == true) {
                display.drawBitmap(80, firstLine, icon_cal, 16, 16, ST7735_RED);
        } else {
                display.drawBitmap(80, firstLine, icon_cal, 16, 16, ST7735_GREEN);
        }
        //Icon Frequency Tuned
        if (TUNED_STATUS == STATUS_ERROR) {
                display.drawBitmap(105, firstLine, icon_tuned, 16, 16, ST7735_RED);
        } else if (TUNED_STATUS == WRONG_POSITION) {
                display.drawBitmap(105, firstLine, icon_tuned, 16, 16, ST7735_YELLOW);
        } else if (TUNED_STATUS == OK) {
                display.drawBitmap(105, firstLine, icon_tuned, 16, 16, ST7735_GREEN);
        }
        //Icon Current Band (Text)
        display.setCursor( 125, (firstLine + 3) );
        display.setTextColor( ST7735_GREEN, ST7735_BLACK );
        displayBand();


        //***************************************
        //Display Status Icons Grid - Second line

        //Icon Network Present
        if (isNetworkPresent == false) {
                display.drawBitmap(5, secondLine, icon_network, 16, 16, ST7735_RED);
        } else {
                display.drawBitmap(5, secondLine, icon_network, 16, 16, ST7735_GREEN);
        }
        //Icon Internet Present - icon_cloud or icon_www
        if (WWW_STATUS == OK) {
                display.drawBitmap(30, secondLine, icon_cloud, 16, 16, ST7735_GREEN);
        } else if (WWW_STATUS == PROCESSING) {
                display.drawBitmap(30, secondLine, icon_cloud, 16, 16, ST7735_YELLOW);
        } else if (WWW_STATUS == STATUS_ERROR) {
                display.drawBitmap(30, secondLine, icon_cloud, 16, 16, ST7735_RED);
        }
        //Icon radio is present
        if (radio.radioIsPresent == false) {
                display.drawBitmap(55, secondLine, icon_radio, 16, 16, ST7735_RED);
        } else {
                display.drawBitmap(55, secondLine, icon_radio, 16, 16, ST7735_GREEN);
        }
        //Icon auto tune
        if (config.AUTO_TUNE == false) {
                display.drawBitmap(77, secondLine, icon_autotune, 32, 16, ST7735_RED);
        } else {
                display.drawBitmap(77, secondLine, icon_autotune, 32, 16, ST7735_GREEN);
        }
        //Icon auto follow
        if (config.AUTO_FOLLOW == false) {
                display.drawBitmap(115, secondLine, icon_autofollow, 32, 16, ST7735_RED);
        } else {
                display.drawBitmap(115, secondLine, icon_autofollow, 32, 16, ST7735_GREEN);
        }
}
//*********************************
//
//   Affichage de la bande
//
//*********************************
void displayBand() {
        if (CURRENT_BAND == BAND_10M) {
                display.println( " 10M" );
        } else if (CURRENT_BAND == BAND_12M) {
                display.println( " 12M" );
        } else if (CURRENT_BAND == BAND_15M) {
                display.println( " 15M" );
        } else if (CURRENT_BAND == BAND_17M) {
                display.println( " 17M" );
        } else if (CURRENT_BAND == BAND_20M) {
                display.println( " 20M" );
        } else if (CURRENT_BAND == BAND_30M) {
                display.println( " 30M" );
        } else if (CURRENT_BAND == BAND_40M) {
                display.println( " 40M" );
        } else if (CURRENT_BAND == BAND_60M) {
                display.println( " 60M" );
        } else if (CURRENT_BAND == BAND_80M) {
                display.println( " 80M" );
        } else if (CURRENT_BAND == BAND_160M) {
                display.println( "160M" );
        }
}
//*********************************
//
//   Affichage du menu settings
//
//*********************************
void displaySettings() {
        resetTimers();
        display.print( MENU_STRING[CURRENT_MODE]  );
        displaySettingsGrid(GRID_TOP);
        display.setTextSize( 2 );
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 70 );
        display.print( "A:Autotune:" );
        display.print( config.AUTO_TUNE );
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 90 );
        display.print( "B:Fol. Freq:" );
        display.print( config.AUTO_FOLLOW );
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 110 );
        display.print( "C:Calib?" );
}
//*********************************
//
// Affichage du menu coarse tune
//
//*********************************
void displayCoarseTune() {
        resetTimers();
        display.print( MENU_STRING[CURRENT_MODE]  );
        display.setTextSize( 2 );
        display.setTextColor( ST7735_WHITE, ST7735_BLACK );
        //display.setCursor( 4, 20 );
        //display.print( "SWR:" );
        //displaySWR();
        display.setCursor( 4, 32 );
        display.print( " P:" );
        displayCurrentPosition(config.CURRENT_POSITION);
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 70 );
        display.print( "A:Fine Tune?" );
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 90 );
        display.print( "B:Auto Tune?" );
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 110 );
        display.print( "C:Save freq?" );
}
//*********************************
//
// Affichage du menu fine tune
//
//*********************************
void displayFineTune() {
        resetTimers();
        display.print( MENU_STRING[CURRENT_MODE]  );
        display.setTextSize( 2 );
        display.setTextColor( ST7735_WHITE, ST7735_BLACK );
        //display.setCursor( 4, 20 );
        //display.print( "SWR:" );
        //displaySWR();
        display.setCursor( 4, 32 );
        display.print( "P:" );
        displayCurrentPosition(config.CURRENT_POSITION);
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 70 );
        display.print( "A:Coar. Tune?" );
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 90 );
        display.print( "B:Auto Tune?" );
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
        display.setCursor( 4, 110 );
        display.print( "C:Save freq?" );
}
//*********************************
//
//        Affichage SWR
//
//*********************************
void displaySWR() {
        //playAlarm(); if threshold limit reached
        //Do auto tune if activated and threshold limit reached
        boolean limitReached = false;
        limitReached = checkSWRLimit();
        //Adjust swr text color regarding SWR threshold
        if (limitReached == true) {
                display.setTextColor( ST7735_RED, ST7735_BLACK );
        } else {
                display.setTextColor( ST7735_GREEN, ST7735_BLACK );
        }
#ifdef SWR_SENSOR
        int swr = analogRead(swrSensorPin);
        if (swr < 10) {
                display.print(  "00" );
        } else if (swr > 9 && swr < 100) {
                display.print(  "0" );
        }
        display.println( swr );
#endif
#ifdef SWR_RADIO
        if (radio.trx_swr < 10) {
                display.print(  "00" );
        } else if (radio.trx_swr > 9 && radio.trx_swr < 100) {
                display.print(  "0" );
        }
        display.println( radio.trx_swr );
#endif
        checkSWRAlarm(limitReached);

}
//*************************************
//
// Affichage transmission en cours...
//
//*************************************
void displayTxmiting() {

        if (radio.txmit == false) {
                display.fillScreen(ST7735_BLACK);
                radio.txmit = true;
        }
        display.setTextSize( 2 );
        display.setTextColor( ST7735_GREEN, ST7735_BLACK );
        display.setCursor( 4, 30 );
        display.println( "     TX" );
        display.setCursor( 4, 50 );
        display.print(  "  SWR:" );
        displaySWR();
}
//*********************************
//
//    Affichage recherche radio
//
//*********************************
void displaySearchingRadio() {

        display.setTextSize( 2 );
        display.setTextColor( ST7735_RED, ST7735_BLACK );
        display.setCursor( 4, 50 );
        display.println( "  Waiting" );
        display.setCursor( 4, 70 );
        display.println(  "  radio ..." );
}
//*********************************
//
//    Display return to home
//
//*********************************
void displayReturnToHome() {

        display.setTextSize( 2 );
        display.setTextColor( ST7735_RED, ST7735_BLACK );
        display.setCursor( 4, 50 );
        display.println( "  Return" );
        display.setCursor( 4, 70 );
        display.println(  " to home ..." );
}
//*********************************
//
// Display searching band ...
//
//*********************************
void displaySearchingBand() {

        display.setTextSize( 2 );
        display.setTextColor( ST7735_GREEN, ST7735_BLACK );
        display.setCursor( 4, 30 );
        display.println( "  Searching" );
        display.setCursor( 4, 50 );
        display.print(  " band ..." );
}
//*********************************
//
//    Display Auto tuning ...
//
//*********************************
void displayTuning(uint32_t ORIGIN_POSITION, String MESSAGE) {

        display.setTextSize( 2 );
        display.setTextColor( ST7735_YELLOW, ST7735_BLACK );
        display.setCursor( 4, 10 );
        display.println( " Auto Tuning" );
        display.setTextSize( 1 );
        display.setTextColor( ST7735_WHITE, ST7735_BLACK );
        display.setCursor( 4, 40 );
        display.print(  "SWR: " );
        displaySWR();
        display.setTextColor( ST7735_WHITE, ST7735_BLACK );
        display.setCursor( 4, 55 );
        display.print(  "Current Pos:" );
        displayCurrentPosition(config.CURRENT_POSITION);
        display.setCursor( 4, 70 );
        display.print(  "Target Pos:" );
        displayCurrentPosition(ORIGIN_POSITION);
        display.setCursor( 4, 88 );
        display.setTextSize( 2 );
        if (MESSAGE == SWR_ERROR_TUNING_MESSAGE) {
                display.setTextColor( ST7735_RED, ST7735_BLACK );
        } else {
                display.setTextColor( ST7735_GREEN, ST7735_BLACK );
        }
        if (MESSAGE == WAITING_RADIO_MODE_MESSAGE || MESSAGE == WAITING_RADIO_SAFE_POWER_MESSAGE || MESSAGE == WAITING_RADIO_TXMIT_MESSAGE) {
                display.println( getSplitedMessage(MESSAGE, '|', 0) );
                display.setCursor( 4, 108 );
                display.println( getSplitedMessage(MESSAGE, '|', 1) );
        } else {
                display.println(  MESSAGE );
                display.setCursor( 4, 108 );
                display.println(  EMPTY_SECOND_LINE_MESSAGE );
        }


}
//*********************************
//
//    Display Calibration ...
//
//*********************************
void displayCalibration(uint32_t ORIGIN_POSITION, String MESSAGE) {

        display.setTextSize( 2 );
        display.setTextColor( ST7735_YELLOW, ST7735_BLACK );
        display.setCursor( 4, 10 );
        display.println( " Calibration" );
        display.setTextSize( 1 );
        display.setTextColor( ST7735_WHITE, ST7735_BLACK );
        display.setCursor( 4, 40 );
        display.print(  "SWR: " );
        displaySWR();
        display.setTextColor( ST7735_WHITE, ST7735_BLACK );
        display.setCursor( 4, 55 );
        display.print(  "Current Pos:" );
        displayCurrentPosition(config.CURRENT_POSITION);
        display.setCursor( 4, 70 );
        display.print(  "Target Pos:" );
        displayCurrentPosition(ORIGIN_POSITION);
        display.setCursor( 4, 88 );
        display.setTextSize( 2 );
        if (MESSAGE == SWR_ERROR_TUNING_MESSAGE) {
                display.setTextColor( ST7735_RED, ST7735_BLACK );
        } else {
                display.setTextColor( ST7735_GREEN, ST7735_BLACK );
        }
        if (MESSAGE == WAITING_RADIO_MODE_MESSAGE || MESSAGE == WAITING_RADIO_SAFE_POWER_MESSAGE || MESSAGE == WAITING_RADIO_TXMIT_MESSAGE) {
                display.println( getSplitedMessage(MESSAGE, '|', 0) );
                display.setCursor( 4, 108 );
                display.println( getSplitedMessage(MESSAGE, '|', 1) );
        } else {
                display.println(  MESSAGE );
                display.setCursor( 4, 108 );
                display.println(  EMPTY_SECOND_LINE_MESSAGE );
        }


}
//*********************************
//
//   Display loading memory...
//
//*********************************
void displayLoadingMemories() {
        display.setTextSize( 2 );
        display.setTextColor( ST7735_YELLOW, ST7735_BLACK );
        display.setCursor( 4, 50 );
        display.println( "Loading" );
        display.setCursor( 4, 70 );
        display.println( "Memories ..." );

}
//*********************************
//
//  Display loading network...
//
//*********************************
void displayLoadingNetwork() {
        display.setTextSize( 2 );
        display.setTextColor( ST7735_YELLOW, ST7735_BLACK );
        display.setCursor( 4, 50 );
        display.println( "Starting" );
        display.setCursor( 4, 70 );
        display.println( "Network ..." );

}
//*********************************
//
//    Affichage Du menu Goto 1
//
//*********************************
void displayGOTOONE() {
        resetTimers();
        display.print( MENU_STRING[CURRENT_MODE]  );
        displaySettingsGrid(GRID_TOP);
        display.setTextSize( 2 );
  #ifdef ANTENNA_BAND_10M
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 70 );
        display.print( "A:10M" );
        display.setTextColor( JOY_BUTTON_COLOR, ST7735_BLACK );
        display.print( " J:HOME" );
  #ifdef ANTENNA_BAND_12M
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 90 );
        display.print( "B:12M" );
  #ifdef ANTENNA_BAND_15M
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 110 );
        display.print( "C:15M" );
}
//*********************************
//
//    Affichage Du menu Goto 2
//
//*********************************
void displayGOTOTWO() {
        resetTimers();
        display.print( MENU_STRING[CURRENT_MODE]  );
        displaySettingsGrid(GRID_TOP);
        display.setTextSize( 2 );

  #ifdef ANTENNA_BAND_20M
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 70 );
        display.print( "A:20M" );
  #ifdef ANTENNA_BAND_17M
        display.setTextColor( JOY_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.print( " J:17M" );
  #ifdef ANTENNA_BAND_30M
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 90 );
        display.print( "B:30M" );
  #ifdef ANTENNA_BAND_40M
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 110 );
        display.print( "C:40M" );
}
//*********************************
//
//    Affichage Du menu Goto 3
//
//*********************************
void displayGOTOTHREE() {
        resetTimers();
        display.print( MENU_STRING[CURRENT_MODE]  );
        displaySettingsGrid(GRID_TOP);
        display.setTextSize( 2 );
  #ifdef ANTENNA_BAND_60M
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 70 );
        display.print( "A:60M" );
  #ifdef ANTENNA_BAND_80M
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 90 );
        display.print( "B:80M" );
  #ifdef ANTENNA_BAND_160M
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 110 );
        display.print( "C:160M" );
}
//*********************************
//
//   Affichage Du menu Reset 1
//
//*********************************
void displayRESETONE() {
        resetTimers();
        display.setTextColor( ST7735_RED, ST7735_BLACK );
        display.print( MENU_STRING[CURRENT_MODE]  );
        displaySettingsGrid(GRID_TOP);
        display.setTextSize( 2 );

  #ifdef ANTENNA_BAND_10M
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 70 );
        display.print( "A:10M" );
        display.setTextColor( JOY_BUTTON_COLOR, ST7735_BLACK );
        display.print( " J:HOME" );
  #ifdef ANTENNA_BAND_12M
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 90 );
        display.print( "B:12M" );
  #ifdef ANTENNA_BAND_15M
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 110 );
        display.print( "C:15M" );
}
//*********************************
//
//   Affichage Du menu Reset 2
//
//*********************************
void displayRESETTWO() {
        resetTimers();
        display.setTextColor( ST7735_RED, ST7735_BLACK );
        display.print( MENU_STRING[CURRENT_MODE]  );
        displaySettingsGrid(GRID_TOP);
        display.setTextSize( 2 );

  #ifdef ANTENNA_BAND_20M
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 70 );
        display.print( "A:20M" );
  #ifdef ANTENNA_BAND_17M
        display.setTextColor( JOY_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.print( " J:17M" );
  #ifdef ANTENNA_BAND_30M
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 90 );
        display.print( "B:30M" );
  #ifdef ANTENNA_BAND_40M
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 110 );
        display.print( "C:40M" );
}
//*********************************
//
//   Affichage Du menu Reset 3
//
//*********************************
void displayRESETTHREE() {
        resetTimers();
        display.setTextColor( ST7735_RED, ST7735_BLACK );
        display.print( MENU_STRING[CURRENT_MODE]  );
        displaySettingsGrid(GRID_TOP);
        display.setTextSize( 2 );
  #ifdef ANTENNA_BAND_60M
        display.setTextColor( A_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 70 );
        display.print( "A:60M" );
  #ifdef ANTENNA_BAND_80M
        display.setTextColor( B_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 90 );
        display.print( "B:80M" );
  #ifdef ANTENNA_BAND_160M
        display.setTextColor( C_BUTTON_COLOR, ST7735_BLACK );
  #else
        display.setTextColor( DISABLED_COLOR, ST7735_BLACK );
  #endif
        display.setCursor( 4, 110 );
        display.setCursor( 4, 110 );
        display.print( "C:160M" );
}
//*********************************
//
// Affichage de la Freq. en cours
//
//*********************************
void display_frq(int32_t frq)
{

        String strToReturn = "Icom";
        char print_buf;
        int32_t f1, f2, f3; // Used to format frequency printout
        int8_t sign = 1;
        display.setCursor( 4, 65 );
        if (frq < 0) sign = -1; // Format negative frequency correctly
        f1 = frq / 1000000; // (although this makes limited sense :)
        f3 = sign * frq % 1000000;
        f2 = f3 / 1000;
        f3 = f3 % 1000;

        if (f1 <= -10) {
                display.print("-");
        }
        else if ((frq < 0) && (f1 > -10)) {
                display.print(" -");
        }
        else if (f1 < 10) {
                display.print(" ");
        }
        display.print((String) f1 );
        display.print(".");
        if (f2 < 10) {
                display.print("00");
        }
        else if (f2 < 100 && f2 > 9) {
                display.print("0");
        }
        display.print((String) f2 );
        display.print(".");
        if (f3 < 10) {
                display.print("00");
        }
        else if (f3 < 100 && f3 > 9) {
                display.print("0");
        }
        display.print((String) f3 );
        display.setTextSize( 1 );
        display.println( " MHz" );
        display.setTextSize( 2 );
}
//**********************************************
//
//   Affichage de la position du step motor
//
//**********************************************
void displayCurrentPosition(uint32_t tempPos) {

        String sign = " ";
        if (tempPos < 0) {
                sign = "-";
                tempPos = -1 * tempPos;
        }
        if (tempPos < 10) {
                display.print( sign );
                display.print( "00000" );
        }
        else if (tempPos > 9 && tempPos < 100) {
                display.print( sign );
                display.print( "0000" );
        }
        else if (tempPos > 99 && tempPos < 1000) {
                display.print( sign );
                display.print( "000" );
        }
        else if (tempPos > 999 && tempPos < 10000 ) {
                display.print( sign );
                display.print( "00" );
        }
        else if (tempPos > 9999 && tempPos < 100000) {
                display.print( sign );
                display.print( "0" );
        } else {
                display.print( sign );
        }
        display.print( tempPos );
}
//*********************************
//
//         Screensaver
//
//*********************************
void RunScreenSaver()
{
        randomSeed(millis() / 100);

        int x = random(4, 80);
        int y = random(4, 120);
        int color = random(1, 6);
        if (color == 1) {
                display.setTextColor( ST7735_YELLOW, ST7735_BLACK );
        }
        if (color == 2) {
                display.setTextColor( ST7735_WHITE, ST7735_BLACK );
        }
        if (color == 3) {
                display.setTextColor( ST7735_RED, ST7735_BLACK );
        }
        if (color == 4) {
                display.setTextColor( ST7735_BLUE, ST7735_BLACK );
        }
        if (color == 5) {
                display.setTextColor( ST7735_GREEN, ST7735_BLACK );
        }
        if (color == 6) {
                display.setTextColor( ST7735_MAGENTA, ST7735_BLACK );
        }
        display.fillScreen(ST77XX_BLACK);
        display.setCursor(x, y);
        display.setTextSize(1);
        display.print(SCREENSAVER_MESSAGE);
}
//*********************************
//
//     Blank the screen
//
//*********************************
void blanckLCD() {
        display.fillScreen(ST77XX_BLACK);
}
//*****************************************************
//
//  Reset screen ready to receive new display update
//
//*****************************************************
void resetScreenSaver() {
        timeoutCycle = 0;
        screensaver = false;
        screenSaverCycle = 0;
}
//**************************************************************
//
// Parse message separated by | into multiple line message ...
//
//**************************************************************
String getSplitedMessage(String data, char separator, int index)
{
        int found = 0;
        int strIndex[] = { 0, -1 };
        int maxIndex = data.length() - 1;

        for (int i = 0; i <= maxIndex && found <= index; i++) {
                if (data.charAt(i) == separator || i == maxIndex) {
                        found++;
                        strIndex[0] = strIndex[1] + 1;
                        strIndex[1] = (i == maxIndex) ? i+1 : i;
                }
        }
        return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
