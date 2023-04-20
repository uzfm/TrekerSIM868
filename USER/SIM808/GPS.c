#include <stdio.h>
#include <string.h>

#define MAX_DATA_SIZE 256

extern  unsigned char RxDataGPS[300];
struct Coordinates {
    float latitude;
    float longitude;
};

char test[100];

char get_coordinates( char* data, struct Coordinates* coords) {


//$GNRMC,153652.621,A,5045.030632,N,02520.324466,E,0.10,0.00,210423,,,A*7·0$GNVTG,0.00,T,,M,0.10,N,0.18,K,A*2B
	    // Find the RMC data   // Find the line with coordinates
	    char* ptr = strstr(data, "$GNRMC");
	    if (ptr == NULL) {

	        return 0;
	    }

	    // Parse latitude
	    strcpy(test, ptr);
	    ptr = strtok(NULL, ",");
	    strcpy(test, ptr);
	    ptr = strtok(NULL, ",");
	    strcpy(test, ptr);
	    ptr = strtok(NULL, ",");

	    strcpy(test, ptr);

	    double latitude_degrees = atof(ptr) / 100;
	    double latitude_minutes = fmod(atof(ptr), 100);
	    coords->latitude = latitude_degrees + latitude_minutes / 60;


	    // Declare variables to store latitude and longitude
	    float latitude, longitude;

	    // Parse latitude

	    ptr = strtok(NULL, ","); // Skip time
	    latitude = atof(ptr);
	    ptr = strtok(NULL, ",");
	    if (ptr[0] == 'S') {
	        latitude = -latitude;
	    }


	    // Parse N/S indicator
	    ptr = strtok(NULL, ",");
	    if (strcmp(ptr, "S") == 0) {
	        coords->latitude *= -1;
	    }

	    // Parse longitude
	    ptr = strtok(NULL, ",");
	    double longitude_degrees = atof(ptr) / 100;
	    double longitude_minutes = fmod(atof(ptr), 100);
	    coords->longitude = longitude_degrees + longitude_minutes / 60;

	    // Parse E/W indicator
	    ptr = strtok(NULL, ",");
	    if (strcmp(ptr, "W") == 0) {
	        coords->longitude *= -1;
	    }
	    return 1;

}


void SendUSB_DT(char *Bufer, short Leng);


int GPS_Read(char *data) {

    struct Coordinates coords;
   if(0 ==get_coordinates(data, &coords)){ return 0;};

    char latitude_string[20]; // Буфер для зберігання рядка
    // Конвертування числа в рядок
    sprintf(latitude_string, "%.7f", coords.latitude);

    char longitude_string[20]; // Буфер для зберігання рядка
    // Конвертування числа в рядок
    sprintf(longitude_string, "%.7f", coords.longitude);

    char coordinates_string[50]; // Буфер для зберігання рядка з координатами
    // Складання рядка з координатами
    strcpy(coordinates_string, latitude_string);
    strcat(coordinates_string, ",");
    strcat(coordinates_string, longitude_string);
    int len = strlen(coordinates_string);
    SendUSB_DT(coordinates_string, len);

    return 1;
}

int GPS_Write(char *data){



}
