 #include"header.h"
void lcd_data(unsigned char data)
{
        IOCLR1=0xfe<<16;
        IOSET1=(data&0xf0)<<16;
        IOSET1=1<<17;
        IOCLR1=1<<18;
        IOSET1=1<<19;
        delay_ms(2);
        IOCLR1=1<<19;

        IOCLR1=0xfe<<16;
        IOSET1=(data&0xf)<<20;
        IOSET1=1<<17;
        IOCLR1=1<<18;
        IOSET1=1<<19;
        delay_ms(2);
        IOCLR1=1<<19;
}
void lcd_cmd(unsigned char cmd)
{
        IOCLR1=0xfe<<16;
        IOSET1=(cmd&0xf0)<<16;
        IOCLR1=1<<17;
        IOCLR1=1<<18;
        IOSET1=1<<19;
        delay_ms(2);
        IOCLR1=1<<19;

        IOCLR1=0xfe<<16;
        IOSET1=(cmd&0xf)<<20;
        IOCLR1=1<<17;
        IOCLR1=1<<18;
        IOSET1=1<<19;
        delay_ms(2);
        IOCLR1=1<<19;
}
void lcd_init()
{
        IODIR1=0xfe<<16;
        PINSEL2=0;
        lcd_cmd(0x02);
        lcd_cmd(0x28);
        lcd_cmd(0x0e);
        lcd_cmd(0x0c);
        lcd_cmd(0x01);
}
void lcd_string(char *ptr)
{
        while(*ptr)
        {
                lcd_data(*ptr);
                ptr++;
        }
}
void lcd_integer(int num)
{
        int a[15],i;
        if(num==0)
        {
                lcd_data('0');
        }
        if(num<0)
        {
                lcd_data('-');
                num=-num;
        }
        i=0;
        while(num>0)
        {
                a[i]=num%10+48;
                num=num/10;
                i++;
        }
        while(i>0)
        {
                lcd_data(a[--i]);
        }
}
void lcd_cgram(void)
{
//      unsigned char a[]={0x0,0xa,0xa,0x0,0x0,0x11,0xe,0x0,0x17,0x14,0x14,0x1f,0x05,0x05,0x1d,0x00},i;

         unsigned char a[]={0x00,0x04,0x08,0x1f,0x1f,0x08,0x04,0x00,0x00,0x0e,0x00,0x1f,0x11,0x11,0x0e,0x00,0x0,0x04,0x02,0x1f,0x1f,0x02,0x04,0x00},i;
                lcd_cmd(0x40);
        for(i=0;i<=24;i++)
                lcd_data(a[i]);
}
/*
void lcd_float_adc(float num)
{
        u8 p[15];
        if(num<0)
        {
                lcd_data('-');
                num=-num;
        }
        sprintf(p,"%.1f",num);
        lcd_string(p);
}
*/

void lcd_float(float num)
{
        int temp,frac_part,int_part;
        temp=num;
        if(temp<0)
        {
                lcd_data('-');
                temp=-temp;
                num=-num;
        }
        int_part=(int)num;
        frac_part=(int)((num-int_part)*1000000);
        
        lcd_integer(temp);
				lcd_data('.');
				if(frac_part<10)
					lcd_data('0');
				lcd_integer(frac_part);
}
void lcd_float_adc(float num)
{

        int temp,a[15],i,j,c=0,k;
        if(num<0)
        {
                lcd_data('-');
                num=-num;
        }
        temp=num*10;
        j=num;
        for(c=0,k=num;k;c++,k/=10);
        i=0;
        if(temp==0)
        {
                a[i]=0;
                i++;
        }
        else
        {
                while(temp)
                {
                        a[i]=temp%10;
                        temp=temp/10;
                        i++;
                }
        }
        lcd_integer(j);
        lcd_data('.');
        //for(i=i-c-1;i>=0;i--)
        lcd_integer(a[0]);
}
