#include <cstdint>
#include <string.h>

//A tram reading library created for the GL3 Mini project from scratch by Zouaghi Mohamed.

typedef struct {
    uint8_t Degree;
    uint32_t Minute;
}LocationReading; //used to encode Latitude and Longitude

typedef struct {
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;
    uint8_t Hour;
    uint8_t Minute;
    uint32_t Second;
    LocationReading Latitude;
    uint8_t NSIndicator; //0 north, 1 south
    LocationReading Longitude;
    uint8_t EWIndicator; //0 east, 1 west
	  uint8_t Altitude;
    uint8_t SatelliteNumber;
    uint8_t dataValid;
}GpsSnapshot;

typedef enum {
    NONE = -1,
    GPGGA = 0,
    GPRMC = 1
}TramType;

extern char Receive_Buffer[]; //DMA Buffer

extern GpsSnapshot* CurrentLocation; //Current Location

extern GpsSnapshot GPSInfo[100];

extern int GPSCursor;

/*Separates reading logic and storage logic*/
void TramFound(void); //Implement when tram is fully loaded

void ReadTram(int os); //Reads a tram from the buffer, Argument is the offset of the tram in the buffer (is used in both DMA interrupts)

void SerializeSnapshot(GpsSnapshot* snap, char* buffer); //Translates a GPSSnapshot into text to be displayed and  puts into a buffer
