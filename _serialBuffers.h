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
#if defined(PZEM004_SOFTSERIAL)
#include <SoftwareSerial.h>
#endif

/* Variables */
byte payloadResponse[3 * sizeof(response)];

/* PZEMs */
HardwareSerial* portA = &Serial2;
HardwareSerial* portB = &Serial2;
HardwareSerial* portC = &Serial2;

/*****************************
 _____           _      
/  __ \         | |     
| /  \/ ___   __| | ___ 
| |    / _ \ / _` |/ _ \
| \__/\ (_) | (_| |  __/
 \____/\___/ \__,_|\___|
*****************************/

/* Functions prototypes declarations for PZEMs --> 22 Functions \('~') */
#if defined(PZEM004_SOFTSERIAL)
void softwareSerial(uint8_t receivePin, uint8_t transmitPin, uint8_t addr=PZEM_DEFAULT_ADDR);
#endif

#if defined(PZEM004_HARDSERIAL)
void hardwareSerial(HardwareSerial* port, uint8_t addr=PZEM_DEFAULT_ADDR);
void isSoftwareSerial();
#endif

float voltage();
float current();
float power();
float energy();
float frequency();
float powerFactory();

/* Getters and Setters (Address and Alarm) */
bool setAddress(uint8_t addr);
uint8_t getAddress();

bool setPowerAlarm(uint16_t watts);
bool getPowerAlarm();

bool resetEnergy(uint8_t _address);                   /* Reset power by device address */

void search();

void init(uint8_t addr);                              /* Init common to all constructors */

bool updateValues();                                  /* Get most up to date values from device registers and cache them */

uint16_t receiveBuffer(uint8_t *resp, uint16_t len);  /* Receive len bytes into a buffer */

bool sendCmd8(uint8_t cmd, uint16_t rAddr, uint16_t val, bool check = false, uint16_t slave_addr = 0xFFFF);   /* Send 8 byte command */

void setCRC(uint8_t *buf, uint16_t len);              /* Set the CRC for a buffer */
bool checkCRC(const uint8_t *buf, uint16_t len);      /* Check CRC of buffer */

uint16_t CRC16(const uint8_t *data, uint16_t len);    /* Calculate CRC of buffer */

/* Debugging function PZEM004Tv30 */
void printBufferPZEM004Tv30();

/* Functions for PZEM004Tv30 */
/*
 *  Software Serial constructor:
 *  @param receivePin RX pin
 *  @param transmitPin TX pin
 *  @param addr Slave address of device
 */
#if defined(PZEM004_SOFTSERIAL)
void softwareSerial(uint8_t receivePin, uint8_t transmitPin, uint8_t addr)
{
    SoftwareSerial *port = new SoftwareSerial(receivePin, transmitPin);
    port->begin(PZEM_BAUD_RATE);
    _serial = port;
    _isSoft = true;
    init(addr);
}
#endif

/*
 *  Hardware Serial constructor:
 *  @param port Hardware serial to use
 *  @param addr Slave address of device
 */
#if defined(PZEM004_HARDSERIAL)
void hardwareSerial(HardwareSerial *port, uint8_t addr)
{
    port->begin(PZEM_BAUD_RATE);
    _serial = port;
    _isSoft = false;
    init(addr);
}
#endif

/*
 * Destructor deleting software serial:
 *
*/
#if defined(PZEM004_SOFTSERIAL)
void isSoftwareSerial()
{
    if(_isSoft)
    delete _serial;
}
#endif

/*
 *  Voltage:
 *  Get line voltage in Volts
 *  @return current L-N volage
 */
float voltage()
{
    if (!updateValues()) /* Update vales if necessary */
        return NAN;      /* Update did not work, return NAN */
    return _currentValues.voltage;
}

/*
 *  Current:
 *  Get line in Amperes
 *  @return line current
 */
float current()
{
    if (!updateValues()) /* Update vales if necessary */
        return NAN;      /* Update did not work, return NAN */
    return _currentValues.current;
}

/*
 *  Power:
 *  Get Active power in Watts
 *  @return active power in Watts
 */
float power()
{
    if (!updateValues()) /* Update vales if necessary */
        return NAN;      /* Update did not work, return NAN */
    return _currentValues.power;
}

/*
 *  Energy:
 *  Get Active energy in kWh since last reset
 *  @return active energy in kWh
 */
float energy()
{
    if (!updateValues()) /* Update vales if necessary */
        return NAN;      /* Update did not work, return NAN */
    return _currentValues.energy;
}

/*
 *  Frequency:
 *  Get current line frequency in Hz
 *  @return line frequency in Hz
 */
float frequency()
{
    if (!updateValues()) /* Update vales if necessary */
        return NAN;      /* Update did not work, return NAN */
    return _currentValues.frequeny;
}

/*
 *  Power Factor:
 *  Get power factor of load
 *  @return load power factor
 */
float powerFactor()
{
    if (!updateValues()) /* Update vales if necessary */
        return NAN;      /* Update did not work, return NAN */
    return _currentValues.powerFactor;
}

/*
 *  sendCmd8:
 *  Prepares the 8 byte command buffer and sends
 *  @param[in] cmd    - Command to send (position 1)
 *  @param[in] rAddr  - Register address (postion 2-3)
 *  @param[in] val    - Register value to write (positon 4-5)
 *  @param[in] check  - perform a simple read check after write
 *  @return success
 */
bool sendCmd8(uint8_t cmd, uint16_t rAddr, uint16_t val, bool check, uint16_t slave_addr)
{
    uint8_t sendBuffer[8]; /* Send buffer */
    uint8_t respBuffer[8]; /* Response buffer (only used when check is true) */

    if ((slave_addr == 0xFFFF)  ||
        (slave_addr < 0x01)     ||
        (slave_addr > 0xF7))
    {
        slave_addr = _addr;
    }

    sendBuffer[0] = slave_addr;           /* Set slave address */
    sendBuffer[1] = cmd;                  /* Set command */

    sendBuffer[2] = (rAddr >> 8) & 0xFF;  /* Set high byte of register address */
    sendBuffer[3] = (rAddr)&0xFF;         /* Set low byte =//= */

    sendBuffer[4] = (val >> 8) & 0xFF;    /* Set high byte of register value */
    sendBuffer[5] = (val)&0xFF;           /* Set low byte =//= */

    setCRC(sendBuffer, 8);                /* Set CRC of frame */

    _serial->write(sendBuffer, 8);        /* Send frame */

    if (check)
    {
        if (!receiveBuffer(respBuffer, 8))
        {
            /* If check enabled, read the response */
            return false;
        }

        /* Check if response is same as send */
        for (uint8_t i = 0; i < 8; i++)
        {
            if (sendBuffer[i] != respBuffer[i])
                return false;
        }
    }
    return true;
}

/*
 *  setAddress:
 *  Set a new device address and update the device
 *  WARNING - should be used to set up devices once.
 *  Code initializtion will still have old address on next run!
 *  @param[in] addr New device address 0x01-0xF7
 *  @return success
 */
bool setAddress(uint8_t addr)
{
    if (addr < 0x01 || addr > 0xF7) /* Sanity check */
        return false;

    /* Write the new address to the address register */
    if (!sendCmd8(CMD_WSR, WREG_ADDR, addr, true))
        return false;

    _addr = addr; /* If successful, update the current slave address */

    return true;
}

/*
 *  getAddress:
 *  Get the current device address
 *  @return address
 */
uint8_t getAddress()
{
    return _addr;
}

/*
 *  setPowerAlarm:
 *  Set power alarm threshold in watts
 *  @param[in] watts Alamr theshold
 *  @return success
 */
bool setPowerAlarm(uint16_t watts)
{
    if (watts > WATTS_LIMIT_ON_ALARM)
    {
        /* Sanitych check */
        watts = WATTS_LIMIT_ON_ALARM;
    }
    
    /* Write the watts threshold to the Alarm register */
    if (!sendCmd8(CMD_WSR, WREG_ALARM_THR, watts, true))
        return false;
    return true;
}

/*
 *  getPowerAlarm:
 *  Is the power alarm set
 *  @return arlam triggerd
 */
bool getPowerAlarm()
{
    if (!updateValues()) /* Update vales if necessary */
        return NAN;      /* Update did not work, return NAN */
    return _currentValues.alarms != 0x0000;
}

/*
 *  init:
 *  initialization common to all consturctors
 *  @param[in] addr - device address
 *  @return success
 */
void init(uint8_t addr)
{
    if (addr < 0x01 || addr > 0xF8) /* Sanity check of address */
        addr = PZEM_DEFAULT_ADDR;
    _addr = addr;

    /* Set initial lastRed time so that we read right away */
    _lastRead = 0;
    _lastRead -= UPDATE_TIME;
}

/*
 *  updateValues:
 *  Read all registers of device and update the local values
 *  @return success
 */
bool updateValues()
{
    //static uint8_t buffer[] = {0x00, CMD_RIR, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00};
    
    /* If we read before the update time limit, do not update */
    if (_lastRead + UPDATE_TIME > millis())
    {
        return true;
    }

    /* Read 10 registers starting at 0x00 (no check) */
    sendCmd8(CMD_RIR, 0x00, 0x0A, false);

    if (receiveBuffer(response, PAYLOAD_LENGTH_ENERGY_METTER) != PAYLOAD_LENGTH_ENERGY_METTER)
    {
        /* Something went wrong */
        return false;
    }
    
    /*
     *  Update the current values:
     *  
     *  Raw Voltage in 0.1 Volts:
     *  ( response[3] << 8 | response[4] ) / 10.0 )
     *  
     *  Raw Current in 0.001 Amperes:
     *  ( response[5] << 8 | response[6] | response[7] << 24 | response[8] << 16 ) / 1000.0
     *  
     *  Raw Power in 0.1 Watts:
     *  ( response[9] << 8 | response[10] | response[11] << 24 | response[12] << 16 ) / 10.0
     *  
     *  Raw Energy in 1Wh:
     *  ( response[13] << 8 | response[14] | response[15] << 24 | response[16] << 16 ) / 1000.0
     *  
     *  Raw Frequency in 0.1 Hz:
     *  ( response[17] << 8 | response[18] ) / 10.0
     *  
     *  Raw Power Factory in 0.01:
     *  ( response[19] << 8 | response[20] ) / 100.0
     *  
     *  Raw Alarm value:
     *  ( response[21] << 8 | response[22] )
     */
         
    _currentValues.voltage =      ((uint32_t) response[3] << 8    | /* Raw Voltage in 0.1 Volts */
                                  (uint32_t)  response[4])        / 10.0;

    _currentValues.current =      ((uint32_t) response[5] << 8    | /* Raw Current in 0.001 Amperes */
                                  (uint32_t)  response[6]         |
                                  (uint32_t)  response[7] << 24   |
                                  (uint32_t)  response[8] << 16)  / 1000.0;

    _currentValues.power =        ((uint32_t) response[9] << 8    | /* Raw Power in 0.1 Watts */
                                  (uint32_t)  response[10]        |
                                  (uint32_t)  response[11] << 24  |
                                  (uint32_t)  response[12] << 16) / 10.0;

    _currentValues.energy =       ((uint32_t) response[13] << 8   | /* Raw Energy in 1Wh */
                                  (uint32_t)  response[14]        |
                                  (uint32_t)  response[15] << 24  |
                                  (uint32_t)  response[16] << 16) / 1000.0;

    _currentValues.frequeny =     ((uint32_t) response[17] << 8   | /* Raw Frequency in 0.1 Hz */
                                  (uint32_t)  response[18])       / 10.0;

    _currentValues.powerFactor =  ((uint32_t) response[19] << 8   | /* Raw Power Factory in 0.01 */
                                  (uint32_t)  response[20])       / 100.0;

    _currentValues.alarms =       ((uint32_t) response[21] << 8   | /* Raw Alarm value */
                                  (uint32_t)  response[22]);

    
    /* Transferring data buffer */
    for (u1_t i = 0; i < sizeof(response); i++)
    {
        if (response[0] == 0x01)
        {
            payloadResponse[i] = response[i];
        }
        else if (response[0] == 0x02)
        {
            payloadResponse[i + 25] = response[i];
        }

        else if (response[0] == 0x03)
        {
            payloadResponse[i + 50] = response[i];
        }
    }
        
    /* WARNING: Informations with 25 Bytes */
    DEBUG_PORT.println();
    DEBUG_PORT.println(F(" --> Data of PZEM to send"));
    printBufferPZEM004Tv30(response, PAYLOAD_LENGTH_ENERGY_METTER);
    DEBUG_PORT.println();
    
    /* Record current time as _lastRead */
    _lastRead = millis();

    return true;
}

/*
 *  resetEnergy:
 *  Reset the Energy counter on the device
 *  @return success
 */
bool resetEnergy(uint8_t _addr)
{
    uint8_t buffer[] = {0x00, CMD_REST, 0x00, 0x00};
    uint8_t reply[5];
    buffer[0] = _addr;

    setCRC(buffer, 4);
    _serial->write(buffer, 4);

    uint16_t length = receiveBuffer(reply, 5);

    if (length == 0 || length == 5)
    {
        return false;
    }

    return true;
}

/*
 *  receiveBuffer:
 *  Receive data from serial with buffer limit and timeout
 *  @param[out] resp Memory buffer to hold response. Must be at least `len` long
 *  @param[in] len Max number of bytes to read
 *  @return number of bytes read
 */
uint16_t receiveBuffer(uint8_t *resp, uint16_t len)
{
#ifdef PZEM004_SOFTSERIAL
    if (_isSoft)
        ((SoftwareSerial *)_serial)->listen(); /* Start software serial listen */
#endif

    unsigned long startTime = millis(); /* Start time for Timeout */
    uint8_t index = 0;                  /* Bytes we have read */
    while ((index < len) && (millis() - startTime < READ_TIMEOUT))
    {
        if (_serial->available() > 0)
        {
            uint8_t c = (uint8_t)_serial->read();

            resp[index++] = c;
        }
        yield(); /* Do background netw tasks while blocked for IO (prevents ESP watchdog trigger) */
    }
        
    /* Check CRC with the number of bytes read */
    if (!checkCRC(resp, index))
    {
        return 0;
    }

    return index;
}

/*
 *  checkCRC:
 *  Performs CRC check of the buffer up to len-2 and compares check sum to last two bytes
 *  @param[in] data Memory buffer containing the frame to check
 *  @param[in] len  Length of the respBuffer including 2 bytes for CRC
 *  @return is the buffer check sum valid
 */
bool checkCRC(const uint8_t *buf, uint16_t len)
{
    if (len <= 2) /* Sanity check */
        return false;

    uint16_t crc = CRC16(buf, len - 2); /* Compute CRC of data */
    return ((uint16_t)buf[len - 2] | (uint16_t)buf[len - 1] << 8) == crc;
}

/*
 *  setCRC:
 *  Set last two bytes of buffer to CRC16 of the buffer up to byte len-2
 *  Buffer must be able to hold at least 3 bytes
 *  @param[out] data Memory buffer containing the frame to checksum and write CRC to
 *  @param[in] len  Length of the respBuffer including 2 bytes for CRC
 */
void setCRC(uint8_t *buf, uint16_t len)
{
    if (len <= 2) /* Sanity check */
        return;

    uint16_t crc = CRC16(buf, len - 2); /* CRC of data */

    /* Write high and low byte to last two positions */
    buf[len - 2] = crc & 0xFF;        /* Low byte first */
    buf[len - 1] = (crc >> 8) & 0xFF; /* High byte second */
}

/* Pre computed CRC table */
static const uint16_t crcTable[] PROGMEM = {
    0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
    0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
    0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
    0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
    0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
    0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
    0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
    0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
    0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
    0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
    0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
    0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
    0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
    0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
    0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
    0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
    0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
    0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
    0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
    0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
    0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
    0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
    0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
    0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
    0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
    0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
    0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
    0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
    0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
    0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
    0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
    0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040};

/*
 *  CRC16:
 *  Calculate the CRC16-Modbus for a buffer
 *  Based on https://www.modbustools.com/modbus_crc16.html
 *  @param[in] data Memory buffer containing the data to checksum
 *  @param[in] len  Length of the respBuffer
 *  @return Calculated CRC
 */
uint16_t CRC16(const uint8_t *data, uint16_t len)
{
    uint8_t nTemp;         /* CRC table index */
    uint16_t crc = 0xFFFF; /* Default value */

    while (len--)
    {
        nTemp = *data++ ^ crc;
        crc >>= 8;
        crc ^= (uint16_t)pgm_read_word(&crcTable[nTemp]);
    }
    return crc;
}

/*
 *  search:
 *  Search for available devices. This should be used only for debugging!
 *  Prints any found device addresses on the bus.
 *  Can be disabled by defining PZEM004T_DISABLE_SEARCH
 */
void search()
{
#if (not defined(PZEM004T_DISABLE_SEARCH))
    static uint8_t response[7];
    for (uint16_t addr = 0x01; addr <= 0xF8; addr++)
    {
        //DEBUG_PORT.println(addr);
        sendCmd8(CMD_RIR, 0x00, 0x01, false, addr);
        
        if (receiveBuffer(response, 7) != 7)
        {
            /* Something went wrong */
            continue;
        }
        else
        {
            #ifdef DEBUG_PZEM004Tv3
            DEBUG_PORT.print("Device on addr: ");
            DEBUG_PORT.print(addr);
            #endif
        }
    }
#endif
}
/* End of Functions for PZEM004Tv30 */
