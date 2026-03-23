#ifndef UTILWIN32_H
#define UTILWIN32_H

void gotoxy(int x, int y);

void clrscr();

void delay(int milliSecond);

WORD setTextColor(WORD color);

void HideCursor();

void SetConsoleFontSize(int fontSize);

#endif
