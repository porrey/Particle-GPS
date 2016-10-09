#ifndef _GPS_H
#define _GPS_H

#include "application.h"
#include "spark_wiring_usartserial.h"
#include "Pmtk.h"
#include "NmeaCache.h"

#define BUFFER_SIZE 128

class Gps : public NmeaCache
{
    public:
        Gps(USARTSerial *);
        void begin(uint32_t);
        void end();
        void sendCommand(const char *);
        void onSerialData();

    private:
        USARTSerial* _serial;
        void clearBuffer();
        
        volatile char _buffer[BUFFER_SIZE];
        volatile int _bufferIndex = 0;
        volatile bool _synced = false;
};
#endif