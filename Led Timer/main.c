#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
int a=2;
void timerkesmesi(){

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, a);
    //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));

}
int main(void){
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); // 40mhz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 123 output

    IntMasterEnable();
    IntEnable(INT_TIMER0A); // global kesme adresi

    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC); // asağı sayıcı
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()-1); // 4000000 yüklendii
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // eksi 1 olunca kesme üretsin
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerkesmesi); //gideceği kesme adresi
    TimerEnable(TIMER0_BASE, TIMER_A); // timer calısmaya basladı setb tr0
    while(1){}
}

