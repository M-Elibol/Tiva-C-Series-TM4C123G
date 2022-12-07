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
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, 0x30);
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(5000);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0
}


void lcdfunctionset( unsigned char dl,unsigned char n,unsigned char f) // dl,N,F
{

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
        GPIOPinWrite(LCDPORT, RS, 0); // rs=0
        lcdwait();
        lcdwait();
        lcdwait();
        SysCtlDelay(50000);
        SysCtlDelay(50000);
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x20 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(200);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000);
                lcdcom(0x28);
                lcdcom(0x06);
                lcdcom(0x0c);
                lcdclear();
    }

    void lcdcom (unsigned char c)
    {
        GPIOPinWrite(LCDPORT, RS, 0); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (c & 0xF0));
        GPIOPinWrite(LCDPORT, E, 2); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(50000); // yeni değiştirdim

        GPIOPinWrite(LCDPORT, RS, 0); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (c & 0x0F)<<4);
        GPIOPinWrite(LCDPORT, E, 2); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(50000); // yeni ekledim
    }

    void lcdclear(void)
    {
        lcdcom(0x01);
    }
    void lcdwrite(unsigned char c)
    {

        GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (c & 0xF0));
        GPIOPinWrite(LCDPORT, RS, 0x01); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(50000);


        GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (c & 0x0F)<<4);
        GPIOPinWrite(LCDPORT, RS, 0x01); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(50000);
    }

    void lcdgotoxy(unsigned char x, unsigned char y)
    {

        if(x==1){
            lcdcom(0x80+((y-1)%16));  //birinci satır 80h-8Fh arası.
        }

        if(x==2) {
            lcdcom(0xC0+((y-1)%16));  //ikinci satır C0h-CFh arası.
        }
    }
    void lcdtext( char* s){
            while(*s)
                    lcdwrite(*s++);
    }



