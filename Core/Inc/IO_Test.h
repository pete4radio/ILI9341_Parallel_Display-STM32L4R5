/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : IO_Test.h
  * @brief          : Header for IO_Test.c file.
  *                   This file contains the function declaration for GPIO
  *                   testing using TIM1 for precise timing.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IO_TEST_H
#define __IO_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Function prototypes -------------------------------------------------------*/
void IO_Test(void);
void delay_us_tim1(uint32_t microseconds);

#ifdef __cplusplus
}
#endif

#endif /* __IO_TEST_H */
