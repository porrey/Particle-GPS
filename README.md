# Particle-GPS

GPS library for the Particle Electron and Photon. Current version is **v1.0.4**. 

##About
Instead of porting libraries written for other platforms, this library was written from scratch using the Particle firmware. This library allows you to easily add additional sentences or support to any serial based GPS.

##NMEA Output Sentences
This library will read the following NMEA sentences from the device into a buffer, but only supports parsing for the ones highlighted:

- **PGTOP** (Status of antenna)
- **GGA** (Time, position and fix type data)
- GSA (GPS receiver operating mode, active satellites used in the
position solution and DOP values.)
- GSV (The number of GPS satellites in view satellite ID numbers,
elevation, azimuth, and SNR values.)
- **RMC** (Time, date, position, course and speed data. Recommended
Minimum Navigation Information.)
- VTG (Course and speed information relative to the ground.)

More parsing will be added in later releases. If you wish to parse additional sentences, or you need to parse custom data, take a look at **Sentence.h** and **Sentence.cpp** to see how to implement an additional parser.

##Using the Library
###Create the Gps Instance
Define a **Gps** object in your code and assign the appropriate serial port. In the example below, the serial pins on the **TX** and **RX** pins is used (**Serial1**).

    Gps _gps = Gps(&Serial1);


###Create a Timer
In order to read the serial port fast enough, a Software Timer is used. The software timer i setup to fire every 1 ms and capture data coming in on the serial pins. The line of code below creates a software timer.

    Timer _timer = Timer(1, onSerialData);

In the callback function, simply call the **onSerialData()** method on the **Gps** object.

    void onSerialData()
    {
    	_gps.onSerialData();
    }

###Initialize the Objects
In the setup() method, call the begin method on the **Gps** object.

    _gps.begin(9600);

Also call the start() method of the timer.

    _timer.start();

###Get the Data
In the loop method, create an **Nmea** object for the specific data you want to read from the GPS. There are currently three NMEA sentences defined.

1. Antenna Status ($PGTOP) => Pgtop
2. Global Positioning System Fixed Data ($GPGGA) => Gga
3. Recommended Minimum Navigation Information ($GPRMC) => Rmc4. 

####Reading Antenna Status
First create the object passing the **Gps** instance in the constructor.

    Pgtop pgtop = Pgtop(_gps);

Next, parse the data and read the values if successful.

    if (pgtop.parse())
    {    
	    Serial.println("1) Antenna Status ($PGTOP)");
	    Serial.println("======================================================");
	    Serial.print("Command ID: "); Serial.println(pgtop.commandId);
	    Serial.print("Antenna Status: "); Serial.println(pgtop.reference);
	    Serial.println("");
    }

####Global Positioning System Fixed Data
First create the object passing the **Gps** instance in the constructor.

    Gga gga = Gga(_gps);

Next, parse the data and read the values if successful.

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

####Recommended Minimum Navigation Information
First create the object passing the Gps instance in the constructor.

    Rmc rmc = Rmc(_gps);

Next, parse the data and read the values if successful.

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

###Serial Port Debugging
Note the sample lines of code above use the serial pins connected through the USB port to send data back to the computer. Make sure the following line of code is included in your setup().

    Serial.begin();
