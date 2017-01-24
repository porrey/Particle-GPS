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
// *** Include the appropriated serial
// *** file for ports 2, 4 and 5.
// ***
#include "Serial2/Serial2.h"
#include "Serial4/Serial4.h"
#include "Serial5/Serial5.h"

// ***
// *** Create a Gps instance. The RX an TX pins are connected to
// *** the TX and RX pins on the device. Uncomment the correct
// *** the line below to match your wiring.
// ***
Gps _gps = Gps(&Serial1);	// TX and RX pins on the Photon and Electron.
//Gps _gps = Gps(&Serial2);	// RGB Green (TX) and Blue (RX) LED pins on the Photon and Electron.
//Gps _gps = Gps(&Serial4);	// C3(TX) and C2(RX) pins on the Electron.
//Gps _gps = Gps(&Serial5);	// C1(TX) and C0(RX) pins on the Electron.

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