#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "math.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "driverlib/timer.h"
#include "inc/hw_sysctl.h"
#include "lcd.h"
#include "driverlib/adc.h"

uint32_t gelendeger[4];
long ort,temp;
long temp2onlar;
long temp2birler;
long temp2_1;
long temp2_2;

void adckesme(){

   ADCSequenceDataGet(ADC0_BASE, 2, gelendeger);
   ort=(gelendeger[0]+gelendeger[1]+gelendeger[2]+gelendeger[3])/4;
   int pot=ort*12.21;
   int potonbin=(pot/10000) +48 ;
   int potbin=(pot%10000)/1000 + 48 ;
   int potyüz=(pot%1000)/100 + 48 ;
   int poton=(pot%100)/10 + 48 ;
   int potbir=(pot%10) + 48 ;
   lcdgotoxy(1, 6);
   lcdwrite(potonbin);
   lcdgotoxy(1, 7);
   lcdwrite(potbin);
   lcdgotoxy(1, 8);
   lcdwrite(potyüz);
   lcdgotoxy(1, 9);
   lcdwrite(poton);
   lcdgotoxy(1, 10);
   lcdwrite(potbir);
   lcdgotoxy(1, 12);
   lcdwrite('o');
   lcdgotoxy(1, 13);
   lcdwrite('h');
   lcdgotoxy(1, 14);
   lcdwrite('m');
   ADCIntClear(ADC0_BASE, 2);
   ADCProcessorTrigger(ADC0_BASE, 2);
}

    int saniye=0;
    int dakika=0;
    int saat=0;

void Timerkesmefonk(void)
{
    int saniyeonlar=saniye/10;
    int saniye2=48+saniyeonlar;
    int saniyebirler=saniye%10;
    int saniye1=48+saniyebirler;
    int dakikaonlar=dakika/10;
    int dakika2=48+dakikaonlar;
    int dakikabirler=dakika%10;
    int dakika1=48+dakikabirler;
    int saatonlar=saat/10;
    int saat2=48+saatonlar;
    int saatbirler=saat%10;
    int saat1=48+saatbirler;
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
    lcdgotoxy(2, 5);
    lcdwrite(saat2);
    lcdgotoxy(2, 6); 
    lcdwrite(saat1);
    lcdgotoxy(2, 7);
    lcdwrite(0x2E);
    lcdgotoxy(2, 8);
    lcdwrite(dakika2);
    lcdgotoxy(2, 9); 
    lcdwrite(dakika1);
    lcdgotoxy(2, 10);
    lcdwrite(0x2E);
    lcdgotoxy(2, 11);
    lcdwrite(saniye2); 
    lcdgotoxy(2, 12);
    lcdwrite(saniye1);

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


}


int main(void)
{
    lcdfirstset();
    SysCtlDelay(5000000);
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_RCC_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    long a=SysCtlClockGet();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    IntMasterEnable();
    IntEnable(INT_TIMER0A);
    IntEnable(INT_ADC0SS2);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); 
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()-1);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 1, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 2, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 3, ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
    ADCIntClear(ADC0_BASE, 2);
    ADCIntRegister(ADC0_BASE, 2, adckesme);
    ADCIntEnable(ADC0_BASE, 2);
    ADCSequenceEnable(ADC0_BASE, 2);
    ADCProcessorTrigger(ADC0_BASE, 2); 
    while(1);

}

