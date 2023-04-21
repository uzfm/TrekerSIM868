//#include <stdio.h>
#include <string.h>


#define MAX_DATA_SIZE 256

extern  unsigned char RxDataGPS[300];
struct Coordinates {
    float latitude;
    float longitude;
};


struct GPSData {
  char time[10];
  char latitude[12];
  char longitude[12];
  int quality;
  int satellites;
  float hdop;
  float altitude;
};

char * _chrtok(char *str, const char delim)
{
    static char *next_token = NULL; // зберігаємо значення покажчика між викликами
    char *token_start;

    if (str) { // якщо передано новий рядок
        next_token = str; // починаємо з початку рядка
    }

    // шукаємо наступний токен
    token_start = next_token;
    while (*next_token && (*next_token != delim)) {
        next_token++;
    }
    if (*next_token == '\0') { // якщо досягнуто кінця рядка, повертаємо NULL
        return NULL;
    }
    *next_token = '\0'; // замінюємо роздільник нуль-термінатором
    next_token++; // переміщуємо покажчик на наступний символ після роздільника

    return token_start; // повертаємо вказівник на початок токена
}

char * _strtok(char *str, const char *delim) {
    static char *last = NULL;
    if (str != NULL) {
        last = str;
    } else {
        str = last;
    }
    if (str == NULL) {
        return NULL;
    }
    char *token = str;
    while (*str != '\0') {
        const char *d = delim;
        while (*d != '\0') {
            if (*str == *d) {
                *str = '\0';
                last = str + 1;
                if (token != str) {
                    return token;
                } else {
                    token = last;
                    break;
                }
            }
            d++;
        }
        str++;
    }
    last = NULL;
    if (token == str) {
        return NULL;
    } else {
        return token;
    }
}



char str[100];
// char str[] = "$GNGGA,223114.000,5046.311516,N,02522.257864,E,1,5,2.66,157.344,M,33.970,M,,*47";
char get_coordinates( char* data1, struct Coordinates* coords) {

char data[] = "$GNGGA,223114.000,5046.311516,N,02522.257864,E,1,5,2.66,157.344,M,33.970,M,,*47";
//$GNRMC,153652.621,A,5045.030632,N,02520.324466,E,0.10,0.00,210423,,,A*7В·0$GNVTG,0.00,T,,M,0.10,N,0.18,K,A*2B
static char gps_data[100];
strcpy(gps_data, "$GNGGA,223114.000,5046.311516,N,02522.257864,E,1,5,2.66,157.344,M,33.970,M,,*47");




char str[] = "apple,world,cherry,donut,22222,3333,9";
char tokens[5][10] ;
char delimiter[] = ",";
int i=0;

 char *tokenq = _strtok(str,",");

 while (tokenq != NULL) {

   if (strcmp(tokenq, "world") == 0) {
		 strcpy(tokens[i++], tokenq);
   }

	 tokenq = _strtok(NULL, ",");




	 strcpy(tokens[i++], tokenq);



     //printf("%s\n", tokenq);
    // tokenq = strstr(NULL, ",");
 }

float convert_coordinate(char* str);
 char stree[] = "02522.257864";
   float coordr = convert_coordinate(stree);
 //  printf("%.7f", coord); // виведе 25.3709641
char resa[]="                      ";
     sprintf(&resa ,
		   "%.7f", coordr);



 //char *token;
int field_num = 0;
struct GPSData gps;
char *delim = ",";



char *token = _strtok(gps_data, delim);

while (token != NULL) {

  if (strcmp(token, "$GNGGA") == 0) {
		//token = token+7;

		 token = _strtok(NULL, ",");

		while (token != NULL) {
		  field_num++;

		  switch(field_num) {
		    case 1:  strcpy(gps.time,      token);  break;
		    case 2:
		    strcpy(gps.latitude,  token);
		    //float latitude_degrees =      atof(  token) / 100;
		   // float latitude_minutes = fmod(atof(  token), 100);
		  // float  latitudeFloat = (latitude_degrees + latitude_minutes) / 60;
		    float  latitudeFloat   = convert_coordinate(token);
		    sprintf( gps.latitude , "%.7f", latitudeFloat);
		    break;

		    case 4:  strcpy(gps.longitude, token);
		    float  latitudeFloat1   = convert_coordinate(token);
		    //float  longitude_degrees =      atof(  token) / 100;
		    //float  longitude_minutes = fmod(atof(  token), 100);
		    // float   latitudeFloat1 = (latitude_degrees + latitude_minutes) / 60;
		    sprintf( gps.longitude , "%.7f", latitudeFloat1);
		    break;
		    case 6:  gps.quality =    atoi(token);  break;
		    case 7:  gps.satellites = atoi(token); break;
		    case 8:  gps.hdop =       atof(token); break;
		    case 9:  gps.altitude =   atof(token); return 1;
		  }

		  token = _strtok(NULL, ",");

		}



  }
	 token = _strtok(NULL, ",");
	 //strcpy(token[i++], token);

}




	    return 1;

}


float convert_coordinate(char* str) {
    float coord = atof(str); // перетворюємо рядок на число з плаваючою крапкою
    int degrees = (int)coord / 100; // визначаємо ступені
    float minutes = coord - degrees * 100; // визначаємо хвилини
    return degrees + minutes / 60.0; // повертаємо координату у десятковому форматі
}




void SendUSB_DT(char *Bufer, short Leng);


int GPS_Read(char *data) {

    struct Coordinates coords;
   if(0 ==get_coordinates(data, &coords)){ return 0;};

    char latitude_string[20]; // Р‘СѓС„РµСЂ РґР»СЏ Р·Р±РµСЂС–РіР°РЅРЅСЏ СЂСЏРґРєР°
    // РљРѕРЅРІРµСЂС‚СѓРІР°РЅРЅСЏ С‡РёСЃР»Р° РІ СЂСЏРґРѕРє
    sprintf(latitude_string, "%.7f", coords.latitude);

    char longitude_string[20]; // Р‘СѓС„РµСЂ РґР»СЏ Р·Р±РµСЂС–РіР°РЅРЅСЏ СЂСЏРґРєР°
    // РљРѕРЅРІРµСЂС‚СѓРІР°РЅРЅСЏ С‡РёСЃР»Р° РІ СЂСЏРґРѕРє
    sprintf(longitude_string, "%.7f", coords.longitude);

    char coordinates_string[50]; // Р‘СѓС„РµСЂ РґР»СЏ Р·Р±РµСЂС–РіР°РЅРЅСЏ СЂСЏРґРєР° Р· РєРѕРѕСЂРґРёРЅР°С‚Р°РјРё
    // РЎРєР»Р°РґР°РЅРЅСЏ СЂСЏРґРєР° Р· РєРѕРѕСЂРґРёРЅР°С‚Р°РјРё
    strcpy(coordinates_string, latitude_string);
    strcat(coordinates_string, ",");
    strcat(coordinates_string, longitude_string);
    int len = strlen(coordinates_string);
    SendUSB_DT(coordinates_string, len);

    return 1;
}




/*
$GNGGA,223114.000,5046.311516,N,02522.257864,E,1,5,2.66,157.344,M,33.970,M,,*47


$GPGSA,A,3,06,11,07,09,,,,,,,,,2.83,2.66,0.96*0E
$GLGSA,A,3,66,,,,,,,,,,,,2.83,2.66,0.96*1A
$GPGSV,3,1,12,09,76,279,20,04,65,068,,06,45,256,24,07,37,194,28*72
$GPGSV,3,2,12,03,31,131,,11,29,308,31,16,20,088,,26,19,050,17*71
$GPGSV,3,3,12,20,07,310,,30,05,209,20,31,02,039,,29,02,358,*7F
$GLGSV,3,1,09,65,71,345,,74,43,057,,75,40,136,,72,38,084,*6F
$GLGSV,3,2,09,81,33,302,22,66,23,290,21,88,23,242,19,82,12,348,*67
$GLGSV,3,3,09,73,11,021,*5B
$GNRMC,223114.000,A,5046.311516,N,02522.257864,E,0.03,68.80,210423,,,A*4F
$GNVTG,68.80,T,,M,0.03,N,0.06,K,A*10
*/




