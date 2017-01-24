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
