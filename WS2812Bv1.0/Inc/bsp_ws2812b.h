#ifndef __bsp_ws2812b_H
#define __bsp_ws2812b_H

#ifdef __cplusplus
extern "C"{
#endif

#include "stm32f1xx_hal.h"
#include "gpio.h"

void bsp_ws2812bInit(void);
void bsp_ws2812bReset(void);
void bsp_ws2812bSendArryDataToRight(uint8_t *pArry, uint16_t len);
void bsp_ws2812bSendArryDataToLeft(uint8_t *pArry, uint16_t len);


void bsp_ws2812bFlashModeOne(void);
void bsp_ws2812bFlashModeTwo(void);
void bsp_ws2812bFlashModeThree(void);
void bsp_ws2812bFlashModeFour(void);

 
#ifdef __cplusplus
}
#endif

#endif
