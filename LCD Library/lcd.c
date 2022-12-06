#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "lcd.h"

void lcdwait()
{

    SysCtlDelay(50000);
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, 0x30);
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(5000);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0
}

void lcdfunctionset( unsigned char dl,unsigned char n,unsigned char f) // dl,N,F
{
    // dl için ya 4 yada 8
    // N için 1 için 1 satıra, 2 gelirse 2 satır
    // F için 7 gelise 5x7 fontu
    // eğer 10 gelirse de 5x10 fonutunu
    if(dl==4)
    {
        if(n==1)
        {
            if(f==7)
            {
                lcdcom(0x20);
            }
            else if(f==10)
            {
                lcdcom(0x24);
            }

        }
        if(n==2)
        {
            if(f==7)
            {
                lcdcom(0x28);
            }
            else if(f==10)
            {
                lcdcom(0x2C);
            }
        }
    }
    if(dl==8)
            {
                if(n==1)
                {
                    if(f==7)
                    {
                        lcdcom(0x30);
                    }
                    else if(f==10)
                    {
                        lcdcom(0x34);
                    }

                }
                if(n==2)
                {
                    if(f==7)
                    {
                        lcdcom(0x38);
                    }
                    else if(f==10)
                    {
                        lcdcom(0x3C);
                    }
                }
            }


    }

    void lcdfirstset(void)
    {
        SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // portb aktif
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF); // butun pinler output
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, rs, 0); // rs=0
        lcdwait();
        lcdwait();
        lcdwait();
        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, d4 | d5 | d6 | d7,  0x20 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(200);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000);
      
        // Since we are sending 4 bits of data, we need to send 0x20 data, otherwise 8 bits will remain. This should be noted...

        lcdcom(0x28);
        lcdcom(0xC0);
        lcdcom(0x06);
        lcdcom(0x80);
        lcdcom(0x28);
        lcdcom(0x0f);
        lcdclear();

    }

    void lcdcom (unsigned char c)
    {
        GPIOPinWrite(LCDPORT, rs, 0); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0xF0));
        GPIOPinWrite(LCDPORT, E, 2); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(50000); 

        GPIOPinWrite(LCDPORT, rs, 0); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0x0F)<<4);
        GPIOPinWrite(LCDPORT, E, 2); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(50000); 

    void lcdclear(void)
    {
        lcdcom(0x01);
    }

    void lcdwrite(unsigned char c)
    {
        GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0xF0));
        GPIOPinWrite(LCDPORT, rs, 0x01); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(50000);


        GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0x0F)<<4);
        GPIOPinWrite(LCDPORT, rs, 0x01); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(50000);
    }
      
    void lcdgotoxy(unsigned char x, unsigned char y)
    {
        if(x==1){
            lcdcom(0x80+((y-1)%16));  //first line between 80h-8Fh .
        }
    }
