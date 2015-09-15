#ifndef __FUNKCJE_H
#define __FUNKCJE_H
	
#define ABS(x)         (x < 0) ? (-x) : x

#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"
#include "stm32f3_discovery_accelerometer.h"
#include "stm32f3_discovery_gyroscope.h"

extern	TIM_HandleTypeDef htim2;	
extern UART_HandleTypeDef huart2;
extern __IO ITStatus UartReadyRX;
extern __IO ITStatus UartReadyTX;

extern uint8_t aTxBuffer[];
extern uint8_t aRxBuffer[];
extern uint8_t buf_in_bluetooth[4];
extern uint8_t bluetooth_connect_string[];
extern uint8_t buff_temp[12];
	
	int pwm = 1000;
	int smiec;
	int flaga_silnik_konf=0;
	int pwm2=1000;
	void konfiguruj_uart(void);
	void Error_Handler(void); 
	void konfiguruj_silniki(void);
	void testuj_obroty(void);
	void testuj_zyro(void);
	void testuj_bluetooth(void);
	int bluetooth_nawiaz_polaczenie(UART_HandleTypeDef *huart);
	void bluetooth_wyslij(UART_HandleTypeDef *huart, uint8_t *pData);
	void bluetooth_odbierz_4bity_int(UART_HandleTypeDef *huart);
	void silniki_wszystkie(int pwm_val);
#endif


