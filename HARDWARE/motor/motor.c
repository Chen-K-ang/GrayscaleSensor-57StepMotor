#include "motor.h"

void motor_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(TB6600_RCC, ENABLE);	 //ʹ��PA,PD�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = DIR_PIN | PUL_PIN | ENA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(TB6600_PORT, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	GPIO_ResetBits(TB6600_PORT, DIR_PIN | PUL_PIN | ENA_PIN);
}

void motor_cmd(uint8_t mode, uint16_t pul, uint16_t half_time)
{
	uint16_t x;
	switch (mode) {
	case 1:
		GPIO_SetBits(DIR_PIN_PORT, DIR_PIN);
		break;
	case 0:
		GPIO_ResetBits(DIR_PIN_PORT,DIR_PIN);
		break;
	default:
		break;
	}
	
	GPIO_SetBits(ENA_PIN_PORT, ENA_PIN);
	
	for (x=0;x<=pul;x++) {
		GPIO_SetBits(PUL_PIN_PORT, PUL_PIN);
		delay_us(half_time);
		GPIO_ResetBits(PUL_PIN_PORT, PUL_PIN);
		delay_us(half_time);
	}
}
