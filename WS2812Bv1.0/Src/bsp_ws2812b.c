#include "bsp_ws2812b.h"

static uint8_t i,j,k;
extern uint8_t gModeCode;
extern uint8_t gModeChangeFlag;
extern uint8_t gDisplayedFlag;
extern uint8_t gFlashNumberCnt;
extern uint8_t gFlashColorCnt;
extern uint8_t leds[108];


void delay600ns(void)
{
	uint8_t i;
	for(i = 0; i < 3; i++)
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

void bsp_ws2812bInit(void)
{
  i = 0;
  j = 0;
  k = 0;
}
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
			if(0x01 == ((temp >> j) & 0x01))
			{
				GPIOB->ODR |= (1<<13);
				delay850ns();
				GPIOB->ODR  &= 0xFFFFDFFF;
				delay250ns();
			}
			else
			{
				GPIOB->ODR |= (1 << 13);
				delay400ns();
				GPIOB->ODR &= 0xFFFFDFFF;
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
			if(0x01 == ((temp >> j) & 0x01))
			{
				GPIOB->ODR |= (1 << 14);
				delay850ns();
				GPIOB->ODR &= 0xFFFFBFFF;
				delay250ns();
			}
			else
			{
				GPIOB->ODR |= (1 << 14);
				delay400ns();
				GPIOB->ODR &= 0xFFFFBFFF;
				delay600ns();
			}
		}
	}	
}

/****************************** entern code ***********************************/        
void bsp_ws2812bFlashModeOne(void)
{
      uint8_t n;
      if(1 != gModeCode)
      {
        return ;
      }
      
      if(0 == gDisplayedFlag)
      {
        return;
      }
      if(gModeChangeFlag)
      {
        i = 0;
        j = 0;
        k = 0;
        gModeChangeFlag = 0;
      }
      
      if(k > 0)
      {
        for(n = 0; n < 12; n++)
        {
          leds[9*n + 0] = 0xAC;
          leds[9*n + 1] = 0xF0;
          leds[9*n + 2] = 0x6B;
          
          leds[9*n + 3] = 0x79;
          leds[9*n + 4] = 0xCC;
          leds[9*n + 5] = 0xF0;
          
          leds[9*n + 6] = 0xF0;
          leds[9*n + 7] = 0x00;
          leds[9*n + 8] = 0xF0;
        }
        
        if(0 == k%2)
        {
          for(n = 0; n < 108; n++)
          {
            leds[n] = 0x00;
          }
        }
        
        k++;
        if(k > 40)
        {
          k = 0;
        }
        
        gDisplayedFlag = 0;
        return ;
      }
      
      
      leds[3*j + i] = 0xFF;
      j++;
      if(j > 35)
      {
        j = 0;
        for(n = 0; n < 108;n++)
        {
          leds[n] = 0;
        }
        i++;
        if(i > 2)
        {
          i = 0;
          j = 0;
          k = 1;
          for(n = 0; n < 108; n++)
          {
            leds[n] = 0;
          }
        }
      }
      gDisplayedFlag = 0;

}
void bsp_ws2812bFlashModeTwo(void)
{
      uint8_t n;
      if(2 != gModeCode)
      {
        return ;
      }
      
      if(0 == gDisplayedFlag)
      {
        return;
      }
      if(gModeChangeFlag)
      {
        i = 0;
        j = 0;
        k = 0;
        gModeChangeFlag = 0;
      }  
      
      
}
void bsp_ws2812bFlashModeThree(void)
{
      uint8_t n;
      if(3 != gModeCode)
      {
        return ;
      }
      
      if(0 == gDisplayedFlag)
      {
        return;
      }
      if(gModeChangeFlag)
      {
        i = 0;
        j = 0;
        k = 0;
        gModeChangeFlag = 0;
      } 
      
      
}
void bsp_ws2812bFlashModeFour(void)
{
       uint8_t n;
      if(4 != gModeCode)
      {
        return ;
      }
      
      if(0 == gDisplayedFlag)
      {
        return;
      }
      if(gModeChangeFlag)
      {
        i = 0;
        j = 0;
        k = 0;
        gModeChangeFlag = 0;
      } 
      
      
}

