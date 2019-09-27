//*********************************
//
//      Setup Routine
//
//*********************************
void setup() {

        pinMode(buzzer, OUTPUT);
        if (PTT_DTR_CTS == 1) {
                pinMode(DTR_PIN, OUTPUT);
                pinMode(CTS_PIN, OUTPUT);
                digitalWrite(DTR_PIN, HIGH);
                digitalWrite(CTS_PIN, HIGH);
        }

        playBeep();
        display.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab
        display.fillScreen(ST7735_BLACK);
        display.setRotation(display.getRotation() + 1);
        display.drawBitmap(0, 0, logoInvert, 160, 128, ST7735_YELLOW);
        delay(250);
        display.drawBitmap(0, 0, logoInvert, 160, 128, ST7735_GREEN);
        delay(250);
        display.drawBitmap(0, 0, logoInvert, 160, 128, ST7735_RED);
        delay(250);
        display.drawBitmap(0, 0, logoInvert, 160, 128, ST7735_YELLOW);
        delay(250);
        display.drawBitmap(0, 0, logoInvert, 160, 128, ST7735_MAGENTA);
        delay(250);
        display.drawBitmap(0, 0, logoInvert, 160, 128, ST7735_CYAN);
        delay(250);
        display.drawBitmap(0, 0, logoInvert, 160, 128, ST7735_WHITE);
        delay(1000);

        Serial.begin(9600);
        pinMode(sleeppin, OUTPUT);
        pinMode(resetpin, OUTPUT);
        pinMode(DIR, OUTPUT);
        pinMode(STEP, OUTPUT);
        pinMode(swrSensorPin, INPUT);
        pinMode(buttonJoystickPin, INPUT_PULLUP);
        pinMode(buttonAPin, INPUT_PULLUP);
        pinMode(buttonBPin, INPUT_PULLUP);
        pinMode(buttonCPin, INPUT_PULLUP);
        pinMode(switchPin, INPUT_PULLUP);
        pinMode(networkShieldCSPin, OUTPUT);//TODO Verifier si cest pas un bug que ce soit la
        digitalWrite(networkShieldCSPin, HIGH);//TODO Verifier si cest pas un bug que ce soit la
        motorStop();
        CURRENT_MODE = WAITING;
        blanckLCD();
        updateDisplay(0,"");
        initRadioCom();
        initSDCard();
        display.fillScreen(ST7735_BLACK);
        displayLoadingMemories();
  #ifdef ANTENNA_BAND_10M
        loadMemory(BAND_10M);
  #endif
  #ifdef ANTENNA_BAND_12M
        loadMemory(BAND_12M);
  #endif
  #ifdef ANTENNA_BAND_15M
        loadMemory(BAND_15M);
  #endif
  #ifdef ANTENNA_BAND_17M
        loadMemory(BAND_17M);
  #endif
  #ifdef ANTENNA_BAND_20M
        loadMemory(BAND_20M);
  #endif
  #ifdef ANTENNA_BAND_30M
        loadMemory(BAND_30M);
  #endif
  #ifdef ANTENNA_BAND_40M
        loadMemory(BAND_40M);
  #endif
  #ifdef ANTENNA_BAND_60M
        loadMemory(BAND_60M);
  #endif
  #ifdef ANTENNA_BAND_80M
        loadMemory(BAND_80M);
  #endif
  #ifdef ANTENNA_BAND_160M
        loadMemory(BAND_160M);
  #endif
        display.fillScreen(ST7735_BLACK);
#ifdef NETWORK
        displayLoadingNetwork();
        initNetworkServer();
        display.fillScreen(ST7735_BLACK);
#endif
        updateDisplay(0,"");
}
