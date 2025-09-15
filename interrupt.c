#include"header.h"
int a[]={15,60,30,15,15};
unsigned int pclk;
extern u8 flag,flag1,flag2,flag3;
void TIMER1_Handler(void) __irq
{

        flag=1;
        T1IR=1;
        VICVectAddr=0;
		
}
void EINT0_Handler(void)__irq
{
        flag1=1;


        EXTINT|=1;
        VICVectAddr=0;

}
void EINT1_Handler(void)__irq
{
        flag2=1;

        EXTINT|=2;
        VICVectAddr=0;


}

void EINT2_Handler(void)__irq
{

        flag3=1;

        EXTINT|=4;
        VICVectAddr=0;


}
void config_vic_for_interrupt(void)
{
        VICIntSelect=0;
        VICVectCntl2=5|(1<<5);
        VICVectAddr2=(int)TIMER1_Handler;
        VICIntEnable|=(1<<5);
		//-------------------------------------//
		VICIntSelect=0;
        VICVectCntl1=14|(1<<5);
        VICVectAddr1=(u32)EINT0_Handler;
        VICIntEnable|=(1<<14);
		//---------------------------------------//
		VICIntSelect=0;
        VICVectCntl0=15|(1<<5);
        VICVectAddr0=(u32)EINT1_Handler;
        VICIntEnable|=(1<<15);
		//-------------------------------------//
		//VICIntSelect=0;
        VICVectCntl3=16|(1<<5);
        VICVectAddr3=(u32)EINT2_Handler;
        VICIntEnable|=(1<<16);
		
}
void vic_interrupt(void)
{
        T1MCR=3;
        pclk=a[VPBDIV]*1000000;
        T1PC=0;
        T1PR=pclk-1;
        T1TC=0;
        T1MR0=1;
        T1TCR=1;
		//--------------------------------//
		  EXTPOLAR=0;
        EXTMODE|=1;
        PINSEL1|=1;
		//-----------------------//
        EXTPOLAR=0;
        EXTMODE|=2;
        PINSEL0|=0x20000000;
		//---------------------------//
		EXTPOLAR=0;
        EXTMODE|=4;
        PINSEL0|=0x80000000;


}
