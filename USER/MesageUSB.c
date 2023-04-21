
#include "usart.h"


UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;


uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/* USER CODE BEGIN Includes */
//--------------  UART -------
//static unsigned char TxData[500];
//static unsigned char RxDataSize;

static char           SizeGSM;
static unsigned char RxDataGSM[256];

static char            SizeGPS;
 unsigned char RxDataGPS[300];




static char statusDMA;

const  unsigned char ReceivSize= 100;









void ReadComand(char * Bufer,int Leng){


 /// HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,1);
//	HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,ReceivSize);
  HAL_UART_Transmit_DMA (&huart1  ,Bufer,Leng);



  //CDC_Transmit_FS(Bufer, Leng);



}



void UsbWritCDM  (unsigned char *data, char lengh){
   //CDC_Transmit_FS(data,lengh);
};








//--------------  UART -------


void Print_GSM(char*data){
//HAL_UART_Transmit_DMA (&huart1  ,data,  sizeof(data));
}





  int GPS_Read(char *data);
void SendToUSB(void){

  if((SizeGSM !=0) &&(statusDMA==0)){
	  statusDMA=1;
      CDC_Transmit_FS(RxDataGSM,SizeGSM);
      SizeGSM=0;
  }

  if((SizeGPS !=0) &&(statusDMA==0)){
	  statusDMA=1;
      GPS_Read(RxDataGPS);
      SizeGSM=0;
  }





  statusDMA=0;

}


void SendUSB_DT(char *Bufer, short Leng){
	SizeGPS=0;
	for (short var = 0;  var < Leng ;var++ ) {
	  RxDataGSM[SizeGSM++] = Bufer[var];
	                          } }






 void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
      HAL_StatusTypeDef  error;
      unsigned char RxDataBuf[256];
      statusDMA=1;

      if(huart ==&huart1 ){

          error = HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxDataBuf,Size);
                           if( error == HAL_OK){
                            for (short var = 0;  var < Size; ) {RxDataGSM[SizeGSM++] = RxDataBuf[var++];}
                            error = HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxDataBuf,Size);
                           }else{

                         if( error ==HAL_BUSY){HAL_GPIO_WritePin(GPIOC, LED_WORK_Pin, GPIO_PIN_RESET);}else{
                          if( error ==HAL_ERROR){
                           MX_USART1_UART_Init();
           error =  HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxDataGSM,ReceivSize);
                          }}}


      }else{
                if(huart==&huart2 ){
                error = HAL_UARTEx_ReceiveToIdle_DMA(&huart2 ,RxDataBuf,255);
                                 if( error == HAL_OK){
                                  for (short var = 0;  var < Size; ) {
                                        RxDataGPS[SizeGPS++] = RxDataBuf[var++];
                                        RxDataBuf[var-1]=0; }
                                  GPS_Read(RxDataGPS);
                                 // CDC_Transmit_FS(RxDataGPS,SizeGPS);
                                  SizeGSM=0;


                                  error = HAL_UARTEx_ReceiveToIdle_DMA(&huart2 ,RxDataBuf,255);}else{
                               if( error ==HAL_BUSY){ HAL_GPIO_WritePin(GPIOC, LED_WORK_Pin, GPIO_PIN_RESET);}else{
                                if( error ==HAL_ERROR){
                                 MX_USART1_UART_Init();
                 error =  HAL_UARTEx_ReceiveToIdle_DMA(&huart2 ,RxDataGPS,255);
                                }}}  }}
                                 statusDMA=0;
}


void  ReadUart(void){
	        HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxDataGSM, ReceivSize);
	        HAL_UARTEx_ReceiveToIdle_DMA(&huart2 ,RxDataGPS, ReceivSize);
}
