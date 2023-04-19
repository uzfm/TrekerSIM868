
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
static unsigned char RxData[500];
//static unsigned char RxDataSize;



const  unsigned char ReceivSize= 100;








void ReadComand(char * Bufer,int Leng){


  HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,1);

  HAL_UART_Transmit_DMA (&huart1  ,Bufer,Leng);



  //CDC_Transmit_FS(Bufer, Leng);



}


//--------------  UART -------




 void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
      HAL_StatusTypeDef  error;

            error =  HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,Size);

                                 if( error == HAL_OK){

                                    CDC_Transmit_FS(RxData,ReceivSize);


                                 }else{
                                 while( error !=HAL_OK){
                                 MX_USART1_UART_Init();
                                 error = HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,ReceivSize);
                                            CDC_Transmit_FS(RxData,Size);
                                 }
                                while( error !=HAL_OK){
                                 MX_USART1_UART_Init();
                                 error =  HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData,ReceivSize);
                                 CDC_Transmit_FS(RxData,Size);}}


}


 HAL_StatusTypeDef  ReadUart(void){ return HAL_UARTEx_ReceiveToIdle_DMA(&huart1 ,RxData, ReceivSize);}
