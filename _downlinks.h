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

/* Functions */
/* Reset board */
void IRAM_ATTR resetModule()
{
    delay(10000);
    delayMicroseconds(16383); /* Maximum value: 16383 */
    esp_restart(); // TODO: Verificar qual Função para Reiniciar ESP8266. Fazer um #ifdef #endif para esp32 e esp8266.
}

void downlinksControlTime()
{
    #ifdef RX_DELAY
    /* Set the delay for the first RX window in seconds */
    LMIC.rxDelay = RX_DELAY;
    #endif
    
    #ifdef CLOCK_ERROR
        /* Let LMIC compensate for +/- n% clock error, Value default MAX_CLOCK_ERROR: 65536 */
        LMIC_setClockError( MAX_CLOCK_ERROR * CLOCK_ERROR / 100 );
    #endif
}

void downlinksRule()
{
    /* LMIC.dataBeg - 1 (- 2, - 3, - 4, ...) Defines the position of each frame index */
    
    if (LMIC.dataLen == 1)
    {
        uint8_t result = LMIC.frame[LMIC.dataBeg + 0];
    
        if (result == 0)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F(" [INFO] RESULT 0"));
            #endif
            digitalWrite(YELLOW_LED_PIN, LOW);
        }
        if (result == 1)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F(" [INFO] RESULT 1"));
            #endif
            digitalWrite(YELLOW_LED_PIN, HIGH);
        }
        /* Decimal number: 101 | Base64: ZQ== | Hexadecimal number: 65 */
        if (result == 101)
        {
            #ifdef DEBUG
            DEBUG_PORT.println(F(" [INFO] RESULT 101, Call a new Uplink. \\('~')/"));
            #endif
            /* Tem mais sentido em Classe C, porém LMiC trabalha apenas em classes A e B. */
            //do_send(&sendjob); /* When so called, shipping goes without Payload */
            /* After calling function do_send, you don't get here */
            payloadSend(UPLINK_PORT, payloadRelayUplink, sizeof(payloadRelayUplink), UPLINK_CONFIRMED);
        }
        
    }
    
    if (LMIC.dataLen == 5 & LMIC.frame[LMIC.dataBeg - 1] == 255)
    {
        #ifdef DEBUG
        DEBUG_PORT.println(F(" [INFO] Downlink with Five bytes is available"));
        DEBUG_PORT.println(F(" [INFO] Downlink FPort            : 255"));
        #endif
        
        /* Get packet information */
        uint8_t   header  =       LMIC.frame[LMIC.dataBeg + 0];
        uint8_t   cmd     =       LMIC.frame[LMIC.dataBeg + 1];
        uint16_t  dat     = 256 * LMIC.frame[LMIC.dataBeg + 2] + LMIC.frame[LMIC.dataBeg + 3];
        uint8_t   tail    =       LMIC.frame[LMIC.dataBeg + 4];

        #ifdef DEBUG
        DEBUG_PORT.println(" [INFO] Header                    : " + String(header,  HEX));
        DEBUG_PORT.println(" [INFO] Command                   : " + String(cmd,     HEX));
        DEBUG_PORT.println(" [INFO] Data                      : " + String(dat,     HEX));
        DEBUG_PORT.println(" [INFO] Tail                      : " + String(tail,    HEX));
        #endif
        
        /*
         *  Downlink structure --> { 0x55, cmd, dat0, dat1, 0xFF }
         *  @cmd                  : Set interval - 01, Reboot - 02.
         *  @dat                  : 2 bytes data
         *  Example New Interval  : 55 01 00 1E FF on FPort 255
         *  Base64                : VQEAHv8=
         *  Change                : 1E = 30 to new TX_INTERVAL
         *  
         *  Example New Interval
         *  to LoRa Data Publish  : 55 02 00 1E FF on FPort 255
         *  Base64                : VQIAHv8=  
         *  Change                : 1E = 30 to new LORA_DATA_PUBLISH_INTERVAL
         *  
         *  Reboot Example        : 55 03 00 00 FF on FPort 255
         *  Base64                : VQMAAP8=
         *  Effect                : Reboot...
         */
        if (header == 0x55 & tail == 0xFF)
        {
            if (cmd == 0x01)
            {
                #ifdef DEBUG
                DEBUG_PORT.println(F(" [INFO] Received CHANGE_TX_INTERVAL request"));
                #endif
                TX_INTERVAL = dat;
                #ifdef DEBUG
                DEBUG_PORT.println(" [INFO] New CHANGE_TX_INTERVAL: " + String(TX_INTERVAL));
                #endif                
            }

            if (cmd == 0x02)
            {
                #ifdef DEBUG
                DEBUG_PORT.println(F(" [INFO] Received CHANGE_LORA_DATA_PUBLISH_INTERVAL request"));
                #endif
                LORA_DATA_PUBLISH_INTERVAL = dat;
                #ifdef DEBUG
                DEBUG_PORT.println(" [INFO] New CHANGE_LORA_DATA_PUBLISH_INTERVAL: " + String(LORA_DATA_PUBLISH_INTERVAL));
                #endif                
            }
            
            /*
             *  This logic prevents an Infinite Loop of Reboots when the Network Server
             *  responds for the second time to a Confirmed Downlink request,
             *  in which the first Downlink sends a normal Module Reboot command.
             *  In order to restart the equipment only once.
             */
//            if (cmd == 0x03 & seqNoUp != 0 & seqNoDn != 0)
            /* 
             *  At this point in the execution, seqNoUp
             *  will be set to 2 after restarting the MCU */
            if (cmd == 0x03 & seqNoUp > 2)
            {
                #ifdef DEBUG
                DEBUG_PORT.println(F(" [INFO] Received REBOOT request"));
                DEBUG_PORT.println(F(" [INFO] Resetting the Module in 10 seconds... ~('.')~"));
                #endif
                /* Reset */
                resetModule();
            }
        }
    }    
    else
    {
        /* Default Port 0 */
        #ifdef DEBUG
        DEBUG_PORT.println(" [INFO] Downlink FPort      : " + String(LMIC.frame[LMIC.dataBeg - 1]));
        #endif
    }
}
