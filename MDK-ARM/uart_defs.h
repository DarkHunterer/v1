#ifndef __UART_DEFS
#define __UART_DEFS
/* Size of Trasmission buffer */
#define TXBUFFERSIZE                      (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                      TXBUFFERSIZE
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"
#include "stm32f3_discovery_accelerometer.h"
#include "stm32f3_discovery_gyroscope.h"

extern int pwm;
extern UART_HandleTypeDef huart2;

int flaga_bluetooth_odbiera=0;
__IO ITStatus UartReadyRX = RESET;
__IO ITStatus UartReadyTX = RESET;

uint8_t aTxBuffer[] = "****";
uint8_t aRxBuffer[RXBUFFERSIZE];
uint8_t buf_in_bluetooth[4]="1000";
uint8_t bluetooth_connect_string[]="DRON CONNECT";
uint8_t buff_temp[12];
#endif

