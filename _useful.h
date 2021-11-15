/* 
 *   
 *  Project:          IoT Energy Meter with C/C++, Java/Spring, TypeScript/Angular and Dart/Flutter;
 *  About:            End-to-end implementation of a LoRaWAN network for monitoring electrical quantities;
 *  Version:          1.0;
 *  Backend Mote:     ATmega328P/ESP32/ESP8266/ESP8285/STM32;
 *  Radios:           RFM95w and LoRaWAN EndDevice Radioenge Module: RD49C;
 *  Sensors:          Peacefair PZEM-004T 3.0 Version TTL-RTU kWh Meter;
 *  Backend API:      Java with Framework: Spring Boot;
 *  LoRaWAN Stack:    MCCI Arduino LoRaWAN Library (LMiC: LoRaWAN-MAC-in-C) version 3.0.99;
 *  Activation mode:  Activation by Personalization (ABP) or Over-the-Air Activation (OTAA);
 *  Author:           Adail dos Santos Silva
 *  E-mail:           adail101@hotmail.com
 *  WhatsApp:         +55 89 9 9433-7661
 *  
 *  In the _serialBuffers.h tab, some changes were made to the implementation by the creator of this project,
 *  but the copyright will continue to be for: Jakub Mandula Copyright (c) 2019;
 *  All the remaining implementation is authored by the creator of the LoRaWAN Electricity Meter project.
 *  
 *  WARNINGS:
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 *  this software and associated documentation files (the “Software”), to deal in
 *  the Software without restriction, including without limitation the rights to
 *  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 *  the Software, and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 *  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 *  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 *  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *  
 */

/*
 *  Important Tools for Working with LoRaWAN
 * 
 *  Airtime calculator                - https://www.thethingsnetwork.org/airtime-calculator
 *  LoraW packet decoder              - https://lorawan-packet-decoder-0ta6puiniaut.runkit.sh/?data
 *  LoraW packet decoder(GitHub)      - https://github.com/anthonykirby/lora-packet
 *  RF unit converter                 - https://www.eeweb.com/tools/rf-unit-converter/
 *  Coax calculator                   - https://www.eeweb.com/tools/coax
 *  dBm conversion                    - https://www.rapidtables.com/convert/power/dBm_to_Watt.html
 *  Return loss                       - https://www.ubcorp.com/return-loss-vs-voltage-standing.../
 *  JPole calculator                  - http://www.hamuniverse.com/jpole.html
 *  RF propagation                    - http://radiomobile.pe1mew.nl
 *  Calculate distance                - http://www.movable-type.co.uk/scripts/latlong.html
 *  Open port checker                 - https://www.yougetsignal.com/tools/open-ports/
 *  IPv6 checker                      - http://test-ipv6.com/
 *  Wire Gauge conv                   - https://www.engineeringtoolbox.com/awg-wire-gauge-d_731.html
 *  EASY EDA                          - https://easyeda.com/editor
 *  Circuit sim                       - http://lushprojects.com/circuitjs/
 *  Tone Generator                    - https://onlinetonegenerator.com/
 *  Calculate LM317                   - http://www.muzique.com/schem/lm317.htm
 *  Battery life calcu                - http://oregonembedded.com/batterycalc.htm
 *  Voltage drop                      - https://www.calculator.net/voltage-drop-calculator.html
 *  Bin to Hex                        - https://www.mathsisfun.com/binary-decimal-hexadecimal...
 *  Dec to Bin                        - https://www.rapidtables.com/.../decimal-to-binary.html
 *  Hex to Dec                        - https://www.binaryhexconverter.com/hex-to-decimal-converter
 *  Hex to Bin                        - https://www.binaryhexconverter.com/hex-to-binary-converter
 *  Hex to Base64                     - https://base64.guru/converter/encode/hex
 *  Base64 to ASCII                   - https://www.base64decode.org/
 *  Resistive devider                 - http://www.magic-worlld.narod.ru/
 *  BMP converter                     - https://products.groupdocs.app/metadata/bmp
 *  Epub converter                    - https://www.convertfiles.com/convert/ebook/EPUB-to-PDF.html
 *  CODEPILE                          - https://www.codepile.net
 *  CODESHARE                         - https://codeshare.io/
 *  Hookbin                           - https://hookbin.com/
 *  RequestsBin.NET                   - https://requestbin.net/
 *  RequestBin.com (pipedream)        - https://requestbin.com/
 *  JSON Formatter & Validator        - https://jsonformatter.curiousconcept.com/
 *  Free Online Tools For Developers  - https://www.freeformatter.com/
 *  JSON for in line String           - https://tools.knowledgewalls.com/jsontostring
 *  JSON to Java POJO Converter       - http://www.jsonschema2pojo.org/
 *  
 *  Info:
 *  SNR                               - https://en.wikipedia.org/wiki/Signal-to-noise_ratio
 *  RSSI                              - https://en.wikipedia.org/.../Received_signal_strength...
 *  DBI                               - https://en.wikipedia.org/wiki/Antenna_gain
 *  
 *  Simulation of radio propagation (also useful for LoRaWAN)
 *  https://link.ui.com/?fbclid=IwAR12Lh9sqspdMmBwyCiI3sjtFzMB80ZlnONlck40ltbYA48uNi6li35E5Uo
 *  
 */

/*
 *  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
 *  Nodes in The Things Network - TTN
 *  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *  # OTAA
 *  Device ID       ttgo_tbeam_otaa
 *  Description     TTGO TBeam OTAA
 *  Device EUI      00275bef0fbde4f0
 *  Application EUI 70b3d57ed0031701
 *  App Key         70dca98078374c51633e4d7316a6b3b1
 *  ------------------------------------------------
 *  # ABP
 *  ttgo_tbeam_abp
 *  Description         TTGO TBeam ABP
 *  Device EUI          00275bef0fbde4f0
 *  Application EUI     70b3d57ed0031701
 *  App Key             70dca98078374c51633e4d7316a6b3b1
 *  
 *  Device Address      26031738 // Variable
 *  Network Session Key a59b565ed0c708cc2bf27d8b7140ed90
 *  App Session Key     f358b74f3603036b463ec486dbb22955
 *  ----------------------------------------------------
 *  
 *  %%%%%%%%%%%%%%%%%%%%%%%%%
 *  Nodes in ChirpStack - CS
 *  %%%%%%%%%%%%%%%%%%%%%%%%%
 *  
 *  Details
 *  deviceName:     "esp32-rfm95w-pzem-004t"
 *  Name            ESP32+RFM95W+PZEM-004T_v3.0
 *  Description     Three-Phase Electrical Monitoring with the LoRaWAN Protocol
 *  Device-profile  EnergyMetterDP
 * 
 */
  
/* 
 *  To view logs at the gateways
 *  tail -f /var/log/syslog | grep "JSON up"
 *  tail -f /var/log/syslog | grep "JSON down"
 */

/*
 *  IN GATEWAY
 *  
 *  ### Downlinks OTAA:
 *  
 *  JSON up: {"time":"2020-12-25T18:28:46Z","rxpk":[{"tmst":3635223316,"time":"2020-12-25T18:28:46.704289Z","chan":5,"rfch":1,"freq":917.800000,"stat":1,"modu":"LORA","datr":"SF10BW125","codr":"4/5","lsnr":9.2,"rssi":-25,"size":23,"data":"AAEXA9B+1bNw8OS9D+9bJwBFN37uDrU="}]}
 *  
 *  5000000
 *  
 *  JSON down: {"txpk":{"imme":false,"tmst":3640223316,"freq":926.3,"rfch":0,"powe":20,"modu":"LORA","datr":"SF10BW500","codr":"4/5","ipol":true,"size":17,"ncrc":true,"data":"IFskvyGfiBxj7+un82Xh0PQ="}}
 *  
 *  1184543 - Calibrate this moment...
 *  
 *  JSON up: {"time":"2020-12-25T18:28:52Z","rxpk":[{"tmst":3641407859,"time":"2020-12-25T18:28:52.888912Z","chan":3,"rfch":0,"freq":917.400000,"stat":1,"modu":"LORA","datr":"SF7BW125","codr":"4/5","lsnr":9.0,"rssi":-31,"size":23,"data":"QMUmAyYAAABll2Y8tWcHNMvlsvlWalY="}]}
 *  
 *  3 640 223 316 - 3 635 223 316 = 5 000 000 (5000000)
 *  3 641 407 859 - 3 640 223 316 = 1 184 543 (1184543)
 *  
 *  ### Downlinks Comuns:
 *  
 *  JSON up: {"time":"2020-12-25T18:36:50Z","rxpk":[{"tmst":4119158379,"time":"2020-12-25T18:36:50.645765Z","chan":4,"rfch":1,"freq":917.600000,"stat":1,"modu":"LORA","datr":"SF7BW125","codr":"4/5","lsnr":9.5,"rssi":-33,"size":23,"data":"QOAgAyYAAgBlOaVbpuXsD3kxT2ppQUw="}]}
 *  
 *  1000000
 *  
 *  JSON down: {"txpk":{"imme":false,"tmst":4120158379,"freq":925.7,"rfch":0,"powe":20,"modu":"LORA","datr":"SF7BW500","codr":"4/5","ipol":true,"size":14,"ncrc":true,"data":"YOAgAyYAAAABXKj0hwQ="}}
 *  
 *  4 120 158 379 - 4 119 158 379 = 1 000 000 (1000000)
 *
 */

/*
 *  IN NODE
 *  
 *  ### CLOCK_ERROR 0 %:
 *  
 *  ### Join Request - OTAA:
 *  56697: TXMODE, freq=917200000, len=23, SF=10, BW=125, CR=4/5, IH=0
 *  
 *  start single rx: now-rxtime: 3
 *  392256: RXMODE_SINGLE, freq=924500000, SF=10, BW=500, CR=4/5, IH=0
 *  
 *  ### Time Join Response - OTAA:
 *  392 256 - 56 697 = 335 559
 *  
 *  ### Time Downlinks:
 *  463576: TXMODE, freq=917400000, len=23, SF=7, BW=125, CR=4/5, IH=0
 *  
 *  start single rx: now-rxtime: 4
 *  530320: RXMODE_SINGLE, freq=925100000, SF=7, BW=500, CR=4/5, IH=0
 *  rxtimeout: entry: 530547 rxtime: 530312 entry-rxtime: 235 now-entry: 4 rxtime-txend: 62375
 *  
 *  start single rx: now-rxtime: 4
 *  592819: RXMODE_SINGLE, freq=923300000, SF=9, BW=125, CR=4/5, IH=0
 *  rxtimeout: entry: 594627 rxtime: 592812 entry-rxtime: 1815 now-entry: 4 rxtime-txend: 124875
 *  
 *  ### Time to Open RX1:
 *  530 320 - 463 576 = 66 744  (Tx   -->   Rx1 time  : 1 000 000)
 *  
 *  ### Time to Open RX2:
 *  592 819 - 530 320 = 62 499  (Rx1  -->   Rx2 time  : 1 000 000) --> (Duration Rx1)
 *  592 819 - 463 576 = 129 243 (TX   -->   Rx2 time  : 2 000 000)
 *  
 *  
 *  
 *  ### CLOCK_ERROR 10 %:
 *  
 *  ### Join Request - OTAA:
 *  56702: TXMODE, freq=918200000, len=23, SF=10, BW=125, CR=4/5, IH=0
 *  
 *  start single rx: now-rxtime: 3
 *  392262: RXMODE_SINGLE, freq=927500000, SF=10, BW=500, CR=4/5, IH=0
 *  
 *  ### Time Join Response - OTAA:
 *  392 262 - 56 702 = 335 560
 *  
 *  ### Time Downlinks:
 *  463582: TXMODE, freq=916800000, len=23, SF=7, BW=125, CR=4/5, IH=0
 *  
 *  start single rx: now-rxtime: 4
 *  530077: RXMODE_SINGLE, freq=923300000, SF=7, BW=500, CR=4/5, IH=0
 *  rxtimeout: entry: 530800 rxtime: 530069 entry-rxtime: 731 now-entry: 4 rxtime-txend: 62126
 *  
 *  start single rx: now-rxtime: 4
 *  592326: RXMODE_SINGLE, freq=923300000, SF=9, BW=125, CR=4/5, IH=0
 *  rxtimeout: entry: 595158 rxtime: 592319 entry-rxtime: 2839 now-entry: 4 rxtime-txend: 124376
 *  
 *  ### Time to Open RX1:
 *  530 077 - 463 582 = 66 495  (Tx --> Rx1 time  : 1 000 000)
 *  
 *  ### Time to Open RX2:
 *  592 326 - 530 077 = 62 249  (Rx1  -->   Rx2 time  : 1 000 000) --> (Duration Rx1)
 *  592 326 - 463 582 = 128 744 (TX   -->   Rx2 time  : 2 000 000)
 *  
 */

 /*
  *   AU915-928 in The Things Network - TTN
  *   
  *   Uplink:
  *   916.8 - SF7BW125 to SF12BW125
  *   917.0 - SF7BW125 to SF12BW125
  *   917.2 - SF7BW125 to SF12BW125
  *   917.4 - SF7BW125 to SF12BW125
  *   917.6 - SF7BW125 to SF12BW125
  *   917.8 - SF7BW125 to SF12BW125
  *   918.0 - SF7BW125 to SF12BW125
  *   918.2 - SF7BW125 to SF12BW125
  *   917.5 - SF8BW500
  *   
  *   Downlink:
  *   923.3 - SF7BW500 to SF12BW500 (RX1)
  *   923.9 - SF7BW500 to SF12BW500 (RX1)
  *   924.5 - SF7BW500 to SF12BW500 (RX1)
  *   925.1 - SF7BW500 to SF12BW500 (RX1)
  *   925.7 - SF7BW500 to SF12BW500 (RX1)
  *   926.3 - SF7BW500 to SF12BW500 (RX1)
  *   926.9 - SF7BW500 to SF12BW500 (RX1)
  *   927.5 - SF7BW500 to SF12BW500 (RX1)
  *   923.3 - SF12BW500 (RX2)
  *   
  *   Note that The Things Network uses 2nd Sub-Band only (channels 8 to 15 and 65).
  *   You’ll need to program the specific channels into the devices in order to make them work with TTN.
  * 
  */  

/* A DETAIL FOR THE LoRaWAN PROTOCOL:
 * 
 * For the First Reception Window, each DOWNLINK frequency is heard by the node, in a channel whose index of the same,
 * taking into account the plan used, it will correspond to the channel index of the last UPLINK frequency sent by the node.
 *
 * For the second Reception Window, it will always be active to listen to the default channel for Downlinks 0, which has a frequency of 923.3MHz.
 * This channel (frequency) of the second reception window can be customized, respecting the downlink frequencies of the chosen plan.
 *
 * Regarding the order of channels, it also applies to the sending rules (TX) by the Gateway at the request of the Network Server to the nodes.
 *
 * 
 * EXAMPLE FOR THE AU915-928 FREQUENCY PLAN:
 * 
 * "UPLINK at 916.8MHz then Listen DOWNLINK at: RX1 923.3MHz RX2 923.3MHz. (Customizable RX2)";
 *
 * "UPLINK at 918.2MHz then Listen DOWNLINK at: RX1 927.5MHz RX2 923.3MHz. (Customizable RX2)"; 
 * 
 *  
 * | Channel | Direction | Frequency (MHz) | Bandwidth (kHz) |  Data Rate |
 * |:-------:|:---------:|:---------------:|:---------------:|:----------:|
 * |    8    |     UP    |      916.8      |       125       |  DR0 - DR3 |
 * |    9    |     UP    |      917.0      |       125       |  DR0 - DR3 |
 * |    10   |     UP    |      917.2      |       125       |  DR0 - DR3 |
 * |    11   |     UP    |      917.4      |       125       |  DR0 - DR3 |
 * |    12   |     UP    |      917.6      |       125       |  DR0 - DR3 |
 * |    13   |     UP    |      917.8      |       125       |  DR0 - DR3 |
 * |    14   |     UP    |      918.0      |       125       |  DR0 - DR3 |
 * |    15   |     UP    |      918.2      |       125       |  DR0 - DR3 |
 * |    65   |     UP    |      917.5      |       500       |     DR4    |
 * |    0    |    DOWN   |      923.3      |       500       | DR8 - DR13 |
 * |    1    |    DOWN   |      923.9      |       500       | DR8 - DR13 |
 * |    2    |    DOWN   |      924.5      |       500       | DR8 - DR13 |
 * |    3    |    DOWN   |      925.1      |       500       | DR8 - DR13 |
 * |    4    |    DOWN   |      925.7      |       500       | DR8 - DR13 |
 * |    5    |    DOWN   |      926.3      |       500       | DR8 - DR13 |
 * |    6    |    DOWN   |      926.9      |       500       | DR8 - DR13 |
 * |    7    |    DOWN   |      927.5      |       500       | DR8 - DR13 |
 * 
 */

 /*
  *   ChirpStack HTTP Integration:
  *   
  *   cURL Commands Examples:
  *   curl -X POST -d "AdailSilva" http://localhost:8080/api
  *   curl -X POST -H "Content-Type: application/json" -d '{"name": "AdailSilva"}' http://localhost:8080/api
  *   
  *   
  *   ### Enqueue downlink
  *   
  *   The following examples enqueues the base64 payload AQID (which is 010203 in HEX)
  *   for the device with DevEUI f38df5e5a31e63de. Do not forget to replace <API TOKEN> with an API token retrieved using the web-interface.
  *   
  *   ### Global API keys
  *   
  *   ## API key ID:
  *   994f0123-0c49-4316-abfe-25987d9655f1
  *   
  *   ## API key name:
  *   EnergyMetterGlobalAPIK
  *   
  *   ## Token:
  *   eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcGlfa2V5X2lkIjoiOTk0ZjAxMjMtMGM0OS00MzE2LWFiZmUtMjU5ODdkOTY1NWYxIiwiYXVkIjoiYXMiLCJpc3MiOiJhcyIsIm5iZiI6MTYxODE2Nzg0Niwic3ViIjoiYXBpX2tleSJ9.gy6vAmkihnKjuYjiBSJZ06hRGZ2wf31l_SN0Dw9qo_o
  *   WARNING: Use this token when making API request with this API key. This token is provided once.
  *   
  *   # Integration HTTP with curl:
  *   curl -X POST --header 'Content-Type: application/json' --header 'Accept: application/json' --header 'Grpc-Metadata-Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcGlfa2V5X2lkIjoiOTk0ZjAxMjMtMGM0OS00MzE2LWFiZmUtMjU5ODdkOTY1NWYxIiwiYXVkIjoiYXMiLCJpc3MiOiJhcyIsIm5iZiI6MTYxODE2Nzg0Niwic3ViIjoiYXBpX2tleSJ9.gy6vAmkihnKjuYjiBSJZ06hRGZ2wf31l_SN0Dw9qo_o' -d '{ "deviceQueueItem": { "confirmed": false, "data": "AQID", "fPort": 101 } }' 'http://192.168.1.203:8080/api/devices/f38df5e5a31e63de/queue'
  *   
  *   
  *   Front-end in Application Server:   
  *   # JWT secret used for api authentication / authorization
  *   # You could generate this by executing 'openssl rand -base64 32' for example
  *   jwt_secret="newp2YSvBYgci5QSfu1wwkD/YDKykOvKl/M0GGZF6mI="
  *   
  *   
  *   ### Organization API keys
  *   
  *   ## API key ID:
  *   6e796091-b4d5-43e2-98e2-90c1bd462518
  *   
  *   ## API key name:
  *   EnergyMetterOrganizationAPIK
  *   
  *   ## Token:
  *   eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcGlfa2V5X2lkIjoiNmU3OTYwOTEtYjRkNS00M2UyLTk4ZTItOTBjMWJkNDYyNTE4IiwiYXVkIjoiYXMiLCJpc3MiOiJhcyIsIm5iZiI6MTYxODE2NzQzNiwic3ViIjoiYXBpX2tleSJ9.HYmj63YSTK5NUClb1Jo2DnDMRVDpRP8YeaZ4k-AqRVA
  *   WARNING: Use this token when making API request with this API key. This token is provided once.
  *   
  *   
  *   
  *   ChirpStack MQTT Commands
  *   
  *   ### Uplinks
  *   By Application:
  *   application/1/device/+/event/up
  *   
  *   By Device:
  *   application/1/device/de631ea3e5f58df3/event/up
  *   
  *   ### Downlinks
  *   By Application:
  *   [não se aplica]
  *   
  *   By Device:
  *   application/1/device/de631ea3e5f58df3/command/down
  *   
  *   Payload:
  *   HEX           BASE64      DEC
  *   00            AA==        0
  *   01            AQ==        1
  *   65            ZQ==        101
  *   5501001eff    VQEAHv8=    85 1 0 30 61440
  *   5502001eff    VQIAHv8=    85 2 0 30 61440
  *   55030000ff    VQMAAP8=    85 3 0  0 61440
  *   
  *   
  *   
  *   ### Mosquitto in Terminal:
  *   
  *   (Identical topics)
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "/topic/energymetter" -v
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "/topic/energymetter" -m "AdailSilva"
  *   
  *   (Different topics, subscribe to the publisher and publish to the subscriber, used in WATT METER JE05 - Rev 03.00)
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "/topic/pub/energymetter" -v
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "/topic/sub/energymetter" -m "AdailSilva"
  *   
  *   ### Mosquitto in Terminal to ChirpStack:  (SUBSCRIBE)
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/#" -v                  # Display everything for the given application ID
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/+/event/up" -v  # Display only the uplink payloads for the given application ID
  *   
  *   Any device event:
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/#" -v
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/+/event/#" -v
  *   
  *   
  *   #################
  *   Examples UPLINKS:
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/+/event/up" -v
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/event/up" -v
  *   
  *   Examples STATUS:  (I didn't capture anything here)
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/+/event/status" -v
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/event/status" -v
  *   
  *   Examples JOIN:
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/+/event/join" -v
  *   
  *   Examples ACK:
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/+/event/ack" -v
  *   
  *   Examples TXACK:
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/+/event/txack" -v
  *   
  *   Examples ERROR:
  *   mosquitto_sub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/+/event/error" -v
  *   
  *   
  *   ### Mosquitto in Terminal to ChirpStack:  (PUBLISH)
  *   ################################
  *   Examples Scheduling a DOWNLINKS:
  *   The default topic for scheduling downlink payloads is:
  *   application/[ApplicationID]/device/[DevEUI]/command/down.
  *   
  *   Before v3.11.0, the default event topic was:
  *   application[ApplicationID]/device/[DevEUI]/tx.
  *   In case these are configured in the ChirpStack Application Server 
  *   configuration, then these will override the default configuration.
  *   
  *   
  *   {
  *       "confirmed": true,                            // Whether the payload must be sent as confirmed data down or not
  *       "fPort": 10,                                  // FPort to use (must be > 0)
  *       "data": "....",                               // Base64 encoded data (plaintext, will be encrypted by ChirpStack Network Server)
  *       "object": {                                   // Decoded object (when application coded has been configured)
  *                     "temperatureSensor": {"1": 25}, // When providing the 'object', you can omit 'data'
  *                     "humiditySensor": {"1": 32}
  *                 }
  *   }
  *   
  *   
  *   {
  *       "confirmed":true,
  *       "fPort":10,
  *       "data":"QWRhaWxTaWx2YQ=="
  *   }
  *   
  *   {
  *       "confirmed":true,
  *       "fPort":10,
  *       "data":"QWRhaWxTaWx2YQ==",
  *       "object": {
  *                     "temperatureSensor":{"1":25},
  *                     "humiditySensor":{"1":32}
  *                 }
  *   }
  *   
  *   
  *   Examples:
  *   
  *   {
  *       "confirmed": false,
  *       "fPort": 101,
  *       "data": "AQ=="
  *   }
  *   
  *   "{\"confirmed\":false,\"fPort\":101,\"data\":\"AQ==\"}"
  *   
  *   {
  *       "confirmed": false,
  *       "fPort": 101,
  *       "data": "AA=="
  *   }
  *   
  *   "{\"confirmed\":false,\"fPort\":101,\"data\":\"AA==\"}"
  *   
  *   {
  *       "confirmed": true,
  *       "fPort": 101,  
  *       "data": "AQ=="
  *   }
  *   
  *   "{\"confirmed\":true,\"fPort\":101,\"data\":\"AQ==\"}"
  *   
  *   {
  *       "confirmed": true,
  *       "fPort": 101,
  *       "data": "AA=="
  *   }
  *   
  *   "{\"confirmed\":true,\"fPort\":101,\"data\":\"AA==\"}"
  *   
  *   {
  *       "confirmed": false,
  *       "fPort": 101,
  *       "data": "AQ==",
  *       "object": {
  *                     "temperatureSensor": {"1": 25},
  *                     "humiditySensor": {"1": 32}
  *                 }
  *   }
  *   
  *   "{\"confirmed\":false,\"fPort\":101,\"data\":\"AQ==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   
  *   {
  *       "confirmed": false,
  *       "fPort": 101,
  *       "data": "AA==",
  *       "object": {
  *                     "temperatureSensor": {"1": 25},
  *                     "humiditySensor": {"1": 32}
  *                 }
  *   }
  *   
  *   "{\"confirmed\":false,\"fPort\":101,\"data\":\"AA==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   {
  *       "confirmed": true,
  *       "fPort": 101,
  *       "data": "AQ==",
  *       "object": {
  *                     "temperatureSensor": {"1": 25},
  *                     "humiditySensor": {"1": 32}
  *                 }
  *   }
  *   
  *   "{\"confirmed\":true,\"fPort\":101,\"data\":\"AQ==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   {
  *       "confirmed": true,
  *       "fPort": 101,
  *       "data": "AA==",
  *       "object": {
  *                   "temperatureSensor": {"1": 25},
  *                   "humiditySensor": {"1": 32}
  *                 }
  *   }
  *   
  *   "{\"confirmed\":true,\"fPort\":101,\"data\":\"AA==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   
  *   
  *   No Object, Unconfirmed Downlinks:
  *   
  *   ### Light up, TX topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/tx" -m "{\"confirmed\":false,\"fPort\":101,\"data\":\"AQ==\"}"
  *   
  *   ### Light up, DOWN topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/down" -m "{\"confirmed\":false,\"fPort\":101,\"data\":\"AQ==\"}"
  *   
  *   ### Disconnect, TX topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/tx" -m "{\"confirmed\":false,\"fPort\":101,\"data\":\"AA==\"}"
  *   
  *   ### Disconnect, DOWN topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/down" -m "{\"confirmed\":false,\"fPort\":101,\"data\":\"AA==\"}"
  *   
  *   
  *   No Object, Confirmed Downlinks:
  *   
  *   ### Light up, TX topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/tx" -m "{\"confirmed\":true,\"fPort\":101,\"data\":\"AQ==\"}"
  *   
  *   ### Light up, DOWN topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/down" -m "{\"confirmed\":true,\"fPort\":101,\"data\":\"AQ==\"}"
  *   
  *   ### Disconnect, TX topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/tx" -m "{\"confirmed\":true,\"fPort\":101,\"data\":\"AA==\"}"
  *   
  *   ### Disconnect, DOWN topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/down" -m "{\"confirmed\":true,\"fPort\":101,\"data\":\"AA==\"}"
  *   
  *   
  *   
  *   With Object, Unconfirmed Downlinks:
  *   
  *   ### Light up, TX topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/tx" -m "{\"confirmed\":false,\"fPort\":101,\"data\":\"AQ==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   ### Light up, DOWN topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/down" -m "{\"confirmed\":false,\"fPort\":101,\"data\":\"AQ==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   ### Disconnect, TX topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/tx" -m "{\"confirmed\":false,\"fPort\":101,\"data\":\"AA==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   ### Disconnect, DOWN topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/down" -m "{\"confirmed\":false,\"fPort\":101,\"data\":\"AA==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   
  *   No Object, Confirmed Downlinks:
  *   
  *   ### Light up, TX topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/tx" -m "{\"confirmed\":true,\"fPort\":101,\"data\":\"AQ==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   ### Light up, DOWN topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/down" -m "{\"confirmed\":true,\"fPort\":101,\"data\":\"AQ==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   ### Disconnect, TX topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/tx" -m "{\"confirmed\":true,\"fPort\":101,\"data\":\"AA==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   ### Disconnect, DOWN topic:
  *   mosquitto_pub -h localhost -p 1883 -u "adailsilva" -P "@Hacker101" -t "application/123/device/de631ea3e5f58df3/command/down" -m "{\"confirmed\":true,\"fPort\":101,\"data\":\"AA==\",\"object\":{\"temperatureSensor\":{\"1\":25},\"humiditySensor\":{\"1\":32}}}"
  *   
  *   
  *   
  *   Limit 242 bytes:
  *   Em Hexadecimal:
  *   0001020304050607080900010203040506070809000102030405060708090001020304050607080900010203040506070809000102030405060708090001020304050607080900010203040506070809000102030405060708090001020304050607080900010203040506070809000102030405060708090001020304050607080900010203040506070809000102030405060708090001020304050607080900010203040506070809000102030405060708090001020304050607080900010203040506070809000102030405060708090001020304050607080900010203040506070809000102030405060708090001
  *   
  *   In Base64:
  *   AAECAwQFBgcICQABAgMEBQYHCAkAAQIDBAUGBwgJAAECAwQFBgcICQABAgMEBQYHCAkAAQIDBAUGBwgJAAECAwQFBgcICQABAgMEBQYHCAkAAQIDBAUGBwgJAAECAwQFBgcICQABAgMEBQYHCAkAAQIDBAUGBwgJAAECAwQFBgcICQABAgMEBQYHCAkAAQIDBAUGBwgJAAECAwQFBgcICQABAgMEBQYHCAkAAQIDBAUGBwgJAAECAwQFBgcICQABAgMEBQYHCAkAAQIDBAUGBwgJAAECAwQFBgcICQABAgMEBQYHCAkAAQIDBAUGBwgJAAE=
  *   
  */

/*    
 *     Access in PostgreSQL:
 *     
 *     Install PostgreSQL Client:
 *     sudo apt -y install postgresql-client postgresql-client-common     
 *     
 *     psql -h 127.0.0.1 -U chirpstack_as -d chirpstack_as
 *     Password for user chirpstack_as: @Hacker101
 *     psql -h 127.0.0.1 -U chirpstack_ns -d chirpstack_ns
 *     Password for user chirpstack_ns: @Hacker101 
 */

 /*   
  *   Baud-rates available:
  *   300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200, 256000, 512000, 962100
  *  
  *   Protocols available:
  *   SERIAL_5N1  5-bit No parity 1 stop bit
  *   SERIAL_6N1  6-bit No parity 1 stop bit
  *   SERIAL_7N1  7-bit No parity 1 stop bit
  *   SERIAL_8N1  8-bit No parity 1 stop bit (the default)
  *   SERIAL_5N2  5-bit No parity 2 stop bits 
  *   SERIAL_6N2  6-bit No parity 2 stop bits
  *   SERIAL_7N2  7-bit No parity 2 stop bits
  *   SERIAL_8N2  8-bit No parity 2 stop bits 
  *   SERIAL_5E1  5-bit Even parity 1 stop bit
  *   SERIAL_6E1  6-bit Even parity 1 stop bit
  *   SERIAL_7E1  7-bit Even parity 1 stop bit 
  *   SERIAL_8E1  8-bit Even parity 1 stop bit 
  *   SERIAL_5E2  5-bit Even parity 2 stop bit 
  *   SERIAL_6E2  6-bit Even parity 2 stop bit 
  *   SERIAL_7E2  7-bit Even parity 2 stop bit  
  *   SERIAL_8E2  8-bit Even parity 2 stop bit  
  *   SERIAL_5O1  5-bit Odd  parity 1 stop bit  
  *   SERIAL_6O1  6-bit Odd  parity 1 stop bit   
  *   SERIAL_7O1  7-bit Odd  parity 1 stop bit  
  *   SERIAL_8O1  8-bit Odd  parity 1 stop bit   
  *   SERIAL_5O2  5-bit Odd  parity 2 stop bit   
  *   SERIAL_6O2  6-bit Odd  parity 2 stop bit    
  *   SERIAL_7O2  7-bit Odd  parity 2 stop bit    
  *   SERIAL_8O2  8-bit Odd  parity 2 stop bit    
  */

//        // PZEMs TESTs:
//        _serial = portA;
//        _isSoft = false;
//        init(_address_PZEM_PHASE_A);
//        uint8_t _addressA = getAddress();
//        float _voltageA = voltage();
//        #ifdef DEBUG_PZEM004Tv3
//        DEBUG_PORT.println(F("############ PZEM_PHASE_A ############"));
//        DEBUG_PORT.print(F("Device Address  : "));
//        DEBUG_PORT.println(_addressA, HEX);
//        #endif
//        bufferPrintAndInformationOfPZEM004Tv30();
//    
//        _serial = portB;
//        _isSoft = false;
//        init(_address_PZEM_PHASE_B);
//        uint8_t _addressB = getAddress();
//        float _voltageB = voltage();
//        #ifdef DEBUG_PZEM004Tv3
//        DEBUG_PORT.println(F("############ PZEM_PHASE_B ############"));
//        DEBUG_PORT.print(F("Device Address  : "));
//        DEBUG_PORT.println(_addressB, HEX);
//        #endif
//        bufferPrintAndInformationOfPZEM004Tv30();
//    
//        _serial = portC;
//        _isSoft = false;
//        init(_address_PZEM_PHASE_C);
//        uint8_t _addressC = getAddress();
//        float _voltageC = voltage();
//        #ifdef DEBUG_PZEM004Tv3
//        DEBUG_PORT.println(F("############ PZEM_PHASE_C ############"));
//        DEBUG_PORT.print(F("Device Address  : "));
//        DEBUG_PORT.println(_addressC, HEX);
//        #endif
//        bufferPrintAndInformationOfPZEM004Tv30();
