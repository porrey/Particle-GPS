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
#include "Gps.h"

Gps::Gps(USARTSerial* serial)
{
    this->_serial = serial;
};

void Gps::begin(uint32_t baud)
{
    // ***
    // *** Initialize the serial port.
    // ***
    this->_serial->begin(baud);
    this->_serial->blockOnOverrun(true);
    
    // ***
    // *** Initialize the GPS.
    // ***
    this->sendCommand(PMTK_SET_BAUD_9600);
    this->sendCommand(PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ);
    this->sendCommand(PMTK_API_SET_FIX_CTL_1HZ);
    this->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    this->sendCommand(PMTK_ENABLE_WAAS);
    this->sendCommand(PGCMD_ANTENNA);
};

void Gps::end()
{
    this->_serial->end();
}

void Gps::sendCommand(const char* data)
{
    this->_serial->println(data);
    delay(250);
}


void Gps::onSerialData()
{
    if (this->_serial->available())
    {
        char c = this->_serial->read();
        
        if (!this->_synced && c == '$') this->_synced = true;
        
        if (this->_synced)
        {
            if (this->_bufferIndex > BUFFER_SIZE)
            {
                Serial.println("Buffer Overun: '");
                this->_bufferIndex = 0;
                this->_synced = false;
            }
            else if (c == '\r')
            {
                // ***
                // *** Replace this character will a NULL.
                // ***
                this->_buffer[this->_bufferIndex] =  0;
                this->_bufferIndex++;
            }
            else if (c == '\n')
            {
                // ***
                // *** Replace this character will a NULL.
                // ***
                this->_buffer[this->_bufferIndex] =  0;
                
                // ***
                // *** This is the end of a sentence. Copy the data to
                // *** a secondary backup buffer.
                // ***
                String tempBuffer = String((char*)this->_buffer);
                
                // ***
                // *** Check which sentence we have and copy it to the
                // *** correct buffer. Note the first buffer at index 0
                // *** is a discard buffer in case we get a sentence that
                // *** is not expected.
                // ***
                uint8_t index = this->msgIdToIndex(tempBuffer);
                this->data[index] = tempBuffer;

                // ***
                // *** Reset the buffer.
                // ***
                this->_bufferIndex = 0;
                this->_synced = false;
                this->clearBuffer();
            }
            else
            {
                this->_buffer[this->_bufferIndex] = c;
                this->_bufferIndex++;
            }
        }
    }
}

void Gps::clearBuffer()
{
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        this->_buffer[i] = 0;
    }
}
