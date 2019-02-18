//
// Created by lsy on 17-5-9.
//

#ifndef LCD_DEV_H
#define LCD_DEV_H

#include "stm32f4xx.h"
#include "stdint-gcc.h"

//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左

#define DFT_SCAN_DIR  L2R_D2U  //默认的扫描方向

//LCD分辨率设置
#define SSD_HOR_RESOLUTION		800		//LCD水平分辨率
#define SSD_VER_RESOLUTION		480		//LCD垂直分辨率
//LCD驱动参数设置
#define SSD_HOR_PULSE_WIDTH		30		//水平脉宽
#define SSD_HOR_BACK_PORCH		16		//水平前廊
#define SSD_HOR_FRONT_PORCH		210		//水平后廊

#define SSD_VER_PULSE_WIDTH		13		//垂直脉宽
#define SSD_VER_BACK_PORCH		10		//垂直前廊
#define SSD_VER_FRONT_PORCH		22		//垂直前廊

typedef struct
{
    u16 LCD_REG;
    u16 LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))
#define LCD             ((LCD_TypeDef *) LCD_BASE)


class LCD_DEV{
private:
    typedef struct
    {
        u16 width;			//LCD 宽度
        u16 height;			//LCD 高度
        u16 id;				//LCD ID
        u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。
        u16	wramcmd;		//开始写gram指令
        u16  setxcmd;		//设置x坐标指令
        u16  setycmd;		//设置y坐标指令
    }_lcd_dev;


    void LCD_WR_REG(vu16 regval);
    void LCD_WR_DATA(vu16 data);
    u16 LCD_RD_DATA(void);

    void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
    u16 LCD_ReadReg(u16 LCD_Reg);
    void LCD_WriteRAM_Prepare(void);
    void LCD_WriteRAM(u16 RGB_Code);
    void LCD_Scan_Dir(u8 dir);							//设置屏扫描方向
    void LCD_Display_Dir(u8 dir);						//设置屏幕显示方向
    void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);//设置窗口
    u16 LCD_BGR2RGB(u16 c);

public:
    u16 w,h;

    _lcd_dev lcddev;
    LCD_DEV();
    void on(void);
    void off(void);
    void black_light(uint8_t duty);
    void clear(u32 c);

    void cursor(u16 x,u16 y);
    void write(u16 c);

    u16 read_dot(u16 x,u16 y);
    void dot(u16 x,u16 y, u32 c);
};

#endif //LCD_DEV_H
