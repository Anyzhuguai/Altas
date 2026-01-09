/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pid.h"
#include "bsp_IR_i2c.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


// 0 = 右转, 1 = 左转
int turn_direction = 1; 

int speed_L = 150;
int speed_R = 150;
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
uint8_t ir_x1,ir_x2,ir_x3,ir_x4,ir_x5,ir_x6,ir_x7,ir_x8;

int real_speed_L = 0;
int real_speed_R = 0;
int pwm_L = 0;
int pwm_R = 0;
int target_L = 0;
int target_R = 0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); // PA9
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3); // PA10
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	printf("Pelase wait!\r\n");
  HAL_Delay(3000);//等待模块稳定
//  set_adjust_mode(1);
//  HAL_Delay(500);
//
//  set_adjust_mode(0);
//  HAL_Delay(500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		deal_IRdata(&ir_x1,&ir_x2,&ir_x3,&ir_x4,&ir_x5,&ir_x6,&ir_x7,&ir_x8);
//	  printf("x1:%d,x2:%d,x3:%d,x4:%d,x5:%d,x6:%d,x7:%d,x8:%d\r\n",ir_x1,ir_x2,ir_x3,ir_x4,ir_x5,ir_x6,ir_x7,ir_x8);
//		Motor_Set(300, 300); // 强制往前走
//	  HAL_Delay(300);
		
		deal_IRdata(&ir_x1,&ir_x2,&ir_x3,&ir_x4,&ir_x5,&ir_x6,&ir_x7,&ir_x8);
		Read_Encoder(&real_speed_L, &real_speed_R);
if (Is_Horizontal_Line(ir_x1, ir_x2, ir_x3, ir_x4, ir_x5, ir_x6, ir_x7, ir_x8))
    {
        // 盲走冲线 - 闭环控制版
        // 给他一个固定的目标速度，PID会自动调整PWM去克服阻力
        int blind_speed = 100; // 目标脉冲数
        
        // 简单粗暴点：冲线时可以直接给固定PWM，或者用PID
        // 这里演示用PID保持直行
        // 重置积分，防止之前积累的误差导致冲线歪斜
        error_sum_L = 0;
        error_sum_R = 0; 
        
        // 冲线循环 (比如冲 260ms)
        // 可以在这里用一个小循环，或者用 delay + 简单的 Motor_Set
        Motor_Set(300, 300); // 冲线建议直接给大 PWM 比较稳，PID 反应有时不够快
        HAL_Delay(260);
        
        // 停车再看
        Motor_Set(0, 0);
        deal_IRdata(&ir_x1,&ir_x2,&ir_x3,&ir_x4,&ir_x5,&ir_x6,&ir_x7,&ir_x8);
        
        // 判断逻辑 (保持你的原样)
        if (ir_x4 == 0 || ir_x5 == 0 ||(ir_x2 == 0 && ir_x6 == 0)) {
             // 十字路口：什么都不做，继续走
        }
        else {
             // 丁字路口：转向
             if (turn_direction == 0) { // 右转
                 Motor_Set(-300, 300); // 转向直接给 PWM 比较干脆
                 HAL_Delay(350);
             } else { // 左转
                 Motor_Set(300, -300);
                 HAL_Delay(350);
             }
             // 转弯后清除 PID 历史，防止暴冲
             error_sum_L = 0;
             error_sum_R = 0;
             last_error = 0;
        }
    }
    
    // 4. 循迹 PID 计算 (计算偏差)
    error = Calc_Error(ir_x1, ir_x2, ir_x3, ir_x4, ir_x5, ir_x6, ir_x7, ir_x8);
    float pid_turn_val = (Kp * error) + (Kd * (error - last_error));
    last_error = error;

    // 5. 计算左右轮的【目标速度】 (不是PWM了！)
    // base_speed 应该是你希望编码器每 10ms 读到的脉冲数，比如 50~150
    target_L = base_speed + (int)pid_turn_val;
    target_R = base_speed - (int)pid_turn_val;

    // 6. 速度闭环 PID 计算 (核心修改)
    // 根据 目标速度 和 真实速度，算出来到底要给多少 PWM
    pwm_L = Speed_PID_Calc(target_L, real_speed_L, &error_sum_L);
    pwm_R = Speed_PID_Calc(target_R, real_speed_R, &error_sum_R);

    // 7. 最终驱动电机
    Motor_Set(pwm_L, pwm_R);

    // 8. 循环频率控制 (采样时间)
    // 这个延时非常重要！因为它决定了编码器积累了多少脉冲。
    // 如果延时太短，脉冲数很少，速度波动大；太长，控制迟钝。
    // 推荐 10ms
    HAL_Delay(10); 
		
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
