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
#include "Sentence.h"

// **************************************
// *** $PGTOP
// ***
Pgtop::Pgtop(NmeaCache nmeaCache) : Nmea(NMEA_MSGID_PGT, NMEA_INDEX_PGT, nmeaCache)
{
}

bool Pgtop::parse()
{
    bool returnValue = false;
    
    if (this->isValid())
    {
        // ***
        // *** Get the first field value (Command ID).
        // ***
        uint32_t index = this->getNextUint32(0, &this->commandId);
        
        // ***
        // *** Get the next field value (Reference).
        // ***
        index = getNextUint32(index, &this->reference);
        
        // ***
        // *** Parsing was successful.
        // ***
        returnValue = true;
    }
    
    return returnValue;
}

// **************************************
// *** $GPGGA
// ***
Gga::Gga(NmeaCache nmeaCache) : Nmea(NMEA_MSGID_GGA, NMEA_INDEX_GGA, nmeaCache)
{
}

bool Gga::parse()
{
    bool returnValue = false;
    
    if (this->isValid())
    {
        // ***
        // *** Get the first field value (UTC Time).
        // ***
        int32_t index = this->getNextString(0, 10,  &this->utcTime);
        
        // ***
        // *** Get the next field value (Latitude).
        // ***
        index = this->getNextString(index, 9,  &this->latitude);
        
        // ***
        // *** Get the next field value (North/South Indicator).
        // ***
        index = this->getNextString(index, 1,  &this->northSouthIndicator);
        
        // ***
        // *** Get the next field value (Longitude).
        // ***
        index = this->getNextString(index, 10,  &this->longitude);
        
        // ***
        // *** Get the next field value (East/West Indicator).
        // ***
        index = this->getNextString(index, 1,  &this->eastWestIndicator);
        
        // ***
        // *** Get the next field value (Position Fix Indicator).
        // ***
        index = this->getNextUint8(index, &this->positionFixIndicator);

        // ***
        // *** Get the next field value (Satellites Used).
        // ***
        index = this->getNextUint8(index, &this->satellitesUsed);

        // ***
        // *** Get the next field value (Satellites Used).
        // ***
        index = this->getNextFloat(index, &this->hdop);

        // ***
        // *** Get the next field value (Satellites Used).
        // ***
        index = this->getNextFloat(index, &this->altitude);
        
        // ***
        // *** Get the next field value (East/West Indicator).
        // ***
        index = this->getNextString(index, 1,  &this->altitudeUnit);
        
        // ***
        // *** Get the next field value (Satellites Used).
        // ***
        index = this->getNextFloat(index, &this->geoidalSeparation);
        
        // ***
        // *** Get the next field value (East/West Indicator).
        // ***
        index = this->getNextString(index, 1,  &this->geoidalSeparationUnit);
        
        // ***
        // *** Get the next field value (East/West Indicator).
        // ***
        index = this->getNextString(index, 1,  &this->ageOfDiffCorr);
        
        // ***
        // *** Parsing was successful.
        // ***
        returnValue = true;
    }
    
    return returnValue;
}

// **************************************
// *** $GPRMC
// ***
Rmc::Rmc(NmeaCache nmeaCache) : Nmea(NMEA_MSGID_RMC, NMEA_INDEX_RMC, nmeaCache)
{
}

bool Rmc::parse()
{
    bool returnValue = false;
    
    if (this->isValid())
    {
        // ***
        // *** Get the first field value (UTC Time).
        // ***
        int32_t index = this->getNextString(0, 10,  &this->utcTime);
        
        // ***
        // *** Get the next field value (Status).
        // ***
        index = this->getNextString(index, 1,  &this->status);

        // ***
        // *** Get the next field value (Latitude).
        // ***
        index = this->getNextString(index, 9,  &this->latitude);
        
        // ***
        // *** Get the next field value (North/South Indicator).
        // ***
        index = this->getNextString(index, 1,  &this->northSouthIndicator);
        
        // ***
        // *** Get the next field value (Longitude).
        // ***
        index = this->getNextString(index, 10,  &this->longitude);
        
        // ***
        // *** Get the next field value (East/West Indicator).
        // ***
        index = this->getNextString(index, 1,  &this->eastWestIndicator);

        // ***
        // *** Get the next field value (Speed Over Ground).
        // ***
        index = this->getNextFloat(index, &this->speedOverGround);
       
        // ***
        // *** Get the next field value (Course Over Ground).
        // ***
        index = this->getNextFloat(index, &this->courseOverGround);
        
        // ***
        // *** Get the next field value (Date).
        // ***
        index = this->getNextString(index, 6, &this->date);
        
        // ***
        // *** Get the next field value (Magnetic Variation).
        // ***
        index = this->getNextFloat(index, &this->magneticVariation);
        
        // ***
        // *** Get the next field value (Magnetic Variation Direction).
        // ***
        index = this->getNextString(index, 1, &this->magneticVariationDirection);
        
        // ***
        // *** Get the next field value (Mode).
        // ***
        index = this->getNextString(index, 1, &this->mode);

        // ***
        // *** Parsing was successful.
        // ***
        returnValue = true;
    }
    
    return returnValue;
}