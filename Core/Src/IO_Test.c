/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : IO_Test.c
  * @brief          : GPIO testing function with precise timing using TIM1
  ******************************************************************************
  * @attention
  *
  * This function tests GPIO pins by toggling each one 1 million times with
  * 1 microsecond delays between toggles, using TIM1's counter for timing.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "IO_Test.h"
#include "stm32l4xx_hal.h"

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} GPIO_Pin_t;

/* Private define ------------------------------------------------------------*/
#define NUM_TEST_GPIOS 13
#define TOGGLES_PER_GPIO 1000000UL

/* Private variables ---------------------------------------------------------*/
static const GPIO_Pin_t test_gpios[NUM_TEST_GPIOS] = {
    {GPIOF, GPIO_PIN_12},  // PF12
    {GPIOD, GPIO_PIN_15},  // PD15
    {GPIOF, GPIO_PIN_15},  // PF15
    {GPIOE, GPIO_PIN_13},  // PE13
    {GPIOF, GPIO_PIN_14},  // PF14
    {GPIOE, GPIO_PIN_11},  // PE11
    {GPIOE, GPIO_PIN_9},   // PE9
    {GPIOF, GPIO_PIN_13},  // PF13
    {GPIOA, GPIO_PIN_3},   // PA3
    {GPIOC, GPIO_PIN_0},   // PC0
    {GPIOC, GPIO_PIN_3},   // PC3
    {GPIOC, GPIO_PIN_1},   // PC1
    {GPIOC, GPIO_PIN_4}    // PC4
};

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Delay function using TIM1 counter for microsecond precision
  * @param  microseconds: Number of microseconds to delay
  * @retval None
  * @note   TIM1 is configured with 1 MHz clock (1 count = 1 microsecond)
  */
void delay_us_tim1(uint32_t microseconds)
{
    uint32_t start = __HAL_TIM_GET_COUNTER(&htim1);
    uint32_t target_ticks = microseconds;
    uint32_t elapsed = 0;

    /* Wait until the desired number of microseconds have elapsed */
    while (elapsed < target_ticks) {
        uint32_t current = __HAL_TIM_GET_COUNTER(&htim1);

        /* Handle counter overflow (16-bit counter wraps at 65535) */
        if (current >= start) {
            elapsed = current - start;
        } else {
            /* Counter has wrapped around */
            elapsed = (0xFFFF - start) + current + 1;
        }
    }
}

/**
  * @brief  Test function that toggles each GPIO 1 million times
  * @param  None
  * @retval None
  * @note   Tests GPIOs one by one with 1 us delay between toggles
  */
void IO_Test(void)
{
    uint32_t i, j;

    /* Start TIM1 counter for timing */
    HAL_TIM_Base_Start(&htim1);

    /* Test each GPIO sequentially */
    for (i = 0; i < NUM_TEST_GPIOS; i++) {
    	printf("%d ", i);
        /* Toggle current GPIO 1 million times */
        for (j = 0; j < TOGGLES_PER_GPIO; j++) {
            /* Toggle the GPIO pin */
            HAL_GPIO_TogglePin(test_gpios[i].port, test_gpios[i].pin);

            /* Wait 1 microsecond */
            delay_us_tim1(1);
        }
    }

    /* Stop TIM1 counter after testing is complete */
    HAL_TIM_Base_Stop(&htim1);
}
