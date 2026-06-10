#include<lpc21xx.h>
#include"lcd1.h"
#include"uart0.h"
#include"gsmtrain.h"
#define ir1 1<<15
#define ir2 1<<16
#define led 1<<10
#define m1 1<<3
#define m2 1<<4

int f=0,s=0;
int main()
{
UART0_CONFIG();
LCD_INIT();
IODIR0  |=led|m1|m2;
IOSET0=led;
LCD_SCROLL_RL("Railguard : Intelligent GSM Based Automatic Railway Gate System");
LCD_COMMAND(0X80);
LCD_STR(" WAIT FOR TRAIN ");
while(1)
{
if(((IOPIN0&(1<<15))==0))
{
    IOCLR0 = led;
	if(f==0)
{
    LCD_COMMAND(0x01);
    LCD_COMMAND(0x80);LCD_STR("TRAIN ARRIVED ");
    LCD_COMMAND(0xC0);LCD_STR("GATE CLOSED ");
		
		gsm_sms("TRAIN ARRIVER  AND GATE IS CLOSED");
		while(s==0)
		{
		IOSET0 = m1;
        IOCLR0 = m2;
        delay_ms(1000);
        IOCLR0 = m1 | m2;   // stop motor
        s = 1;
		}
    f=1;
	IOSET0= led;
}  // object detected
}

else if((IOPIN0 & ir2)==0)
{   // no object}
     if(f==1)
	{
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);LCD_STR("TRAIN PASSED");
	
    LCD_COMMAND(0xC0);LCD_STR("GATE OPENED ");
	gsm_sms("TRAIN PASSED AND GATE IS OPENED");
	while(s==1)
	{
	IOSET0 = m2;
    IOCLR0 = m1;
    delay_ms(1000);
    IOCLR0 = m1 | m2;   // stop motor
    s = 0;
	}
	f=0;
}	
	}

}

}
