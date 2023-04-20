
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
static unsigned char RxData[300];
//static unsigned char RxDataSize;


<<<<<<< HEAD
static char statusDMA;
const  unsigned char ReceivSize = 50;
=======

const  unsigned char ReceivSize= 100;
>>>>>>> branch 'master' of https://github.com/uzfm/TrekerSIM868.git








void ReadComand(char * Bufer,int Leng){


 /// HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,1);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,ReceivSize);
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




static int SizeRxData;

void SendToUSB(void){

  if((SizeRxData !=0) &&(statusDMA==0)){
	  statusDMA=1;
      CDC_Transmit_FS(RxData,SizeRxData);
      SizeRxData=0;
  }
  statusDMA=0;

}



 void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
      HAL_StatusTypeDef  error;
      unsigned char RxDataBuf[100];
      while (statusDMA==1);
      statusDMA=1;
                error = HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxDataBuf,Size);

                                 if( error == HAL_OK){
                                  for (short var = 0;  var < Size; ) {
                                	   if(SizeRxData>=300){break;}
                                        RxData[SizeRxData++] =
                                        		RxDataBuf[var++];
                                  }




                                 }else{

                               if( error ==HAL_BUSY){

                                 for (short var = 0;  var < Size;) {
                                	 if(SizeRxData>=300){break;}
                                	 RxData[SizeRxData++] = RxDataBuf[var++];
                                 }


                                 }
                                while( error !=HAL_OK){
                                 MX_USART1_UART_Init();
                                 error =  HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,ReceivSize);
                                // CDC_Transmit_FS(RxData,Size);
                                }}

                                 statusDMA=0;
}


 HAL_StatusTypeDef  ReadUart(void){ return HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData, ReceivSize);}
