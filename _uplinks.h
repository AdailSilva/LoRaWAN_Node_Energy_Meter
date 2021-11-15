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

/********************************************************************
 _____              __ _                       _   _             
/  __ \            / _(_)                     | | (_)            
| /  \/ ___  _ __ | |_ _  __ _ _   _ _ __ __ _| |_ _  ___  _ __  
| |    / _ \| '_ \|  _| |/ _` | | | | '__/ _` | __| |/ _ \| '_ \ 
| \__/\ (_) | | | | | | | (_| | |_| | | | (_| | |_| | (_) | | | |
 \____/\___/|_| |_|_| |_|\__, |\__,_|_|  \__,_|\__|_|\___/|_| |_|
                          __/ |                                  
                         |___/                                   
********************************************************************/

#pragma once

/* Includes */
#include "_serialBuffers.h"

/* Payloads */
//uint8_t payload_HexadecimalValue_101[1] = { 0x65 }; /* Test - Send Decimal: 101 - ASCII: "e" */

/* Only accepts decimal values */
//byte payloadMyNameHorizontalBytes[10] = { 65, 100, 97, 105, 108, 83, 105, 108, 118, 97 };

/* Uplink by Button */
//static uint8_t button_activated[1] = { 0x01 };      /* In Hexadecimal */
static uint8_t button_activated[1] = { 0b00000001 };  /* In Binary */

/* Relay uplink - Ok in Decimal Values */
//byte payloadRelayUplink[17] = { 82, 101, 108, 97, 121, 32, 117, 112, 108, 105, 110, 107, 32, 45, 32, 79, 107 };

/* Relay uplink - Ok in Hexadecimal Values */
byte payloadRelayUplink[17] = { 0x52, 0x65, 0x6c, 0x61, 0x79, 0x20, 0x75, 0x70, 0x6c, 0x69, 0x6e, 0x6b, 0x20, 0x2d, 0x20, 0x4f, 0x6b };

/* Send Functions */

/* Shipments - Byte uploads */
/* Calls uplink sending function */
void payloadSend(uint8_t port, uint8_t * data, uint8_t data_size, bool confirmed)
{
    /*
     *  Prepare upstream data transmission at the next possible time.
     *  Parameters are port, data, length, confirmed.
     */
    LMIC_setTxData2(port, data, data_size, confirmed ? 1 : 0);
}

/* Shipments - Byte uploads */
/* Calls uplink sending function */
void payloadMyNameVerticalBytes()
{
    /*
     *  Payload My Name
     *  ASCII text:  AdailSilva
     *  Base64:      QWRhaWxTaWx2YQ==
     *  Hexadecimal: 41 64 61 69 6C 53 69 6C 76 61
     *  Decimal:     65 100 97 105 108 83 105 108 118 97
     *  Binary:      01000001 01100100 01100001 01101001 01101100 01010011 01101001 01101100 01110110 01100001
     */
    byte payload[10];
    /* In Binary */
    payload[0] = 0b01000001;
    payload[1] = 0b01100100;
    payload[2] = 0b01100001;
    payload[3] = 0b01101001;
    payload[4] = 0b01101100;
    payload[5] = 0b01010011;
    payload[6] = 0b01101001;
    payload[7] = 0b01101100;
    payload[8] = 0b01110110;
    payload[9] = 0b01100001;

//    /* In Decimal */
//    payload[0] = 65;
//    payload[1] = 100;
//    payload[2] = 97;
//    payload[3] = 105;
//    payload[4] = 108;
//    payload[5] = 83;
//    payload[6] = 105;
//    payload[7] = 108;
//    payload[8] = 118;
//    payload[9] = 97;

//    /* In Hexadecimal */
//    payload[0] = 0x41;
//    payload[1] = 0x64;
//    payload[2] = 0x61;
//    payload[3] = 0x69;
//    payload[4] = 0x6c;
//    payload[5] = 0x53;
//    payload[6] = 0x69;
//    payload[7] = 0x6c;
//    payload[8] = 0x76;
//    payload[9] = 0x61;

    /* Direct Transmission LMiC */
    /*
     *  Prepare upstream data transmission at the next possible time.
     *  Parameters are port, data, length, confirmed.
     */
     LMIC_setTxData2(UPLINK_PORT, payload, sizeof(payload), UPLINK_CONFIRMED);
}

/* Shipments - Byte uploads */
/* Calls uplink sending function */
void payloadEnergyMetter()
{
    /*
     *  Payload Energy Metter
     */
    /*
     *  Voltage       (Volts)   --> ( response[3]   << 8 | response[4] )  / 10.0 )
     *  Current       (Amperes) --> ( response[5]   << 8 | response[6]    | response[7]  << 24 | response[8]  << 16 ) / 1000.0 )
     *  Power         (Watts)   --> ( response[9]   << 8 | response[10]   | response[11] << 24 | response[12] << 16 ) / 10.0 )
     *  Energy        (kWh)     --> ( response[13]  << 8 | response[14]   | response[15] << 24 | response[16] << 16 ) / 1000.0 )
     *  Frequency     (Hz)      --> ( response[17]  << 8 | response[18] ) / 10.0 )
     *  Power Factor  (.)       --> ( response[19]  << 8 | response[20] ) / 100.0 )
     *  Alarm         (.)       --> ( response[21]  << 8 | response[22] ) )
     */
     
    /* Direct Transmission LMiC */
    /*
     *  Prepare upstream data transmission at the next possible time.
     *  Parameters are port, data, length, confirmed.
     */
     LMIC_setTxData2(UPLINK_PORT, payloadResponse, sizeof(payloadResponse), UPLINK_CONFIRMED);
}
