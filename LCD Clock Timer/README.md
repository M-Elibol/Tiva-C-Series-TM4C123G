In this project, I implemented a clock on the LCD that starts from 00:00:00 and increases every second. I made the clock increment every second using a timer interrupt.
Some codes are written using a ready-made library. So be careful.
**I use Code Composer Studio IDE.

Important Note: The function named "perset" is assigned as extern void in the file "tm4c123gh6pm_startup_ccs.c" and should be written next to "Timer 0 subtimer A".
