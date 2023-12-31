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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"

#include <stdio.h>
#include <sys/lock.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 256 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
	if (!stdout->_lock) {
		__lock_init_recursive(stdout->_lock);
	}
	if (!stdin->_lock) {
		__lock_init_recursive(stdin->_lock);
	}
	if (!stderr->_lock) {
		__lock_init_recursive(stderr->_lock);
	}
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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  static char* str =
		  "1234567890"
		  "1234567890"
		  "1234567890"
		  "1234567890"
		  "1234567890"
		  "1234567890"
		  "1234567890";
  osDelay(500);
	if (!stdout->_lock) {
		__lock_init_recursive(stdout->_lock);
	}
	if (!stdin->_lock) {
		__lock_init_recursive(stdin->_lock);
	}
	if (!stderr->_lock) {
		__lock_init_recursive(stderr->_lock);
	}

  printf ("hello world!\n");

  /* Infinite loop */
  for(;;)
  {
    unsigned int rc;

    rc = CDC_Transmit_FS((uint8_t*) str, 63);
    printf ("Transmit len = 63, rc = %u\n", rc);
    osDelay(500);
    rc = CDC_Transmit_FS((uint8_t*) "xx\r\n", 4);
    printf ("Transmit len = 4, rc = %u\n", rc);

    osDelay(2000);
    rc = CDC_Transmit_FS((uint8_t*) str, 64);
    printf ("Transmit len = 64, rc = %u\n", rc);
    osDelay(500);
    rc = CDC_Transmit_FS((uint8_t*) "xx\r\n", 4);
    printf ("Transmit len = 4, rc = %u\n", rc);

    osDelay(2000);
    rc = CDC_Transmit_FS((uint8_t*) str, 64);
    printf ("Transmit len = 64, rc = %u\n", rc);
    rc = USBD_BUSY;
    while (rc == USBD_BUSY) {
        osDelay(1);
    	rc = CDC_Transmit_FS((uint8_t*) str, 0);
    	printf ("Transmit len = 0, rc = %u\n", rc);
    }
    osDelay(500);
    rc = CDC_Transmit_FS((uint8_t*) "xx\r\n", 4);
    printf ("Transmit len = 4, rc = %u\n", rc);

    osDelay(2000);
    rc = CDC_Transmit_FS((uint8_t*) str, 65);
    printf ("Transmit len = 65, rc = %u\n", rc);
    osDelay(500);
    rc = CDC_Transmit_FS((uint8_t*) "xx\r\n", 4);
    printf ("Transmit len = 4, rc = %u\n", rc);

    osDelay(5000);

  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

