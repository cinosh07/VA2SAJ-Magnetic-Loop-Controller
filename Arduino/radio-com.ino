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
        return icom_getRadioTxmitStatus();
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
void setRadioMode(uint8_t modeid) {
#ifdef ICOM
        radioIcomSetMode(modeid, MODE_FILTER_DEFAULT);
        delay(10);
        getRadioStatus();
        delay(10);
        receiveRadioCom();
        while (radio.trx_mode != MODE_TYPE_RTTY) {
                radioIcomSetMode(modeid, MODE_FILTER_DEFAULT);
                delay(10);
                getRadioStatus();
                delay(10);
                receiveRadioCom();
                updateDisplay(position,WAITING_RADIO_MODE_MESSAGE);
        }
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
