#include "GPSTramReader.h"
#include <stdio.h>

int found = 0; //says if a desired sentence is found.
TramType Tram = NONE; //current sentence to be treated.
int cursor = 0; //curent part of the sentence that is getting read.
int offset = 0; //how far arre we in each part of the current snetence
int overflow = 0; //ensures we are capable of recognizing the current sentence even if our buffer cuts it in half
int GPGGAC = 0; //GPGGA scentence found
int GPRMCC = 0; //GPRMC scentence found


//Converts a character into a number
int charToInt(char x) {
    return x - '0';
}

//detects the current tram by analizing it's 4th character
//the sentences supported by the GPS module are GPGSA GPGSV GPGLL GPRMC GPVTG GPGGA, the 4th character is unique for GPRMC and GPGGA
void gettrametype(char x) {
    switch (x) {
    case 'G':
        if (GPGGAC > 0) { //no need to read the sentence again if we read the previous one
            Tram = NONE;
            break;
        }
        Tram = GPGGA;
        found = 1;
        GPGGAC++;
        break;
    case 'M':
        if (GPRMCC > 0) { //no need to read the sentence again if we read the previous one
            Tram = NONE;
            break;
        }
        Tram = GPRMC;
        GPRMCC++;
        found = 1;
        break;
    default:
        Tram = NONE;
        found = 0;
        break;
    }
}

/* Both decode functions work by reading character by character, ensuring the ability to read half of the buffer while the other loads*/
//Reads Altitude and satellite number from GPGAA
void decodeGPGAA(int i) {
    if (cursor == 7) {
        CurrentLocation->SatelliteNumber *= 10;
        CurrentLocation->SatelliteNumber += charToInt(Receive_Buffer[i]);
    }else if(cursor == 9){
        CurrentLocation->Altitude *= 10;
        CurrentLocation->Altitude += charToInt(Receive_Buffer[i]);		
		}
}
//Reads Date, Time and position from GPRMC
void decodeGPRMC(int i) {
    switch (cursor)
    {
    case 1:
        if (offset < 2) {
            CurrentLocation->Hour *= 10;
            CurrentLocation->Hour += charToInt(Receive_Buffer[i]);
        }
        else if (offset < 4) {
            CurrentLocation->Minute *= 10;
            CurrentLocation->Minute += charToInt(Receive_Buffer[i]);
        }
        else {
            CurrentLocation->Second *= 10;
            CurrentLocation->Second += charToInt(Receive_Buffer[i]);
        }
        break;
    case 2:
        if (Receive_Buffer[i] == 'A') {
            CurrentLocation->dataValid = 1;
        }
        break;
    case 3:
        if (offset < 2) {
            CurrentLocation->Latitude.Degree *= 10;
            CurrentLocation->Latitude.Degree += charToInt(Receive_Buffer[i]);
        }
        else {
            CurrentLocation->Latitude.Minute *= 10;
            CurrentLocation->Latitude.Minute += charToInt(Receive_Buffer[i]);
        }
        break;
    case 4:
        if (Receive_Buffer[i] == 'S') {
            CurrentLocation->NSIndicator = 1;
        }
        break;
    case 5:
        if (offset < 2) {
            CurrentLocation->Longitude.Degree *= 10;
            CurrentLocation->Longitude.Degree += charToInt(Receive_Buffer[i]);
        }
        else {
            CurrentLocation->Longitude.Minute *= 10;
            CurrentLocation->Longitude.Minute += charToInt(Receive_Buffer[i]);
        }
        break;
    case 6:
        if (Receive_Buffer[i] == 'W') {
            CurrentLocation->EWIndicator = 1;
        }
        break;
    case 9:
        if (offset < 2) {
            CurrentLocation->Day *= 10;
            CurrentLocation->Day += charToInt(Receive_Buffer[i]);
        }
        else if (offset < 4) {
            CurrentLocation->Month *= 10;
            CurrentLocation->Month += charToInt(Receive_Buffer[i]);
        }
        else {
            CurrentLocation->Year *= 10;
            CurrentLocation->Year += charToInt(Receive_Buffer[i]);
        }
        break;
    default:
        break;
    }
}

int i; //our reading position in the buffer
void ReadTram(int os) {
	  //sentence detection method in case of overflow
    if (overflow) {
        gettrametype(Receive_Buffer[os * 100 + overflow - 1]);
        overflow = 0;
    }
		
    for (i = 100 * os; i < 100 + os * 100; i++) {
        if (Receive_Buffer[i] == '$') {
            if (GPGGAC > 0 && GPRMCC > 0) { //resets all variables and calls TramFound function when both sentences are found
                GPGGAC = 0;
                GPRMCC = 0;
                overflow = 0;
                cursor = 0;
                offset = 0;
                found = 0;
                Tram = NONE;
                TramFound();
                return;
            }
            if (i + 4 > 99 + 100 * os) { //detects overflow case
                overflow = 4 - (99 + os * 100 - i);
            }
            else { //calls sentence detection function
                gettrametype(Receive_Buffer[i + 4]);
            }
            cursor = 0;
            offset = 0;
            continue;
        }
        if (found) {
            if (Receive_Buffer[i] == ',') { //inceremnts counter whenever a "," is found
                cursor++;
                offset = 0;
            }
            else if (Receive_Buffer[i] != '.') { //ignores "." becase they are always at XX.XXX in any given number
                if (Tram == GPGGA) {
                    decodeGPGAA(i); //Calls GPGGA decode function
                    offset++;
                }
                else if (Tram == GPRMC) {
                    decodeGPRMC(i); //Calls GPRMC decode function
                    offset++;
                }
            }
        }
    }
}

//transforms a snapshot into a readiable text
void SerializeSnapshot(GpsSnapshot* snap, char* buffer){
	memset(buffer,0,200);
	sprintf(buffer,"\n\nReading is valid?:%d\nDate: %d/%d/%d\nTime:%d:%d:%d\nLatitude:%d deg %d South?:%d\nLongitude:%d deg %d West?:%d\nAltitude:%d m\nSatiliteNumber:%d",snap->dataValid,
	snap->Day, snap->Month,snap->Year, snap->Hour,snap->Minute,snap->Second,snap->Latitude.Degree,snap->Latitude.Minute,snap->NSIndicator,
	snap->Longitude.Degree,snap->Longitude.Minute,snap->EWIndicator,snap->Altitude,snap->SatelliteNumber);
}
