/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : stm32f3xx_hal_msp.c
 * Description        : This file provides code for the MSP Initialization
 *                      and de-Initialization codes.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
    /* USER CODE BEGIN MspInit 0 */

    /* USER CODE END MspInit 0 */

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    /* System interrupt init*/
    /* PendSV_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);

    /* USER CODE BEGIN MspInit 1 */

    /* USER CODE END MspInit 1 */
}

static uint32_t HAL_RCC_ADC12_CLK_ENABLED = 0;

/**
 * @brief ADC MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hadc: ADC handle pointer
 * @retval None
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    if (hadc->Instance == ADC1)
    {
        /* USER CODE BEGIN ADC1_MspInit 0 */

        /* USER CODE END ADC1_MspInit 0 */
        /* Peripheral clock enable */
        HAL_RCC_ADC12_CLK_ENABLED++;
        if (HAL_RCC_ADC12_CLK_ENABLED == 1)
        {
            __HAL_RCC_ADC12_CLK_ENABLE();
        }

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**ADC1 GPIO Configuration
        PC0     ------> ADC1_IN6
        PC1     ------> ADC1_IN7
        PC2     ------> ADC1_IN8
        PC3     ------> ADC1_IN9
        PA0     ------> ADC1_IN1
        PA2     ------> ADC1_IN3
        PA3     ------> ADC1_IN4
        */
        GPIO_InitStruct.Pin = IS_AUX1_AUX2_Pin | IS_AIR_SHDN_LV_PWR_Pin |
                              IS_DI_BL_DI_BR_Pin | IS_DI_FL_DI_FR_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin =
            VBAT_SENSE_Pin | CUR_SNS_DI_REAR_RHS_Pin | CUR_SNS_DI_REAR_LHS_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* USER CODE BEGIN ADC1_MspInit 1 */

        /* USER CODE END ADC1_MspInit 1 */
    }
    else if (hadc->Instance == ADC2)
    {
        /* USER CODE BEGIN ADC2_MspInit 0 */

        /* USER CODE END ADC2_MspInit 0 */
        /* Peripheral clock enable */
        HAL_RCC_ADC12_CLK_ENABLED++;
        if (HAL_RCC_ADC12_CLK_ENABLED == 1)
        {
            __HAL_RCC_ADC12_CLK_ENABLE();
        }

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**ADC2 GPIO Configuration
        PA5     ------> ADC2_IN2
        PA6     ------> ADC2_IN3
        PA7     ------> ADC2_IN4
        PC4     ------> ADC2_IN5
        PC5     ------> ADC2_IN11
        PB2     ------> ADC2_IN12
        */
        GPIO_InitStruct.Pin = CUR_SNS_DI_FRONT_RHS_Pin |
                              CUR_SNS_DI_FRONT_LHS_Pin | CUR_SNS_AUX2_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin  = CUR_SNS_AUX1_Pin | CUR_SNS_LVPWR_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin  = CUR_SNS_AIR_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(CUR_SNS_AIR_GPIO_Port, &GPIO_InitStruct);

        /* USER CODE BEGIN ADC2_MspInit 1 */

        /* USER CODE END ADC2_MspInit 1 */
    }
}

/**
 * @brief ADC MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hadc: ADC handle pointer
 * @retval None
 */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        /* USER CODE BEGIN ADC1_MspDeInit 0 */

        /* USER CODE END ADC1_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_ADC12_CLK_ENABLED--;
        if (HAL_RCC_ADC12_CLK_ENABLED == 0)
        {
            __HAL_RCC_ADC12_CLK_DISABLE();
        }

        /**ADC1 GPIO Configuration
        PC0     ------> ADC1_IN6
        PC1     ------> ADC1_IN7
        PC2     ------> ADC1_IN8
        PC3     ------> ADC1_IN9
        PA0     ------> ADC1_IN1
        PA2     ------> ADC1_IN3
        PA3     ------> ADC1_IN4
        */
        HAL_GPIO_DeInit(
            GPIOC, IS_AUX1_AUX2_Pin | IS_AIR_SHDN_LV_PWR_Pin |
                       IS_DI_BL_DI_BR_Pin | IS_DI_FL_DI_FR_Pin);

        HAL_GPIO_DeInit(
            GPIOA,
            VBAT_SENSE_Pin | CUR_SNS_DI_REAR_RHS_Pin | CUR_SNS_DI_REAR_LHS_Pin);

        /* USER CODE BEGIN ADC1_MspDeInit 1 */

        /* USER CODE END ADC1_MspDeInit 1 */
    }
    else if (hadc->Instance == ADC2)
    {
        /* USER CODE BEGIN ADC2_MspDeInit 0 */

        /* USER CODE END ADC2_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_ADC12_CLK_ENABLED--;
        if (HAL_RCC_ADC12_CLK_ENABLED == 0)
        {
            __HAL_RCC_ADC12_CLK_DISABLE();
        }

        /**ADC2 GPIO Configuration
        PA5     ------> ADC2_IN2
        PA6     ------> ADC2_IN3
        PA7     ------> ADC2_IN4
        PC4     ------> ADC2_IN5
        PC5     ------> ADC2_IN11
        PB2     ------> ADC2_IN12
        */
        HAL_GPIO_DeInit(
            GPIOA, CUR_SNS_DI_FRONT_RHS_Pin | CUR_SNS_DI_FRONT_LHS_Pin |
                       CUR_SNS_AUX2_Pin);

        HAL_GPIO_DeInit(GPIOC, CUR_SNS_AUX1_Pin | CUR_SNS_LVPWR_Pin);

        HAL_GPIO_DeInit(CUR_SNS_AIR_GPIO_Port, CUR_SNS_AIR_Pin);

        /* USER CODE BEGIN ADC2_MspDeInit 1 */

        /* USER CODE END ADC2_MspDeInit 1 */
    }
}

/**
 * @brief CAN MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hcan: CAN handle pointer
 * @retval None
 */
void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    if (hcan->Instance == CAN)
    {
        /* USER CODE BEGIN CAN_MspInit 0 */

        /* USER CODE END CAN_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**CAN GPIO Configuration
        PA11     ------> CAN_RX
        PA12     ------> CAN_TX
        */
        GPIO_InitStruct.Pin       = GPIO_PIN_11 | GPIO_PIN_12;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_NOPULL;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_CAN;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* CAN interrupt Init */
        HAL_NVIC_SetPriority(USB_HP_CAN_TX_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USB_HP_CAN_TX_IRQn);
        HAL_NVIC_SetPriority(USB_LP_CAN_RX0_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USB_LP_CAN_RX0_IRQn);
        HAL_NVIC_SetPriority(CAN_RX1_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(CAN_RX1_IRQn);
        /* USER CODE BEGIN CAN_MspInit 1 */

        /* USER CODE END CAN_MspInit 1 */
    }
}

/**
 * @brief CAN MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hcan: CAN handle pointer
 * @retval None
 */
void HAL_CAN_MspDeInit(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance == CAN)
    {
        /* USER CODE BEGIN CAN_MspDeInit 0 */

        /* USER CODE END CAN_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_CAN1_CLK_DISABLE();

        /**CAN GPIO Configuration
        PA11     ------> CAN_RX
        PA12     ------> CAN_TX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);

        /* CAN interrupt DeInit */
        HAL_NVIC_DisableIRQ(USB_HP_CAN_TX_IRQn);
        HAL_NVIC_DisableIRQ(USB_LP_CAN_RX0_IRQn);
        HAL_NVIC_DisableIRQ(CAN_RX1_IRQn);
        /* USER CODE BEGIN CAN_MspDeInit 1 */

        /* USER CODE END CAN_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
