#include "Particle.GPS.h"
#include "Nmea.h"
#include "Pmtk.h"
#include "Sentence.h"
#include "NmeaCache.h"

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
  delay(2000);

  // ***
  // *** Initialize the USB Serial for debugging.
  // ***
  Serial.begin(9600);
  Serial.println("Initializing...");

  // ***
  // *** Initialize the GPS.
  // ***
  _gps.begin(9600);

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
  /*
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
  */

  // ***
  // *** Get the Antenna Status ($PGTOP).
  // ***
  Pgtop pgtop = Pgtop(_gps);
  if (pgtop.parse())
  {

    Serial.println("1) Antenna Status ($PGTOP)");
    Serial.println("======================================================");
    Serial.print("Command ID: "); Serial.println(pgtop.commandId);
    Serial.print("Antenna Status: "); Serial.println(pgtop.reference);
    Serial.println("");
  }

  // ***
  // *** Get the Global Positioning System Fixed Data ($GPGGA).
  // ***
  Gga gga = Gga(_gps);
  if (gga.parse())
  {
    Serial.println("2) Global Positioning System Fixed Data ($GPGGA)");
    Serial.println("======================================================");
    Serial.print("UTC Time: "); Serial.println(gga.utcTime);
    Serial.print("Latitude: "); Serial.println(gga.latitude);
    Serial.print("North/SouthIndicator: "); Serial.println(gga.northSouthIndicator);
    Serial.print("Longitude: "); Serial.println(gga.longitude);
    Serial.print("East/WestIndicator: "); Serial.println(gga.eastWestIndicator);
    Serial.print("Position Fix Indicator: "); Serial.println(gga.positionFixIndicator);
    Serial.print("Satellites Used: "); Serial.println(gga.satellitesUsed);
    Serial.print("Horizontal Dilution of Precision: "); Serial.println(gga.hdop);
    Serial.print("Altitude: "); Serial.print(gga.altitude); Serial.print(" "); Serial.println(gga.altitudeUnit);
    Serial.print("Geoidal Separation: "); Serial.print(gga.geoidalSeparation); Serial.print(" "); Serial.println(gga.geoidalSeparationUnit);
    Serial.print("Age of Diff. Corr.: "); Serial.println(gga.ageOfDiffCorr);
    Serial.println("");
  }

  // ***
  // *** Get the Recommended Minimum Navigation Information ($GPRMC).
  // ***
  Rmc rmc = Rmc(_gps);
  if (rmc.parse())
  {
    Serial.println("3) Recommended Minimum Navigation Information ($GPRMC)");
    Serial.println("======================================================");
    Serial.print("UTC Time: "); Serial.println(rmc.utcTime);
    Serial.print("Latitude: "); Serial.println(rmc.latitude);
    Serial.print("North/SouthIndicator: "); Serial.println(rmc.northSouthIndicator);
    Serial.print("Longitude: "); Serial.println(rmc.longitude);
    Serial.print("East/WestIndicator: "); Serial.println(rmc.eastWestIndicator);
    Serial.print("Speed Over Ground: "); Serial.println(rmc.speedOverGround);
    Serial.print("Course Over Ground: "); Serial.println(rmc.courseOverGround);
    Serial.print("Date: "); Serial.println(rmc.date);
    Serial.print("Magnetic Variation: "); Serial.print(rmc.magneticVariation); Serial.print(" "); Serial.println(rmc.magneticVariationDirection);
    Serial.print("Mode: "); Serial.println(rmc.mode);
    Serial.println("");
  }

  delay(1000);
}
