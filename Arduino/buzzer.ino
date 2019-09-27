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
//         Play Beep
//
//*********************************
void playBeep() {
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(500);
        noTone(buzzer);
}
//*********************************
//
//       Play Beep beep
//
//*********************************
void playBeepBeep() {
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(250);
        noTone(buzzer);
        delay(250);
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(250);
        noTone(buzzer);
}
//*********************************
//
//       Play Short Beep
//
//*********************************
void playShortBeep() {
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(250);
        noTone(buzzer);
}
//*********************************
//
//    Play SWR to hight Alarm
//
//*********************************
void playAlarmSWR() {

        int toneOne = 2000;
        int toneTwo = 1000;
        int toneDelay = 50;
        int repeat = 20;

        for (int i = 0; i < repeat; i++) {
                tone(buzzer, toneOne); // Send 2KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);
                tone(buzzer, toneTwo); // Send 1KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);

        }
}
//*********************************
//
//     Play no SD Card Alarm
//
//*********************************
void playAlarmNOSD() {
        int toneOne = 2000;
        int toneTwo = 1000;
        int toneDelay = 50;
        int repeat = 3;

        for (int i = 0; i < repeat; i++) {
                tone(buzzer, toneOne); // Send 2KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);
                tone(buzzer, toneTwo); // Send 1KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);

        }
}
//*********************************
//
//    Play no network Alarm
//
//*********************************
void playAlarmNONETWORK() {
        int toneOne = 2000;
        int toneTwo = 1000;
        int toneDelay = 50;
        int repeat = 6;

        for (int i = 0; i < repeat; i++) {
                tone(buzzer, toneOne); // Send 2KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);
                tone(buzzer, toneTwo); // Send 1KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);

        }
}
//*********************************
//
//      Play no cloud Alarm
//
//*********************************
void playAlarmNOCLOUD() {
        int toneOne = 2000;
        int toneTwo = 1000;
        int toneDelay = 50;
        int repeat = 9;

        for (int i = 0; i < repeat; i++) {
                tone(buzzer, toneOne); // Send 2KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);
                tone(buzzer, toneTwo); // Send 1KHz sound signal...
                delay(toneDelay);
                noTone(buzzer);
                delay(toneDelay);

        }
}
