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
//***************************************************************************************
//
//                         Networking Initialization
//         (NOT COMPATIBLE WITCH MEGA 2560 - USE ARDUINO DUE 32bit platform)
//   https://github.com/asksensors/AskSensors-Arduino-Ethernet/blob/master/http_get.ino
//
//***************************************************************************************
void initNetworkServer() {
        activateNetwork();
#ifdef NETWORK
        Ethernet.init(W5500_SS);
        delay(1000);
        Ethernet.begin(mac, ip, gateway, subnet);
        // give the Ethernet shield a second to initialize:
        delay(1000);
        if (Ethernet.hardwareStatus() == EthernetNoHardware) {
                playAlarmNONETWORK();
#ifdef DEBUG
                Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
#endif
                while (true) {
                        delay(1); // do nothing, no point running without Ethernet hardware
                }
        }
        if (Ethernet.linkStatus() == LinkOFF) {
                isNetworkPresent = false;
                playAlarmNONETWORK();
        } else {
                isNetworkPresent = true;
        }
        server.begin();
#endif
}
//******************************************************
//
//  Listen Web Request from external APP or Cloud App
//     No Control Allowed over the web.
//   For management, configurations and backup only
//
//******************************************************
void checkServerConnection() {
        // Create a client connection
        activateNetwork();
#ifdef NETWORK
        EthernetClient client = server.available();

        boolean currentLineIsBlank = true;
        boolean sentHeader = false;

        if (client) {
                while (client.connected()) {
                        char c;
#ifdef DEBUG
                        Serial.println("Connection Received");
#endif
                        while (client.available()) {

                                c = client.read();
                                readString += c;
                                if (readString.indexOf("{\"request\":") > -1) {
                                        readString = "";
                                }
                        }
                        if (readString.indexOf("}}") > -1) {

                                readString = readString.substring(0, readString.length() - 1);
                                StaticJsonDocument<500> request;
                                StaticJsonDocument<3000> response;
                                deserializeJson(request, readString);
                                String command = request["command"].as<char *>();
                                String type = request["type"].as<char *>();
                                int value = request["value"].as<int>();
                                //******************************************
                                //Command Received:  Get Configuration file;
                                //******************************************
                                if (command.indexOf("getConfig") > -1)
                                {

                                        response["version"] = VERSION;
                                        response["position"] = config.CURRENT_POSITION;
                                        response["frequency"] = config.CURRENT_FRQ;
                                        response["mode"] = config.CURRENT_MODE;
                                        response["band"] = config.CURRENT_BAND;
                                        response["autotune"] = config.AUTO_TUNE;
                                        response["autofollow"] = config.AUTO_FOLLOW;
                                        response["iscalib"] = config.ISCALIB;
                                        response["pos20m"] = 0;
                                        response["pos30m"] = config.POS30M;
                                        response["pos40m"] = config.POS40M;
                                        response["pos60m"] = config.POS60M;
                                        response["pos80m"] = config.POS80M;
                                        response["CURRENT_MODE"] = config.CURRENT_MODE;
                                        response["CURRENT_BAND"] = config.CURRENT_BAND;
                                        response["CURRENT_DIRECTION"] = config.CURRENT_DIRECTION;
                                        response["BACKSLASH"] = config.BACKSLASH;
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Set Configuration file;
                                //******************************************
                                if (command.indexOf("setConfig") > -1)
                                {
                                        response["status"] = "TODO";
                                        // response["version"] = VERSION;
                                        // response["position"] = config.CURRENT_POSITION;
                                        // response["frequency"] = config.CURRENT_FRQ;
                                        // response["mode"] = config.CURRENT_MODE;
                                        // response["band"] = config.CURRENT_BAND;
                                        // response["autotune"] = config.CURRENT_BAND;
                                        // response["autofollow"] = config.CURRENT_BAND;
                                        // response["iscalib"] = config.ISCALIB;
                                        // response["pos20m"] = 0;
                                        // response["pos30m"] = config.POS30M;
                                        // response["pos40m"] = config.POS40M;
                                        // response["pos60m"] = config.POS60M;
                                        // response["pos80m"] = config.POS80M;

                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Get 20M Memory File
                                //******************************************
                                if (command.indexOf("getMem20M") > -1)
                                {
                                        //          response["memory20m"] = memoryToJson(BAND_20M);
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Get 30M Memory File
                                //******************************************
                                if (command.indexOf("getMem30M") > -1)
                                {
                                        //          response["memory30m"] = memoryToJson(BAND_30M);
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Get 40M Memory File
                                //******************************************
                                if (command.indexOf("getMem40M") > -1)
                                {

                                        //          response["memory40m"] = memoryToJson(BAND_40M);
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Get 60M Memory File
                                //******************************************
                                if (command.indexOf("getMem60M") > -1)
                                {
                                        //          response["memory60m"] = memoryToJson(BAND_60M);
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Get 80M Memory File
                                //******************************************
                                if (command.indexOf("getMem80M") > -1)
                                {
                                        //          response["memory80m"] = memoryToJson(BAND_80M);
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Set 20M Memory File
                                //******************************************

                                if (command.indexOf("setMem20M") > -1)
                                {
                                        response["status"] = "TODO";
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Set 30M Memory File
                                //******************************************
                                if (command.indexOf("setMem30M") > -1)
                                {
                                        response["status"] = "TODO";
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Set 40M Memory File
                                //******************************************
                                if (command.indexOf("setMem40M") > -1)
                                {
                                        response["status"] = "TODO";
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Set 60M Memory File
                                //******************************************
                                if (command.indexOf("setMem60M") > -1)
                                {
                                        response["status"] = "TODO";
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Set 80M Memory File
                                //******************************************
                                if (command.indexOf("setMem80M") > -1)
                                {
                                        response["status"] = "TODO";
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                                //******************************************
                                //Command Received:  Todo
                                //******************************************
                                if (command.indexOf("todo") > -1)
                                {
                                        //
                                        //          if (type.indexOf("slowup") > -1 && currentPosition < maxSteps) {
                                        //
                                        //
                                        //          }
                                        response["position"] = config.CURRENT_POSITION;
                                        client.println(F("HTTP/1.0 200 OK"));
                                        client.println(F("Content-Type: application/json"));
                                        client.println(F("Connection: close"));
                                        client.print(F("Content-Length: "));
                                        client.println(measureJsonPretty(response));
                                        client.println();
                                        // Write JSON document
                                        serializeJsonPretty(response, client);
                                        //clearing string for next read
                                        readString = "";
                                        delay(10);
                                        client.stop();
                                }
                        }
                }
        }
#endif
}
//*******************************************************
//
//      Send Configs and memories to the cloud service
//
//*******************************************************
void sendCloudConfig() {
        activateNetwork();
#ifdef CLOUD_SAVE
        if (cloudClient.connect(cloudServer, port)) {
#ifdef DEBUG
                Serial.print("connected asksensors.com");
#endif
                //Create a URL for the request
                String url = "http://asksensors.com/api.asksensors/write/";
                url += apiKeyIn;
                url += "?module1=";
                url += dumData;
#ifdef DEBUG
                Serial.print("********** requesting URL: ");
                Serial.println(url);
#endif
                //Make a HTTP request:
                cloudClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                                  "Host: " + cloudServer + "\r\n" +
                                  "Connection: close\r\n\r\n");
                cloudClient.println();
#ifdef DEBUG
                Serial.println("> Request sent to ASKSENSORS");
#endif
        } else {
                // if you didn't get a connection to the cloudClient:
#ifdef DEBUG
                Serial.println("connection failed");
                playAlarmNOCLOUD();
#endif
        }
#endif
}
//***********************************************
//
//      Read response from the cloud service
//
//***********************************************
void readCloudResponse() {
#ifdef CLOUD_SAVE
        // if there are incoming bytes available
        // from the cloudClient, read them and print them:
        if (cloudClient.available()) {
                char c = cloudClient.read();
#ifdef DEBUG
                Serial.print(c);
#endif
        }
        //   if the cloudClient's disconnected, stop the client:
        if (!cloudClient.connected()) {
#ifdef DEBUG
                Serial.println();
                Serial.println("disconnecting.");
#endif
                cloudClient.stop();
                // do nothing forevermore:
                while (true);
        }
#endif
}
//*****************************************************
//
//    Switch SPI interface to use Network Shield
//
//*****************************************************
void activateNetwork() {
        digitalWrite(sdCardCSPin, HIGH);
        digitalWrite( networkShieldCSPin, LOW  );
        delay(50);
}
