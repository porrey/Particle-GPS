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
#ifndef _NMEA_CACHE_H
#define _NMEA_CACHE_H

#include "application.h"

#define NMEA_INDEX_GGA      1
#define NMEA_INDEX_GSA      2
#define NMEA_INDEX_GSV      3
#define NMEA_INDEX_RMC      4
#define NMEA_INDEX_VTG      5
#define NMEA_INDEX_PGT      6

#define NMEA_MSGID_GGA      "$GPGGA"
#define NMEA_MSGID_GSA      "$GPGSA"
#define NMEA_MSGID_GSV      "$GPGSV"
#define NMEA_MSGID_RMC      "$GPRMC"
#define NMEA_MSGID_VTG      "$GPVTG"
#define NMEA_MSGID_PGT      "$PGTOP"

#define NMEA_MSGID_LENGTH   6
#define NMEA_MAX_SENTENCE   6

class NmeaCache
{
    public:
        NmeaCache();
        String data[NMEA_MAX_SENTENCE + 1];
        
    protected:
        uint8_t msgIdToIndex(String);
};
#endif