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
