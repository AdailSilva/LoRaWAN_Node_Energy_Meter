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

/* Comments */
/* Set to UP e DOWN:  LMIC_setSeqnoUp(0) & LMIC_setSeqnoDn(0) */
/* LMIC_setTxData2(101, (xref2u1_t)data, sizeof(data), true or false confirmed) */
/* Received downlink, window=RX1, port=-1, ack=0, txrxFlags=0x21 --> After Join */
/* Received downlink, window=RX1, port=-1, ack=1, txrxFlags=0xa1  --> Confirmed Uplink */
/* Notice when UPLINK_CONFIRMED active is varying UPLINK_DATA_RATE, ADR appears to be active */
/* TODO: Try RX calibration with microsecond delays (16383) /* Maximum value: 16383 */

/* 
 *  To Deep Sleep ATmega328P:
 *  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
 *  digitalWrite(lmic_pins.nss, LOW);
 *  LMIC_shutdown();
 *  LMIC.rps = updr2rps(LMIC.datarate);
 *  
 *  OTAA Force:
 *  LMIC_startJoining();
 *  LMIC.txChnl = 8;
 *  
 *  To working with EEPROM in ATmega328P:
 *  EEPROMWritelong(end_eeprom_1, pulse_count_1);
 *  EEPROMWritelong(end_eeprom_2, pulse_count_2);
 *  EEPROMWritelong(end_eeprom_3, pulse_count_3);
 *  
 */
