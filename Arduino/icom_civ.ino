/*
   Mag loop antenna auto tuner

   Created 30 March. 2019
   Updated september 26th 2019
   by Carl Tremblay - VA2SAJ AKA cinosh07

   Attribution-NonCommercial 2.0 Generic (CC BY-NC 2.0) License

   code and circuitry inspired from
   https://create.arduino.cc/editor/JMardling/67243a05-af85-4b7b-832c-b67a56f8b77c/preview
   www.ve1zac.com/Simple%20Loop%20Automatic%20Tuner.pdf
   https://sites.google.com/site/lofturj/to-automatically-tune-a-magnetic-loop-antenna
 */
//***********************************************
//
// Serial port initialization for CI-V protocol
//
//***********************************************
#ifdef ICOM
void initCat() {
        configRadioBaud(9600);
        radio_address = 0x00;

        while (radio_address == 0x00) {
                if (!searchRadio()) {
                        initCat();
#ifdef DEBUG
                        Serial.println("Radio not found");
#endif
                } else {
#ifdef DEBUG
                        Serial.print("Radio found at ");
                        Serial.print(radio_address, HEX);
                        Serial.println();
#endif
                        radio_address = 0x5E;
                        sendCatRequest(MASTER_CMD_READ_FREQ);
                        delay(100);
                        sendCatRequest(MASTER_CMD_READ_MODE);
                        delay(100);
                        playBeepBeep();
                        break;
                }
        }
}
//*******************************************************************
//
//             Check if radio is currently transmitting
//
//*******************************************************************
int icom_getRadioTxmitStatus() {
        if (PTT_DTR_CTS == 0) {
                //TODO Check cat serial if radio is transmitting
        } else {
                if ( analogRead(swrSensorPin) == 0) {
                        return 0;
                } else {
                        return 1;
                }
        }
}
//*******************************************************************
//
//                 Request CI-V radio status
//
//*******************************************************************
void getIcomRadioStatus() {
        icom_request_signal();
        delay(10);
        receiveRadioCom();
        icom_request_mode();
        delay(10);
        receiveRadioCom();
        icom_request_pwr();
        delay(10);
        receiveRadioCom();
        icom_request_frequency();
        delay(10);
        receiveRadioCom();
}

//********************************************
//
//  Check if Radio serial com is availlable
//
//********************************************
void checkRadioCom() {
        if (Serial1.available() > 0)
        {
                incomingByte = Serial1.read(); //read the incoming byte
        }
}

//*********************************
//
//     Process CI-V message
//
//*********************************
void processCatMessages()
{
        /*
           <FE FE E0 42 04 00 01 FD  - LSB
           <FE FE E0 42 03 00 00 58 45 01 FD  -145.580.000
           FE FE - start bytes
           00/E0 - target address (broadcast/controller)
           42 - source address
           00/03 - data type
           <data>
           FD - stop byte
         */

        while (Serial1.available()) {

                uint32_t civ_value;
                if (readLine() > 0) {
                        if (transceiver_in_string[0] == START_BYTE && transceiver_in_string[1] == START_BYTE) {

                                if (transceiver_in_string[2] == BROADCAST_ADDRESS || transceiver_in_string[2] == CONTROLLER_ADDRESS) {
                                        if ((transceiver_in_string[4] == MASTER_CMD_TRANS_FREQ) || (transceiver_in_string[4] == MASTER_CMD_READ_FREQ) || (transceiver_in_string[4] == MASTER_CMD_WRITE_FREQ))
                                        {
                                                // Convert BCD to value
                                                civ_value = (transceiver_in_string[5] & 0x0f); // Hz
                                                civ_value += 10 * ((transceiver_in_string[5] & 0xf0) >> 4); // 10 x Hz

                                                civ_value += 100 *  (transceiver_in_string[6] & 0x0f);// 100 x Hz
                                                civ_value += 1000 * ((transceiver_in_string[6] & 0xf0) >> 4); // kHz

                                                civ_value += (uint32_t) 10000 * (transceiver_in_string[7] & 0x0f); // 10 x kHz
                                                civ_value += (uint32_t) 100000 * ((transceiver_in_string[7] & 0xf0) >> 4); // 100 x kHz

                                                civ_value += (uint32_t) 1000000 * (transceiver_in_string[8] & 0x0f); // MHz
                                                civ_value += (uint32_t) 10000000 * ((transceiver_in_string[8] & 0xf0) >> 4); // 10 x MHz

                                                civ_value += (uint32_t) 100000000 * (transceiver_in_string[9] & 0x0f); // 100 x MHz
                                                civ_value += (uint32_t) 1000000000 * ((transceiver_in_string[9] & 0xf0) >> 4); // GHz
                                                //
                                                // Update running frequency of the application
                                                //
                                                if ((civ_value > 1000000) && (civ_value < 31000000)) // Impose some sane boundaries
                                                {
                                                        config.CURRENT_FRQ = civ_value;
                                                        radio.freqSaved = true;
                                                        if (radio.radioIsPresent == 0) {
                                                                CURRENT_MODE = HOME;
                                                                radio.radioIsPresent = 1;
                                                        }
                                                }
                                        }
                                        // Check if this is an incoming Power Level Indication message
                                        else if ((transceiver_in_string[4] == MASTER_CMD_TOOLS) && (transceiver_in_string[5] == SUB_CMD_TOOLS_RF_POWER))
                                        {

                                                radio.trx_byte_pwr[0] = transceiver_in_string[6];
                                                radio.trx_byte_pwr[1] = transceiver_in_string[7];

                                                radio.trx_pwr = 100 * transceiver_in_string[6];
                                                radio.trx_pwr += transceiver_in_string[7];
                                        } else if ((transceiver_in_string[4] == MASTER_CMD_SIGNAL) && (transceiver_in_string[5] == SUB_CMD_SIGNAL_SMETER))
                                        {

                                                radio.trx_signal = 100 * transceiver_in_string[6];
                                                radio.trx_signal += transceiver_in_string[7];

                                        }
                                        else if ((transceiver_in_string[4] == MASTER_CMD_SIGNAL) && (transceiver_in_string[5] == SUB_CMD_SIGNAL_SWR_METER))
                                        {
                                                radio.trx_swr = 100 * transceiver_in_string[6];
                                                //              trx_swr += transceiver_in_string[7];
                                        }
                                        else if (transceiver_in_string[4] == MASTER_CMD_READ_FREQ) // Read active Mode (LSB, USB etc)
                                        {
                                                saveFrequency();
                                        }
                                        // Check if this is an incoming Mode and Filter Indication message
                                        else if (transceiver_in_string[4] == MASTER_CMD_READ_MODE) // Read active Mode (LSB, USB etc)
                                        {
                                                radio.trx_mode = transceiver_in_string[5]; // 0=LSB 1=USB 2=AM 3=CW...
                                                icom_filter = transceiver_in_string[6];
                                                printMode();
                                                if (prevTrxMode != radio.trx_mode) {
                                                        checkMemories();
                                                }
                                                prevTrxMode = radio.trx_mode;
                                        }
                                        // Check if this is a Positive acknowlegement message
                                        else if (transceiver_in_string[4] == RESPONSE_OK) // OK
                                        {
                                                //TODO
                                        }
                                        // Check if this is a Negative acknowlegement message
                                        else if (transceiver_in_string[4] == RESPONSE_ERROR) // OK
                                        {
                                                //TODO
                                        }
                                }
                        }
                }
#ifdef DEBUG
                Serial.print("<");
                for (uint8_t i = 0; i < sizeof(transceiver_in_string); i++) {
                        if (transceiver_in_string[i] < 16) Serial.print("0");
                        Serial.print(transceiver_in_string[i], HEX);
                        Serial.print(" ");
                        if (transceiver_in_string[i] == STOP_BYTE) break;
                }
                Serial.println();
#endif
        }

#ifdef MIRRORCAT
        while (Serial.available()) {
                Serial1.print(Serial.read(), BYTE);
        }
#endif
}
//***************************************
//
//      CI-V Receiving Transmit Mode
//
//***************************************
void printMode(void)
{
        //FE FE E0 42 04 <00 01> FD
        radio.trx_mode = transceiver_in_string[5];
#ifdef DEBUG
        Serial.println(mode[transceiver_in_string[5]]);
#endif
        //transceiver_in_string[6] -> 01 - Wide, 02 - Medium, 03 - Narrow
}
//*********************************
//
// CI-V baud rate configuration
//
//*********************************
void configRadioBaud(uint16_t baudrate)
{
        if (baud_rate != baudrate) {
                Serial1.end();
                Serial1.begin(baudrate);
        }
        baud_rate = baudrate;

        switch (baud_rate) {
        case 4800:
                readtimeout = 50000;
                break;
        case 9600:
                readtimeout = 40000;
                break;
        case 19200:
                readtimeout = 30000;
                break;
        default:
                readtimeout = 100000;
                break;
        }
}
//*************************************
//
// CI-V  decodage des messages seriel
//
//*************************************
uint8_t readLine(void)
{
        uint8_t byte;
        uint8_t counter = 0;
        uint32_t ed = readtimeout;

        while (true)
        {
                while (!Serial1.available()) {
                        if (--ed == 0) return 0;
                }
                ed = readtimeout;
                byte = Serial1.read();
                if (byte == 0xFF) continue; //TODO skip to start byte instead
#ifdef MIRRORCAT
                Serial.print(byte, BYTE);
#endif
                transceiver_in_string[counter++] = byte;
                if (STOP_BYTE == byte) break;

                if (counter >= sizeof(transceiver_in_string)) return 0;
        }
        return counter;
}
//---------------------------------------------------------------------------------
//
//     ICOM CI-V Command to execute after a request to get the asynch callback
//
//---------------------------------------------------------------------------------
void delayProcessCatMessages(uint16_t msec)
{
        unsigned long starttime, stoptime;
        starttime = millis();
        stoptime  = starttime + msec;

        while (stoptime > millis())
        {
                processCatMessages();
        }
}
//---------------------------------------------------------------------------------
//
//                 ICOM CI-V style polling for frequency
//
//---------------------------------------------------------------------------------
void icom_request_frequency(void)
{
        // Transmit a request to read operating frequency
        uint8_t req[] = {START_BYTE, START_BYTE, radio_address, CONTROLLER_ADDRESS, MASTER_CMD_READ_FREQ, STOP_BYTE};
#ifdef DEBUG
        Serial.print(">");
#endif
        for (uint8_t i = 0; i < sizeof(req); i++) {
                Serial1.write(req[i]);
#ifdef DEBUG
                if (req[i] < 16) Serial.print("0");
                Serial.print(req[i], HEX);
                Serial.print(" ");
#endif
        }
#ifdef DEBUG
        Serial.println();
#endif
        delayProcessCatMessages(SERIAL_DELAY);
}
//---------------------------------------------------------------------------------
//
//                    ICOM CI-V style Request Power
//
//---------------------------------------------------------------------------------
void icom_request_pwr(void)
{
        // Transmit a request to read RF Power Level setting
        uint8_t req[] = {START_BYTE, START_BYTE, radio_address, CONTROLLER_ADDRESS, MASTER_CMD_TOOLS, SUB_CMD_TOOLS_RF_POWER, STOP_BYTE};
#ifdef DEBUG
        Serial.print(">");
#endif
        for (uint8_t i = 0; i < sizeof(req); i++) {
                Serial1.write(req[i]);
#ifdef DEBUG
                if (req[i] < 16) Serial.print("0");
                Serial.print(req[i], HEX);
                Serial.print(" ");
#endif
        }
#ifdef DEBUG
        Serial.println();
#endif
        delayProcessCatMessages(SERIAL_DELAY);
}
//---------------------------------------------------------------------------------
//
//                ICOM CI-V style Request S Signal Strenght
//
//---------------------------------------------------------------------------------
void icom_request_signal(void)
{
        // Transmit a request to read ModeRF Power Level setting
        uint8_t req[] = {START_BYTE, START_BYTE, radio_address, CONTROLLER_ADDRESS, MASTER_CMD_SIGNAL, SUB_CMD_SIGNAL_SMETER, STOP_BYTE};
#ifdef DEBUG
        Serial.print(">");
#endif
        for (uint8_t i = 0; i < sizeof(req); i++) {
                Serial1.write(req[i]);
#ifdef DEBUG
                if (req[i] < 16) Serial.print("0");
                Serial.print(req[i], HEX);
                Serial.print(" ");
#endif
        }
#ifdef DEBUG
        Serial.println();
#endif
        delayProcessCatMessages(SERIAL_DELAY);
}
//---------------------------------------------------------------------------------
//
//                ICOM CI-V style Request Mode and Filter
//
//---------------------------------------------------------------------------------
void icom_request_mode(void)
{
        // Transmit a request to read ModeRF Power Level setting
        uint8_t req[] = {START_BYTE, START_BYTE, radio_address, CONTROLLER_ADDRESS, MASTER_CMD_READ_MODE, STOP_BYTE};
#ifdef DEBUG
        Serial.print(">");
#endif
        for (uint8_t i = 0; i < sizeof(req); i++) {
                Serial1.write(req[i]);
#ifdef DEBUG
                if (req[i] < 16) Serial.print("0");
                Serial.print(req[i], HEX);
                Serial.print(" ");
#endif
        }
#ifdef DEBUG
        Serial.println();
#endif
        delayProcessCatMessages(SERIAL_DELAY);
}
//---------------------------------------------------------------------------------
//
//                      ICOM CI-V style Set Power
//
//---------------------------------------------------------------------------------
void icom_set_pwr(uint8_t pwrFirstByte, uint8_t pwrSecondByte)
{
        // Set RF Power Level setting
        uint8_t req[] = {START_BYTE, START_BYTE, radio_address, CONTROLLER_ADDRESS, MASTER_CMD_TOOLS, SUB_CMD_TOOLS_RF_POWER, pwrFirstByte, pwrSecondByte, STOP_BYTE};
#ifdef DEBUG
        Serial.print(">");
#endif
        for (uint8_t i = 0; i < sizeof(req); i++) {
                Serial1.write(req[i]);
#ifdef DEBUG
                if (req[i] < 16) Serial.print("0");
                Serial.print(req[i], HEX);
                Serial.print(" ");
#endif
        }
#ifdef DEBUG
        Serial.println();
#endif
        delayProcessCatMessages(SERIAL_DELAY);
}
//*********************************
//
//    CI-V Radio Set Mode
//
//*********************************
void radioIcomSetMode(uint8_t modeid, uint8_t modewidth)
{
        uint8_t req[] = {START_BYTE, START_BYTE, radio_address, CONTROLLER_ADDRESS, MASTER_CMD_WRITE_MODE, modeid, modewidth, STOP_BYTE};
#ifdef DEBUG
        Serial.print(">");
#endif
        for (uint8_t i = 0; i < sizeof(req); i++) {
                Serial1.write(req[i]);
#ifdef DEBUG
                if (req[i] < 16) Serial.print("0");
                Serial.print(req[i], HEX);
                Serial.print(" ");
#endif
        }
#ifdef DEBUG
        Serial.println();
#endif
        delayProcessCatMessages(SERIAL_DELAY);
}
//---------------------------------------------------------------------------------
//
//                 ICOM CI-V style Set Transmit Mode
//
//---------------------------------------------------------------------------------
void icom_set_tx(uint8_t tx)
{
        // Set Transmit on or off
        if (PTT_DTR_CTS == 0) {
                uint8_t req[] = {START_BYTE, START_BYTE, radio_address, CONTROLLER_ADDRESS, MASTER_CMD_TXMIT, SUB_CMD_TXMIT, tx, STOP_BYTE};
#ifdef DEBUG
                Serial.print(">");
#endif
                for (uint8_t i = 0; i < sizeof(req); i++) {
                        Serial1.write(req[i]);
#ifdef DEBUG
                        if (req[i] < 16) Serial.print("0");
                        Serial.print(req[i], HEX);
                        Serial.print(" ");
#endif
                }
#ifdef DEBUG
                Serial.println();
#endif
                delayProcessCatMessages(SERIAL_DELAY);
        } else {
                //Use DTR-CTS to trigger PTT
                icom_set_tx_dtr(tx);
        }
}
//--------------------------------------------------------------------------------------------------------------
//
// ICOM CI-V style Set Transmit Mode - DTR -CTS Mode (To use when radion doesn't support transmitting over cat)
//
//--------------------------------------------------------------------------------------------------------------
void icom_set_tx_dtr(uint8_t tx)
{
        // Set Transmit on or off DTR-CTS Mode
        if (tx == 0x00) {
                digitalWrite(CTS_PIN, HIGH);
                digitalWrite(DTR_PIN, HIGH);
                delay(100);
                playBeep();
        } else if (tx == 0x01) {
                digitalWrite(CTS_PIN, LOW);
                digitalWrite(DTR_PIN, LOW);
                delay(100);
                playBeep();
        }
}
//*********************************
//
//       Send CI-V Request
//
//*********************************
void sendCatRequest(uint8_t requestCode)
{
        uint8_t req[] = {START_BYTE, START_BYTE, radio_address, CONTROLLER_ADDRESS, requestCode, STOP_BYTE};
#ifdef DEBUG
        Serial.print(">");
#endif
        for (uint8_t i = 0; i < sizeof(req); i++) {
                Serial1.write(req[i]);
#ifdef DEBUG
                if (req[i] < 16) Serial.print("0");
                Serial.print(req[i], HEX);
                Serial.print(" ");
#endif
        }
#ifdef DEBUG
        Serial.println();
#endif
}
//********************************************
//
//   CI-V Serial port for Radio presence
//
//********************************************
bool searchRadio()
{

        for (uint8_t baud = 0; baud < BAUD_RATES_SIZE; baud++) {
#ifdef DEBUG
                Serial.print("Try baudrate ");
                Serial.println(baudRates[baud]);
#endif
                configRadioBaud(baudRates[baud]);
                sendCatRequest(MASTER_CMD_READ_FREQ);
                if (readLine() > 0)
                {
                        if (transceiver_in_string[0] == START_BYTE && transceiver_in_string[1] == START_BYTE) {
                                //        radio_address = transceiver_in_string[3];
                                radio_address = transceiver_in_string[2];
                                if (radio_address == 0x00 ) {
                                        radio_address = 0x5E;
                                }
                        }
                        return true;
                }
        }
        radio_address = 0x5E;
        return false;
}
//******************************************
//
//    CI-V Receiving current frequency
//
//******************************************
void saveFrequency(void)
{
        config.CURRENT_FRQ = 0;
        //FE FE E0 42 03 <00 00 58 45 01> FD ic-820
        //FE FE 00 40 00 <00 60 06 14> FD ic-732
        for (uint8_t i = 0; i < 5; i++) {
                if (transceiver_in_string[9 - i] == 0xFD) continue; //spike
#ifdef DEBUG
                if (transceiver_in_string[9 - i] < 16) Serial.print("0");
                Serial.print(transceiver_in_string[9 - i], HEX);
#endif
                config.CURRENT_FRQ += (transceiver_in_string[9 - i] >> 4) * decMulti[i * 2];
                config.CURRENT_FRQ += (transceiver_in_string[9 - i] & 0x0F) * decMulti[i * 2 + 1];
        }
#ifdef DEBUG
        Serial.println();
#endif
}
//******************************************
//
//       Put Radio In autotune mode
//
//******************************************
void startIcomAutotune() {
        uint32_t position = config.CURRENT_POSITION;
        updateDisplay(position,WAITING_RADIO_TUNING_MESSAGE);
        PREVIOUS_POWER[0] = radio.trx_byte_pwr[0];
        PREVIOUS_POWER[1] = radio.trx_byte_pwr[1];
  #ifdef DEBUG
        Serial.println(PREVIOUS_POWER[0]);
        Serial.println(PREVIOUS_POWER[1]);
  #endif
        icom_set_pwr(TUNING_SAFE_POWER_FIRST_BYTE, TUNING_SAFE_POWER_SECOND_BYTE);
        delay(10);
        getIcomRadioStatus();
        delay(10);
        receiveRadioCom();
        while(radio.trx_byte_pwr[0] != TUNING_SAFE_POWER_FIRST_BYTE && radio.trx_byte_pwr[1] != TUNING_SAFE_POWER_SECOND_BYTE) {
                icom_set_pwr(TUNING_SAFE_POWER_FIRST_BYTE, TUNING_SAFE_POWER_SECOND_BYTE);
                delay(10);
                getIcomRadioStatus();
                delay(10);
                receiveRadioCom();
                updateDisplay(position,WAITING_RADIO_SAFE_POWER_MESSAGE);
        }
        updateDisplay(position,WAITING_RADIO_MODE_MESSAGE);
        PREVIOUS_TRX_MODE = radio.trx_mode;
        radioIcomSetMode(MODE_TYPE_RTTY, icom_filter);
        delay(10);
        getIcomRadioStatus();
        delay(10);
        receiveRadioCom();
        while (radio.trx_mode != MODE_TYPE_RTTY) {
                radioIcomSetMode(MODE_TYPE_RTTY, icom_filter);
                delay(10);
                getIcomRadioStatus();
                delay(10);
                receiveRadioCom();
                updateDisplay(position,WAITING_RADIO_MODE_MESSAGE);
        }
        updateDisplay(position,WAITING_RADIO_TXMIT_MESSAGE);
        icom_set_tx(TRANSMITTING);
        delay(100);
        getIcomRadioStatus();
        delay(100);
        receiveRadioCom();
        while (getRadioTxmitStatus() != 1) {
                getIcomRadioStatus();
                delay(100);
                receiveRadioCom();
                if(getRadioTxmitStatus() != 1) {
                        icom_set_tx(RECEIVING);
                        delay(10);
                        getIcomRadioStatus();
                        delay(100);
                        receiveRadioCom();
                        icom_set_tx(TRANSMITTING);
                        delay(10);
                        getIcomRadioStatus();
                        delay(500);
                        receiveRadioCom();
                        delay(10);
                        getIcomRadioStatus();
                        delay(10);
                        receiveRadioCom();
                }

                getIcomRadioStatus();
                delay(10);
                receiveRadioCom();
                icom_set_tx(TRANSMITTING);
                delay(10);
                getIcomRadioStatus();
                delay(10);
                receiveRadioCom();
                updateDisplay(position,WAITING_RADIO_TXMIT_MESSAGE);
        }
}
//******************************************
//
//     Remove Radio from autotune mode
//
//******************************************
void stopIcomAutotune() {
        uint32_t position = config.CURRENT_POSITION;
        updateDisplay(position,WAITING_RADIO_TUNING_MESSAGE);
        radio.txmit = false;
        icom_set_tx(RECEIVING);
        delay(10);
        getIcomRadioStatus();
        delay(10);
        receiveRadioCom();
        while (getRadioTxmitStatus() != 0) {
                getIcomRadioStatus();
                delay (10);
                receiveRadioCom();
                updateDisplay(position,WAITING_RADIO_TUNING_MESSAGE);
        }
        icom_set_pwr(PREVIOUS_POWER[0], PREVIOUS_POWER[1]);
        delay(10);
        getIcomRadioStatus();
        delay(10);
        receiveRadioCom();
        while(radio.trx_byte_pwr[0] !=  PREVIOUS_POWER[0] && radio.trx_byte_pwr[1] != PREVIOUS_POWER[1]) {
                icom_set_pwr(PREVIOUS_POWER[0], PREVIOUS_POWER[1]);
                delay(10);
                getIcomRadioStatus();
                delay(10);
                receiveRadioCom();
                updateDisplay(position,WAITING_RADIO_MODE_MESSAGE);
        }
        radioIcomSetMode(PREVIOUS_TRX_MODE, icom_filter);
        delay(10);
        getIcomRadioStatus();
        delay(10);
        receiveRadioCom();
        while (radio.trx_mode != PREVIOUS_TRX_MODE) {
                radioIcomSetMode(PREVIOUS_TRX_MODE, icom_filter);
                delay(10);
                getIcomRadioStatus();
                delay(10);
                receiveRadioCom();
                updateDisplay(position,WAITING_RADIO_MODE_MESSAGE);
        }
}
#endif
