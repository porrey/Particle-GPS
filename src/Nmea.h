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
#ifndef _NMEA_H
#define _NMEA_H

#include "application.h"
#include "NmeaCache.h"

class Nmea
{
    public:
        Nmea(String, uint8_t, NmeaCache);
        bool isValid();
        bool parse();

    protected:
        uint16_t extractChecksum();
        uint16_t calculateChecksum();
        uint8_t parseHex(char c);
        
        int32_t getNextPosition(uint32_t);
        bool getNextIsNull(uint32_t);
        int32_t getNextUint32(uint32_t, uint32_t*);
        int32_t getNextUint8(uint32_t, uint8_t*);
        int32_t getNextFloat(uint32_t, float*);
        int32_t getNextString(uint32_t, uint32_t, String*);

        String _messageId;
        uint8_t _dataIndex;
        String _data;
};
#endif