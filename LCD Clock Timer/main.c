#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "math.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "driverlib/timer.h"
#include "lcd.h"

void perset(void){
        lcdtext("  Musab Elibol");
        lcdgotoxy(2, 1);
        lcdtext("   Clock Work");
        SysCtlDelay(25000000);
        lcdcom(1);
        lcdgotoxy(1, 7);
        lcdtext("Clock");
        SysCtlDelay(2500000);
    }
       int saniye=0;
       int dakika=0;
       int saat=0;
int main(void)
{
lcdfirstset();
    perset();

SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_RCC_XTAL_16MHZ|SYSCTL_OSC_MAIN);//40MHZ
long a =SysCtlClockGet();
SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
IntMasterEnable();
IntEnable(INT_TIMER0A);
TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()-1);
TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
TimerEnable(TIMER0_BASE, TIMER_A);
    while(1){}
}


void Timerkesmefonk(void)
{

        saniye++;
        if(saniye==60)
        {
         saniye=0;
         dakika++;
        }if(dakika==60)
        {
         dakika=0;
         saat++;
        }if(saat==24)
        {
            saat=0;
        }

int saniyeonlar=saniye/10;
int s1=saniyeonlar+48;
int saniyebirler=saniye%10;
int s2=saniyebirler+48;
int dakikaonlar=dakika/10;
int d1=dakikaonlar+48;
int dakikabirler=dakika%10;
int d2=dakikabirler+48;
int saatonlar=saat/10;
int saat1=saatonlar+48 ;
int saatbirler=saat%10;
int saat2=saatbirler+48;

      lcdgotoxy(2, 5);
      lcdwrite(saat1);
      lcdgotoxy(2, 6);
      lcdwrite(saat2);
      lcdgotoxy(2, 7);
      lcdwrite(0x2e);
      lcdgotoxy(2, 8);
      lcdwrite(d1);
      lcdgotoxy(2, 9);
      lcdwrite(d2);
      lcdgotoxy(2, 10);
      lcdwrite(0x2e);
      lcdgotoxy(2, 11);
      lcdwrite(s1);
      lcdgotoxy(2, 12);
      lcdwrite(s2);
        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}
