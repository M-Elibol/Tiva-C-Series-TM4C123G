#ifndef LCD_H_
#define LCD_H_

#define LCDPORT                          GPIO_PORTB_BASE
#define rs                               GPIO_PIN_0 // pb0
#define E                                GPIO_PIN_1 // pb1
#define d4                               GPIO_PIN_4  // lcd db4=pb4
#define d5                               GPIO_PIN_5 // lcd db5=pb5
#define d6                               GPIO_PIN_6 // lcd db6=pb6
#define d7                               GPIO_PIN_7 // lcd db7=pb7

void lcdclear(void);
void lcdcom (unsigned char);
void lcdwrite(unsigned char); // single character
void lcdgotoxy(unsigned char, unsigned char);
void lcdfunctionset( unsigned char,unsigned char,unsigned char); // dl,N,F
void lcdfirstset(void);

#endif
