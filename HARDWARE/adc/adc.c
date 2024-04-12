 #include "adc.h"
 #include "delay.h"
//  #include "car.h"
//////////////////////////////////////////////////////////////////////////////////	 
						  
////////////////////////////////////////////////////////////////////////////////// 
#define ADC1_DR_Address     ((u32)0x4001244C)
u16  AD_Value[4];
		   
																   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	 
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 A2 A3 A4 配置                        
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  //ADC配置
	
	ADC_DeInit(ADC1);  //复位ADC1 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//多通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//多次转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//右对齐
	ADC_InitStructure.ADC_NbrOfChannel =4;	//ADC通道转换4
	ADC_Init(ADC1, &ADC_InitStructure);	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道,采样时间为55.5周期	
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5 );	
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_55Cycles5 );		
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime_55Cycles5 );		
		
	ADC_DMACmd(ADC1, ENABLE);

	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
   ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}		


//DMA配置
	void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	
  DMA_DeInit(DMA1_Channel1);   //将DMA的通道1寄存器重设为缺省值

	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //
	DMA_InitStructure.DMA_BufferSize =4;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作	循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 拥有高优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
  DMA_Cmd(DMA1_Channel1, ENABLE);	
} 


//				printf ("%4d  %4d  %4d  %4d\r\n",left1,mid1,mid2,right1);	


//获得ADC值
//ch:通道值 0~3
//u16 Get_Adc1(void)   
//{
//  ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
//	
//	DMA_Cmd(DMA1_Channel1, ENABLE);	
//	
//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
//	
//	for(i=0;i<4;i++)
//	{
//	 printf ("AD_Value[i]\r\n")
//	}

//	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
//}


//u16 Get_Adc_Average(u8 ch,u8 times)
//{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc(ch);
//		delay_ms(5);
//	}
//	return temp_val/times;
//} 	 



























