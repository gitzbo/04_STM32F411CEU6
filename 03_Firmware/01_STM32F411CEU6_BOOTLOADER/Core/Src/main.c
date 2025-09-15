/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "main.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_driver_led.h"
#include "bsp_driver_flash.h"
#include "bsp_driver_key.h"

#include "app_adapter_led.h"
#include "app_adapter_flash.h"
#include "app_adapter_key.h"

#include "app_updata.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
static void _app_key_callback(const bsp_driver_key_object_t *dev);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void _app_key_callback(const bsp_driver_key_object_t *dev)
{
  bsp_driver_led_object_t blue_led = {0};
  bsp_driver_led_get_object(0, &blue_led);
	
  switch(dev->key_state.key_state) {
    case KEY_DRIVER_PRESS_EVENT: {
      break;
    }
    case KEY_DRIVER_RELEASE_EVENT: {
      break;
    }
    case KEY_DRIVER_SHORT_PRESS_EVENT: {
	  bsp_driver_led_on(&blue_led);
	  HAL_Delay(100);
	  bsp_driver_led_off(&blue_led);
	  HAL_Delay(100);
      break;
    }
    case KEY_DRIVER_LONG_PRESS_EVENT: {
      break;
    }
    case KEY_DRIVER_DOUBLE_SHORT_PRESS_EVENT: {
      break;
    }
    case KEY_DRIVER_CONTINUE_PRESS_EVENT: {
      break;
    }
    default:
      break;
  }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  SystemInit();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  /**> 启动独立看门狗 */
  app_adapter_led_register();                   /**< 将实例注册到led驱动中 */
  app_adapter_key_register(_app_key_callback);  /**< 将实例注册到key驱动中 */
  app_adapter_flash_register();					/**< 将实例注册到flash驱动中 */
  
  bsp_driver_led_object_t blue_led = {0};		/**< 对象指针 */
  bsp_driver_led_get_object(0, &blue_led);      /**< 获取目标对象 */
  bsp_driver_led_init(&blue_led);               /**< 目标对象初始化 */
  
  bsp_driver_key_object_t user_key = {0};		/**< 对象指针 */
  bsp_driver_key_get_object(0, &user_key);		/**< 获取目标对象 */
  bsp_driver_key_init(&user_key);				/**< 目标对象初始化 */
  
  bsp_driver_flash_object_t in_flash = {0};		/**< 对象指针 */
  bsp_driver_flash_get_object(0, &in_flash);	/**< 获取目标对象 */
  bsp_driver_flash_init(&in_flash);				/**< 目标对象初始化 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	  
	/**< 1.检测强制升级信号 */
		
	  
	/**< 2.检测计划升级信号 */
	  

	/**< 3.跳转到APPLIATION中执行 */
	  app_updata_jump_app();

	HAL_Delay(1000);
	  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
