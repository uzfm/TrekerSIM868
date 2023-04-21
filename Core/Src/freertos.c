/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"



#define  AT       1
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId GPSHandle;
osThreadId GSMHandle;
osThreadId MasageHandle;
osThreadId mySTATUSHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartGPS(void const * argument);
void StartGSM(void const * argument);
void StartMasage(void const * argument);
void StartSTATUS(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of GPS */
  osThreadDef(GPS, StartGPS, osPriorityNormal, 0, 128);
  GPSHandle = osThreadCreate(osThread(GPS), NULL);

  /* definition and creation of GSM */
  osThreadDef(GSM, StartGSM, osPriorityIdle, 0, 128);
  GSMHandle = osThreadCreate(osThread(GSM), NULL);

  /* definition and creation of Masage */
  osThreadDef(Masage, StartMasage, osPriorityIdle, 0, 128);
  MasageHandle = osThreadCreate(osThread(Masage), NULL);

  /* definition and creation of mySTATUS */
  osThreadDef(mySTATUS, StartSTATUS, osPriorityIdle, 0, 128);
  mySTATUSHandle = osThreadCreate(osThread(mySTATUS), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartGPS */
/**
  * @brief  Function implementing the GPS thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartGPS */
void StartGPS(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartGPS */
  /* Infinite loop */
  for(;;)
  {
    osDelay(500);
    HAL_GPIO_WritePin(GPIOC, LED_WORK_Pin, GPIO_PIN_RESET);
    osDelay(500);
    HAL_GPIO_WritePin(GPIOC, LED_WORK_Pin, GPIO_PIN_SET);
  }
  /* USER CODE END StartGPS */
}

/* USER CODE BEGIN Header_StartGSM */
/**
* @brief Function implementing the GSM thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGSM */

    void ATcomand(char Comand);
void StartGSM(void const * argument)
{
  /* USER CODE BEGIN StartGSM */
  /* Infinite loop */
  for(;;){

   //ATcomand(AT);
   //HAL_GPIO_WritePin(GNSS_EN_GPIO_Port, GNSS_EN_Pin, GPIO_PIN_SET);

   // HAL_GPIO_WritePin(GNSS_EN_GPIO_Port, GNSS_EN_Pin, GPIO_PIN_RESET);
    //osDelay(5000);


  // ATcomand(AT);
   osDelay(2000);
   char get_coordinates( char* data1, struct Coordinates* coords);

    get_coordinates( "test",0);


  }
  /* USER CODE END StartGSM */
}

/* USER CODE BEGIN Header_StartMasage */
/**
* @brief Function implementing the Masage thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMasage */
void SendToUSB(void);

void StartMasage(void const * argument)
{
  /* USER CODE BEGIN StartMasage */
  /* Infinite loop */
  for(;;)
  {

    osDelay(1000);

    SendToUSB();

  }
  /* USER CODE END StartMasage */
}

/* USER CODE BEGIN Header_StartSTATUS */
/**
* @brief Function implementing the mySTATUS thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSTATUS */
void StartSTATUS(void const * argument)
{
  /* USER CODE BEGIN StartSTATUS */
  /* Infinite loop */
  for(;;)
  {

      osDelay(500);
      HAL_GPIO_WritePin(GPIOC, LED_WORK_Pin, GPIO_PIN_RESET);
      osDelay(500);
      HAL_GPIO_WritePin(GPIOC, LED_WORK_Pin, GPIO_PIN_SET);

  }
  /* USER CODE END StartSTATUS */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

