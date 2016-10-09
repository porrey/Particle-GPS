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