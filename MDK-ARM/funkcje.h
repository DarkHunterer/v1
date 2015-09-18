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
	
	
	int16_t ThresholdHigh = 1000;
	int16_t ThresholdLow = -1000;
	int pwm = 1000;
	int pwm1 = 1000;
	int pwm2 = 1000;
	int pwm3 = 1000;
	int pwm4 = 1000;
	int smiec;
	uint8_t raport_string[24];
	int flaga_silnik_konf=0;
	
	void konfiguruj_uart(void);
	void konfiguruj_silniki(void);

	void testuj_obroty(void);
	void testuj_zyro(void);
	void testuj_akcelerometr(void);
	void testuj_bluetooth(void);
	
	int bluetooth_nawiaz_polaczenie(UART_HandleTypeDef *huart);
	void bluetooth_wyslij(UART_HandleTypeDef *huart, uint8_t *pData);
	void bluetooth_odbierz_4bity_int(UART_HandleTypeDef *huart);

	void raport_pwm_stan(void);
	void Error_Handler(void); 
	void silniki_wszystkie(int pwm_val);

	void koryguj_poziomo(void);
#endif


