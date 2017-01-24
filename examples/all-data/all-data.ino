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
#include "Particle-GPS.h"

// ***
// *** Create a Gps instance. The RX an TX pins are connected to
// *** the TX and RX pins on the electron (Serial1).
// ***
Gps _gps = Gps(&Serial1);

// ***
// *** Create a timer that fires every 1 ms to capture
// *** incoming serial port data from the GPS.
// ***
Timer _timer = Timer(1, onSerialData);

void setup()
{
  // ***
  // *** Initialize the USB Serial for debugging.
  // ***
  Serial.begin();
  Serial.println("Initializing...");

  // ***
  // *** Initialize the GPS.
  // ***
  _gps.begin(9600);

  // ***
  // *** Request that all data be sent.
  // ***
  _gps.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);

  // ***
  // *** Start the timer.
  // ***
  _timer.start();
}

void onSerialData()
{
  _gps.onSerialData();
}

void loop()
{
  // ***
  // *** This will display the strings received from
  // *** the GPS unit. Some may be empty if the GPS
  // *** is not set to send all data.
  // ***
  Serial.print("Data[0] = "); Serial.println(_gps.data[0]);
  Serial.print("Data[1] = "); Serial.println(_gps.data[1]);
  Serial.print("Data[2] = "); Serial.println(_gps.data[2]);
  Serial.print("Data[3] = "); Serial.println(_gps.data[3]);
  Serial.print("Data[4] = "); Serial.println(_gps.data[4]);
  Serial.print("Data[5] = "); Serial.println(_gps.data[5]);
  Serial.print("Data[6] = "); Serial.println(_gps.data[6]);

  delay(1000);
}