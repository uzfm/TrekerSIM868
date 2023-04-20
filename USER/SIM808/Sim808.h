

#include "main.h"

void delayWritCom (char comand);
void ATcomand(char Comand);

#define  AT       1
#define  ATE0     2
#define  ATCREG   3
#define  ATCSQ    4
#define  ATGSN    5
#define  ATCBC    6
#define  ATMGD    7
#define  ATMGR    8
#define  ATCPOWD  9
#define  ATCPIN  10
#define ATCGNSPWR1 11
#define ATCGNSINF 12 
#define  ATCMGF  13
#define  ATCMGDA 14
#define  ATCMGS  15
#define  SMSSEND 16
#define  STATUS  17
#define  CSCLK   18
#define  CGNSTST  19
#define  CNETLIGHT 20
#define  CWHITELIST 21
#define  ATCGNSPWR0 22
#define  CFUN1      23 



static union {
 char Buf[94];
 struct DT{
char  RunStatus;
char  point0;
char  FixStatus;
char  point1;
char  DateTime[18];
char  point2;
//char year [4];
//char month[2];
//char day  [2];
//char hours[2];
//char moments[2];
//char seconds[2];
//char secondss[4];
char Latitude[10];
char  point3;
char Longitude [11];
char  point4;
char Altitude[8]; //meters
char  point5;
char Speed[6];   //Km/hour
char  point6;
char Course[6];  //degrees
char  point7;
char FixMode[1];
char  point8;
char Reserved1[1];
char  point9;
char HDOP [4];
char  point10;
char PDOP [4];
char  point11;
char VDOP [4];
char  point12;
char Reserved2[1];
char  point13;
char GPS_Satellites[2];
char  point14;
char GNSS_Satellites[2];
char  point15;
char GLONASS_Satellites[2];
char  point16;
char Reserved3[1];
char  point17;
char CN0_max [2];  //dBHz
char  point18;
char HPA [6];  //meters
char  point19;
char VPA [6];  //meters
char  point20;

 }; struct DT DT;}GPS;




#define  OK      30
#define  ERROR_COMAND   31

#define  PWRKEY_ON    HAL_GPIO_WritePin( SIM_PWR_KEY_GPIO_Port, SIM_PWR_KEY_Pin , GPIO_PIN_SET)
#define  PWRKEY_OF    HAL_GPIO_WritePin( SIM_PWR_KEY_GPIO_Port, SIM_PWR_KEY_Pin , GPIO_PIN_RESET)


#define  PWRSENSOR_OF  HAL_GPIO_WritePin(PWR_Sensor_GPIO_Port, PWR_Sensor_Pin , GPIO_PIN_RESET)
#define  PWRSENSOR_ON  HAL_GPIO_WritePin(PWR_Sensor_GPIO_Port, PWR_Sensor_Pin , GPIO_PIN_SET)


#define   SLEEP_OF      HAL_GPIO_WritePin(DTR_SlEEP_GPIO_Port, DTR_SlEEP_Pin, GPIO_PIN_RESET)
#define   SLEEP_ON      HAL_GPIO_WritePin(DTR_SlEEP_GPIO_Port, DTR_SlEEP_Pin, GPIO_PIN_SET)

//Print_GSM("AT\n");
 struct SMS {
char NambeRead;      //����� ��� � ����� GSM
char NambePhon[20]; //����� �������� ���������� ���
char TextRead[200];     //����� ��� 
char TextWRid[200];     //����� ��� 
char New;           //������� ���� ���
};
static struct SMS SMS;

 struct Buf {
char RX[257] ;
char TX[257] ;
int  Timeout;
char LongRX;
char LongTX;
};static struct Buf Buf;

 struct GSM {
char REG;
char IM[15] ;
char BAT_PERCENT[2];
char BAT_V[4];
char LINK[2];
char installed;
char Sensor[10];
};static struct GSM GSM;



