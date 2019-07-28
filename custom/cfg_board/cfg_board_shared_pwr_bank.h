/**
  ******************************************************************************
  * 文件:app_board_haier.h
  * 作者: steve
  * 版本: V1.0.0
  * 描述: 海尔扫地机相关配置
  ******************************************************************************
  *
  *                  版权所有 (C), steve
  *                                
  *
  ******************************************************************************
  */
  
/* 防止递归包含该头文件 ------------------------------------------------------*/
#ifndef __CFG_BOARD_PWR_BANK_H__
#define __CFG_BOARD_PWR_BANK_H__

#ifdef __cplusplus
 extern "C" {
#endif 
#define PRINTF_USART        USART5
#define WIFI_USART          USART6
/* sys base timer -> TIM3 */
#define BASE_TIM_IRQn       TIM3_IRQn
#define BASE_TIM_NUM        TIM3
#define BASE_TIM_RCC        RCC_APB1Periph_TIM3

/* LED1628 DATA -> PE10 */
#define LED1628_DATA_GPIO_PIN      GPIO_Pin_10
#define LED1628_DATA_GPIO_PORT     GPIOE
#define LED1628_DATA_RCC_PERIPH    RCC_APB2Periph_GPIOE

/* LED1628 CLK -> PE8 */
#define LED1628_CLK_GPIO_PIN       GPIO_Pin_8
#define LED1628_CLK_GPIO_PORT      GPIOE
#define LED1628_CLK_RCC_PERIPH     RCC_APB2Periph_GPIOE

/* LED1628 STB -> PD11 */
#define LED1628_STB_GPIO_PIN       GPIO_Pin_11
#define LED1628_STB_GPIO_PORT      GPIOD
#define LED1628_STB_RCC_PERIPH     RCC_APB2Periph_GPIOD


/* 负载功率控制 -> TIM1_CH1 -> PA8 */
#define LOAD_POWER_TIM_GPIO_PORT    GPIOA
#define LOAD_POWER_TIM_GPIO_PIN     GPIO_Pin_8
#define LOAD_POWER_TIM_GPIO_RCC     RCC_APB2Periph_GPIOA
#define LOAD_POWER_TIM_NUM          TIM1
#define LOAD_POWER_TIM_CHAN         TIM_Channel_1
#define LOAD_POWER_TIM_FLAG_CC      TIM_FLAG_CC1
#define LOAD_POWER_TIM_IT_CC        TIM_IT_CC1
#define LOAD_POWER_TIM_OCInit       TIM_OC1Init 
#define LOAD_POWER_TIM_OCPreloadConfig   TIM_OC1PreloadConfig
#define LOAD_POWER_TIM_GetCapture   TIM_GetCapture1
#define LOAD_POWER_TIM_SetCompare   TIM_SetCompare1
#define LOAD_POWER_TIM_RCC          RCC_APB2Periph_TIM1
#define LOAD_POWER_OC_TIM_IRQn      TIM1_CC_IRQn
#define LOAD_POWER_TIM_CCxCmd       TIM_CCxCmd
/* beep控制 -> Pb8 TIM4_CH3*/
#define BEEP_TIM_GPIO_PORT    GPIOB
#define BEEP_TIM_GPIO_PIN     GPIO_Pin_8
#define BEEP_TIM_GPIO_RCC     RCC_APB2Periph_GPIOB
#define BEEP_TIM_NUM          TIM4
#define BEEP_TIM_CHAN         TIM_Channel_3
#define BEEP_TIM_FLAG_CC      TIM_FLAG_CC3
#define BEEP_TIM_IT_CC        TIM_IT_CC3
#define BEEP_TIM_OCInit       TIM_OC3Init 
#define BEEP_TIM_OCPreloadConfig   TIM_OC3PreloadConfig
#define BEEP_TIM_GetCapture   TIM_GetCapture3
#define BEEP_TIM_SetCompare   TIM_SetCompare3
#define BEEP_TIM_RCC          RCC_APB1Periph_TIM4
#define BEEP_TIM_CCxCmd       TIM_CCxCmd
#define P_BEEP_ON()           GPIO_SetBits(BEEP_TIM_GPIO_PORT, BEEP_TIM_GPIO_PIN);   
#define P_BEEP_OFF()          GPIO_ResetBits(BEEP_TIM_GPIO_PORT, BEEP_TIM_GPIO_PIN);    

/* 交流电电流 -> ADC1_IN2 -> PA2 */
#define CURRENT_ADC_GPIO_PORT       GPIOA
#define CURRENT_ADC_GPIO_PIN        GPIO_Pin_2
#define CURRENT_ADC_GPIO_RCC        RCC_APB2Periph_GPIOA
#define CURRENT_ADC_NUM             ADC1
#define CURRENT_ADC_CHAN            ADC_Channel_2
#define CURRENT_ADC_RCC             RCC_APB2Periph_ADC1

/* 没有用到第二个 ADC, 设置和第一个 ADC 相同 */
#define CURRENT_ADC_2ND_GPIO_PORT   GPIOA
#define CURRENT_ADC_2ND_GPIO_PIN    GPIO_Pin_2
#define CURRENT_ADC_2ND_GPIO_RCC    RCC_APB2Periph_GPIOA
#define CURRENT_ADC_2ND_NUM         ADC1
#define CURRENT_ADC_2ND_CHAN        ADC_Channel_2
#define CURRENT_ADC_2ND_RCC         RCC_APB2Periph_ADC1

/* 负载电流 -> ADC1_IN8 -> PB0 */
#define LOAD_CUR_ADC_GPIO_PORT       GPIOB
#define LOAD_CUR_ADC_GPIO_PIN        GPIO_Pin_0
#define LOAD_CUR_ADC_GPIO_RCC        RCC_APB2Periph_GPIOB
#define LOAD_CUR_ADC_NUM             ADC1
#define LOAD_CUR_ADC_CHAN            ADC_Channel_8
#define LOAD_CUR_ADC_RCC             RCC_APB2Periph_ADC1

/* 没有用到第二个 ADC, 设置和第一个 ADC 相同 */
#define LOAD_CUR_ADC_2ND_GPIO_PORT   GPIOB
#define LOAD_CUR_ADC_2ND_GPIO_PIN    GPIO_Pin_0
#define LOAD_CUR_ADC_2ND_GPIO_RCC    RCC_APB2Periph_GPIOB
#define LOAD_CUR_ADC_2ND_NUM         ADC1
#define LOAD_CUR_ADC_2ND_CHAN        ADC_Channel_8
#define LOAD_CUR_ADC_2ND_RCC         RCC_APB2Periph_ADC1

/* 负载电压 -> ADC1_IN9 -> PB1 */
#define LOAD_V_ADC_GPIO_PORT       GPIOB
#define LOAD_V_ADC_GPIO_PIN        GPIO_Pin_1
#define LOAD_V_ADC_GPIO_RCC        RCC_APB2Periph_GPIOB
#define LOAD_V_ADC_NUM             ADC1
#define LOAD_V_ADC_CHAN            ADC_Channel_9
#define LOAD_V_ADC_RCC             RCC_APB2Periph_ADC1

/* 没有用到第二个 ADC, 设置和第一个 ADC 相同 */
#define LOAD_V_ADC_2ND_GPIO_PORT   GPIOB
#define LOAD_V_ADC_2ND_GPIO_PIN    GPIO_Pin_1
#define LOAD_V_ADC_2ND_GPIO_RCC    RCC_APB2Periph_GPIOB
#define LOAD_V_ADC_2ND_NUM         ADC1
#define LOAD_V_ADC_2ND_CHAN        ADC_Channel_9
#define LOAD_V_ADC_2ND_RCC         RCC_APB2Periph_ADC1

/* unnormal led -> PB10 */
#define UNUSUAL_LED_GPIO_PIN       GPIO_Pin_10
#define UNUSUAL_LED_GPIO_PORT      GPIOB
#define UNUSUAL_LED_RCC_PERIPH     RCC_APB2Periph_GPIOB
#define UNUSUAL_LED_ON()        GPIO_SetBits(UNUSUAL_LED_GPIO_PORT, UNUSUAL_LED_GPIO_PIN);    
#define UNUSUAL_LED_OFF()       GPIO_ResetBits(UNUSUAL_LED_GPIO_PORT, UNUSUAL_LED_GPIO_PIN);    

/* normal LED -> PB11 */
#define NORMAL_LED_GPIO_PIN       GPIO_Pin_11
#define NORMAL_LED_GPIO_PORT      GPIOB
#define NORMAL_LED_RCC_PERIPH     RCC_APB2Periph_GPIOB
#define NORMAL_LED_ON()        GPIO_SetBits(NORMAL_LED_GPIO_PORT, NORMAL_LED_GPIO_PIN);    
#define NORMAL_LED_OFF()       GPIO_ResetBits(NORMAL_LED_GPIO_PORT, NORMAL_LED_GPIO_PIN);    


/* KEY0 -> PC2 disp*/
#define KEY0_GPIO_PIN       GPIO_Pin_2
#define KEY0_GPIO_PORT      GPIOC
#define KEY0_RCC_PERIPH     RCC_APB2Periph_GPIOC
/* KEY0 -> EXTI2 -> PC2 */
#define KEY0_NVIC_CHANNEL   EXTI2_IRQn
#define KEY0_EXTI_PIN_SRC   GPIO_PinSource2     
#define KEY0_EXTI_PORT_SRC  GPIO_PortSourceGPIOC
#define KEY0_EXTI_LINE      EXTI_Line2

/* KEY1 -> PC3 up*/
#define KEY1_GPIO_PIN       GPIO_Pin_3
#define KEY1_GPIO_PORT      GPIOC
#define KEY1_RCC_PERIPH     RCC_APB2Periph_GPIOC
/* KEY1 -> EXTI3 -> PC3 */
#define KEY1_NVIC_CHANNEL   EXTI3_IRQn
#define KEY1_EXTI_PIN_SRC   GPIO_PinSource3     
#define KEY1_EXTI_PORT_SRC  GPIO_PortSourceGPIOC
#define KEY1_EXTI_LINE      EXTI_Line3

/* KEY2 -> PA0 down*/
#define KEY2_GPIO_PIN       GPIO_Pin_0
#define KEY2_GPIO_PORT      GPIOA
#define KEY2_RCC_PERIPH     RCC_APB2Periph_GPIOA

/* KEY2 -> EXTI0 -> PA0 */
#define KEY2_NVIC_CHANNEL   EXTI0_IRQn
#define KEY2_EXTI_PIN_SRC   GPIO_PinSource0     
#define KEY2_EXTI_PORT_SRC  GPIO_PortSourceGPIOA
#define KEY2_EXTI_LINE      EXTI_Line0

/* KEY3 -> PA1 loop*/
#define KEY3_GPIO_PIN       GPIO_Pin_1
#define KEY3_GPIO_PORT      GPIOA
#define KEY3_RCC_PERIPH     RCC_APB2Periph_GPIOA
/* KEY3 -> EXTI1 -> PA1 */
#define KEY3_NVIC_CHANNEL   EXTI1_IRQn
#define KEY3_EXTI_PIN_SRC   GPIO_PinSource1     
#define KEY3_EXTI_PORT_SRC  GPIO_PortSourceGPIOA
#define KEY3_EXTI_LINE      EXTI_Line1

/* IIC SCL -> PB6 */
#define SCL_GPIO_PIN      GPIO_Pin_6
#define SCL_GPIO_PORT     GPIOB
#define SCL_RCC_PERIPH    RCC_APB2Periph_GPIOB

/* IIC SDA -> PB7 */
#define SDA_GPIO_PIN      GPIO_Pin_7
#define SDA_GPIO_PORT     GPIOB
#define SDA_RCC_PERIPH    RCC_APB2Periph_GPIOB
#ifdef __cplusplus
}
#endif

#endif /* __CFG_BOARD_PWR_BANK_H__ */
 
/*************************************************************************************/
