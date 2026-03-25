/******************************************************************************
*@file  : main.c
*@brief : main program
******************************************************************************/
#include "hal.h"
#include "uart.h"
#include "psram.h"
#include "lcd.h"
#include "ctp.h"
#include "nnom.h"
#include "image.h"
#include "weights.h"
#include "font.h"
/******************************************************************************
*@brief : main program
*@param : none
*@return: none
******************************************************************************/
#define WHITE_COLOR 0xFFFF
#define BLACK_COLOR 0x0000
#define RED_COLOR 0xF800
#define GREEN_COLOR 0x07E0
#define BLUE_COLOR 0x001F

PSRAM_SECTION uint16_t LCD_GRAM[LCD_HEIGHT][LCD_WIDTH];

nnom_model_t *model;

void lcd_show_char(uint16_t xs,uint16_t ys,uint8_t ch)
{
    uint8_t idx = ch - ' ';
    uint16_t x,y,i,j,k;
    uint8_t byte;

    y = ys;
    
    for(i = 0;i<24;i++)
    {
        x = xs;
        for(k = 0;k < 24/8;k++)
        {   
            byte = F24x24[idx][3*i+k];
            for(j = 0;j<8;j++)
            {
                if(byte & 0x80)
                    LCD_GRAM[y][x] = WHITE_COLOR;
                else
                    LCD_GRAM[y][x] = BLACK_COLOR;
                byte <<= 1;
                x++;
            }
        }
        y++;
    }
    lcd_fill_screen(0,0,LCD_WIDTH,LCD_HEIGHT,LCD_GRAM);
}

void lcd_show_string(uint16_t xs,uint16_t ys,uint8_t *str)
{
    if (*str == '\0') // ¿Õ×Ö·û´®Ö±½ÓÍË³ö
        return;

    while(*str != '\0')
    {
        lcd_show_char(xs,ys,*str);
        xs += 24;
        str++;
    }
}

void lcd_show_num(uint16_t xs,uint16_t ys,uint16_t num)
{
    const uint8_t num_table[10] = {'0','1','2','3','4','5','6','7','8','9'}; 
    lcd_show_char(xs,ys,num_table[num]);
}

void lcd_show_nums(uint16_t xs,uint16_t ys,uint16_t num)
{
    uint16_t n;
    const uint8_t num_table[10] = {'0','1','2','3','4','5','6','7','8','9'}; 
    n = num / 100;
    lcd_show_char(xs,ys,num_table[n]);
    xs += 24;
    n = (num % 100) / 10;
    lcd_show_char(xs,ys,num_table[n]);
    xs += 24;
    n = (num % 100) % 10;
    lcd_show_char(xs,ys,num_table[n]);
}

// ASCII lib from (https://www.jianshu.com/p/1f58a0ebf5d9)
const char codeLib[] = "@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.   ";
void print_img(int8_t * buf)
{
    for(int y = 0; y < 28; y++) 
    {
        for (int x = 0; x < 28; x++) 
        {
            int index =  69 / 127.0 * (127 - buf[y*28+x]); 
            if(index > 69) index =69;
            if(index < 0) index = 0;
            printf("%c",codeLib[index]);
            printf("%c",codeLib[index]);
        }
        printf("\n");
    }
}

void mnist_test(int32_t index)
{
    uint32_t tick,time;
    uint32_t predic_label;
    float prob;

    if(index >= TOTAL_IMAGE)
    {
        printf("Please input image number within %d\n", TOTAL_IMAGE-1);
        return;
    }

    printf("\nprediction start.. \n");
    tick = SysTick->VAL;

    // copy data and do prediction
    memcpy(nnom_input_data, (int8_t*)&img[index][0], 784);
    nnom_predict(model, &predic_label, &prob);
    time = SysTick->VAL - tick;

    //print original image to console
    print_img((int8_t*)&img[index][0]);

    printf("Time: %d tick\n", time);
    printf("Truth label: %d\n", label[index]);
    printf("Predicted label: %d\n", predic_label);
    printf("Probability: %d%%\n", (int)(prob*100));
}

int8_t mnist_input_buff[784];
void mnist(int8_t *input)
{
    uint32_t tick,time;
    uint32_t predic_label;
    float prob;

    printf("\nprediction start.. \n");
    tick = SysTick->VAL;

    // copy data and do prediction
    memcpy(nnom_input_data, input, 784);
    nnom_predict(model, &predic_label, &prob);
    time = SysTick->VAL - tick;

    //print original image to console
    print_img(input);

    printf("Time: %d tick\n", time);
    printf("Predicted label: %d\n", predic_label);
    printf("Probability: %d%%\n", (int)(prob*100));
    lcd_show_num(716,320,predic_label);
    lcd_show_nums(636,360,(uint16_t)(prob*100));
}

void draw_grid(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint8_t d)
{
    uint8_t i;
    uint16_t x,y;

    uint8_t dx = (xe - xs) / 28;
    uint8_t dy = (ye - ys) / 28;
    
    for(x = xs; x <= xe; x += dx)
    {
        for(y = ys; y < ye + d; y++)
        {
            for(i = 0; i < d; i++)
            {
                LCD_GRAM[y][x+i] = BLUE_COLOR;
            }
        }  
    }

    for(y = ys; y <= ye; y += dy)
    {
        for(x = xs; x < xe + d; x++)
        {
            for(i = 0; i < d; i++)
            {
                LCD_GRAM[y+i][x] = BLUE_COLOR;
            }
        }  
    }
    lcd_fill_screen(0,0,LCD_WIDTH,LCD_HEIGHT,LCD_GRAM);
}

void draw_grid_dot(int16_t x, int16_t y)
{
    uint16_t i,j;
    int16_t xs,ys;
    int16_t x_temp,y_temp;
    x_temp = x / 17;
    y_temp = y / 17;
    xs = 17 * x_temp;
    ys = 17 * y_temp;
    if((xs == 0 && ys == 0) || xs >= 476)
        return;
    // printf("x = %d,xs = %d,y = %d,ys = %d\r\n",x,xs,y,ys);
    for(i = xs;i < xs + 17;i++)
    {
        for(j = ys; j < ys + 17;j++)
        {
            LCD_GRAM[j][i] = WHITE_COLOR;
        }
    }
    mnist_input_buff[x_temp+y_temp*28] = 127;
    lcd_fill_screen(0,0,LCD_WIDTH,LCD_HEIGHT,LCD_GRAM);
}

void draw_predict_key(void)
{
    uint16_t i,j;

    for(i = 700;i < 750;i++)
    {
        for(j = 50; j < 100;j++)
        {
            LCD_GRAM[j][i] = GREEN_COLOR;
        }
    }
    lcd_fill_screen(0,0,LCD_WIDTH,LCD_HEIGHT,LCD_GRAM);
}

void draw_clean_key(void)
{
    uint16_t i,j;

    for(i = 700;i < 750;i++)
    {
        for(j = 250; j < 300;j++)
        {
            LCD_GRAM[j][i] = RED_COLOR;
        }
    }
    lcd_fill_screen(0,0,LCD_WIDTH,LCD_HEIGHT,LCD_GRAM);
    // lcd_show_char(716,340,'0');
}

void clean_dot(void)
{
    uint16_t x,y;
    for(x = 0;x < 476;x++)
    {
        for(y = 0; y < 476;y++)
        {
            LCD_GRAM[y][x] = BLACK_COLOR;
        }
    }
    draw_grid(0,0,476,476,1);
    memset(mnist_input_buff,0x00,784);
    lcd_show_char(716,320,' ');
    lcd_show_string(636,360,"   ");
}

int main(void)
{
    uint32_t i;
    int16_t x=0,y=0;
    bool status;
    HAL_Init();  
    SystemClock_Config(SYSCLK_220M_SRC_XTH_12M, PCLK1_DIV_SELECT, PCLK2_DIV_SELECT, PCLK3_DIV_SELECT, PCLK4_DIV_SELECT);    

    Uart_Init(USART1, 115200);    
    printf("\r\n\r\n******** ACM32H5XX MCU is runing ********\r\n");
    printf("HCK: %u, PCLK1: %u\r\n", (int)HAL_RCC_GetHCLKFreq(),(int)HAL_RCC_GetPCLK1Freq());

    Lcd_Init();
    lcd_disp_init(LCD_WIDTH, LCD_HEIGHT);
    ctp_init();

    // create and compile the model 
	model = nnom_model_create();
   
	// dummy run
	model_run(model);

    memset(LCD_GRAM,0x00,LCD_WIDTH * LCD_HEIGHT * 2);
    lcd_fill_screen(0,0,LCD_WIDTH,LCD_HEIGHT,LCD_GRAM);

    draw_grid(0,0,476,476,1);
    draw_predict_key();
    draw_clean_key();

    lcd_show_string(500,320,"Predict:");
    lcd_show_string(500,360,"Prob:");
    lcd_show_string(720,360,"%");

    while(1)
    {
        status = ctp_is_pressed();
        
        if(status)
        {
            ctp_get_xy(&x,&y);
            draw_grid_dot(x, y);
            if(x >= 700 && x <= 750)
            {
                if(y >= 50 && y <= 100)
                {
                    mnist(mnist_input_buff);
                }
            }

            if(x >= 700 && x <= 750)
            {
                if(y >= 250 && y <= 300)
                {
                    clean_dot();
                }
            }
        }
    }
}

