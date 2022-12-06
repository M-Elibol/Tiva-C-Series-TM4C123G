#include"inc/tm4c123gh6pm.h"
#include "lcd.h"

void main(void)
{
    lcdfirstset();
    lcdgotoxy(1, 3);
    lcdwrite('A');
    while(1)
    {}
}
