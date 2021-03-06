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
//**************************************
//    Tool to generate bitmap icons
//      http://dotmatrixtool.com/
//**************************************

static const uint8_t PROGMEM logo[] = {
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x3,0xff,0xff,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x7f,0xff,0xff,0xf8,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x3,0xff,0xff,0xff,0xff,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x1f,0xff,0xff,0xff,0xff,0xe0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x7f,0xff,0xff,0xff,0xff,0xf8,0x1,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xf8,0x1,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xf0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x3f,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xe0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x1f,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0x80,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x7,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x3,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xfe,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x1,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xfc,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xf8,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x7f,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xf0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x3f,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xe0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x1f,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xc0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xf,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xc0,0xfc,0xff,0x3c,0xff,0xff,0xf0,0x7f,0x3f,0xf3,0xfc,0xf,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0x81,0xfc,0x7e,0x38,0x7f,0x7,0xe0,0x7e,0x1f,0xf3,0xfe,0x7,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0x3,0xfe,0x7e,0x78,0x7e,0x3,0xc7,0xfe,0x1f,0xf3,0xff,0x3,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xfe,0x7,0xfe,0x7e,0x78,0x7e,0xf1,0xcf,0xfe,0x1f,0xf3,0xff,0x81,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xfe,0x7,0xfe,0x3c,0x73,0x3f,0xf9,0xcf,0xfc,0xcf,0xf3,0xff,0x81,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xfc,0xf,0xff,0x3c,0xf3,0x3f,0xf9,0xc7,0xfc,0xcf,0xf3,0xff,0xc0,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xf8,0x1f,0xff,0x3c,0xf3,0x3f,0xf9,0xe1,0xfc,0xcf,0xf3,0xff,0xe0,0x7f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xf8,0x3f,0xff,0x18,0xe3,0x1f,0xf3,0xf0,0xf8,0xc7,0xf3,0xff,0xf0,0x7f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xf0,0x3f,0xff,0x99,0xe7,0x9f,0xe3,0xfc,0x79,0xe7,0xf3,0xff,0xf0,0x3f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xf0,0x7f,0xff,0x99,0xe0,0x1f,0xe7,0xff,0x38,0x7,0xf3,0xff,0xf8,0x3f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xe0,0x7f,0xff,0x93,0xc0,0xf,0xcf,0xff,0x30,0x3,0xf3,0xff,0xf8,0x1f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xe0,0xff,0xff,0xc3,0xcf,0xcf,0x9f,0xff,0x33,0xf3,0xf3,0xff,0xfc,0x1f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xc1,0xff,0xff,0xc3,0xcf,0xcf,0x3f,0xde,0x33,0xf3,0xe3,0xff,0xfe,0xf,0xff,0xff,0xff,
        0xff,0xff,0xff,0xc1,0xff,0xff,0xc7,0x8f,0xc6,0x1,0xc0,0x63,0xf1,0x7,0xff,0xfe,0xf,0xff,0xff,0xff,
        0xff,0xff,0xff,0x81,0xff,0xff,0xc7,0x9f,0xe4,0x1,0xc0,0xe7,0xf9,0xf,0xff,0xfe,0x7,0xff,0xff,0xff,
        0xff,0xff,0xff,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7,0xff,0xff,0xff,
        0xff,0xff,0xff,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3,0xff,0xff,0xff,
        0xff,0xff,0xff,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x83,0xff,0xff,0xff,
        0xff,0xff,0xff,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x83,0xff,0xff,0xff,
        0xff,0xff,0xfe,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x81,0xff,0xff,0xff,
        0xff,0xff,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xff,0xff,0xff,
        0xff,0xff,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xff,0xff,0xff,
        0xff,0xff,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xff,0xff,0xff,
        0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,
        0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,
        0xff,0xff,0xfc,0x1f,0xf8,0xfe,0x3f,0xff,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,
        0xff,0xff,0xfc,0x1f,0xf8,0xfe,0x3f,0xff,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf8,0xfc,0x3f,0xff,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf8,0x7c,0x3f,0xff,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf8,0x7c,0x3c,0x1f,0xc2,0x7f,0x3f,0xf0,0xfe,0x1f,0x20,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf8,0x79,0x3c,0xf,0x0,0x7f,0x3f,0xc0,0x38,0x7,0x0,0x7f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf9,0x39,0x3f,0xc7,0x3c,0x7f,0x3f,0xcf,0x39,0xe7,0x1e,0x3f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf1,0x39,0x3f,0xe6,0x7e,0x7f,0x3f,0x9f,0x11,0xf3,0x3f,0x3f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf3,0x33,0x3f,0xc6,0x7e,0x7f,0x3f,0x9f,0x93,0xf3,0x3f,0x3f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf3,0x93,0x3c,0x6,0x7e,0x7f,0x3f,0x9f,0x93,0xf3,0x3f,0x3f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf3,0x93,0x18,0xe6,0x7e,0x7f,0x3f,0x9f,0x93,0xf3,0x3f,0x3f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf3,0x87,0x19,0xe6,0x7e,0x7f,0x3f,0x9f,0x11,0xf3,0x3f,0x3f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf3,0xc7,0x19,0xc6,0x3c,0x7f,0x3f,0xcf,0x39,0xe7,0x1e,0x7f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf3,0xc7,0x98,0x7,0x0,0x7f,0x0,0xc0,0x38,0x7,0x0,0x7f,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xf3,0xcf,0x9c,0x27,0x82,0x7f,0x0,0xf0,0xfe,0x1f,0x21,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xfe,0x7f,0xff,0xff,0xff,0xff,0x3f,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xfc,0x7f,0xff,0xff,0xff,0xff,0x3f,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0x3f,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0x3,0xff,0xff,0xff,0xff,0xff,0x3f,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xff,0xff,
        0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,
        0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,
        0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,
        0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,
        0xff,0xff,0xfe,0xf,0xff,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0x9c,0xff,0xff,0xff,0xc0,0xff,0xff,0xff,
        0xff,0xff,0xfe,0xf,0xfe,0x1,0xff,0xff,0xff,0x3f,0xff,0xff,0x9c,0xff,0xff,0xff,0xc1,0xff,0xff,0xff,
        0xff,0xff,0xfe,0xf,0xfc,0x7f,0xff,0xff,0xff,0x3f,0xff,0xff,0x9c,0xff,0xff,0xff,0xc1,0xff,0xff,0xff,
        0xff,0xff,0xfe,0x7,0xf9,0xff,0xff,0xff,0xff,0x3f,0xff,0xff,0x9c,0xff,0xff,0xff,0xc1,0xff,0xff,0xff,
        0xff,0xff,0xff,0x7,0xf1,0xff,0xe1,0xf2,0x1c,0x6,0x4f,0xf,0x9c,0xf8,0x79,0x3f,0x83,0xff,0xff,0xff,
        0xff,0xff,0xff,0x7,0xf3,0xff,0x80,0x70,0xe,0x6,0xc,0x3,0x9c,0xf0,0x38,0x3f,0x83,0xff,0xff,0xff,
        0xff,0xff,0xff,0x3,0xf3,0xff,0x9e,0x71,0xc7,0x3e,0x3c,0xf3,0x9c,0xe7,0x38,0xff,0x3,0xff,0xff,0xff,
        0xff,0xff,0xff,0x83,0xf3,0xff,0x3f,0x33,0xe7,0x3e,0x79,0xf1,0x9c,0xcf,0x98,0xff,0x7,0xff,0xff,0xff,
        0xff,0xff,0xff,0x81,0xf3,0xff,0x3f,0x33,0xe7,0x3e,0x79,0xf9,0x9c,0xcf,0x99,0xfe,0x7,0xff,0xff,0xff,
        0xff,0xff,0xff,0xc1,0xf3,0xff,0x3f,0x33,0xe7,0x3e,0x79,0xf9,0x9c,0xc0,0x19,0xfe,0xf,0xff,0xff,0xff,
        0xff,0xff,0xff,0xc1,0xf1,0xff,0x3f,0x33,0xe7,0x3e,0x79,0xf9,0x9c,0xc0,0x19,0xfe,0xf,0xff,0xff,0xff,
        0xff,0xff,0xff,0xe0,0xf9,0xff,0x3f,0x33,0xe7,0x3e,0x79,0xf1,0x9c,0xcf,0xf9,0xfc,0x1f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xe0,0x78,0xff,0x9e,0x73,0xe7,0x3e,0x7c,0xf3,0x9c,0xc7,0xf9,0xf8,0x1f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xf0,0x7c,0x1,0x80,0x73,0xe7,0x6,0x7c,0x3,0x9c,0xe0,0x39,0xf8,0x3f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xf0,0x3f,0x3,0xe1,0xf3,0xe7,0x86,0x7f,0xf,0x9c,0xf8,0x39,0xf0,0x3f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xf8,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x7f,0xff,0xff,0xff,
        0xff,0xff,0xff,0xfc,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xfe,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x81,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xfe,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x81,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0x81,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x7,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xc0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xf,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xe0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x1f,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xf0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x3f,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xf8,0xf,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xff,0xc0,0x7f,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xfc,0x7,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xff,0x80,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xfe,0x1,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xfe,0x1,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xfc,0x3,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0x80,0x7f,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xf8,0x7,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xe0,0x1f,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xe0,0x1f,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xf0,0x7,0xff,0xf0,0x7f,0xfe,0xf,0xff,0x80,0x3f,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xf8,0x1,0xff,0xf0,0x7f,0xfe,0xf,0xfe,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xfe,0x0,0x7f,0xf0,0x7f,0xfe,0xf,0xf8,0x1,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x1f,0xf0,0x7f,0xfe,0xf,0xe0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x3,0xf0,0x7f,0xfe,0xf,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,0x70,0x7f,0xfe,0x8,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x7f,0xfe,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x7f,0xfe,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0x7f,0xfe,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x7f,0xfe,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x7f,0xfe,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x7f,0xfe,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

static const uint8_t PROGMEM logoInvert[] = {
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0x80,0x7,0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xe0,0x0,0x0,0x1f,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xfe,0x0,0x0,0x0,0x1,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xf8,0x0,0x0,0x0,0x0,0x3f,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xc0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x1,0xff,0x0,0x0,0x0,0x0,0x0,0x3,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x3,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x1f,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xe0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xf8,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x1,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x3,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0xf,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x1f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x3e,0x1,0x0,0x83,0x0,0x0,0x3,0x0,0xc0,0xc,0x1,0xf0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x7e,0x1,0x0,0x83,0x0,0x30,0x18,0x80,0xc0,0xc,0x1,0xf8,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0xfc,0x1,0x81,0x87,0x81,0x9c,0x10,0x1,0xe0,0xc,0x0,0xfc,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0xf8,0x1,0x81,0x4,0x80,0x4,0x30,0x1,0x20,0xc,0x0,0x7c,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x1,0xf0,0x0,0x81,0x4,0x80,0x6,0x30,0x1,0x20,0xc,0x0,0x3e,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x3,0xe0,0x0,0x83,0xc,0xc0,0x6,0x10,0x3,0x30,0xc,0x0,0x1f,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x3,0xe0,0x0,0xc2,0x8,0x40,0x4,0x1c,0x2,0x10,0xc,0x0,0x1f,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x7,0xc0,0x0,0x42,0x8,0x40,0x4,0x7,0x2,0x10,0xc,0x0,0xf,0x80,0x0,0x0,0x0,
        0x0,0x0,0x0,0x7,0x80,0x0,0x46,0x8,0x60,0x8,0x1,0x82,0x18,0xc,0x0,0x7,0x80,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf,0x80,0x0,0x64,0x1f,0xe0,0x18,0x0,0xc7,0xf8,0xc,0x0,0x7,0xc0,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf,0x0,0x0,0x24,0x10,0x20,0x30,0x0,0xc4,0x8,0xc,0x0,0x3,0xc0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x1f,0x0,0x0,0x24,0x10,0x30,0x60,0x0,0xc4,0xc,0xc,0x0,0x3,0xe0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x1e,0x0,0x0,0x28,0x30,0x10,0xc0,0x0,0x8c,0x4,0x8,0x0,0x1,0xe0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x3c,0x0,0x0,0x18,0x20,0x11,0x80,0x33,0x88,0x4,0xb8,0x0,0x0,0xf0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x3c,0x0,0x0,0x18,0x20,0x19,0xfe,0xc,0x8,0x6,0x40,0x0,0x0,0xf0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x7c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf8,0x0,0x0,0x0,
        0x0,0x0,0x0,0x78,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x78,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7c,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3c,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3c,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3c,0x0,0x0,0x0,
        0x0,0x0,0x1,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x0,0x0,0x0,
        0x0,0x0,0x1,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x0,0x0,0x0,
        0x0,0x0,0x1,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x0,0x0,0x0,
        0x0,0x0,0x1,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x6,0x0,0x80,0x0,0x0,0x0,0xc0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x7,0x1,0xc0,0x0,0x0,0x0,0xc0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x7,0x1,0xc0,0x0,0x0,0x0,0xc0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x5,0x2,0x40,0x0,0x0,0x0,0xc0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x4,0x82,0x40,0xc0,0x18,0x80,0xc0,0x6,0x0,0xc0,0x84,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x4,0x82,0x42,0x30,0x67,0x80,0xc0,0x19,0x83,0x30,0x93,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x7,0x80,0x4,0x86,0x40,0x10,0xc1,0x80,0xc0,0x20,0xc6,0x8,0xe0,0x80,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x4,0xc4,0x40,0x10,0x81,0x80,0xc0,0x20,0x44,0x8,0xc0,0x80,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x4,0x44,0x40,0x19,0x81,0x80,0xc0,0x60,0x6c,0xc,0xc0,0xc0,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x4,0x48,0x41,0xf9,0x81,0x80,0xc0,0x60,0x6c,0xc,0xc0,0xc0,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x4,0x68,0x42,0x19,0x81,0x80,0xc0,0x60,0x6c,0xc,0xc0,0xc0,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x4,0x28,0x46,0x18,0x81,0x80,0xc0,0x20,0x44,0x8,0xc0,0x80,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x4,0x30,0x46,0x18,0x81,0x80,0xc0,0x30,0xc6,0x18,0xc0,0x80,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x4,0x30,0x43,0x38,0x65,0x80,0xc0,0x19,0x83,0x30,0xf3,0x0,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0xc,0x10,0x41,0x88,0x11,0x80,0xff,0x6,0x0,0xc0,0xcc,0x0,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0xc0,0x0,0x7,0x80,0x0,0x0,
        0x0,0x0,0x7,0x80,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0xc0,0x0,0x7,0x80,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x0,0x0,0x0,0x0,0xc6,0x0,0x0,0x0,0x0,0x0,0xc0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x0,0x0,0x0,0x0,0x30,0x0,0x0,0x0,0x0,0x0,0xc0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x3,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x0,0x0,
        0x0,0x0,0x1,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x0,0x0,0x0,
        0x0,0x0,0x1,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x0,0x0,0x0,
        0x0,0x0,0x1,0xe0,0x0,0x38,0x0,0x0,0x0,0x0,0x0,0x0,0x63,0x0,0x0,0x0,0x1e,0x0,0x0,0x0,
        0x0,0x0,0x1,0xe0,0x1,0xc4,0x0,0x0,0x0,0x0,0x0,0x0,0x63,0x0,0x0,0x0,0x1e,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf0,0x3,0x0,0x0,0x0,0x0,0xc0,0x0,0x0,0x63,0x0,0x0,0x0,0x3c,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf0,0x6,0x0,0x0,0x0,0x0,0xc0,0x0,0x0,0x63,0x0,0x0,0x0,0x3c,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf0,0x4,0x0,0xc,0x8,0x41,0xf1,0x10,0x60,0x63,0x3,0x4,0x40,0x3c,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf8,0x4,0x0,0x33,0xd,0x30,0xc1,0x71,0x98,0x63,0xc,0x84,0xc0,0x7c,0x0,0x0,0x0,
        0x0,0x0,0x0,0x78,0xc,0x0,0x61,0x8c,0x10,0xc1,0x82,0xc,0x63,0x10,0x47,0x0,0x78,0x0,0x0,0x0,
        0x0,0x0,0x0,0x7c,0xc,0x0,0x40,0x8c,0x18,0xc1,0x82,0x4,0x63,0x10,0x46,0x0,0xf8,0x0,0x0,0x0,
        0x0,0x0,0x0,0x3c,0xc,0x0,0xc0,0xcc,0x18,0xc1,0x86,0x6,0x63,0x10,0x66,0x0,0xf0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x3c,0xc,0x0,0xc0,0xcc,0x18,0xc1,0x86,0x6,0x63,0x3f,0xe6,0x0,0xf0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x1e,0x4,0x0,0xc0,0xcc,0x18,0xc1,0x86,0x6,0x63,0x30,0x6,0x1,0xe0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x1f,0x6,0x0,0x40,0x8c,0x18,0xc1,0x82,0x4,0x63,0x10,0x6,0x3,0xe0,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf,0x3,0x0,0x61,0x8c,0x18,0xc1,0x83,0xc,0x63,0x10,0x6,0x3,0xc0,0x0,0x0,0x0,
        0x0,0x0,0x0,0xf,0x81,0xc4,0x33,0xc,0x18,0x61,0x81,0x98,0x63,0xc,0x46,0x7,0xc0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x7,0x80,0x30,0xc,0xc,0x18,0x31,0x80,0x60,0x63,0x3,0x6,0x7,0x80,0x0,0x0,0x0,
        0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x0,0x0,0x0,
        0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3e,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7c,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xf8,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x3e,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x1f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0xf,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x3,0xf0,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x0,0x3f,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x1,0xf8,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x7e,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x1,0xf8,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0xf,0x80,0x1,0xf0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x1f,0xc0,0x0,0xf,0x80,0x1,0xf0,0x0,0xf,0xe0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0xf,0x80,0x1,0xf0,0x0,0x3f,0x80,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x3,0xfc,0x0,0xf,0x80,0x1,0xf0,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x1,0xff,0x0,0xf,0x80,0x1,0xf0,0x3,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xc0,0xf,0x80,0x1,0xf0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xf0,0xf,0x80,0x1,0xf0,0x3f,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xfe,0xf,0x80,0x1,0xf1,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xef,0x80,0x1,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0x80,0x1,0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0x80,0x1,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0x80,0x1,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x80,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};
