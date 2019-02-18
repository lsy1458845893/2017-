#include "IIC_Key.h"
#include "delay.h"




void IIC_RCC_Configration()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
}

void IIC_CLK_Configration()//PB.14
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /**/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	  
	/*????????*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	
	/*?????????????*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*???????50MHz*/	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
			
	/*?????,??? GPIOE*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
}

void IIC_SDA_DIR(u8 dir)//PB.13
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /**/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	  
	/*????????*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	
	if(dir==1)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	else
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    
	/*???????50MHz*/	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
			
	/*?????,??? GPIOE*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
}

void IIC_Bus_Init()
{
    /*初始化IIC所在外设总线的时钟*/
    IIC_RCC_Configration();
    
    IIC_CLK_Configration();
    
    IIC_SDA_DIR(1);
    
    
    IIC_CLK_0;
    IIC_SDA_0;
    
    delay_ms(1);
    
    IIC_CLK_1;
    IIC_SDA_1;
}


void IIC_Start()
{
    IIC_CLK_1;
    delay_us(TIME);
    IIC_SDA_1;
    delay_us(TIME);
    IIC_SDA_0;
    delay_us(TIME);
    IIC_CLK_0;
    delay_us(TIME);
}

void IIC_Stop()
{
  IIC_CLK_0;
  delay_us(TIME);
  IIC_SDA_0;
  delay_us(TIME);
  IIC_SDA_1;
  delay_us(TIME);
  IIC_CLK_1;
  delay_us(TIME);
}

void IIC_WriteByte(u8 Data)
{
    u8 i,temp;
    
    temp=Data;
    
    for(i=0;i<8;i++)
    {
        IIC_CLK_0;
        delay_us(TIME);
        if((temp&0x80)==0x80)
        {
            IIC_SDA_1;
        }
        else
        {
            IIC_SDA_0;
        }
        
        delay_us(TIME);
        temp = temp << 1;
        IIC_CLK_1;
        delay_us(TIME);
    }
    
    IIC_CLK_0;
    delay_us(TIME);
    
    IIC_SDA_1;
    delay_us(TIME);
    
    IIC_CLK_1;
    delay_us(TIME);
    
    IIC_CLK_0;
    delay_us(TIME);
    
}

u8 IIC_ReadByte()
{
    u8 i,read_temp;
    read_temp=0;
    
    IIC_SDA_1;
    IIC_SDA_DIR(0);
    for(i=0;i<8;i++)
    {
        IIC_CLK_0;
        delay_us(TIME);
        IIC_CLK_1;
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13))
            read_temp |= (0x80 >> i);
        delay_us(TIME);
    }
    IIC_SDA_DIR(1);
    
    IIC_CLK_0;
    delay_us(TIME);
    
    IIC_SDA_0;
    delay_us(TIME);
    
    IIC_CLK_1;
    delay_us(TIME);
    
    IIC_CLK_0;
    delay_us(TIME);
    
    return read_temp;
}

void IIC_SendWord(u8 add1, u8 add2, u8 byte1, u8 byte2)
{
    IIC_Start();
    IIC_WriteByte(add1);
    if(add2!=0)
        IIC_WriteByte(add2);
    if(byte1!=0)
        IIC_WriteByte(byte1);
    if(byte2!=0)
        IIC_WriteByte(byte2);
    IIC_Stop();
}

u8 IIC_KeyGet()//只返回键值
{
  u8 KEY;
  IIC_Start();
  IIC_WriteByte(0x70);
  IIC_WriteByte(0x01);
  IIC_Stop();
  IIC_Start();
  IIC_WriteByte(0x71);
  KEY = IIC_ReadByte();//读键值 
  IIC_ReadByte();//读次数
  IIC_Stop();
  KEY = Key_Recode(KEY);
  return KEY;
}

u8 Key_Recode(u8 old_code)
{
    u8 new_code;
    if (old_code == 1)
        new_code = 0;
    else if (old_code == 2)
        new_code = 11;
    else if (old_code == 4)
        new_code = 1;
    else if (old_code == 5)
        new_code = 2;
    else if (old_code == 6)
        new_code = 3;
    else if (old_code == 8)
        new_code = 4;
    else if (old_code == 9)
        new_code = 5;
    else if (old_code == 10)
        new_code = 6;
    else if (old_code == 12)
        new_code = 7;
    else if (old_code == 13)
        new_code = 8;
    else if (old_code == 14)
        new_code = 9;
    else
        new_code=17;
    
    return new_code;
}

