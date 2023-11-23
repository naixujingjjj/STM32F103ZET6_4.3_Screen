#include "lcd.h"
//file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/*.*" "Users/*.*")
//include_directories(Users/Inc)
#include "retarget.h"
#include "usart.h"
#include "touch.h"
void KEY0_Scan(){
    if(LL_GPIO_IsInputPinSet(GPIOE,LL_GPIO_PIN_3) == 0){
        LL_mDelay(10);
        if(LL_GPIO_IsInputPinSet(GPIOE,LL_GPIO_PIN_3) == 0){

            while(LL_GPIO_IsInputPinSet(GPIOE,LL_GPIO_PIN_3)==0);
        }
    }
}
void KEY1_Scan(){
    if(LL_GPIO_IsInputPinSet(GPIOE,LL_GPIO_PIN_4) == 0){
        LL_mDelay(10);
        if(LL_GPIO_IsInputPinSet(GPIOE,LL_GPIO_PIN_4) == 0){

            while(LL_GPIO_IsInputPinSet(GPIOE,LL_GPIO_PIN_4)==0);
        }
    }
}
__IO float usDelayBase;
void delay_us(uint32_t Delay)
{
    __IO uint32_t delayReg;

    __IO uint32_t msNum = Delay/1000;
    __IO uint32_t usNum = (uint32_t)((Delay%1000)*usDelayBase);

    if(msNum>0) LL_mDelay(msNum);

    delayReg = 0;
    while(delayReg!=usNum) delayReg++;
}
//void lcd_draw_bline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint16_t color)
//{
//    uint16_t t;
//    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
//    int incx, incy, row, col;
//
//    if (x1 < size || x2 < size || y1 < size || y2 < size)
//        return;
//
//    delta_x = x2 - x1; /* 计算坐标增量 */
//    delta_y = y2 - y1;
//    row = x1;
//    col = y1;
//
//    if (delta_x > 0)
//    {
//        incx = 1; /* 设置单步方向 */
//    }
//    else if (delta_x == 0)
//    {
//        incx = 0; /* 垂直线 */
//    }
//    else
//    {
//        incx = -1;
//        delta_x = -delta_x;
//    }
//
//    if (delta_y > 0)
//    {
//        incy = 1;
//    }
//    else if (delta_y == 0)
//    {
//        incy = 0; /* 水平线 */
//    }
//    else
//    {
//        incy = -1;
//        delta_y = -delta_y;
//    }
//
//    if (delta_x > delta_y)
//        distance = delta_x; /* 选取基本增量坐标轴 */
//    else
//        distance = delta_y;
//
//    for (t = 0; t <= distance + 1; t++) /* 画线输出 */
//    {
//        lcd_fill_circle(row, col, size, color); /* 画点 */
//        xerr += delta_x;
//        yerr += delta_y;
//
//        if (xerr > distance)
//        {
//            xerr -= distance;
//            row += incx;
//        }
//
//        if (yerr > distance)
//        {
//            yerr -= distance;
//            col += incy;
//        }
//    }
//}
//const uint16_t POINT_COLOR_TBL[10] = {RED, GREEN, BLUE, BROWN, YELLOW, MAGENTA, CYAN, LIGHTBLUE, BRRED, GRAY};
//void ctp_test(void)
//{
//    uint8_t t = 0;
//    uint8_t i = 0;
//    uint16_t lastpos[10][2];        /* 最后一次的数据 */
//    uint8_t maxp = 5;
//
//    if (lcddev.id == 0X1018)maxp = 10;
//
//    while (1)
//    {
//        tp_dev.scan(0);
//
//        for (t = 0; t < maxp; t++)
//        {
//            if ((tp_dev.sta) & (1 << t))
//            {   /* 坐标在屏幕范围内 */
//                if (tp_dev.x[t] < lcddev.width && tp_dev.y[t] < lcddev.height)
//                {
//                    if (lastpos[t][0] == 0XFFFF)
//                    {
//                        lastpos[t][0] = tp_dev.x[t];
//                        lastpos[t][1] = tp_dev.y[t];
//                    }
//
//                    lcd_draw_bline(lastpos[t][0], lastpos[t][1], tp_dev.x[t],
//                                   tp_dev.y[t], 2, POINT_COLOR_TBL[t]);
//                    lastpos[t][0] = tp_dev.x[t];
//                    lastpos[t][1] = tp_dev.y[t];
//
//                    if (tp_dev.x[t] > (lcddev.width - 24) && tp_dev.y[t] < 20)
//                    {
//                            lcd_clear(WHITE);
//                            lcd_show_string(lcddev.width - 24, 0, 200, 16, 16, "RST", BLUE);
//                    }
//                }
//            }
//            else
//            {
//                lastpos[t][0] = 0XFFFF;
//            }
//        }
//
//        LL_mDelay(10);
//    }
//}
void Task_Init(){
    RetargetInit(&huart1);
    LL_GPIO_ResetOutputPin(GPIOB,LL_GPIO_PIN_5);
    LL_GPIO_SetOutputPin(GPIOE,LL_GPIO_PIN_5);
    lcd_init();
    lcd_display_on();
    lcd_clear(WHITE);
    LL_GPIO_SetOutputPin(LCD_BL_GPIO_Port,LCD_BL_Pin);
    tp_dev.init();
//    ctp_test();
    LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_5);//初始化完毕
    LL_GPIO_ResetOutputPin(GPIOE,LL_GPIO_PIN_5);
}
void Task_Loop(){
    KEY0_Scan();
    KEY1_Scan();
}
