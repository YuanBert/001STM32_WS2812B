#include "bsp_ws2812b.h"


void delay600ns(void)
{
	uint8_t i;
	for(i = 0; i < 3; i++)
		asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
}
void delay850ns(void)
{
	uint8_t i;
	for(i = 0; i < 4; i++)
		asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
}

void delay400ns(void)
{
	uint8_t i;
	for(i = 1; i < 3; i++)
		asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
}

void delay250ns(void)
{
	uint8_t i;

	for(i = 1; i  < 2; i++)
		asm("NOP");
}

void delay60us(void)
{
	uint16_t i;
	for(i = 0; i < 650;i++)
	{
		asm("NOP");
	}
}

void bsp_ws2812bInit(void);
void bsp_ws2812bReset(void)
{
	GPIOB->ODR &= 0xFFFF9FFF;
	delay60us();
}
void bsp_ws2812bSendArryDataToRight(uint8_t *pArry, uint16_t len)
{
	uint8_t j;
	uint8_t temp;
	uint16_t i;
	for(i = 0; i < len; i++)
	{
		temp = *(pArry + i);
		for(j = 0; j < 8;j++)
		{
			if(0x01 == (temp >> j) & 0x01)
			{
				LeftLEDs_Ctrl_GPIO_Port->ODR |= LeftLEDs_Ctrl_Pin;
				delay850ns();
				LeftLEDs_Ctrl_GPIO_Port->ODR &= ~LeftLEDs_Ctrl_Pin;
				delay250ns();
			}
			else
			{
				LeftLEDs_Ctrl_GPIO_Port->ODR |= LeftLEDs_Ctrl_Pin;
				delay400ns();
				LeftLEDs_Ctrl_GPIO_Port->ODR &= ~LeftLEDs_Ctrl_Pin;
				delay600ns();
			}
		}
	}


}
void bsp_ws2812bSendArryDataToLeft(uint8_t *pArry, uint16_t len)
{
	uint8_t j;
	uint8_t temp;
	uint16_t i;
	for(i = 0; i < len; i++)
	{
		temp = *(pArry + i);
		for(j = 0; j < 8;j++)
		{
			if(0x01 == (temp >> j) & 0x01)
			{
				RightLEDs_Ctrl_GPIO_Port->ODR |= RightLEDs_Ctrl_Pin;
				delay850ns();
				RightLEDs_Ctrl_GPIO_Port->ODR &= ~RightLEDs_Ctrl_Pin;
				delay250ns();
			}
			else
			{
				RightLEDs_Ctrl_GPIO_Port->ODR |= RightLEDs_Ctrl_Pin;
				delay400ns();
				RightLEDs_Ctrl_GPIO_Port->ODR &= ~RightLEDs_Ctrl_Pin;
				delay600ns();
			}
		}
	}	
}



