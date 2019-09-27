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

        //TODO Aggregate calibration Frequencies and default Memories in a single array and sort by ascendding order
        uint32_t frequenciesArray[20] = getFrequenciesToCalibrate();

        while ((config.CURRENT_POSITION < goalPosition) && config.CURRENT_POSITION < maxSteps && checkLimitSwitch() == HIGH)
        {
                //TODO get the right frequency to scan from tuning frequency array. And set the radio to this frequency
                capacitorStepper.setSpeed(ultraHighSpeed);

                calibrateCapacitor(goalPosition, TUNING, SCANNING_MESSAGE, frequenciesArray);


                delay(swrSamplingDelay);
                currentSWR = swrAverage(swrAverageSample);
                if (currentSWR < currentMinSWR)
                {
                        currentMinSWR = currentSWR;
                        currentMinPosition = config.CURRENT_POSITION;
                } else {

                        if (wrongDirectionCounter < 4 && currentSWR - currentMinSWR > swrSamplingTreshold) {
                                wrongDirectionCounter = wrongDirectionCounter + 1;
                        } else if (wrongDirectionCounter == 4 )  {
                                wrongDirection = true;
                        }
                }
        }

}

//***************************************
//
//        Capacitor Calibration
//
//***************************************
void calibrateCapacitor(uint32_t position, int mode, String MESSAGE, uint32_t frequenciesArray[20])
{
        //Move capacitor step motor quickly to the provided position
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
                while (config.CURRENT_POSITION != position && config.CURRENT_POSITION < maxSteps && config.CURRENT_POSITION > 0 && checkLimitSwitch() == HIGH)
                {
                        capacitorStepper.step(direction);
                        resetScreenSaver();
                        //TODO Check RF signal strengh to see if we approaching a tuned position
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
//***************************************************
//
//   Join and Sort frequencies array to calibrate
//
//***************************************************
uint32_t getFrequenciesToCalibrate() {
        //TODO Aggregate calibration Frequencies and default Memories in a single array and sort by ascendding order
        int a[];
        int size;
        uint32_t frequenciesArray[20];
        for(int i=0; i<(size-1); i++) {
                for(int o=0; o<(size-(i+1)); o++) {
                        if(a[o] > a[o+1]) {
                                int t = a[o];
                                a[o] = a[o+1];
                                a[o+1] = t;
                        }
                }
        }
        return frequenciesArray;
}
