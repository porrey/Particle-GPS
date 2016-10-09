#ifndef _NMEA_H
#define _NMEA_H

#include "application.h"
#include "Particle.GPS/NmeaCache.h"

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