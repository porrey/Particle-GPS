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