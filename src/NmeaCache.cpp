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
#include "NmeaCache.h"

NmeaCache::NmeaCache()
{
}

uint8_t NmeaCache::msgIdToIndex(String messageId)
{
    uint8_t returnValue = 0;
    
    if (messageId.startsWith(NMEA_MSGID_GGA))
    {
        returnValue = NMEA_INDEX_GGA;
    }
    else if (messageId.startsWith(NMEA_MSGID_GSA))
    {
        returnValue = NMEA_INDEX_GSA;
    }
    else if (messageId.startsWith(NMEA_MSGID_GSV))
    {
        returnValue = NMEA_INDEX_GSV;
    }
    else if (messageId.startsWith(NMEA_MSGID_RMC))
    {
        returnValue = NMEA_INDEX_RMC;
    }
    else if (messageId.startsWith(NMEA_MSGID_VTG))
    {
        returnValue = NMEA_INDEX_VTG;
    }
    else if (messageId.startsWith(NMEA_MSGID_PGT))
    {
        returnValue = NMEA_INDEX_PGT;
    }
    
    return returnValue;
}