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
#include <hal/hal.h> /* Used to fix pin mapping */

/* Definitions */
/* Serial Debug */
#define DEBUG_PORT                    Serial      /* Serial debug port */
#define SERIAL_BAUD_RATE              9600        /* Serial debug baud rate */

#define PZEM_BAUD_RATE                9600        /* Serial PZEM baud rate */
#define PROTOCOL_AVAILABLE            SERIAL_8N1  /* Serial Protocol */
#define RX_Serial2                    16          /* See PinOut ESP32 NodeMCU */
#define TX_Serial2                    17          /* See PinOut ESP32 NodeMCU */
//extern HardwareSerial               Serial; // TODO: Verificar se é necessário


/* To cancel Debug Setar --> //#define DEBUG and LMIC_DEBUG_LEVEL 0 */
#define DEBUG                               /* DEBUG On/Off */
#define DEBUG_PZEM004Tv3                    /* DEBUG_PZEM On/Off */


//#define USE_ABP
#define USE_OTAA
/* Skip EV_JOINING and LMIC_startJoining() in Channel 8 (916,8 MHz) */
//#define USE_FORCE_OTAA
//#define USE_CHANNEL_START_JOINING     8

/* If the activator sets the Channel and DR for uplink transmissions */
//#define GATEWAY_SINGLE_CHANNEL
//#define SINGLE_CHANNEL                8
/* Observe the Data Rate (Spreading Factor) in #define DATA_RATE */

// Only one of these settings must be defined
#define USE_CHIRPSTACK_AU915          /* AU915    (8 at 15 + 65 channels) */
//#define USE_CHIRPSTACK_AU915LA        /* AU915LA  (0 at 7 + 64 channels) */
//#define USE_EVERYNET_AU915LA          /* AU915LA  (0 at 7 channels) */
//#define USE_THETHINGSNETWORK_AU915    /* AU915    (8 at 15 + 65 channels) */

/* 
 *  LoRa SPI
 */
/* ESP32 Dev Module / D1-Mini_ESP32 and RFM95w in Protoboard */
#define SCK_GPIO                      18
#define MISO_GPIO                     19
#define MOSI_GPIO                     23
#define NSS_GPIO                      5
#define RESET_GPIO                    14
#define DIO0_GPIO                     34
#define DIO1_GPIO                     35
#define DIO2_GPIO                     39      /* Note: not really used on this board */

///* ESP32 Heltec and TTGO TBeam */
//#define SCK_GPIO                      5
//#define MISO_GPIO                     19
//#define MOSI_GPIO                     27
//#define NSS_GPIO                      18
//#define RESET_GPIO                    14
//#define DIO0_GPIO                     26
//#define DIO1_GPIO                     33
//#define DIO2_GPIO                     32      /* Note: not really used on this board */

/* Transmission parameters */
#define UPLINK_PORT                   101     /* Ports: 0 (not used) + 1 at 255 */
#define UPLINK_CONFIRMED              0       /* Uplinks Confirmeds  0 = Off, 1 = On */
#define ADR_MODE                      0       /* Adaptive Data Rate: 0 = Off, 1 = On */
#define LINK_CHECK_MODE               0       /* Link check validation: 0 = Off, 1 = On */
/*
 * Possible values (influence the size of the Payload):
 * DR0=DR_SF12, DR1=DR_SF11, DR2=DR_SF10, DR3=DR_SF9, DR4=DR_SF8 e DR5=DR_SF7.
 * NOT USED WHEN ADR is ON.
 */
#define UPLINK_DATA_RATE              DR_SF7  /* Spreading Factor Uplinks */
#define TRANSMIT_POWER                14      /* Power Uplinks */
#define PAYLOAD_LENGTH_ENERGY_METTER  25      /* Payload To Energy Metter */
#define DN2DR                         DR_SF9  /* The Things Networks uses SF9 for its RX2 window */
#define RX_DELAY                      1       /* Set the delay for the first RX window in seconds, Default 1 */
#define CLOCK_ERROR                   1       /* Let LMIC compensate for +/- n% clock error */

/* Others definitions */
#define YELLOW_LED_PIN                25
#define RED_LED_PIN                   26
#define GREEN_LED_PIN                 27
#define BUTTON_PIN                    12

/* Defines to PZEMs */
#define PZEM_DEFAULT_ADDR             0xF8
#define REG_VOLTAGE                   0x0000
#define REG_CURRENT_L                 0x0001
#define REG_CURRENT_H                 0X0002
#define REG_POWER_L                   0x0003
#define REG_POWER_H                   0x0004
#define REG_ENERGY_L                  0x0005
#define REG_ENERGY_H                  0x0006
#define REG_FREQUENCY                 0x0007
#define REG_PF                        0x0008
#define REG_ALARM                     0x0009

#define CMD_RHR                       0x03
#define CMD_RIR                       0X04
#define CMD_WSR                       0x06
#define CMD_CAL                       0x41
#define CMD_REST                      0x42

#define WREG_ALARM_THR                0x0001
#define WREG_ADDR                     0x0002

#define UPDATE_TIME                   200

#define RESPONSE_SIZE                 32
#define READ_TIMEOUT                  100

/* Watts limit to trigger Alarm */
#define WATTS_LIMIT_ON_ALARM          25000 /* In Watts */

/* Choose only one type of Serial */
//#define PZEM004_NO_SWSERIAL
//#define PZEM004_SOFTSERIAL
#define PZEM004_HARDSERIAL
//#define PZEM004T_DISABLE_SEARCH
/* End Define to PZEMs */

/* If we want to work with pre-determined shipping schedules */
//#define SCHEDULE_NEXT_TRANSMISSION

/* Variables */
/* The LEDs Blink Before JOIN every few seconds. */
u1_t          LEDS_BLINK_BeforeJOIN = 100;
/* The LED Blink After JOIN every few seconds. */
int           LED_BLINK_AfterJOIN   = 1500; /* Do not use type u1_t - I need larger size ranges so this type doesn't support */

/*
 *  Is no longer a constant so you can change
 *  the value with configuration downlinks.
 */
int unsigned  TX_INTERVAL                 = 20;   /* In Seconds, Do not use type u1_t */

/* Time interval for sending uplinks */
int unsigned  LORA_DATA_PUBLISH_INTERVAL  = 20;   /* In Seconds, Do not use type u1_t */

/* Interval between data collection and sending */
int unsigned  INTERVAL_BETWEEN_COLLECTION_AND_PUBLICATION = 2000; /* In Seconds */

int lastLoraDataPublishTime = 0;                  /* In Seconds, Do not use type u1_t */

u1_t          buttonState                 = 0;    /* Current state of the button */
u1_t          lastButtonState             = 0;    /* Previous state of the button */
u1_t          joinstatus                  = 0;    /* store the join status.  0 = not joined, 1 = joined */

/* TX or RX to Logs */
String        modeOperation               = "";

/* Counters Control */
int unsigned seqNoUp                      = 0;        /* Do not use type u1_t */
//int unsigned seqNoDn                      = 0;        /* Do not use type u1_t */

/* Variable to PZEMs */
//Stream* _serial;                                      /* Serial interface */
HardwareSerial*                           _serial;    /* Serial interface */
bool                                      _isSoft;    /* Is serial interface software */

/* Devices address */
uint8_t _addr;
uint8_t _address_PZEM_PHASE_A = 0x01;
uint8_t _address_PZEM_PHASE_B = 0x02;
uint8_t _address_PZEM_PHASE_C = 0x03;

struct
{
    float voltage;
    float current;
    float power;
    float energy;
    float frequeny;
    float powerFactor;
    uint16_t alarms;
} _currentValues;                                       /* Measured values */

uint64_t                                  _lastRead;    /* Last time values were updated */

static uint8_t                            response[PAYLOAD_LENGTH_ENERGY_METTER];

/* SoftwareSerial Pins, used to connect the PZEM module */
#if defined(PZEM004_SOFTSERIAL)
u1_t softRxPin = 6;
u1_t softTxPin = 7;
#endif
