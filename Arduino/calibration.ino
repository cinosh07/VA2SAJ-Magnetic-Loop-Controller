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
//  Calibration Process TODO
//
//*********************************
void calibrate() {
        //TODO Calibration Mode
        uint32_t goalPosition = maxSteps;

        //Aggregate calibration Frequencies and default Memories in a single array and sort by ascendding order
        // uint32_t *frequenciesArray[] = {1};

        // frequenciesArray = getFrequenciesToCalibrate();
        //Get the right frequency to scan from tuning frequency array. And set the radio to this frequency

        PREVIOUS_TRX_MODE = radio.trx_mode;
        setRadioMode(MODE_TYPE_RTTY);

        while ((config.CURRENT_POSITION < goalPosition) && config.CURRENT_POSITION < maxSteps && checkLimitSwitch() == HIGH && config.ISCALIB == false )
        {
                calibrateCapacitor(goalPosition, TUNING, SCANNING_MESSAGE, getFrequenciesToCalibrate());
        }
        setRadioMode(PREVIOUS_TRX_MODE);

}

//***************************************
//
//        Capacitor Calibration
//
//***************************************
void calibrateCapacitor(uint32_t position, int mode, String MESSAGE, uint32_t *frequenciesArray)
{
        motorStart();
        int currentRF = 0;
        int currentMaxRF = 0;
        uint32_t currentMaxRFPosition = 0;
        int decreaseCounter = 0;
        capacitorStepper.setSpeed(ultraHighSpeed);
        for (int x = 0; x < 20; x++) {
                setRadioFrequency(frequenciesArray[x]);
                currentRF = getRFSignal();
                currentMaxRF = currentRF;
                currentMaxRFPosition = config.CURRENT_POSITION;
                boolean frequencyTuned = false;
                while (frequencyTuned == false) {
                        goToCapacitorPosition(config.CURRENT_POSITION + rfSearchSteps[CURRENT_BAND], TUNING, SCANNING_MESSAGE);
                        currentRF = getRFSignal();
                        if (currentRF > currentMaxRF)
                        {
                                currentMaxRF = currentRF;
                                currentMaxRFPosition = config.CURRENT_POSITION;
                        } else {
                                if (decreaseCounter > 3) {
                                        decreaseCounter = 0;
                                        tuningProcess(currentMaxRFPosition);
                                        frequencyTuned = true;
                                } else {
                                        decreaseCounter = decreaseCounter + 1;
                                }
                        }
                }
        }
        motorStop();
        config.ISCALIB = true;
}
//*************************************************************************************
//
//   Join and Sort calibration Frequencies and default Memories arrays to calibrate
//
//*************************************************************************************
uint32_t getFrequenciesToCalibrate() {
        //Aggregate calibration Frequencies and default Memories in a single array and sort by ascendding order
        // calibrationFrequencies defaultMemories
        uint32_t frequenciesArray[20];
        int count = 0;
        boolean up = false;
        for(int i=0; i<20; i++) {
                if (up == false) {
                        up = true;
                        uint32_t freq = 0;
                        if (calibrationFrequencies[count] < defaultMemories[count]) {
                                frequenciesArray[i] = calibrationFrequencies[count];
                        } else {
                                frequenciesArray[i] = defaultMemories[count];
                        }
                } else {
                        if (calibrationFrequencies[count] > defaultMemories[count]) {
                                frequenciesArray[i] = calibrationFrequencies[count];
                        } else {
                                frequenciesArray[i] = defaultMemories[count];
                        }
                        count = count + 1;
                        up = false;
                }
        }
        return frequenciesArray;
}
