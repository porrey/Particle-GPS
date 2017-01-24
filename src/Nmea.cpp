// Copyright © 2016-2017 Daniel Porrey. All Rights Reserved.
//
// This file is part of the Particle.GPS library.
// 
// Particle.GPS library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Particle.GPS library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Particle.GPS library. If not, 
// see http://www.gnu.org/licenses/.
//
#include "Nmea.h"

Nmea::Nmea(String messageId, uint8_t dataIndex, NmeaCache nmeaCache)
{
    // ***
    // *** Save the Message ID
    // ***
    this->_messageId = messageId;
    
    // ***
    // *** Save the data index. This is the position
    // *** in the GPS ata array that this sentence 
    // *** can be found.
    // ***
    this->_dataIndex = dataIndex;
    
    // ***
    // *** Make a copy of the data.
    // ***
    this->_data = String(nmeaCache.data[dataIndex]);
}

bool Nmea::parse()
{
    return false;
}

bool Nmea::isValid()
{
    bool returnValue = false;
    
    if (this->_data.startsWith(this->_messageId))
    {
        // ***
        // *** Get the check sumn value from the string.
        // ***
        uint16_t providedChecksum = this->extractChecksum();
        
        // ***
        // *** Calculate the cheksum of the string.
        // ***
        uint16_t calculatedChecksum = this->calculateChecksum();
        
        // ***
        // *** Comparethe two values.
        // ***
        returnValue = (providedChecksum == calculatedChecksum);
    }

    return returnValue;
}

uint16_t Nmea::extractChecksum()
{
    uint16_t returnValue = 0;
    
    // ***
    // *** Get the position of the last * character.
    // ***
    uint8_t index = this->_data.lastIndexOf("*");
    
    // ***
    // *** Check that we have the character and that the string
    // *** is at least two characters longer than the position.
    // ***
    if (index != -1 && this->_data.length() >= (uint16_t)(index + 2))
    {
        char c1 = this->_data.charAt(index + 1);
        char c2 = this->_data.charAt(index + 2);

        returnValue = (parseHex(c1) * 16) + parseHex(c2);
    }
    
    return returnValue;
}

uint16_t Nmea::calculateChecksum()
{
    uint16_t returnValue = 0;
    
    // ***
    // *** The string must start with the $ character.
    // ***
    if (this->_data.startsWith("$"))
    {
        // ***
        // *** The checksum does not include the first character ($)
        // *** and it does not include the check sum value (the last
        // *** 3 characters (*xx).
        // ***
        for (uint8_t i = 1; i < this->_data.length() - 3; i++) 
        {
            // ***
            // *** XOR the bytes.
            // ***
            returnValue ^= this->_data.charAt(i);
        }
    }
    
    return returnValue;
}

// ***
// *** Read a Hex value and return the decimal equivalent.
// ***
uint8_t Nmea::parseHex(char c) 
{
    uint8_t returnValue = 0;

    switch(c)
    {
        case '0':
            returnValue = 0;
            break;
        case '1':
            returnValue = 1;
            break;
        case '2':
            returnValue = 2;
            break;
        case '3':
            returnValue = 3;
            break;
        case '4':
            returnValue = 4;
            break;
        case '5':
            returnValue = 5;
            break;
        case '6':
            returnValue = 6;
            break;
        case '7':
            returnValue = 7;
            break;
        case '8':
            returnValue = 8;
            break;
        case '9':
            returnValue = 9;
            break;
        case 'A':
            returnValue = 10;
            break;
        case 'B':
            returnValue = 11;
            break;
        case 'C':
            returnValue = 12;
            break;
        case 'D':
            returnValue = 13;
            break;
        case 'E':
            returnValue = 14;
            break;
        case 'F':
            returnValue = 15;
            break;
        default:
            returnValue = 0;
            break;
    }

    return returnValue;
}

int32_t Nmea::getNextPosition(uint32_t from)
{
    int32_t returnValue = -1;
    
    if (from >= 0)
    {
        returnValue = this->_data.indexOf(",", from);
    }
    
    return returnValue;
}

bool Nmea::getNextIsNull(uint32_t from)
{
    int32_t returnValue = -1;
    
    if (from >= 0)
    {
        String nextChar = String(this->_data.charAt(from + 1));
        returnValue = nextChar.equals(",");
    }
    
    return returnValue;
}

int32_t Nmea::getNextUint32(uint32_t from, uint32_t* value)
{
    int32_t returnValue = -1;
    *value = 0;

    // ***
    // *** Get the position of the next comma.
    // ***
    int32_t index = this->getNextPosition(from);

    // ***
    // *** Check if one was found.
    // ***
    if (index != -1 && !this->getNextIsNull(index))
    {
        // ***
        // *** The toInt() function will work if there are characters
        // *** after the number so do no worry abut stripping out the
        // *** the text after the number.
        // ***
        returnValue = index + 1;
        *value = this->_data.substring(index + 1).toInt();
    }
    
    return returnValue;
}

int32_t Nmea::getNextUint8(uint32_t from, uint8_t* value)
{
    int32_t returnValue = -1;
    *value = 0;

    // ***
    // *** Get the position of the next comma.
    // ***
    int32_t index = this->getNextPosition(from);

    // ***
    // *** Check if one was found.
    // ***
    if (index != -1 && !this->getNextIsNull(index))
    {
        // ***
        // *** The toInt() function will work if there are characters
        // *** after the number so do no worry abut stripping out the
        // *** the text after the number.
        // ***
        returnValue = index + 1;
        *value = (uint8_t)this->_data.substring(index + 1).toInt();
    }
    
    return returnValue;
}

int32_t Nmea::getNextFloat(uint32_t from, float* value)
{
    int32_t returnValue = -1;
    *value = 0;

    // ***
    // *** Get the position of the next comma.
    // ***
    int32_t index = this->getNextPosition(from);

    // ***
    // *** Check if one was found.
    // ***
    if (index != -1 && !this->getNextIsNull(index))
    {
        // ***
        // *** The toInt() function will work if there are characters
        // *** after the number so do no worry abut stripping out the
        // *** the text after the number.
        // ***
        returnValue = index + 1;
        *value = this->_data.substring(index + 1).toFloat();
    }
    
    return returnValue;
}

int32_t Nmea::getNextString(uint32_t from, uint32_t length, String* value)
{
    int32_t returnValue = -1;
    *value = String("");

     // ***
    // *** Get the position of the next comma.
    // ***
    int32_t index = this->getNextPosition(from);

    // ***
    // *** Check if one was found.
    // ***
    if (index != -1 && !this->getNextIsNull(index))
    {
        // ***
        // *** Parse the string.
        // ***
        returnValue = index + 1;
        *value = String(this->_data.substring(index + 1, index + 1 + length));
    }
    
    return returnValue;
}