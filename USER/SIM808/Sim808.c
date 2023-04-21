
#include "Sim808.h"

void Seep_ON(void);
int Standby(void);
void ReadGSM(char comand);
void delay (int time);
static char  Instal_GSN_GPS = 0;
void Read_HCSR04(char *Buffer);
char comand1[]   ="AT+CMGD=1,4\r";
char comand[]    ="AT+CMGR=1\r";
char StringSMS[250] ;
static char COMANDA=1;
 char Cauntidx = 0;
  char Strin []="AT+CMGS=";
  char Strin1[]="+380931041316";
 // char Strin2[]="Prosto testovsa SMS";
  char COMPARE=0;
  char SEND=1;
  char SMSDT=0;
  int TimeInst=1000;
  char CantSmsOK;
  char SlipGSM=0;
  char ResComand=0;
    char ERRORSTATUS=0;
    char ERRORAT=0;




 /**********************************************************************/
 /******************       GSM          **********************/
 /**********************************************************************/
void UsbWritCDM  (unsigned char *data, char lengh);








//������ SMS
void ReadMessage(void){

if((SMS .TextRead[0]=='B')&&
   (SMS.TextRead[1]=='A')&&
   (SMS.TextRead[2]=='T')){
    SMSDT=ATCBC; //COMANDA = ATMGD;
   }else{


if((SMS.TextRead[0]=='S')&&
   (SMS.TextRead[1]=='T')&&
   (SMS.TextRead[2]=='A')&&
   (SMS.TextRead[3]=='T')&&
   (SMS.TextRead[4]=='U')&&
   (SMS.TextRead[5]=='S')){
   SMSDT=STATUS; //COMANDA = ATMGD;
   }else{


  SMSDT = ERROR_COMAND; }}}






///////////////////////////////////////////////////////////////////////////////
////               ����� ������                          //////////////////////
///////////////////////////////////////////////////////////////////////////////

void ATcomand(char Comand){
 //SLEEP_ON;
//TimeInst++;

//���� �� ������� ���������� gsm ���������� �������
/*if((Instal_GSN_GPS==0)&&(TimeInst>10000)){
	SEND=1; TimeInst=0;  ResComand++;
if(ResComand>3){ResComand=0; COMANDA=ATE0; Seep_OF();}
if(CantSmsOK>6){
	COMANDA=ATE0;
	PWRKEY_ON;
Seep_OF();
delay (2000);
PWRKEY_OF;
CantSmsOK=0;
COMANDA=AT;}}*/

//�������� �������� �������
if(!(COMPARE==COMANDA)){SEND=1; ResComand=0; }

    if(SEND==1){ CantSmsOK++;
    if(CantSmsOK>1000000){Instal_GSN_GPS=0; TimeInst=0;    PWRKEY_ON;   Seep_OF();  delay (2000);  PWRKEY_OF;CantSmsOK=0; COMANDA=AT;}

      SEND=0;
   COMPARE=COMANDA;

  switch (COMANDA){
  case AT: SLEEP_OF ; osDelay(2000); Print_GSM("ATE0\r");   break;           //�������� ������
  case ATE0: SLEEP_OF ; ERRORAT++; Print_GSM("ATE0\r");  break;          //��������� ���
  case ATCREG: Print_GSM("AT+CREG?\r");  break;      //��������� � �����
  case ATCMGF: Print_GSM("AT+CMGF=1\r");  break;      //��������� ����� ���
  case ATCSQ: Print_GSM("AT+CSQ\r");  break;         //������ GSM
  case ATGSN: Print_GSM("AT+GSN\r");  break;         //IMEI
  case ATCBC: Print_GSM("AT+CBC\r");  break;         //����� ������
  //case ATMGD:  Print_GSM("AT+CMGD=1,4\r");  break;    //�������� �� �������� ���
  case ATMGR:  Print_GSM("AT+CMGR=1\r");  break;    //������ ��� �
  case ATCPOWD: Print_GSM("AT+CPOWD=1\r");  break;    //PAWER OF
  case CSCLK: Print_GSM("AT+CSCLK=1\r");  break;    //Sleep  AT+CSCLK=1
  case CGNSTST:  Print_GSM("AT+CGNSTST=1\r");  break;    //RESET GSM
  case ATCPIN: Print_GSM("AT+CPIN?\r");  break;       //�������� �������� ������
  case ATCMGDA: Print_GSM("AT+CMGD=1,4\r");  break;       //�������� �� ���
  case CNETLIGHT: Print_GSM("AT+CNETLIGHT=0\r");  break;       //��������� LED ��������� status work
 //case CFUN1: Print_GSM("AT+CFUN=1\r");  break;       //��������� LED ��������� ��������
case   ATCMGS:
	Cauntidx = 0;
   for(char i = 0; !(Strin[i]==0); )
   {StringSMS[Cauntidx++] = Strin[i++] ; }
     StringSMS[Cauntidx++] ='"';
      for(char i = 0; !(SMS.NambePhon[i]==0); )
   { StringSMS[Cauntidx++] = SMS.NambePhon[i++] ; }
     StringSMS[Cauntidx++] ='"';
     StringSMS[Cauntidx++] ='\r';

////////////������� � ��������///////////////
       /// for(char i = 0; !( SMS.TextWRid[i]==0); )
   //{ StringSMS[idx++] = SMS.TextWRid[i++] ; }
   //  StringSMS[idx++] =0x1A;
    ////////////////////
     StringSMS[Cauntidx++] =0;
    Print_GSM(StringSMS);
  break;

  case   SMSSEND:
	  Cauntidx = 0;

   for(char i = 0; !( SMS.TextWRid[i]==0); )
   { StringSMS[Cauntidx++] = SMS.TextWRid[i++] ; }
     StringSMS[Cauntidx++] =0x1A;
     StringSMS[Cauntidx++] =0;
     Print_GSM(StringSMS);
    break;

  //   gps ////
  case ATCGNSPWR1: Print_GSM("AT+CGNSPWR=1\r");  break;    //�������� GPS
  case ATCGNSPWR0: Print_GSM("AT+CGNSPWR=0\r");  break;    //�������� GPS
  case ATCGNSINF: Print_GSM("AT+CGNSINF\r");    break;    //������ GPS
 }
   }
  }
//AT+CSCLK=1 (GPS power up)
//AT+ CGNSTST =1 (GPS reset)
///////////////////////////////////////



static char ComandWrit[10];



void Programa(char comand){

  if((ERRORSTATUS>9)||(ERRORAT>30)){
   COMANDA = CSCLK;
   delay (4000);
   SlipGSM=0;
   Seep_ON();
   Standby(); }
   delay (2000);
if((Instal_GSN_GPS==1)){
	Cauntidx=0;
 // SMSDT=STATUS;
 delay (3000);
if(SMSDT== ATCBC){
  COMANDA = ATCBC; //����� ������
   delay (4000);
  COMANDA = ATCSQ; // //������ GSM
  delay (6000);
 SMS.TextWRid[0]='B';
 SMS.TextWRid[1]='A';
 SMS.TextWRid[2]='T';
 SMS.TextWRid[3]=GSM.BAT_PERCENT[0];
 SMS.TextWRid[4]=GSM.BAT_PERCENT[1];
 SMS.TextWRid[5]='%';
 SMS.TextWRid[6]=' ';
 SMS.TextWRid[7]=' ';
 SMS.TextWRid[8]=' ';
 SMS.TextWRid[9] =GSM.BAT_V[0];
 SMS.TextWRid[10]=GSM.BAT_V[1];
 SMS.TextWRid[11]=GSM.BAT_V[2];
 SMS.TextWRid[12]=GSM.BAT_V[3];
 SMS.TextWRid[13]='m';
 SMS.TextWRid[14]='V';
 SMS.TextWRid[15]=0;
 COMANDA=ATCMGS;
 SlipGSM=0;
 delay (10000);
  ///COMANDA = CFUN1 ;
   COMANDA = CSCLK;
      delay (4000);
        SlipGSM=0;
        Seep_ON();
     Standby();
}else{



if(SMSDT==STATUS){
	 GPS.DT.Latitude[0]=0;
     GPS.DT.Latitude[1]=0;
     GPS.DT.Latitude[2]=0;
     GPS.DT.Latitude[3]=0;
 for(int i = 0; i < 30; ++i)
 {
   delay (5000);
  COMANDA= ATCGNSINF;
  SEND=1;
  if((!(GPS.DT.Latitude[0]==0))&&(!(GPS.DT.Latitude[1]==0))&&(!(GPS.DT.Latitude[2]==0))&&(!(GPS.DT.Latitude[3]==0))){ break;}
  }
  PWRSENSOR_ON;
  delay (4000);
 COMANDA = ATCGNSPWR0;
  Read_HCSR04(GSM.Sensor);
  PWRSENSOR_OF;
   delay (4000);
     COMANDA = ATCBC; //����� ������
     delay (4000);
 SMS.TextWRid[Cauntidx++]='S';
 SMS.TextWRid[Cauntidx++]='E';
 SMS.TextWRid[Cauntidx++]='N';
 SMS.TextWRid[Cauntidx++]='S';
 SMS.TextWRid[Cauntidx++]='O';
 SMS.TextWRid[Cauntidx++]='R';
 SMS.TextWRid[Cauntidx++]=' ';

  for(int i = 0; i < 6; ++i)
 { if(GSM.Sensor[i]==0){break;}else
 {SMS.TextWRid[Cauntidx++] = GSM.Sensor[i];}}
 SMS.TextWRid[Cauntidx++]=' ';
 SMS.TextWRid[Cauntidx++]=' ';

 SMS.TextWRid[Cauntidx++]='G';
 SMS.TextWRid[Cauntidx++]='P';
 SMS.TextWRid[Cauntidx++]='S';
 SMS.TextWRid[Cauntidx++]=' ';
 for(int i = 0; i < 10; ++i)
 { if(GPS.DT.Latitude[i]==0){break;}else
 {SMS.TextWRid[Cauntidx++] = GPS.DT.Latitude[i];}}
 SMS.TextWRid[Cauntidx++]=' ';
 SMS.TextWRid[Cauntidx++]=' ';
  for(int i = 0; i < 11; ++i)
 { if(GPS.DT.Longitude[i]==0){break;}else
 {SMS.TextWRid[Cauntidx++] = GPS.DT.Longitude[i];}}
  SMS.TextWRid[Cauntidx++]=' ';
  SMS.TextWRid[Cauntidx++]='B';
 SMS.TextWRid[Cauntidx++]='A';
 SMS.TextWRid[Cauntidx++]='T';
 SMS.TextWRid[Cauntidx++]=GSM.BAT_PERCENT[0];
 SMS.TextWRid[Cauntidx++]=GSM.BAT_PERCENT[1];
 SMS.TextWRid[Cauntidx++]='%';
 SMS.TextWRid[Cauntidx++]=' ';
 SMS.TextWRid[Cauntidx++]=' ';
 SMS.TextWRid[Cauntidx++]=' ';
 SMS.TextWRid[Cauntidx++] =GSM.BAT_V[0];
 SMS.TextWRid[Cauntidx++]=GSM.BAT_V[1];
 SMS.TextWRid[Cauntidx++]=GSM.BAT_V[2];
 SMS.TextWRid[Cauntidx++]=GSM.BAT_V[3];
 SMS.TextWRid[Cauntidx++]='m';
 SMS.TextWRid[Cauntidx++]='V';

 SMS.TextWRid[Cauntidx++]=0;
COMANDA=ATCMGS;
 SlipGSM=0;
delay (10000);
 ///COMANDA = CFUN1 ;
   COMANDA = CSCLK;
      delay (4000);
        SlipGSM=0;
        Seep_ON();
     Standby();
}else{
  if(SMSDT== ERROR_COMAND){
 SMS.TextWRid[0]='E';
 SMS.TextWRid[1]='R';
 SMS.TextWRid[2]='R';
 SMS.TextWRid[3]='O';
 SMS.TextWRid[4]='R';
 SMS.TextWRid[5]=' ';
 SMS.TextWRid[6]='C';
 SMS.TextWRid[7]='O';
 SMS.TextWRid[8]='M';
 SMS.TextWRid[9]='M';
 SMS.TextWRid[10]='A';
 SMS.TextWRid[11]='N';
 SMS.TextWRid[12]='D';
 SMS.TextWRid[13]='!';
 SMS.TextWRid[14]=0;
 COMANDA=ATCMGS;
 SlipGSM=0;
 delay (10000);

 ///COMANDA = CFUN1 ;
   COMANDA = CSCLK;
      delay (4000);
        SlipGSM=0;
        Seep_ON();
     Standby();
  }


  else{

 if(SlipGSM>=2) {
   COMANDA = CSCLK;
      delay (4000);
        SlipGSM=0;
        Seep_ON();
     Standby();

 }else{

SlipGSM++;COMANDA = ATMGR; SEND=1; }}}}

SMSDT=0;}}





void delayWritCom (char comand){
for(int i = 0; i < 9; ++i)
{ if( ComandWrit[i]==0){ComandWrit[i]=comand;  break;}}
}










/*****************************************************************************************/
/*****************************************************************************************/
/***********--------  ������ � �Ѳ� UART    -----------************************/
/*****************************************************************************************/

/******------    ��������� ���� USART1    -------**********/
void ReadUART(char comand){
    //if((USART1->SR & USART_SR_RXNE)){ Buf.RX[Buf.LongRX++]=USART1->DR; Buf.Timeout=1;}
   //USART1->SR &= ~USART_SR_RXNE;
   //Buf.Timeout=1;
}



void ReadGSM(char comand){

  if( Buf.Timeout>=1){ Buf.Timeout++;}

  if( Buf.Timeout>=100){
     Buf.Timeout=0;
      CantSmsOK=0;
   UsbWritCDM  (Buf.RX,Buf.LongRX);

 if((Buf.RX[0]=='A')&&(Buf.RX[1]=='T')&& (Buf.RX[2]=='\r')){
   COMANDA=ATE0; }else{

 if((Buf.RX[0]=='A')&&(Buf.RX[1]=='T')&&(Buf.RX[2]=='E')&&(Buf.RX[3]=='0')&& (Buf.RX[4]=='\r')){
   COMANDA=ATE0; }else{

       //   ��������� � �����  GSM 1.//
 if((Buf.RX[2]=='O')&&(Buf.RX[3]=='K')&&(COMANDA==ATE0)){
   COMANDA=ATCREG;}else{

  //   ��������� � �����  GSM 1.//
 if((Buf.RX[2]=='O')&&(Buf.RX[3]=='K')&&(COMANDA==AT)){
   COMANDA=ATCREG;}else{

 //  ��������  ��������� � �����  GSM  2.//
 if((Buf.RX[2]=='+')&&(Buf.RX[3]=='C')&& (Buf.RX[4]=='R')&&(Buf.RX[5]=='E')&&(Buf.RX[6]=='G')&&(Buf.RX[7]==':')){
   GSM.REG =Buf.RX[11]; COMANDA=ATCMGF;}else{
//-------------------------------------------------------------------------------------//

   //   �������� GPS    3.///
  if((Buf.RX[2]=='O')&&(Buf.RX[3]=='K')&&(COMANDA==ATCMGF)){
   GSM.LINK[0] =Buf.RX[8]; GSM.LINK[1] =Buf.RX[9]; COMANDA=ATCGNSPWR1;   }else{
//-----------------------------------------------------------------------------------------//

       //  GPS ���������   4.///
 if((Buf.RX[2]=='O')&&(Buf.RX[3]=='K')&&(COMANDA==ATCGNSPWR1)){
   Buf.LongRX=0; Instal_GSN_GPS=1;  }else{

    //  ������� ���� ��� � ������   ///
 if((Buf.RX[2]=='+')&&(Buf.RX[3]=='C')&& (Buf.RX[4]=='M')&&(Buf.RX[5]=='T')&&(Buf.RX[6]=='I')&&(Buf.RX[7]==':')){
     SMS.NambeRead=Buf.RX[14]; COMANDA=ATMGR;}else{
//------------------------------------------------------------------------------------------//

     //  SMS ����������   ///
 if((Buf.RX[2]=='+')&&(Buf.RX[3]=='C')&& (Buf.RX[4]=='M')&&(Buf.RX[5]=='G')&&(Buf.RX[6]=='S')&&(Buf.RX[7]==':')){
      ATcomand(ATMGD);}else{
//------------------------------------------------------------------------------------------//

   //   ������ ����� GPS    ///
 if((Buf.RX[2]=='+')&&(Buf.RX[3]=='C')&& (Buf.RX[4]=='G')&&(Buf.RX[5]=='N')&&(Buf.RX[6]=='S')&&(Buf.RX[7]=='I')&&(Buf.RX[8]=='N')&&(Buf.RX[9]=='F')&&(Buf.RX[10]==':')){
    int idx=0;
    int IdxChar=0;
   for(int i = 0; i< Buf.LongRX; ++i){
   if(Buf.RX[i]==0){break;}
   if(Buf.RX[i]==','){idx=0; IdxChar++;}else{

     switch(IdxChar){
      case 1: GPS.DT.FixStatus =Buf.RX[i];   break;
      case 2: GPS.DT.DateTime [idx++]=Buf.RX[i];  break;
      case 3: GPS.DT.Latitude [idx++]=Buf.RX[i];  break;
      case 4: GPS.DT.Longitude[idx++]=Buf.RX[i];  break;
      case 5: GPS.DT.Altitude [idx++]=Buf.RX[i];  break;
      case 6: GPS.DT.Speed    [idx++]=Buf.RX[i];  break;
      case 7: GPS.DT.Course   [idx++]=Buf.RX[i];  break;
     };
   }}
   Buf.LongRX=0;
   GPS.DT.VPA[0]=0;
   }else{

 //------------------------------------------------------------------------------------------//
 //   IMEI   //
 //if(COMANDA==ATGSN){ Buf.LongRX=0;for(int i = 0; i < 15; ++i){GSM.IM[i]=Buf.RX[i+2];}  Buf.LongRX=0;for(int i = 0; i < 30; ++i){ Buf.RX[i]=0;}}
 //---------------------------------------------------------------------------------//

  //   ������ GSM     ///
  if((Buf.RX[2]=='+')&&(Buf.RX[3]=='C')&& (Buf.RX[4]=='S')&&(Buf.RX[5]=='Q')&&(Buf.RX[6]==':')){
    GSM.LINK[0] =Buf.RX[8]; GSM.LINK[1] =Buf.RX[9];}else{
//------------------------------------------------------------------------------------------//

  //   ����� ������  //
 if((Buf.RX[2]=='+')&&(Buf.RX[3]=='C')&& (Buf.RX[4]=='B')&&(Buf.RX[5]=='C')&& (Buf.RX[6]==':')){
   GSM.BAT_PERCENT[0] =Buf.RX[10];
   GSM.BAT_PERCENT[1] =Buf.RX[11];
   GSM.BAT_V[0] = Buf.RX[13];
   GSM.BAT_V[1] = Buf.RX[14];
   GSM.BAT_V[2] = Buf.RX[15];
   GSM.BAT_V[3] = Buf.RX[16];}else{
 //------------------------------------------------------------------------------------//
 //�������� ���
 if((COMANDA==ATCMGS)&&(Buf.RX[2]=='>')){ COMANDA=SMSSEND;}else{

  //   SMS ������ ��� ///
   if((COMANDA==ATMGR)&&(Buf.RX[2]=='O')&&(Buf.RX[3]=='K')){
  //COMANDA = ATMGR;
   }else{

   if((Buf.RX[2]=='+')&&(Buf.RX[3]=='C')&&(Buf.RX[4]=='M')&&(Buf.RX[5]=='G')&&(Buf.RX[6]=='R')&&(Buf.RX[7]==':')) {
    int phn = 0;
     for(char i = 0 ;i < 30; ++i){
    if((Buf.RX[i]=='"')){phn++; if(phn>=3){phn=i+1; break;}}
    else{SMS.NambePhon[i]=0; }}

   for(char i = 0 ;i < 19; ++i){
    if(!(Buf.RX[i+phn]=='"')){SMS.NambePhon[i]=Buf.RX[i+phn];}
    else{SMS.NambePhon[i]=0; break;}}

    char startSMS=0;
    char SMSidx=0;
   for(char i = 0; i < 200; ++i){
    if((Buf.RX[i+phn-1]=='\r')&&(Buf.RX[i+phn]=='\n'))
    {startSMS=1;}
    if(startSMS==1)
    { SMS.TextRead[SMSidx++]=Buf.RX[i+phn+1];
    if((Buf.RX[i+phn]=='\r')&&(Buf.RX[i+phn+1]=='\n')){SMS.TextRead[SMSidx-1]=0;SMS.TextRead[SMSidx-2]=0; SMS.TextRead[SMSidx++]=0;break; }}
   } COMANDA=ATMGD;   ReadMessage(); }else{

 if((Buf.RX[2]=='E')&&(Buf.RX[3]=='R')&&(Buf.RX[4]=='R')&&(Buf.RX[5]=='O')&&(Buf.RX[6]=='R')&& (Buf.RX[7]=='\r')){ ERRORSTATUS++;
   if(ATCMGF==COMANDA){ CantSmsOK=6; COMANDA=ATCMGF;}else{ COMANDA=AT; Instal_GSN_GPS=0; }}else{

 //   SMS �������� �� �������� ///
 //if(COMANDA==ATMGR){ ATcomand(ATCMGDA);}
   }}}}}}}}}}}}}}}}
 for(int i = 0; i< Buf.LongRX; ++i){Buf.RX[i]=0;} Buf.LongRX=0;
   }}


/*
0.����� �����
1.�����
2.���������
0.����� �����
3.�������
3.�������
*/
