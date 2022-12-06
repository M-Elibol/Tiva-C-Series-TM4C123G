#ifndef LCD_H_
#define LCD_H_

#define LCDPORT                       GPIO_PORTB_BASE
#define RS                            GPIO_PIN_0//PB0
#define E                             GPIO_PIN_1//PB1
#define D4                            GPIO_PIN_4//PB4=D4
#define D5                            GPIO_PIN_5//PB5=D5
#define D6                            GPIO_PIN_6//PB6=D6
#define D7                            GPIO_PIN_7//PB7=D7

void lcdclear(void);
void lcdcom(unsigned char);
void lcdwrite(unsigned char);
void lcdgotoxy(unsigned char,unsigned char);
void lcdfunctionset(unsigned char,unsigned char,unsigned char);
void lcdtext(char*);
void lcdfirstset(void);
void lcdwait(void);

#endif
