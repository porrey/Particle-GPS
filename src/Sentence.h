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
#ifndef _SENTENCE_H
#define _SENTENCE_H

#include "application.h"
#include "Nmea.h"
#include "NmeaCache.h"

/*

Field                   Example     Units       Description
==========================================================================================================
Message ID              $PGTOP                  GGA protocol header
Command ID              11                      Function Type
Reference               3                       Value of antenna status: 1=>Active Antenna Shorted, 
                                                2=>Using Internal Antenna, 3=>Using Active Antenna
Checksum
<CR> <LF>                                       End of message termination

*/

class Pgtop : public Nmea
{
    public:
        Pgtop(NmeaCache);
        virtual bool parse();

        uint32_t commandId;
        uint32_t reference;
};

/*

Field                   Example     Units       Description
==========================================================================================================
Message ID              $GPGGA                  GGA protocol header
UTC Time                064951.000              hhmmss.sss
Latitude                2307.1256               ddmm.mmmm
N/S Indicator           N                       N=north or S=south
Longitude               12016.4438              dddmm.mmmm
E/W Indicator           E                       E=east or W=west
Position Fix Indicator  1                       0 = Fix not available, 1 = GPS fix, 2 = Differential GPS fix
Satellites Used         8                       Range 0 to 14
HDOP                    0.95                    Horizontal Dilution of Precision
MSL Altitude            39.9        meters      Antenna Altitude above/below mean-sea-level
Units                   M           meters      Units of antenna altitude
Geoidal Separation      17.8        meters
Units                   M           meters      Units of geoids separation
Age of Diff. Corr.                  second      Null fields when DGPS is not used
Checksum
<CR> <LF>                                       End of message termination

*/

class Gga : public Nmea
{
    public:
        Gga(NmeaCache);
        virtual bool parse();
        
        String utcTime;
        String latitude;
        String northSouthIndicator;
        String longitude;
        String eastWestIndicator;
        uint8_t positionFixIndicator;
        uint8_t satellitesUsed;
        float hdop;
        float altitude;
        String altitudeUnit;
        float geoidalSeparation;
        String geoidalSeparationUnit;
        String ageOfDiffCorr;
};

/*

Field                   Example     Units       Description
==========================================================================================================
Message ID              $GPGGA                  GGA protocol header
UTC Time                064951.000              hhmmss.sss
Status                  A                       A=data valid or V=data not valid
Latitude                2307.1256               ddmm.mmmm
N/S Indicator           N                       N=north or S=south
Longitude               12016.4438              dddmm.mmmm
E/W Indicator           E                       E=east or W=west
Speed over Ground       0.03        knots
Course over Ground      165.48      degrees     True
Date                    260406                  ddmmyy 
Magnetic Variation      3.05        degrees     
Magnetic Variation Dir  W                       E=east or W=west (Need GlobalTop Customization Service)
Mode                    A                       A= Autonomous mode D= Differential mode E= Estimated mode
Checksum
<CR> <LF>                                       End of message termination


$GPRMC,033718.000,A,4136.2571,N,08801.8272,W,0.01,132.25,061016,,,D*7E

*/

class Rmc : public Nmea
{
    public:
        Rmc(NmeaCache);
        virtual bool parse();
        
        String utcTime;
        String status;
        String latitude;
        String northSouthIndicator;
        String longitude;
        String eastWestIndicator;
        float speedOverGround;
        float courseOverGround;
        String date;
        float magneticVariation;
        String magneticVariationDirection;
        String mode;
};
#endif
