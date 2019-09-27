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
//       Read JoyStick Axis
//
//*********************************
int readAxis(int thisAxis) {
        // read the analog input:
        int reading = analogRead(thisAxis);

        // map the reading from the analog input range to the output range:
        reading = map(reading, 0, 1023, 0, range);

        // if the output reading is outside from the rest position threshold, use it:
        int distance = reading - center;

        if (abs(distance) < threshold) {
                distance = 0;
        }
        // return the distance for this axis:
        return distance;
}
//*********************************
//
//     Refresh joystick range
//
//*********************************
void refreshJoystickRange() {
        rawRange = (highSpeed * 2) - (lowSpeed * 2);       // output range of X or Y movement
        threshold = rawRange / 29; // resting threshold
        range = rawRange + threshold;
        center = range / 2;
}
void checkJoystickTuning() {
        boolean toSaved = false;
        int tempMode = -1;
        if ((readAxis(xAxis) > threshold && CURRENT_MODE != HOME && CURRENT_MODE != SETTINGS) || (readAxis(xAxis) < -threshold && CURRENT_MODE != HOME && CURRENT_MODE != SETTINGS)) {
                motorStart();
                toSaved = true;
                tempMode = CURRENT_MODE;
                CURRENT_MODE = SEARCHING;
                updateDisplay(0,"");
        }

        // Joystick tuning
        while (readAxis(xAxis) > threshold && CURRENT_MODE != HOME && CURRENT_MODE != SETTINGS)
        {
                currentSpeed = readAxis(xAxis) + (lowSpeed - threshold);
                capacitorStepper.setSpeed(currentSpeed);
                int bSlash = 0;
#ifdef USE_BACKSLASH
                if (config.CURRENT_DIRECTION != 1) {

                        config.CURRENT_DIRECTION = -1;
                }
                if (config.CURRENT_DIRECTION != config.PREVIOUS_DIRECTION) {
                        //TODO Backslash
                        //config.BACKSLASH
                        //TODO Direction Change
                        config.PREVIOUS_DIRECTION = config.CURRENT_DIRECTION;
                }
#endif

                config.CURRENT_POSITION = config.CURRENT_POSITION + 1 + bSlash;
                capacitorStepper.step(1);
                TUNED_STATUS = STATUS_ERROR;
                checkMemories();
                resetScreenSaver();
        }
        while (readAxis(xAxis) < -threshold && CURRENT_MODE != HOME && CURRENT_MODE != SETTINGS)
        {
                currentSpeed = -readAxis(xAxis) + (lowSpeed - threshold);
                capacitorStepper.setSpeed(currentSpeed);
                int bSlash = 0;
#ifdef USE_BACKSLASH

                if (config.CURRENT_DIRECTION != 1) {
                        config.CURRENT_DIRECTION = 1;
                }
                if (config.CURRENT_DIRECTION != config.PREVIOUS_DIRECTION) {
                        //TODO Backslash
                        //config.BACKSLASH
                        //TODO Direction Change
                        config.PREVIOUS_DIRECTION = config.CURRENT_DIRECTION;
                }
#endif


                config.CURRENT_POSITION = config.CURRENT_POSITION - 1 + bSlash;
                capacitorStepper.step(-1);
                TUNED_STATUS = STATUS_ERROR;
                checkMemories();
                resetScreenSaver();
        }
        motorStop();
        if (toSaved == true) {
                startSaveConfig();
                CURRENT_MODE = tempMode;
                updateDisplay(0,"");
        }
}
