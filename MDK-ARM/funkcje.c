#include "funkcje.h"
	
void konfiguruj_silniki()
{
		pwm = 2000;
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, pwm);
		//BSP_LED_Toggle(LED3);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, pwm);
	//	BSP_LED_Toggle(LED5);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, pwm);
	//	BSP_LED_Toggle(LED7);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, pwm);
	//	BSP_LED_Toggle(LED9);

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
		//BSP_LED_Toggle(LED3);
	//	BSP_LED_Toggle(LED5);
	//	BSP_LED_Toggle(LED7);
	//	BSP_LED_Toggle(LED9);
}
void silniki_wszystkie(int pwm_val)
{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, pwm_val);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, pwm_val);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, pwm_val);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, pwm_val);
}
void testuj_bluetooth()
{
	BSP_LED_Toggle(LED9);
	bluetooth_odbierz_4bity_int(&huart2);
	silniki_wszystkie(pwm);
	bluetooth_wyslij(&huart2,buf_in_bluetooth);
	BSP_LED_Toggle(LED10);
}
int bluetooth_nawiaz_polaczenie(UART_HandleTypeDef *huart)
{	
	if(HAL_UART_Receive_IT(&huart2,buff_temp, 12) != HAL_OK)
  {
    Error_Handler();
  }
	 while (UartReadyRX != SET)
  {
  }
	UartReadyRX = RESET;
	BSP_LED_Toggle(LED7);
	if((strcmp(buff_temp ,"DRON CONNECT")))
	{
		bluetooth_wyslij(&huart2, "Nieprawidlowa komenda. Aby polaczyc wpisz \"DRON CONNECT\"\n");
	return 0;
	}
	else
	{
	bluetooth_wyslij(&huart2, "Podlaczony. Rozpoczynam transmisje.\n");	 
	BSP_LED_Toggle(LED9);	
	return 1;
	}
}
void bluetooth_odbierz_4bity_int(UART_HandleTypeDef *huart)
{
	if(HAL_UART_DeInit(&huart2) != HAL_OK)
  {
    Error_Handler();
  } 
  if(HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
	
	if(UartReadyRX==RESET)
	{
		if(HAL_UART_Receive_IT(&huart2, (uint8_t*)buf_in_bluetooth, 4) != HAL_OK)
		{
			//BSP_LED_Toggle(LED9);
			Error_Handler();
		}
		while(UartReadyRX!=SET)
		{
		}
		UartReadyRX = RESET;
	}
}
void bluetooth_wyslij(UART_HandleTypeDef *huart, uint8_t *pData)
{
	if(HAL_UART_DeInit(&huart2) != HAL_OK)
  {
    Error_Handler();
  } 
  if(HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
	if(UartReadyTX==RESET)
	{
		int dlugosc = strlen(pData);
		if(HAL_UART_Transmit_IT(&huart2,pData,dlugosc)!=HAL_OK)
		{
			//Error_Handler();
		}
		while(UartReadyTX!=SET)
		{
		}
		UartReadyTX = RESET;
	}
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
  	BSP_LED_Toggle(LED4);
}

