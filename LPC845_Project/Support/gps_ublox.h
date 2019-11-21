#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "fsl_debug_console.h"

typedef struct GPS_NMEA{

	struct GNGGA{
		char id[10];
		uint32_t utc_time;
		float latitude;
		char n_s;
		float longitude;
		char e_w;
		uint8_t fs;
		uint8_t NoSV;
		float hdop;
		float msl;
		uint8_t uMsl;
		float Altref;
		uint8_t DiffAge;
		uint8_t DiffStation;
		uint8_t crc;
	}gngga;

}nmea;


extern nmea gps_nmea;

float GPS_GetLatitude(char* t);
float GPS_GetLongitude(char* t);
int GPS_CRC_Compute(char* r);
char* GPS_Get_ID(char* r,char* c);
/*
 * @brief   Application entry point.
 */
void Ublox_Initialize(void);


/*
 * @brief   Parse data of GPS
 * [@param] void
 */
int UbloxNMEAParse(char* d);
