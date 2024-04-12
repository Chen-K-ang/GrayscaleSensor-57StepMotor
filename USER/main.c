#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "hc05.h"
#include "usart2.h"			 	 
#include "string.h"	 
#include "key.h"
#include "pwm.h"
#include "adc.h"
#include "motor.h"

int main(void)
{  
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		 //初始化与LED连接的硬件接口
	KEY_Init();
	TIM1_PWM_Init(199,7199); //不分频。PWM频率===(7200*200)/72000000=0.02=20ms
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART2_Init(9600); 	
	Adc_Init();	 //初始adc
	DMA_Config();
	
	//example
	motor_gpio_init();

 	while(1) 
	{		
		u2_printf("a:%d",AD_Value[0]); //向手机发送adc的值
		delay_ms(1000);
		
		//example
		motor_cmd(0,6400,100);
     
	}
} 
