#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "inc/hw_memmap.h"
#include "math.h"

void SetInitSettings();
int main(void)
{

    SetInitSettings();
    while(1){
          int a=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
          int b=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0);
          if(a==0){

              GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,2);
              SysCtlDelay(5000000);
              GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0);
              SysCtlDelay(5000000);
          }
          if(b==0){


              GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,2);
              SysCtlDelay(5000000);
              GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0);
              SysCtlDelay(5000000);

          }
    }

}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    uint32_t saat=SysCtlClockGet();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // PORT AKTIF HALE GECTI
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) =0x01;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0 );
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);
}
