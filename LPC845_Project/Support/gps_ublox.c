#include "gps_ublox.h"


void GPS_Split_Parse(char* u,int c){

	const char _coma_[2] = {","};
	char* tokken;

	tokken = strtok(u,_coma_);

	if(strcmp(tokken,"$GNGGA") == 0){

		strncpy(gps_nmea.gngga.id,tokken,6);
		tokken = strtok(NULL,_coma_);
		gps_nmea.gngga.utc_time = atoi(tokken);
		tokken = strtok(NULL,_coma_);
		gps_nmea.gngga.latitude = atof(tokken);
		tokken = strtok(NULL,_coma_);
		if(strncmp(tokken,"N",1) != 0) gps_nmea.gngga.latitude = -1*gps_nmea.gngga.latitude;
		tokken = strtok(NULL,_coma_);
		gps_nmea.gngga.longitude = atof(tokken);
		tokken = strtok(NULL,_coma_);
		if(strncmp(tokken,"E",1) != 0) gps_nmea.gngga.longitude = -1*gps_nmea.gngga.longitude;

	}


}


char* GPS_Get_ID(char* r,char* c){

	uint16_t toc = 0;

	if(*r != '\0'){

		do{

			(*c++) = (*r++);
			if(toc<100)toc++; else break;

		}while(*r != '\r');

		if(toc<100){

			*c = '\0';
			*r++; //\r
			*r++; //\n
		}else{

			*r = '\0';

		}

	}



    return r;
}

int GPS_CRC_Compute(char* r){

    uint8_t crc = 0;
    uint16_t counter_timeout = 0;
    *r++;

    do{

        crc = crc ^ *r++;
        if(counter_timeout<100)counter_timeout++; else break;


    }while(*r!='*');

    if(counter_timeout>100) *r = '\0';

    return crc;

}

void Ublox_Initialize(void){



}

/*
 * @brief   Parse data of GPS
 * [@param] void
 * [DataGPS]
 * $GNGGA,031254.000,2527.0889,N,10054.0255,W,1,05,7.4,1557.4,M,0.0,M,,*5C<CR><LF>
   $GNGLL,2527.0889,N,10054.0255,W,031254.000,A,A*5D<CR><LF>
   $GPGSA,A,3,09,07,23,08,,,,,,,,,10.1,7.4,6.9*09<CR><LF>
   $BDGSA,A,3,14,,,,,,,,,,,,10.1,7.4,6.9*1A<CR><LF>
   $GPGSV,3,1,11,03,13,190,,04,,,32,07,38,320,23,08,56,117,27*42<CR><LF>
   $GPGSV,3,2,11,09,74,308,35,11,15,161,,16,15,041,,23,71,155,34*7A<CR><LF>
   $GPGSV,3,3,11,27,39,064,,28,11,234,20,30,14,296,*42<CR><LF>
   $BDGSV,1,1,01,14,28,299,28*5E<CR><LF>
   $GNRMC,031254.000,A,2527.0889,N,10054.0255,W,0.00,0.00,031119,,,A*61<CR><LF>
   $GNVTG,0.00,T,,M,0.00,N,0.00,K,A*23<CR><LF><CR><LF>$GNZDA,031254.000,03,11,2019,00,00*40<CR><LF>
   $GPTXT,01,01,01,ANTENNA OK*35<CR><LF>
 */

int UbloxNMEAParse(char* d){


	char _ret[127];
	char *rt;
	uint16_t _crc_ = 0;
	uint16_t resp = 0;

	rt = d;

	while(*rt != '\0'){

		rt = GPS_Get_ID(rt,_ret);
		_crc_ = GPS_CRC_Compute(_ret);
		GPS_Split_Parse(_ret,_crc_);

	}


}
