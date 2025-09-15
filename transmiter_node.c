#include"header.h"
//#define SW1 ((IOPIN0>>14)&1)
//#define SW2 ((IOPIN0>>15)&1)
//#define SW3 ((IOPIN0>>16)&1)

u8 flag,flag1,flag2,flag3;
CAN2 a1,a2;
main()
{
        u8 f1,f2,f3;
        u32 eng_temp,speed;
        f1=f2=f3=0;
        can2_init();
        adc_init();
        config_vic_for_interrupt();
        vic_interrupt();
        a1.dlc=1;
        a1.rtr=0;

        a1.byteA=0;

        a1.byteB=0;
        a2.dlc=2;
        a2.rtr=0;

        a2.byteA=0;

        a2.byteB=0;
        while(1)
        {
                if(flag3)
                {
                        flag3=0;

                        a1.id=0x213;
                        f1^=1;
                        if(f1)
                        {
                                a1.byteA=0x4;
                        }
                        else
                        {
                                a1.byteA=0x5;
                        }
                        can2_tx(a1);
                }
                if(flag2)
                {
                        flag2=0;
                        a1.id=0x214;
                        f2^=1;
                        if(f2)
                        {
                                a1.byteA=0x6;
                        }
                        else
                        {
                                a1.byteA=0x7;
                        }
                        can2_tx(a1);
                }
                if(flag1)
                {
                        flag1=0;
                        a1.id=0x212;
                        f3^=1;
                        if(f3)
                        {
                                a1.byteA=0x2;
                        }
                        else
                        {
                                a1.byteA=0x3;
                        }
                        can2_tx(a1);
                }
                if(flag)
                {
                        flag=0;
                        a2.id=0x215;
                        speed=adc_read(2);
                        a2.byteA=speed;
                        can2_tx(a2);
                        delay_ms(5);
                        a2.id=0x216;
                        eng_temp=adc_read(1);
                        a2.byteA=eng_temp;
                        can2_tx(a2);
                }
        }
}
