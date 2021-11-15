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
#include <lmic.h>

/* Keys for AES-128 Encryption */

/*
 *  Activation by Personalization (ABP)
 *  In some cases you might need to hardcode the DevAddr as well as the security keys in the device
 *  This means activating a device by personalization (ABP). This strategy might seem simpler,
 *  because you skip the join procedure, but it has some downsides related to security.
 */
#ifdef USE_ABP

#ifdef USE_CHIRPSTACK_AU915
// CHIRPSTACK - CS (8 at 15 + 65 channels):
/* little-endian - LSB */ // af c2 cf 56 1e a5 f4 0e 7d da 4b 82 89 c6 bf 59
/* big-endian - MSB */    // 59 bf c6 89 82 4b da 7d 0e f4 a5 1e 56 cf c2 af
static const u1_t PROGMEM APPSKEY[16] = {0x59, 0xBF, 0xC6, 0x89, 0x82, 0x4B, 0xDA, 0x7D, 0x0E, 0xF4, 0xA5, 0x1E, 0x56, 0xCF, 0xC2, 0xAF};

/* little-endian - LSB */ // 99 f2 cd 7c e8 5a 57 a2 e4 6f 6a 48 0e 39 55 a9
/* big-endian - MSB */    // a9 55 39 0e 48 6a 6f e4 a2 57 5a e8 7c cd f2 99
static const PROGMEM u1_t NWKSKEY[16] = {0xA9, 0x55, 0x39, 0x0E, 0x48, 0x6A, 0x6F, 0xE4, 0xA2, 0x57, 0x5A, 0xE8, 0x7C, 0xCD, 0xF2, 0x99};

/* little-endian - LSB */ // 1c e7 c4 23
/* big-endian - MSB */    // 23 c4 e7 1c
static const u4_t DEVADDR = 0x23c4e71c; // <-- Change this address for every node!
#endif

#ifdef USE_CHIRPSTACK_AU915LA
// CHIRPSTACK - CS (0 at 7 + 64 channels):
/* little-endian - LSB */ // af c2 cf 56 1e a5 f4 0e 7d da 4b 82 89 c6 bf 59
/* big-endian - MSB */    // 59 bf c6 89 82 4b da 7d 0e f4 a5 1e 56 cf c2 af
static const u1_t PROGMEM APPSKEY[16] = {0x59, 0xBF, 0xC6, 0x89, 0x82, 0x4B, 0xDA, 0x7D, 0x0E, 0xF4, 0xA5, 0x1E, 0x56, 0xCF, 0xC2, 0xAF};

/* little-endian - LSB */ // 99 f2 cd 7c e8 5a 57 a2 e4 6f 6a 48 0e 39 55 a9
/* big-endian - MSB */    // a9 55 39 0e 48 6a 6f e4 a2 57 5a e8 7c cd f2 99
static const PROGMEM u1_t NWKSKEY[16] = {0xA9, 0x55, 0x39, 0x0E, 0x48, 0x6A, 0x6F, 0xE4, 0xA2, 0x57, 0x5A, 0xE8, 0x7C, 0xCD, 0xF2, 0x99};

/* little-endian - LSB */ // 1c e7 c4 23
/* big-endian - MSB */    // 23 c4 e7 1c
static const u4_t DEVADDR = 0x23c4e71c; // <-- Change this address for every node!
#endif

#ifdef USE_EVERYNET_AU915LA
// EVERYNET - ATC (0 at 7 channels):
/* little-endian - LSB */ // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
/* big-endian - MSB */    // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
static const u1_t PROGMEM APPSKEY[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* little-endian - LSB */ // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
/* big-endian - MSB */    // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
static const PROGMEM u1_t NWKSKEY[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* little-endian - LSB */ // 00 00 00 00
/* big-endian - MSB */    // 00 00 00 00
static const u4_t DEVADDR = 0x00000000; // <-- Change this address for every node!
#endif

#ifdef USE_THETHINGSNETWORK_AU915
// THE THINGS NETWORK - TTN (8 at 15 + 65 channels):
/* little-endian - LSB */ // 90 ed 40 71 8b 7d f2 2b cc 08 c7 d0 5e 56 9b a5
/* big-endian - MSB */    // a5 9b 56 5e d0 c7 08 cc 2b f2 7d 8b 71 40 ed 90
static const u1_t PROGMEM APPSKEY[16] = {0xA5, 0x9B, 0x56, 0x5E, 0xD0, 0xC7, 0x08, 0xCC, 0x2B, 0xF2, 0x7D, 0x8B, 0x71, 0x40, 0xED, 0x90};

/* little-endian - LSB */ // 55 29 b2 db 86 c4 3e 46 6b 03 03 36 4f b7 58 f3
/* big-endian - MSB */    // f3 58 b7 4f 36 03 03 6b 46 3e c4 86 db b2 29 55
static const PROGMEM u1_t NWKSKEY[16] = {0xF3, 0x58, 0xB7, 0x4F, 0x36, 0x03, 0x03, 0x6B, 0x46, 0x3E, 0xC4, 0x86, 0xDB, 0xB2, 0x29, 0x55};

/* little-endian - LSB */ // 38 17 03 26
/* big-endian - MSB */    // 26 03 17 38
static const u4_t DEVADDR = 0x26031738; // <-- Change this address for every node!
#endif

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui(u1_t *buf) {}
void os_getDevEui(u1_t *buf) {}
void os_getDevKey(u1_t *buf) {}

#endif

/* 
 *  Over-the-Air Activation (OTAA)
 *  Is the preferred and most secure way to connect with your Network Server.
 *  Devices perform a join-procedure with the network, during which a dynamic
 *  DevAddr is assigned and security keys are negotiated with the device.
 */
#ifdef USE_OTAA

#ifdef USE_CHIRPSTACK_AU915
// CHIRPSTACK - CS (8 at 15 + 65 channels):
/* little-endian - LSB */ // 00 00 00 00 00 00 00 00
/* big-endian - MSB */    // 00 00 00 00 00 00 00 00
static const u1_t PROGMEM APPEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* little-endian - LSB */ // f3 8d f5 e5 a3 1e 63 de (Usar esta chave no cadastro)
/* big-endian - MSB */    // de 63 1e a3 e5 f5 8d f3
static const u1_t PROGMEM DEVEUI[8] = {0xde, 0x63, 0x1e, 0xa3, 0xe5, 0xf5, 0x8d, 0xf3};

/* little-endian - LSB */ // ae 94 4e 5e 85 b7 bc 02 c5 dd 46 da 4c 7c c5 6f
/* big-endian - MSB */    // 6f c5 7c 4c da 46 dd c5 02 bc b7 85 5e 4e 94 ae (Usar esta chave no Cadastro)
static const u1_t PROGMEM APPKEY[16] = {0x6f, 0xc5, 0x7c, 0x4c, 0xda, 0x46, 0xdd, 0xc5, 0x02, 0xbc, 0xb7, 0x85, 0x5e, 0x4e, 0x94, 0xae};
#endif

#ifdef USE_CHIRPSTACK_AU915LA
// CHIRPSTACK - CS (0 at 7 + 64 channels):
/* little-endian - LSB */ // 00 00 00 00 00 00 00 00
/* big-endian - MSB */    // 00 00 00 00 00 00 00 00
static const u1_t PROGMEM APPEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* little-endian - LSB */ // f3 8d f5 e5 a3 1e 63 de
/* big-endian - MSB */    // de 63 1e a3 e5 f5 8d f3
static const u1_t PROGMEM DEVEUI[8] = {0xde, 0x63, 0x1e, 0xa3, 0xe5, 0xf5, 0x8d, 0xf3};

/* little-endian - LSB */ // ae 94 4e 5e 85 b7 bc 02 c5 dd 46 da 4c 7c c5 6f
/* big-endian - MSB */    // 6f c5 7c 4c da 46 dd c5 02 bc b7 85 5e 4e 94 ae
static const u1_t PROGMEM APPKEY[16] = {0x6f, 0xc5, 0x7c, 0x4c, 0xda, 0x46, 0xdd, 0xc5, 0x02, 0xbc, 0xb7, 0x85, 0x5e, 0x4e, 0x94, 0xae};
#endif

#ifdef USE_EVERYNET_AU915LA
// EVERYNET - ATC (0 at 7 channels):
/* little-endian - LSB */ // 00 00 00 00 00 00 00 00
/* big-endian - MSB */    // 00 00 00 00 00 00 00 00
static const u1_t PROGMEM APPEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* little-endian - LSB */ // 00 00 00 00 00 00 00 00
/* big-endian - MSB */    // 00 00 00 00 00 00 00 00
static const u1_t PROGMEM DEVEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* little-endian - LSB */ // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
/* big-endian - MSB */    // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
static const u1_t PROGMEM APPKEY[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#endif

#ifdef USE_THETHINGSNETWORK_AU915
// THE THINGS NETWORK - TTN (8 at 15 + 65 channels):
/* little-endian - LSB */ // 70 b3 d5 7e d0 03 17 01
/* big-endian - MSB */    // 01 17 03 d0 7e d5 b3 70
static const u1_t PROGMEM APPEUI[8] = {0x01, 0x17, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70};

/* little-endian - LSB */ // 00 27 5b ef 0f bd e4 f0
/* big-endian - MSB */    // f0 e4 bd 0f ef 5b 27 00
static const u1_t PROGMEM DEVEUI[8] = {0xF0, 0xE4, 0xBD, 0x0F, 0xEF, 0x5B, 0x27, 0x00};

/* little-endian - LSB */ // b1 b3 a6 16 73 4d 3e 63 51 4c 37 78 80 a9 dc 70
/* big-endian - MSB */    // 70 dc a9 80 78 37 4c 51 63 3e 4d 73 16 a6 b3 b1
static const u1_t PROGMEM APPKEY[16] = {0x70, 0xDC, 0xA9, 0x80, 0x78, 0x37, 0x4C, 0x51, 0x63, 0x3E, 0x4D, 0x73, 0x16, 0xA6, 0xB3, 0xB1};
#endif

void os_getArtEui(u1_t *buf) { memcpy_P(buf, APPEUI, 8); }
void os_getDevEui(u1_t *buf) { memcpy_P(buf, DEVEUI, 8); }
void os_getDevKey(u1_t *buf) { memcpy_P(buf, APPKEY, 16); }

#endif
