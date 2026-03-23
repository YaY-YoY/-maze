#include <windows.h>
/*
移動位置 gotoxy(int x, int y)
畫面清空 clrscr()
延遲幾秒 delay(int milliSecond) 
改變顏色 WORD setTextColor(WORD color) 
*/ 

static HANDLE hConsole = 0;
static int instanceCount = 0;

// 但這個要以管理員身分開啟才有成功... 
void SetConsoleFontSize(int fontSize) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0; // 字體寬度，0表示自動
    cfi.dwFontSize.Y = fontSize; // 字體高度（調整此處）
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); // 字型名稱
    
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y)
{
    COORD coord;
    
    if( instanceCount == 0 )
    {
        hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
        instanceCount = 1;
    }
    coord.X = x - 1;
    coord.Y = y - 1;
	
    SetConsoleCursorPosition( hConsole, coord );
}

void clrscr()
{
    COORD coordScreen = { 0, 0 }; /* here's where we'll home the cursor */
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
    DWORD dwConSize; /* number of character cells in the current buffer */

    if( instanceCount == 0 )
    {
        hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
        instanceCount = 1;
    }
  
    /* get the number of character cells in the current buffer */
    bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
  
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    /* fill the entire screen with blanks */
    bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
        dwConSize, coordScreen, &cCharsWritten);
  
    /* get the current text attribute */
    bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
  
    /* now set the buffer's attributes accordingly */
    bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten);
  
    /* put the cursor at (0, 0) */
    bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
  
    return;
}

void delay(int milliSecond)
{
    Sleep(milliSecond);
}

WORD setTextColor(WORD color)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WORD oldColor;
    
    if ( instanceCount == 0 )
    {
        hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
        instanceCount = 1;
    }
 
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        oldColor = csbi.wAttributes;
    else
        oldColor = FOREGROUND_RED | FOREGROUND_GREEN | 
                   FOREGROUND_BLUE | FOREGROUND_INTENSITY;
 
    if (color==0x00) color = FOREGROUND_RED | FOREGROUND_GREEN | 
                             FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    
    /* set text and background color */
    SetConsoleTextAttribute(hConsole, color);

    /* 
      FOREGROUND_BLUE(0x01), FOREGROUND_GREEN(0x02), FOREGROUND_RED(0x04), FOREGROUND_INTENSITY(0x08),
      BACKGROUND_BLUE(0x10), BACKGROUND_GREEN(0x20), BACKGROUND_RED(0x40), BACKGROUND_INTENSITY(0x80)
      藍色 綠色 紅色 調亮 
        在第二個參數中有這些屬性可以搭配，搭配的方式可以利用 "|"
      ex: FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE 
    */
    return oldColor;
}

/*
    WORD oldColor;
    oldColor = setTextColor(0x00e0);
    printf("Hello");
    setTextColor(oldColor);
*/

// 進一步的 console 操作請查看 MSDN Library "Consoles and Character Mode support"
// also a complete demo project is in MSDN Library "Console sample (console functions)"
