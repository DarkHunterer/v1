#ifndef __FUNKCJE_H
#define __FUNKCJE_H
	
	/* Definition for USARTx clock resources */
#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __USART1_CLK_ENABLE();
#define DMAx_CLK_ENABLE()                __DMA1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOE_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOC_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_4
#define USARTx_TX_GPIO_PORT              GPIOC
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_5
#define USARTx_RX_GPIO_PORT              GPIOC
#define USARTx_RX_AF                     GPIO_AF7_USART1

/* Definition for USARTx's DMA */
#define USARTx_TX_DMA_STREAM              DMA1_Channel4
#define USARTx_RX_DMA_STREAM              DMA1_Channel5

/* Definition for USARTx's NVIC */
#define USARTx_DMA_TX_IRQn                DMA1_Channel4_IRQn
#define USARTx_DMA_RX_IRQn                DMA1_Channel5_IRQn
#define USARTx_DMA_TX_IRQHandler          DMA1_Channel4_IRQHandler
#define USARTx_DMA_RX_IRQHandler          DMA1_Channel5_IRQHandler

/* Size of Trasmission buffer */
#define TXBUFFERSIZE                      (COUNTOF(TxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                      TXBUFFERSIZE
  
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

	
	
#define ABS(x)         (x < 0) ? (-x) : x

	extern	TIM_HandleTypeDef htim2;	
	UART_HandleTypeDef UartHandle;
__IO ITStatus UartReady = RESET;

	uint8_t TxBuffer[] = " **UART communication -- projekt DRON";
	uint8_t RxBuffer[RXBUFFERSIZE];

	int pwm = 1000;
	int flaga_silnik_konf=0;
	
	void konfiguruj_uart(void);
	void Error_Handler(void); 
	void konfiguruj_silniki(void);
	void testuj_obroty(void);
	void testuj_zyro(void);
	void silniki_wszystkie(int pwm_val);
	
void konfiguruj_uart()
{
	UartHandle.Instance        = USARTx;

  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
}
void konfiguruj_silniki()
{
		pwm = 2000;
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, pwm);
		BSP_LED_Toggle(LED3);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, pwm);
		BSP_LED_Toggle(LED5);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, pwm);
		BSP_LED_Toggle(LED7);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, pwm);
		BSP_LED_Toggle(LED9);

	for (pwm=2000; pwm>=1000; )
	{
		pwm-=50;
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, pwm);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, pwm);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, pwm);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, pwm);
		HAL_Delay(3);
	}
		HAL_Delay(1000);
	flaga_silnik_konf =1;
			BSP_LED_Toggle(LED3);
			BSP_LED_Toggle(LED5);
			BSP_LED_Toggle(LED7);
			BSP_LED_Toggle(LED9);

}
void silniki_wszystkie(int pwm_val)
{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, pwm_val);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, pwm_val);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, pwm_val);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, pwm_val);
}
void testuj_obroty()
{

HAL_Delay(2000);
					for(pwm=1000;pwm<1400;)
					{
						pwm+=20;
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,pwm);
						HAL_Delay(500);
					}
			
					for(;pwm>1000;)
					{
						pwm-=100;
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,pwm);
						HAL_Delay(500);
					}
					pwm=1000;
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,pwm);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,pwm);
}
void testuj_zyro()
{
/* Gyroscope variable */
  float Buffer[3];
  float Xval,Yval = 0x00;
  
  /* Read Gyro Angular data */
  BSP_GYRO_GetXYZ(Buffer);
  
  /* Update autoreload and capture compare registers value*/
  Xval = ABS((Buffer[0]));
  Yval = ABS((Buffer[1])); 
  
  
    if(Buffer[1] > 5000.0f)
    { 
      if(pwm<1400)
			pwm+=10;	
			silniki_wszystkie(pwm);
			BSP_LED_On(LED7);
      HAL_Delay(100);
    }
    else if(Buffer[1] < -5000.0f)
    { 
      if(pwm>1000)
				pwm-=10;	
			silniki_wszystkie(pwm);
			 BSP_LED_On(LED6);
			HAL_Delay(100);
    }
    else
    { 
      HAL_Delay(10);
    }
		BSP_LED_Off(LED3);
    BSP_LED_Off(LED6);
    BSP_LED_Off(LED7);
    BSP_LED_Off(LED4);
    BSP_LED_Off(LED10);
    BSP_LED_Off(LED8);
    BSP_LED_Off(LED9);
    BSP_LED_Off(LED5);
}


void Error_Handler(void)
{
  while(1)
  {
				BSP_LED_Toggle(LED4);
				HAL_Delay(20);
  }
}

#endif