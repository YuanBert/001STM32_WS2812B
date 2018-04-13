#include "bsp_ws2812b.h"

static uint8_t i,j,k,p,q;
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
        p = 0;
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
		for(n = 0; n < 108; n++)
		{
			leds[n] = 0;
		}
      }


	  if(k > 2)
	  {
		if(k > 3)
		{
			for(n = 0; n < 12; n++)
			{
				leds[9*n + i] = 0xFF;
				leds[9*n + 4 - i] = 0xFF;
				leds[9*n + 8 - i] = 0xFF;
				i++;
				i %= 2;
			}
			
			if(0 == k%2)
			{
				for(n = 0; n < 108; n++)
				{
					leds[n] = 0;
				}
			}
			k++;
			if(k > 50)
			{
				k = 0;
				j = 0;
				i = 0;
				for(n = 0; n < 12; n++)
				{
					leds[n] = 0;
				}
			}
			gDisplayedFlag = 0;
			return;
		}
		for(n = 0; n < 108; n++)
		{
			leds[n] = 0;
		}

		leds[9*j + i] = 0xFF;
		leds[9*j + 4 - i] = 0xFF;
		leds[9*j + 8 - i] = 0xFF;

		j++;
		if(j > 11)
		{
			i++;
			j = 0;
			if(i > 2)
			{
				i = 0;
				j = 0;
				k++;
				for(n = 0; n < 108; n++)
				{
					leds[n] = 0;
				}
			}
		}
		gDisplayedFlag = 0;
		return;
	  }

	  if(2 == k)
	  {
		  for(n = 0; n < 108; n++)
		  {
			  leds[n] = 0;
		  }
		  
		  leds[6*j + i] = 0xFF;
		  if(2 == i)
		  {
			leds[6*j + 3] = 0xFF;
		  }
		  else
		  {
		  	leds[6*j + i + 4] = 0xFF;
		  }
		  
		  j++;
		  if(j > 17)
		  {
			  i++;
			  j = 0;
			  if(i > 2)
			  {
				  i = 0;
				  j = 0;
				  k = 3;
				  for(n = 0; n < 108; n++)
				  {
					leds[n] = 0;
				  }
			  }
		  }
		gDisplayedFlag = 0;
		return;
	  }
	  
	  if(1 == k)
	  {
	  	for(n = 0; n < 108; n++)
	  	{
			leds[n] = 0;
		}
		leds[3*j + i] = 0xFF;
		j++;
		if(j > 35)
		{
			i++;
			j = 0;
			if(i > 2)
			{
				i = 0;
				j = 0;
				k = 2;
				for(n = 0; n < 108; n++)
				{
					leds[n] = 0;
				}
			}
		}
		gDisplayedFlag = 0;
		return;
	  }
      
      leds[3*j + i] = 0xFF;
	  i++;
	  j++;
	  if(i > 2)
	  {
		i = 0;
	  }
	  if(j > 35)
	  {
	  	i = 0;
		j = 0;
		k = 1;
		for(n = 0; n < 108; n++)
		{
			leds[n] = 0;
		}
	  }
	  gDisplayedFlag = 0;
	  return;
      
}
void bsp_ws2812bFlashModeThree(void)
{
      uint8_t n;
      uint8_t data;
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
        p = 0;
        q = 0;
        for(n = 0; n < 108; n++)
	{
          leds[n] = 0;
	}
        gModeChangeFlag = 0;
      } 
      
      if(1 == i)
      {
        data = 0x00;
      }
      else
      {
        data = 0xFF;
      }
      
      leds[3*j + k] = data;
      leds[15 + 3*j + k] = data;
      leds[30 + 3*j + k] = data;
      leds[45 + 3*j + k] = data;
      
      leds[60 + 3*p + k] = data;
      leds[69 + 3*p + k] = data;
      leds[78 + 3*p + k] = data;
      leds[87 + 3*p + k] = data;
      
      leds[96 + k] = data;
      leds[99 + k] = data;
      leds[102 + k] = data;
      leds[105 + k] = data;
      
      p++;
      k++;
      if(p > 2)
      {
        p = 0;
      }
      if(k > 2)
      {
        k = 0;
      }
      
      j++;
      if(j > 4)
      {
        j = 0;
        if(1 == i)
        {
          i = 0;
        }
        else
        {
          i = 1;
        }
      }
      gDisplayedFlag = 0;
      
      
}
void bsp_ws2812bFlashModeFour(void)
{
       uint8_t n;
       uint8_t data;
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
        p = 0;
        for(n = 0; n < 108; n++)
	{
          leds[n] = 0;
	}
        gModeChangeFlag = 0;
      } 
      
            
      if(1 == i)
      {
        data = 0x00;
      }
      else
      {
        data = 0xFF;
      }
      
      leds[12 - 3*j + k] = data;
      leds[15 + 12 - 3*j + k] = data;
      leds[30 + 12 - 3*j + k] = data;
      leds[45 + 12 - 3*j + k] = data;
      
      leds[60 + 6 - 3*p + k] = data;
      leds[69 + 6 - 3*p + k] = data;
      leds[78 + 6 - 3*p + k] = data;
      leds[87 + 6 - 3*p + k] = data;
      
      leds[96 + k] = data;
      leds[99 + k] = data;
      leds[102 + k] = data;
      leds[105 + k] = data;
      
      p++;
      k++;
      if(p > 2)
      {
        p = 0;
      }
      if(k > 2)
      {
        k = 0;
      }
      
      j++;
      if(j > 4)
      {
        j = 0;
        //k = 0;
        if(1 == i)
        {
          i = 0;
        }
        else
        {
          i = 1;
        }
      }
      gDisplayedFlag = 0;
}

