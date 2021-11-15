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

/* Log Functions */
void printHex2(unsigned key)
{
    key &= 0xff;

    if (key < 16)
    {
        #ifdef DEBUG
        DEBUG_PORT.print('0');
        #endif
    }

    #ifdef DEBUG
    DEBUG_PORT.print(key, HEX);
    #endif DEBUG
}

/* Debugging function PZEM004Tv30 */
void printBufferPZEM004Tv30(uint8_t *buffer, uint16_t len)
{
    /* WARNING: Informations with 25 Bytes */
    for (uint16_t i = 0; i < len; i++)
    {
        char temp[6];
        sprintf(temp, "%.2x ", buffer[i]);
        #ifdef DEBUG_PZEM004Tv3
        DEBUG_PORT.print(temp);
        #endif
    }
    #ifdef DEBUG_PZEM004Tv3
    DEBUG_PORT.println();
    #endif
}

/* Debugging function PZEM004Tv30 */
void bufferPrintAndInformationOfPZEM004Tv30()
{
    #ifdef DEBUG_PZEM004Tv3
    DEBUG_PORT.println();
    DEBUG_PORT.print(F("Received Buffer : "));
    printBufferPZEM004Tv30(response, PAYLOAD_LENGTH_ENERGY_METTER);
    DEBUG_PORT.println();
    DEBUG_PORT.print(F("Voltage         : "));
    DEBUG_PORT.print( (   response[3]   << 8 | response[4] )  / 10.0 );
    DEBUG_PORT.println(F(" Volts"));
    DEBUG_PORT.print(F("Current         : "));
    DEBUG_PORT.print( (   response[5]   << 8 | response[6]    | response[7]  << 24 | response[8]  << 16 ) / 1000.0 );
    DEBUG_PORT.println(F(" Amperes"));
    DEBUG_PORT.print(F("Power           : "));
    DEBUG_PORT.print( (   response[9]   << 8 | response[10]   | response[11] << 24 | response[12] << 16 ) / 10.0 );
    DEBUG_PORT.println(F(" Watts"));
    DEBUG_PORT.print(F("Energy          : "));
    DEBUG_PORT.print( (   response[13]  << 8 | response[14]   | response[15] << 24 | response[16] << 16 ) / 1000.0 );
    DEBUG_PORT.println(F(" kWh"));
    DEBUG_PORT.print(F("Frequency       : "));
    DEBUG_PORT.print( (   response[17]  << 8 | response[18] ) / 10.0 );
    DEBUG_PORT.println(F(" Hz"));
    DEBUG_PORT.print(F("Power Factor    : "));
    DEBUG_PORT.print( (   response[19]  << 8 | response[20] ) / 100.0 );
    DEBUG_PORT.println();
    DEBUG_PORT.print("Alarm           : ");
    DEBUG_PORT.print( (   response[21]  << 8 | response[22] ) );
    DEBUG_PORT.println();
    DEBUG_PORT.println();
    #endif
}

void showTxRxInformations()
{
    /* 
     *  WARNING: The calculated RSSI and SNR
     *  does not correspond 100% to the NetworkServer RSSI and SNR console values.
     */
    float   freq  = LMIC.freq / 1000000.0;
    int16_t rssi  = (LMIC.rssi - 74);
    u1_t    snr   = LMIC.snr * 0.25;
    
    #ifdef DEBUG
    DEBUG_PORT.println(F("****************************************************"));
    DEBUG_PORT.println(" [INFO] NetID               : x" + String(LMIC.netid, HEX));
    DEBUG_PORT.println(" [INFO] DevAddr             : " + String(LMIC.devaddr, HEX));
    DEBUG_PORT.println(" [INFO] TX on Channel       : " + String(LMIC.txChnl));
    DEBUG_PORT.println(" [INFO] TX Power            : " + String(LMIC.txpow));
    DEBUG_PORT.println(" [INFO] RSSI                : " + String(rssi));
    DEBUG_PORT.println(" [INFO] SNR                 : " + String(snr));
    DEBUG_PORT.println(" [INFO] RPS                 : " + String(LMIC.rps));
    DEBUG_PORT.println(" [INFO] Data rate           : " + String(LMIC.datarate));
    #endif
    
    switch (LMIC.datarate)
    {
    case 0:
        #ifdef DEBUG
        DEBUG_PORT.println(F(" [INFO] Spreading Factor    : 12"));
        #endif
        break;
    case 1:
        #ifdef DEBUG
        DEBUG_PORT.println(F(" [INFO] Spreading Factor    : 11"));
        #endif
        break;
    case 2:
        #ifdef DEBUG
        DEBUG_PORT.println(F(" [INFO] Spreading Factor    : 10"));
        #endif
        break;
    case 3:
        #ifdef DEBUG
        DEBUG_PORT.println(F(" [INFO] Spreading Factor    : 9"));
        #endif
        break;
    case 4:
        #ifdef DEBUG
        DEBUG_PORT.println(F(" [INFO] Spreading Factor    : 8"));
        #endif
        break;
    case 5:
        #ifdef DEBUG
        DEBUG_PORT.println(F(" [INFO] Spreading Factor    : 7"));
        #endif
        break;
    default:
        #ifdef DEBUG
        DEBUG_PORT.println(F(" [INFO] Spreading Factor Unknown <<< "));
        #endif
        break;
    }

    #ifdef DEBUG
    DEBUG_PORT.println(" [INFO] " + modeOperation + " on Frequency     : " + String(freq) + " MHz");
    DEBUG_PORT.println(F("____________________________________________________"));
    DEBUG_PORT.println();
//    DEBUG_PORT.println(" [INFO] txrxFlags           : " + String(LMIC.txrxFlags, HEX));
//    DEBUG_PORT.println(" [INFO] txCnt               : " + String(LMIC.txCnt));
    DEBUG_PORT.println(" [INFO] Counter UP          : " + String(LMIC.seqnoUp - 1));
    DEBUG_PORT.println(" [INFO] Counter DOWN        : " + String(LMIC.seqnoDn - 1));
    DEBUG_PORT.println(F("****************************************************"));
    #endif
}

void showNetworkInformations()
{
    u4_t netid = 0;
    devaddr_t devaddr = 0;
    u1_t nwkKey[16];
    u1_t artKey[16];
    LMIC_getSessionKeys(&netid, &devaddr, nwkKey, artKey);

    #ifdef DEBUG
//    DEBUG_PORT.println(F("_____________________________________________________________________________"));
    DEBUG_PORT.println();
    DEBUG_PORT.println(" [INFO] NetID   (MSB)       : " + String(netid, HEX));
    DEBUG_PORT.println(" [INFO] DevAddr (MSB)       : " + String(devaddr, HEX));
    #endif

    #ifdef DEBUG
    DEBUG_PORT.print(" [INFO] NwkSKey (MSB)       : "); // Not used (F());
    #endif
    
    for (size_t i = 0; i < sizeof(nwkKey); ++i)
    {
        if (i != 0)
            #ifdef DEBUG
            DEBUG_PORT.print("-");
            #endif
        printHex2(nwkKey[i]);
    }

    #ifdef DEBUG
    DEBUG_PORT.println("");        
    DEBUG_PORT.print(" [INFO] AppSKey (MSB)       : ");
    #endif

    for (size_t i = 0; i < sizeof(artKey); ++i)
    {
        if (i != 0)
            #ifdef DEBUG
            DEBUG_PORT.print("-");
            #endif
        printHex2(artKey[i]);
    }
    
    #ifdef DEBUG
    DEBUG_PORT.println();
//    DEBUG_PORT.println(F("_____________________________________________________________________________"));
    DEBUG_PORT.println();
    #endif
}

/* Downlinks Log */
void downlinksLog()
{
    #ifdef DEBUG
    DEBUG_PORT.println(" [INFO] RX Delay            : " + String(LMIC.rxDelay)); /* Default value 1 */
    DEBUG_PORT.println(" [INFO] Maximum Clock Error : " + String(MAX_CLOCK_ERROR)); /* Default value 65536 */
    DEBUG_PORT.println(" [INFO] New Max. Clock Error: " + String(MAX_CLOCK_ERROR * CLOCK_ERROR / 100));
    #endif
    
    /*  
     *  For the EV_RXCOMPLETE and EV_TXCOMPLETE events, the txrxFlags
     *  field sould be evaluated and the following flags are defined:
     *  
     *  TXRX_ACK: confirmed UP frame was acked (mutually exclusive with TXRX_NACK)
     *  TXRX_NACK: confirmed UP frame was not acked (mutually exclusive with TXRX_ACK)
     *  TXRX_PORT: a port field is contained in the received frame IBM
     *  LoRaWAN in C (LMiC) Technical Specification 9 LMiC Library. Version 1.5.
     *  TXRX_DNW1: received in first DOWN slot (mutually exclusive with TXRX_DNW2)
     *  TXRX_DNW2: received in second DOWN slot (mutually exclusive with TXRX_DNW1)
     *  TXRX_PING: received in a scheduled RX slot.   
     */
    if (LMIC.txrxFlags & TXRX_ACK)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F("____________________________________"));
            DEBUG_PORT.println(F(" [INFO] Confirmed UP frame was acked"));
            #endif
        }
    
    if (LMIC.txrxFlags & TXRX_NACK)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F("________________________________________"));
            DEBUG_PORT.println(F(" [INFO] Confirmed UP frame was not acked"));
            #endif
        }
    
    if (LMIC.txrxFlags & TXRX_PORT)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F("_______________________________________________________"));
            DEBUG_PORT.println(F(" [INFO] A port field is contained in the received frame"));
            #endif
        }
    
    /* Check if we have a downlink on either Rx1 or Rx2 windows */
    if (LMIC.txrxFlags & TXRX_DNW1)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F("___________________________________"));
            DEBUG_PORT.println(F(" [INFO] Received in first DOWN slot"));
            #endif
        }
    
    if (LMIC.txrxFlags & TXRX_DNW2)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F("____________________________________"));
            DEBUG_PORT.println(F(" [INFO] Received in second DOWN slot"));
            #endif
        }
    
    if (LMIC.txrxFlags & TXRX_PING)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F("_______________________________________"));
            DEBUG_PORT.println(F(" [INFO] Received in a scheduled RX slot"));
            #endif
        }
        
    if (LMIC.dataLen)
    {
        #ifdef DEBUG
        //DEBUG_PORT.printf(" [INFO] Received %d byte(s) of payload\n", LMIC.dataLen);
        DEBUG_PORT.print(F(" [INFO] Received downlink with "));
        DEBUG_PORT.print(LMIC.dataLen);
        DEBUG_PORT.println(F(" byte(s) of payload. \\('~')/"));
        DEBUG_PORT.print(F(" [INFO] Received at port          : "));
        DEBUG_PORT.print(LMIC.frame[LMIC.dataBeg - 1]);
        DEBUG_PORT.println(F("."));
        DEBUG_PORT.println();
        
        /* Print Downlinks */
        DEBUG_PORT.print(F(" [INFO] Full Frame in DECIMAL     : { "));
        #endif
        
        for (u1_t i = 0; i < LMIC.dataLen; i++)
        {
            #ifdef DEBUG
            DEBUG_PORT.print(LMIC.frame[i]);
            DEBUG_PORT.print(F(" "));
            #endif
        }

        #ifdef DEBUG
        DEBUG_PORT.println(F("}"));
        #endif
        
        /* Print Downlinks */
        #ifdef DEBUG
        DEBUG_PORT.print(F(" [INFO] Payload in HEXADECIMAL    : { "));
        #endif
        
        for (u1_t i = 0; i < LMIC.dataLen; i++)
        {
            if (LMIC.frame[LMIC.dataBeg + i] < 0x10)
            {
                #ifdef DEBUG
                DEBUG_PORT.print(F("0"));
                #endif
            }
            
            #ifdef DEBUG
            DEBUG_PORT.print(LMIC.frame[LMIC.dataBeg + i], HEX);
            DEBUG_PORT.print(F(" "));
            #endif
        }

        #ifdef DEBUG
        DEBUG_PORT.println(F("}"));
        DEBUG_PORT.println();
        #endif
    }
}
