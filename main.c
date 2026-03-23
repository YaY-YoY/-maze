#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>

#include "utilwin32.h"
#define MAX 55

void pass();
void fail();
void choose_a(int ep);
void choose_b(int ep);
int Episode_a0();
int Episode_a1();
int Episode_b0();
int Episode_b1();
void sth();
int t = 0, life_a0 = 0, time_a1 = 0, rand_b0 = 0;
int total_score = 10;
bool hint_b1 = 0;
int chance = 0, min = 0, again[4] = {0}, no_die = 0, ans_sth = 0;
bool Achieve[10] = {0};
int played = 0;
int cout_x, cout_y;

int main(int argc, char *argv[]) {
	
	SetConsoleTitleA("迷宮 411179042");
	//最短路程 173 步 
	
	char maze[MAX/2][MAX];
    char c;
    int ch;
	int i, j;
	int m=1, n=3; //player在哪 
	bool a[2] = {0}, b[2] = {0}; //小關卡玩過 = 1 
	
	FILE *fp = fopen("maze.txt", "r");
    for(i=0; i<MAX/2; i++) 
       	for(j=0; j<MAX; j++) 
			fscanf(fp, "%c", &maze[i][j]); 
	fclose(fp);
	
	gotoxy(50, 8);
	setTextColor(0xD0 | 0x07);
	printf("迷          宮"); delay(300);
	setTextColor(0x00);
	gotoxy(20, 14);
	char *start_1 = "1. 步數增量 + 小關卡難度下降    2. 步數增量    3. 小關卡難度下降    4.原始版本";
	for(i=0; i<strlen(start_1); i++) {
		printf("%c", start_1[i]);
		delay(50);
	}
	gotoxy(45, 18);
	setTextColor(0x08);
	char *start_2 = "*建議第一次玩從難度1開始*";
	for(i=0; i<strlen(start_2); i++) {
		printf("%c", start_2[i]);
		delay(50);
	}
	do {
		c = getch();
	} while(c!='1' && c!='2' && c!='3' && c!='4');
	clrscr();
	if(c == '1') {
		t += 150;
		life_a0 += 5;
		time_a1 += 30;
		rand_b0 += 1;
		hint_b1 = 1;
		ans_sth += 40;
		total_score *= 1;
		gotoxy(40,13);
		setTextColor(0xE0);
		printf("選擇方案：步數增量 + 小關卡難度下降");
	}
	else if(c == '2') {
		t += 150;
		life_a0 += 3;
		time_a1 += 15;
		rand_b0 += 3;
		ans_sth += 25;
		total_score *= 2;				
		gotoxy(50,13);
		setTextColor(0xE0);
		printf("選擇方案：步數增量");
	}
	else if(c == '3') {
		t += 66;
		life_a0 += 5;
		time_a1 += 30;
		rand_b0 += 1;
		hint_b1 = 1;
		ans_sth += 40;
		total_score *= 3;
		gotoxy(45,13);
		setTextColor(0xE0);		
		printf("選擇難度：小關卡難度下降");
	}
	else {
		t += 66;
		life_a0 += 3;
		time_a1 += 15;
		rand_b0 += 3;
		ans_sth += 25;
		total_score *= 4;
		gotoxy(50,13);
		setTextColor(0xE0);
		printf("選擇難度：原始版本"); 
	}
	char *s[] = {"獲勝條件：", "在指定步數內通關迷宮，即由玩家初始點(P)移動至終點(E)。", 
				"圖內符號：", "可選擇是否進行關卡，關卡有一定風險", "強制進入關卡，但失敗也不會減少步數。" ,
				"鍵入上下左右以移動", };
	delay(1000);
	setTextColor(0x00);
	clrscr();
	cout_y = 3;
	for(j=0; j<6; j++) {
		if(cout_y==3 || cout_y==10 || cout_y==20) cout_x = 2;
		else cout_x = 3;
		gotoxy(cout_x, cout_y);
		if(cout_y == 13) {
			setTextColor(0xC0 | 0x07); printf(" ? "); //printf("\033[5m?\033[0m ");
			delay(50); setTextColor(0x00);
		}
		else if(cout_y == 16) {
			setTextColor(0x60 | 0x07); printf(" ! "); //printf("\033[5m!\033[0m ");
			delay(300); setTextColor(0x00);
		}
		for(i=0; i<strlen(s[j]); i++) {
			printf("%c", s[j][i]);
			delay(50);
		}
		if(j==4 || j==2) cout_y += 4;
		else cout_y += 3;
	}
	gotoxy(2, 24); delay(1000);
	setTextColor(0x30);
	printf("  Press Enter to START  \a"); 	
	setTextColor(0x00);

	do {
		ch = getch();
	} while(ch != '\r');
	
	if(ch == '\r') {
		//初始化地圖 
		clrscr();
		maze[m][n]='P';
		for(i=0; i<MAX/2; i++) //貼出迷宮圖 
			for(j=0; j<MAX; j++) {
				if(maze[i][j]=='+' || maze[i][j]=='=' ) {
					setTextColor(0x50);
					printf(" "); 
					setTextColor(0x00);
				} 
				else printf("%c", maze[i][j]);
			} 
			setTextColor(0xC0 | 0x07);
		//	printf("\033[5m");
			gotoxy(47, 13); printf(" ? ");
			gotoxy(31, 6); printf(" ? ");
			setTextColor(0x60 | 0x07);
		//	printf("\033[5m");	
			gotoxy(7, 22); printf(" ! ");	
			gotoxy(15, 14); printf(" ! ");
			setTextColor(0x90 | 0x07);
		//	printf("\033[5m");	
			gotoxy(51, 7); printf(" * ");
		//	printf("\033[0m");	
			setTextColor(0x00);	
		gotoxy(60,2); printf("剩餘步數：%04d", t--);
		
		while(ch=getch()) {
	    	switch(ch) {
	    	case 0xE0:
	    		maze[m][n]=' ';	
	    		gotoxy(n+1, m+1); puts(" ");
		        switch(ch=getch()) { //t++是為了在輸入不符合要求或撞牆時不會導致步數減少 
		            case 72:  if(maze[m-1][n]!='+') m--; else t++; break; //up
		            case 80:  if(maze[m+1][n]!='+') m++; else t++; break; //down
		            case 75:  if(maze[m][n-2]!='+') n-=2; else t++; break; //left
		            case 77:  if(maze[m][n+2]!='+') n+=2; else t++; break; //right
		            default:
		            	t++;
		           		break;
		        }
		        //win
		        if(maze[m][n]=='E') {
		        	clrscr();
		        	Achieve[0] = 1;
		        	pass();
					return 0;
				} 
		 		//路障
				else if(maze[m][n]=='!') {
					played += 1;
					clrscr();
					delay(500);
					gotoxy(2,2);
					srand((unsigned) time(NULL));
					int ep;
					for(;;){
						ep = rand()%2;
						if (a[ep] == 0) {
							a[ep] = 1;
							break;
						} 	
					}
					choose_a(ep);
					gotoxy(1,1);
					for(i=0; i<MAX/2; i++) //貼出迷宮圖 
						for(j=0; j<MAX; j++) {
							if(maze[i][j]=='+' || maze[i][j]=='=' ) {
								setTextColor(0x50);
								printf(" "); 
								setTextColor(0x00);
							} 
							else printf("%c", maze[i][j]);
						} 
				}
				//可選擇 
				else if(maze[m][n]=='?') {
					clrscr();
					gotoxy(2,2);
					printf("是否進入挑戰？ (Y/N) ");
					do {
						c = getch();
					} while(toupper(c) != 'Y' && toupper(c) != 'N');
					if(toupper(c) == 'Y') {
						srand((unsigned) time(NULL));
						int ep;
						for(;;) {
							ep = rand()%2;
							if (b[ep] == 0) {
								b[ep] = 1;
								break;
							} 	
						}
						choose_b(ep);
					}
					clrscr();
					gotoxy(1,1);
					for(i=0; i<MAX/2; i++) //貼出迷宮圖 
						for(j=0; j<MAX; j++) {
							if(maze[i][j]=='+' || maze[i][j]=='=' ) {
								setTextColor(0x50);
								printf(" "); 
								setTextColor(0x00);
							} 
							else printf("%c", maze[i][j]);
						} 
				}
				//數獨 
				else if(maze[m][n]=='*') {
					played += 1;
					clrscr();
					delay(500);
					gotoxy(2,2);
					sth();
					gotoxy(1,1);
					for(i=0; i<MAX/2; i++) //貼出迷宮圖 
						for(j=0; j<MAX; j++) {
							if(maze[i][j]=='+' || maze[i][j]=='=') {
								setTextColor(0x50);
								printf(" "); 
								setTextColor(0x00);
							} 
							else printf("%c", maze[i][j]);
						} 
				}
				//特殊牆 
				else if(maze[m][n]=='=') {
					Achieve[8] = 1;
					clrscr();
					gotoxy(20, 10);
					setTextColor(0xE0);
					printf("另  闢  蹊  徑");
					setTextColor(0x00);
					gotoxy(24, 12);
					printf("撞破特殊牆壁");
					delay(2000);
					clrscr();
					gotoxy(1,1);
					for(i=0; i<MAX/2; i++) //貼出迷宮圖 
						for(j=0; j<MAX; j++) {
							if(maze[i][j]=='+' || maze[i][j]=='=' ) {
								setTextColor(0x50);
								printf(" "); 
								setTextColor(0x00);
							} 
							else printf("%c", maze[i][j]);
						}
				}
		    	break;
		      default:
		      	t++; 
		        break;
		    }
		    maze[m][n]='P';
		    gotoxy(n+1, m+1); puts("P");
		    
			if(maze[5][31]=='?') { //貼出問號 
				gotoxy(31, 6);
				setTextColor(0xC0 | 0x07);
				printf(" ? ");
			//	printf("\033[5m?\033[0m");	
				setTextColor(0x00);			
			}
			if(maze[12][47]=='?') { //貼出問號 
				gotoxy(47, 13);
				setTextColor(0xC0 | 0x07);
				printf(" ? ");
			//	printf("\033[5m?\033[0m");	
				setTextColor(0x00);			
			} 
			if(maze[13][15]=='!') { //貼出驚嘆號
				gotoxy(15, 14);
				setTextColor(0x60 | 0x07);
				printf(" ! ");
			//	printf("\033[5m!\033[0m");	
				setTextColor(0x00);
			}
			if(maze[21][7]=='!') { //貼出驚嘆號 
				gotoxy(7, 22);
				setTextColor(0x60 | 0x07);
				printf(" ! ");	
			//	printf("\033[5m!\033[0m");	
				setTextColor(0x00);			
			}
			if(maze[6][51]=='*') { //貼出米字號 
				gotoxy(51, 7);
				setTextColor(0x90 | 0x07);
				printf(" * ");
			//	printf("\033[5m*\033[0m");	
				setTextColor(0x00);			
			}
			gotoxy(60,2); printf("剩餘步數：%04d", t--); //貼出步數 
			if(t<0) {
				if(no_die == 1) {
					clrscr();
					gotoxy(20, 10);
					setTextColor(0xE0);
					printf("迴  光  返  照");
					setTextColor(0x00);
					gotoxy(24, 12);
					printf("步數增量 20 遊戲繼續");
					delay(2000);
					t += 20;
					no_die = 0;
					clrscr();
					gotoxy(1,1);
					for(i=0; i<MAX/2; i++) //貼出迷宮圖 
						for(j=0; j<MAX; j++) {
							if(maze[i][j]=='+' || maze[i][j]=='=' ) {
								setTextColor(0x50);
								printf(" "); 
								setTextColor(0x00);
							} 
							else printf("%c", maze[i][j]);
						} 
					if(maze[5][31]=='?') { //貼出問號 
						gotoxy(31, 6);
						setTextColor(0xC0 | 0x07);
						printf(" ? ");	
					//	printf("\033[5m?\033[0m");	
						setTextColor(0x00);			
					}
					if(maze[12][47]=='?') { //貼出問號 
						gotoxy(47, 13);
						setTextColor(0xC0 | 0x07);
						printf(" ? ");
					//	printf("\033[5m?\033[0m");	
						setTextColor(0x00);			
					}
					if(maze[13][15]=='!') { //貼出驚嘆號
						gotoxy(15, 14);
						setTextColor(0x60 | 0x07);
						printf(" ! ");
					//	printf("\033[5m!\033[0m");	
						setTextColor(0x00);
					}
					if(maze[21][7]=='!') { //貼出驚嘆號 
						gotoxy(7, 22);
						setTextColor(0x60 | 0x07);
						printf(" ! ");	
					//	printf("\033[5m!\033[0m");	
						setTextColor(0x00);			
					}
					if(maze[6][51]=='*') { //貼出米字號 
						gotoxy(51, 7);
						setTextColor(0x90 | 0x07);
						printf(" * ");
					//	printf("\033[5m*\033[0m");	
						setTextColor(0x00);			
					}
					gotoxy(60,2); printf("剩餘步數：%04d", t); //貼出步數 
				}
				else {
					clrscr();
		        	fail();
					return 0;
				}
			}
		}
	}
	return 0;
}

void pass() {
	printf("\n");
	setTextColor(0xA0);
	printf("  PPPPPPPPPPPPPPPPP            AAA                    SSSSSSSSSSSSSSS        SSSSSSSSSSSSSSS    \n");
    printf("  P::::::::::::::::P          A:::A                  SS:::::::::::::::S     SS:::::::::::::::S  \n");
    printf("  P::::::PPPPPP:::::P        A:::::A                S:::::SSSSSS::::::S    S:::::SSSSSS::::::S  \n");
    printf("  PP:::::P     P:::::P      A:::::::A               S:::::S     SSSSSSS    S:::::S     SSSSSSS  \n");
    printf("    P::::P     P:::::P     A:::::::::A              S:::::S                S:::::S              \n");
    printf("    P::::P     P:::::P    A:::::A:::::A             S:::::S                S:::::S              \n");
    printf("    P::::PPPPPP:::::P    A:::::A A:::::A             S::::SSSS              S::::SSSS           \n");
    printf("    P:::::::::::::PP    A:::::A   A:::::A             SS::::::SSSSS          SS::::::SSSSS      \n");
    printf("    P::::PPPPPPPPP     A:::::A     A:::::A              SSS::::::::SS          SSS::::::::SS    \n");
    printf("    P::::P            A:::::AAAAAAAAA:::::A                SSSSSS::::S            SSSSSS::::S   \n");
    printf("    P::::P           A:::::::::::::::::::::A                    S:::::S                S:::::S  \n");
    printf("    P::::P          A:::::AAAAAAAAAAAAA:::::A                   S:::::S                S:::::S  \n");
    printf("  PP::::::PP       A:::::A             A:::::A      SSSSSSS     S:::::S    SSSSSSS     S:::::S  \n");
    printf("  P::::::::P      A:::::A               A:::::A    S::::::SSSSSS:::::S    S::::::SSSSSS:::::S   \n");
    printf("  P::::::::P     A:::::A                 A:::::A    S:::::::::::::::SS     S:::::::::::::::SS   \n");
    printf("  PPPPPPPPPP    AAAAAAA                   AAAAAAA    SSSSSSSSSSSSSSS         SSSSSSSSSSSSSSS    \n\n");
    delay(1000);
    setTextColor(0x00);
    total_score *= t;
    int i; 
	int k = 0;
    for(i=0; i<10; i++) if(Achieve[i] == 1) total_score += 100;
    if(played == 5) total_score += 200;
    printf("通關分數： %d\n", total_score);
    printf("成 就 ：\n"); delay(500);
    setTextColor(0xE0); 
    if(Achieve[0] == 1) {printf("遊  戲  通  關\n"); delay(100);}
    if(Achieve[1] == 1) {printf("後  顧  無  憂\n"); delay(100);}
    if(Achieve[2] == 1) {printf("及  時  止  損\n"); delay(100);}
    if(Achieve[3] == 1) {printf("金  剛  護  體\n"); delay(100);}
    if(Achieve[4] == 1) {printf("捲  土  重  來\n"); delay(100);}
    if(Achieve[5] == 1) {printf("迴  光  返  照\n"); delay(100);}
    if(Achieve[6] == 1) {printf("天  選  之  人\n"); delay(100);}
    if(Achieve[7] == 1) {printf("交  臂  失  之\n"); delay(100);}
    if(Achieve[8] == 1) {printf("另  闢  蹊  徑\n"); delay(100);}
    if(Achieve[9] == 1) {printf("不  務  正  業\n"); delay(100);}
    if(played == 5) {printf("躍  躍  欲  試  (所有關卡都有遊玩)\n"); delay(100);}
    setTextColor(0x00);
}

void fail() {
	printf("\n");
	setTextColor(0x40);
	printf("  FFFFFFFFFFFFFFFFFFFF          AAA                IIIIIIIIIIIIIIIIIIIII    LLLLLLLLLL                \n");
    printf("  F::::::::::::::::::F         A:::A               II:::::::::::::::::II    L::::::::L                \n");
    printf("  F:FFFFFFFFFFFFFFFFFF        A:::::A              IIIIIII:::::::IIIIIII    L::::::::L                \n");
    printf("  FF:::::F                   A:::::::A                   I:::::::I          L::::::::L                \n");
    printf("    F::::F                  A:::::::::A                  I:::::::I          L::::::::L                \n");
    printf("    F::::F        FFFF     A:::::A:::::A                 I:::::::I          L::::::::L                \n");
    printf("    F::::FFFFFFFFF:::F    A:::::A A:::::A                I:::::::I          L::::::::L                \n");
    printf("    F::::::::::::::::F   A:::::A   A:::::A               I:::::::I          L::::::::L                \n");
    printf("    F::::FFFFFFFFF:::F  A:::::A     A:::::A              I:::::::I          L::::::::L                \n");
    printf("    F::::F        FFFF A:::::AAAAAAAAA:::::A             I:::::::I          L::::::::L                \n");
    printf("    F::::F            A:::::::::::::::::::::A            I:::::::I          L::::::::L                \n");
    printf("    F::::F           A:::::AAAAAAAAAAAAA:::::A           I:::::::I          L::::::::L                \n");
    printf("    F::::F          A:::::A             A:::::A          I:::::::I          L::::::::LLLLLLLLLLLLLLL  \n");
    printf("  FF::::::FF       A:::::A               A:::::A   IIIIIII:::::::IIIIIII    L:::::::::::::::::::::LL  \n");
    printf("  F::::::::F      A:::::A                 A:::::A  II:::::::::::::::::II    L:::::::::::::::::::::LL  \n");
    printf("  FFFFFFFFFF     AAAAAAA                   AAAAAAA IIIIIIIIIIIIIIIIIIIII    LLLLLLLLLLLLLLLLLLLLLLLL  \n\n");
    delay(1000);
	setTextColor(0x00);
    printf("成 就 ：\n"); delay(500);
    setTextColor(0xE0); 
    if(Achieve[0] == 0) {printf("遊  戲  失  敗\n"); delay(100);}
    if(Achieve[1] == 1) {printf("後  顧  無  憂\n"); delay(100);}
    if(Achieve[2] == 1) {printf("及  時  止  損\n"); delay(100);}
    if(Achieve[3] == 1) {printf("金  剛  護  體\n"); delay(100);}
    if(Achieve[4] == 1) {printf("捲  土  重  來\n"); delay(100);}
    if(Achieve[5] == 1) {printf("迴  光  返  照\n"); delay(100);}
    if(Achieve[6] == 1) {printf("天  選  之  人\n"); delay(100);}
    if(Achieve[7] == 1) {printf("交  臂  失  之\n"); delay(100);}
    if(Achieve[8] == 1) {printf("另  闢  蹊  徑\n"); delay(100);}
    if(Achieve[9] == 1) {printf("不  務  正  業\n"); delay(100);}
    if(played == 5) {printf("躍  躍  欲  試  (所有關卡都有遊玩)\n"); delay(100);}
    setTextColor(0x00);
}

void choose_a(int ep) { //步數只會增加 至少兩個 
	if(ep==0) t+=Episode_a0();
	else if(ep==1) t+=Episode_a1();
}

void choose_b(int ep) { //可選擇參加與否
	if(ep==0) {
		int k = Episode_b0();
		if(k==5)
			t=t*log10(t);
		else if(min==0) t-=(5-k)*5;
		else {
			clrscr();
			gotoxy(20, 10);
			setTextColor(0xE0);
			printf("金  剛  護  體");
			setTextColor(0x00);
			gotoxy(24, 12);
			printf("挑戰失敗不扣步數");
			delay(2000);
		}
	}
	if(ep==1) {
		int k = Episode_b1();
		if(k==30) 
			t=t*log10(t);
		else if(min==0) t-=(30-k);
		else {
			clrscr();
			gotoxy(20, 10);
			setTextColor(0xE0);
			printf("金  剛  護  體");
			setTextColor(0x00);
			gotoxy(24, 12);
			printf("挑戰失敗不扣步數");
			delay(2000);
		}
	}
}

int Episode_a0() {

	int row;
	char c, ch;
	char CH[52];
	int score=0, life=life_a0;
	
	int i, j;
	for(i='A',j=0; i<='Z'; i++,j++)
		CH[j]=i;
	for(i='a'; i<='z'; i++,j++)
		CH[j]=i;
	
	//規則說明 
	clrscr();
	gotoxy(1,1);
	printf("打字遊戲\a");
	delay(1000); gotoxy(3,4);
	char *s[] = {"依照指示輸入字母", 
				"若與螢幕上出現的相同，則獲得一分", 
				"若與螢幕上出現的不相同或者字母達到底端，則生命減一",
				"當生命為 0 時，遊戲結束，最終得分即為增加步數",
				"本關卡不會減少步數"};
	cout_y = 4, cout_x = 3;
	for(j=0; j<5; j++) {
		gotoxy(cout_x, cout_y);
		for(i=0; i<strlen(s[j]); i++) {
			printf("%c", s[j][i]);
			delay(50);
		}
		cout_y += 2;
	}
	delay(555); gotoxy(3,15); 
	printf("Press Enter to start\a");
	
	do {
		ch = getch();
	} while(ch != '\r');
	if(ch == '\r') {
		HideCursor();
		gotoxy(3,15);  setTextColor(0x20 | 0x07);
		printf("     遊    戲    開    始     \a"); 
		setTextColor(0x00); delay(1000); clrscr();
		
		srand((unsigned) time(NULL));
		
		setTextColor(0x00);
		gotoxy(2,2);
		puts("| Score = 00 | | Life = 3 |");
		gotoxy(1,20);
		puts("--------------------------");
				
		while(score < 100) {
			ch = CH[rand() % 52];
			
			setTextColor(0x00); //White
			gotoxy(2,2);
			printf("| Score = %02d | | Life = %d |", score, life);
			gotoxy(1,20);
			puts("--------------------------");
			
			for (row=3; row<=20; row++) {
				
				if (kbhit()) {
					c=getch();
					
					//打對 
					if (c == ch) {
						putchar(' ');
						score++;
						clrscr();
						break;	
					}
					//打錯 
					else{
						printf("\a");
						life--;
						clrscr();
					}
					//修正 no life 直接 return 0 
					if(life != 0) {
						gotoxy(2,2);
						printf("Score = %02d |  | Life = %d", score, life);
						gotoxy(1,20);
						puts("--------------------------"); 	
					}
			 	}
			 	
				//觸底 
				else  { 
					if(row==20){
						life--;
						clrscr();
					}
				}
				
				//Game Over
				if(life == 0) {
					if(again[1] == 1) {
						clrscr();
						life = 1;
						again[1] = 0;
						gotoxy(20, 10);
						setTextColor(0xE0);
						printf("捲  土  重  來");
						setTextColor(0x00);
						gotoxy(24, 12);
						printf("各關卡中有一次免死金牌");
						delay(2000);
						gotoxy(2,2);
						printf("Score = %02d |  | Life = %d", score, life);
						gotoxy(1,20);
						puts("--------------------------");
					}
					else {
						setTextColor(0x00);
						return score;
					}
				}
				
				//移動 
				putchar(' ');
				gotoxy(16,row);
				setTextColor(0x04); //Red
				putchar(ch);
				delay(300);
				gotoxy(16,row);
			}
		}
		clrscr();
		gotoxy(20, 10);
		setTextColor(0xE0);
		printf("不  務  正  業");
		Achieve[9] = 1;
		setTextColor(0x00);
		printf("迷宮才是本體啊啊啊（╯= ^ =）╯╧╧");
		delay(2000);
		clrscr();
		return score;
	}
}

int Episode_a1() {
	
	int i, j, m, n, k;
	srand((unsigned) time(NULL));
	int a[6][6] = {0}, b[18], c[26], A[6][6];
	bool d[18] = {0};
	int n1, n2;
	int num = 1;
	int sec;
	
	for(i=0; i<6; i++)
		for(j=0; j<6; j++)
			A[i][j] = num++;
	for(i='A', j=0; i<='Z'; i++, j++) c[j] = i;
	for(i=0; i<18; i++) b[i] = c[rand()%26];
	for(i=0; i<18; i++) {
		do {
			m = (rand()) % 6;
			n = (rand()) % 6;
		} while(a[m][n] != 0); 
		do {
			k = (rand()) % 18;
		} while(d[k] != 0); 
		a[m][n] = b[k];
		d[k] = 1;
	}
	for(i=0; i<18; i++) {
		do {
			m = (rand()) % 6;
			n = (rand()) % 6;
		} while(a[m][n] != 0); 
		do {
			k = (rand()) % 18;
		} while(d[k] != 1); 
		a[m][n] = b[k];
		d[k] = 0;
	}
	
	//規則說明 
	clrscr();
	gotoxy(1,1);
	printf("字母配對\a");
	delay(1000); gotoxy(3,4);
	char *s1[] = {"起初有 ", " 秒的記憶時間，"};
	for(i=0; i<strlen(s1[0]); i++) {
		printf("%c", s1[0][i]);
		delay(50);
	}
	printf("%d", time_a1);
	for(i=0; i<strlen(s1[1]); i++) {
		printf("%c", s1[1][i]);
		delay(50);
	}
	char *s[] = {"依照指示輸入字母", 
				"在 6x6 的矩陣中，將相同的字母兩兩配對",
				"當所有的字母皆配對完成，則遊戲結束",
				"遊戲時間為 240 秒，依照遊戲時間會獲得相對應的步數",
				"本關卡不會減少步數"};
	cout_y = 6, cout_x = 3;
	for(j=0; j<5; j++) {
		gotoxy(cout_x, cout_y);
		for(i=0; i<strlen(s[j]); i++) {
			printf("%c", s[j][i]);
			delay(50);
		}
		cout_y += 2;
	}
	
	delay(1000); gotoxy(3,17); 
	printf("Press Enter to start\a");
	char ch;
	do {
		ch = getch();
	} while(ch != '\r');
	
	if(ch == '\r') {
		gotoxy(3,17);  setTextColor(0x20 | 0x07);
		printf("     遊    戲    開    始     \a");
		setTextColor(0x00); delay(1000); clrscr(); 
		
		//原圖 
		for(i=0, k=0; i<6; i++, k+=3) {
			gotoxy(20,5+k);
			for(j=0; j<6; j++)
				printf("  %c   ", a[i][j]);
		} 
		for(i=time_a1; i>=1; i--) {
			gotoxy(65, 13);
			printf("%02d\a", i);
			delay(1000);
		}
		sec = time(NULL);
		while(1) {
			clrscr();
			//展示圖  
			for(i=0, k=0; i<6; i++, k+=3) { 
				gotoxy(20,5+k);
				for(j=0; j<6; j++) {
					if(A[i][j] == 0) printf("      ");
					else printf("  %02d  ", A[i][j]);
				}
			}
			//第一個位置 
			gotoxy(65, 8);
			printf("輸入第一個位置所代表的數字："); 
			while(1) {
				do {
				    gotoxy(93, 8);
					scanf("%d", &n1);
				} while(n1<1 || n1>36);
				if(n1%6 == 0)
					if(A[n1/6-1][5] != 0) break;
					else {
						gotoxy(93, 8);
						printf("  ");
					}
				if(n1%6 != 0)
					if(A[n1/6][n1%6-1] != 0) break;
					else {
						gotoxy(93, 8);
						printf("  ");
					}
			}
			if(n1%6==0) {
				gotoxy(52, 5+((n1/6)-1)*3);
				setTextColor(0xB0);
				printf(" %c ", a[n1/6-1][5]);
				setTextColor(0x00);
			}
			else {
				gotoxy(19+3*(n1%6-1)+3*(n1%6), 5+(n1/6)*3);
				setTextColor(0xB0);
				printf(" %c ", a[n1/6][n1%6-1]);
				setTextColor(0x00);
			}
			//第二個位置 
			gotoxy(65, 17);
			printf("輸入第二個位置所代表的數字："); 
			while(1) {
				do {
					gotoxy(93, 17);
					scanf("%d", &n2);
				} while(n2<1 || n2>36);
				if(n2 == n1) {
					gotoxy(93, 17);
					printf("  ");
				}
				else {
					if(n2%6 == 0)
						if(A[n2/6-1][5] != 0) break;
						else {
							gotoxy(93, 17);
							printf("  ");
						}
					if(n2%6 != 0)
						if(A[n2/6][n2%6-1] != 0) break;
						else {
							gotoxy(93, 17);
							printf("  ");
						}
				}
			}
			if(n2%6==0) {
				gotoxy(52, 5+((n2/6)-1)*3);
				setTextColor(0xB0);
				printf(" %c ", a[n2/6-1][5]);
				setTextColor(0x00);
			}
			else {
				gotoxy(16+6*(n2%6), 5+(n2/6)*3);
				setTextColor(0xB0);
				printf(" %c ", a[n2/6][n2%6-1]);
				setTextColor(0x00);
			}
			delay(444);
			//判斷是否相等 
			if(a[n1/6][n1%6-1] == a[n2/6][n2%6-1]) {
				A[n1/6][n1%6-1] = 0;
				A[n2/6][n2%6-1] = 0;
			}
			k=0;
			for(i=0; i<6; i++)
				for(j=0; j<6; j++)
					if(A[i][j] != 0)
						k=1;
			if(k==0) {
				clrscr();
				sec = time(NULL) - sec;
				if(t>1) {
					int score = 60*log10(240-sec); 
					return score; 
				}
				else if(sec == 1) return 10;
				else return 0;
			}
		}
	}
}

int Episode_b0() {
	
	int in, out;
	int i, j, m, n, k;
	int sum, ans, totalIn, totalOut;
	srand((unsigned) time(NULL));
	
	//規則說明 
	clrscr();
	gotoxy(1,1);
	printf("進進出出\a");
	delay(1000);
	char *s[] = {"請先依照題目指示計算進出數量，待題目播放結束後回答問題",
				"總共有五題，若回答正確，則播放下一題題目",
				"若回答錯誤，則遊戲結束，每答錯一題步數 -5，未答也視為答錯",
				"全對者步數將變為原始步數取 log 後再乘以原始步數"};
	cout_y = 4, cout_x = 3;
	for(j=0; j<4; j++) {
		gotoxy(cout_x, cout_y);
		for(i=0; i<strlen(s[j]); i++) {
			printf("%c", s[j][i]);
			delay(50);
		}
		cout_y += 2;
	}
	delay(500); gotoxy(3, 12);
	if(rand_b0 == 1) {
		char *s1 = "每題題目皆為 -> 回答最後剩餘的數量";
		for(i=0; i<strlen(s1); i++) {
			printf("%c", s1[i]);
			delay(50);
		}
	}
	else {
		char *s1 = "題型有三種  (1)進入數量  (2)離開數量  (3)剩餘數量";
		for(i=0; i<strlen(s1); i++) {
			printf("%c", s1[i]);
			delay(50);
		}
	}
	delay(500); gotoxy(3,15); 
	if(chance) {
		setTextColor(0xE0);
		printf("及  時  止  損\n\n\a");
		setTextColor(0x00);
		char *s1 = "你有機會可以選擇不要遊玩，是否仍要進入？ (Y/N)";
		for(i=0; i<strlen(s1); i++) {
			printf("%c", s1[i]);
			delay(50);
		}
		char c;
		do {
			c = getch();
		} while(toupper(c) != 'Y' && toupper(c) != 'N');
		if(toupper(c)=='N') return 0;
	}
	played += 1;
	gotoxy(3,15);
	puts("              ");
	gotoxy(3,17); 
	printf("Press Enter to Start\a");
	
	char ch;
	do {
		ch = getch();
	} while(ch != '\r');
	
	if(ch == '\r') {
		gotoxy(3,17);  setTextColor(0x20 | 0x07);
		printf("     遊    戲    開    始     \a");
		setTextColor(0x00); delay(1000); clrscr();
		
		gotoxy(10,10); printf("第一題為練習不計分"); 
		delay(1000); 
		// 總共1+5題
		for (j=0; j<6; j++) {
			clrscr();
			gotoxy(18,10);
			printf("Press anykey to Start...");
			getch();
			clrscr();
			sum = rand()%6+1;
			totalIn=0, totalOut=0;
			
			if(sum == 1) {
				gotoxy(31, 10);
				setTextColor(0x30);
				printf("  ");
				setTextColor(0x00);
				printf("  ");
			}
			else if(sum == 2) {
				gotoxy(29, 10);
				for(i=0; i<2; i++) {
					setTextColor(0x30);
					printf("  ");
					setTextColor(0x00);
					printf("  ");
				}
			}
			else if(sum == 3) {
				gotoxy(28, 10);
				for(i=0; i<3; i++) {
					setTextColor(0x30);
					printf("  ");
					setTextColor(0x00);
					printf(" ");
				}
			}
			else if(sum == 4) {
				gotoxy(29, 9);
				for(i=0; i<2; i++) {
					setTextColor(0x30);
					printf("  ");
					setTextColor(0x00);
					printf("  ");
				}
				gotoxy(29, 11);
				for(i=0; i<2; i++) {
					setTextColor(0x30);
					printf("  ");
					setTextColor(0x00);
					printf("  ");
				}
			}
			else if(sum == 5) {
				gotoxy(29, 9);
				for(i=0; i<2; i++) {
					setTextColor(0x30);
					printf("  ");
					setTextColor(0x00);
					printf("  ");
				}
				gotoxy(31, 10);
				setTextColor(0x30);
				printf("  ");
				setTextColor(0x00);
				printf("  ");
				gotoxy(29, 11);
				for(i=0; i<2; i++) {
					setTextColor(0x30);
					printf("  ");
					setTextColor(0x00);
					printf("  ");
				}
			}
			else {
				gotoxy(28, 9);
				for(i=0; i<3; i++) {
					setTextColor(0x30);
					printf("  ");
					setTextColor(0x00);
					printf(" ");
				}
				gotoxy(28, 11);
				for(i=0; i<3; i++) {
					setTextColor(0x30);
					printf("  ");
					setTextColor(0x00);
					printf(" ");
				}
			}
			
			delay(1000);
			for(k=1; k<7; k++) {
				setTextColor(0xA0);
				gotoxy(27, k);  printf("          "); 
				gotoxy(27, k+1);  printf("          "); 
				gotoxy(27, k+2);  printf("          ");
				gotoxy(27, k+3);  printf("          "); 
				gotoxy(27, k+4);  printf("          "); 
				delay(15);
				setTextColor(0x00);
				gotoxy(27, k);  printf("          "); 
				gotoxy(27, k+1);  printf("          "); 
				gotoxy(27, k+2);  printf("          ");
				gotoxy(27, k+3);  printf("          "); 
				gotoxy(27, k+4);  printf("          ");  
			}
			for(i=0; i<6; i++) {
				clrscr();
				setTextColor(0xA0);
				gotoxy(27, 8);  printf("          "); 
				gotoxy(27, 9);  printf("          "); 
				gotoxy(27, 10);  printf("          ");
				gotoxy(27, 11);  printf("          "); 
				gotoxy(27, 12);  printf("          "); 
				setTextColor(0x00);
				gotoxy(15, 5); printf("進 -> -> -> -> -> -> -> -> -> -> 出");
				//in 
				in = rand()%5;
				sum += in;
				totalIn += in;
				//out
				if(i>2) {
					do {
						out = rand() % 5;
					} while(out > sum);
					sum -= out;	
					totalOut += out;
				}
				else out = 0;
				for(m=(5-in)*4, n=36; m<(5-in)*4+9, n<45; m++, n++) {
					gotoxy(m, 10);
					for(k=0; k<in; k++) {
						setTextColor(0x00);
						printf("  ");
						setTextColor(0x30);
						printf("  ");
					}
					gotoxy(n, 10);
					for(k=0; k<out; k++) {
						setTextColor(0x30);
						printf("  ");
						setTextColor(0x00);
						printf("  ");
					}
					delay(150);
					gotoxy(m, 10);
					for(k=0; k<in; k++) {
						setTextColor(0x00);
						printf("    ");
					}
					gotoxy(n, 10);
					for(k=0; k<out; k++) {
						setTextColor(0x00);
						printf("    ");
					}
				}
			} //題目播放結束 
			
			//三種問題 
			i = rand()%rand_b0;
			clrscr();
			if(i==0) {
				setTextColor(0xA0);
				gotoxy(15, 8);  printf("          "); 
				gotoxy(15, 9);  printf("          "); 
				gotoxy(15, 10);  printf("          ");
				gotoxy(15, 11);  printf("          "); 
				gotoxy(15, 12);  printf("          "); 
				setTextColor(0x30); 
				gotoxy(39, 10); printf("  ");
				setTextColor(0x00);
				gotoxy(26,10);
				printf("後面有多少個");
				gotoxy(15,15);		
				printf("Ans: ");
				scanf("%d", &ans);
				if(ans != sum && j != 0) {
					if(again[2] == 1) {
						clrscr();
						again[2] = 0;
						gotoxy(20, 10);
						setTextColor(0xE0);
						printf("捲  土  重  來");
						setTextColor(0x00);
						gotoxy(24, 12);
						printf("各關卡中有一次免死金牌");
						delay(2000);
					}
					else {
						gotoxy(15,15);
						setTextColor(0x04);
						printf("正解為： %d", sum);
						setTextColor(0x00);
						delay(1000);
						return j;
					}
				}
				else if(j==0) {
					if(ans != sum) {
						gotoxy(15,15);
						setTextColor(0x04);
						printf("正解為： %d", sum);
						delay(500);
						gotoxy(15,17);
						printf("遊戲正式開始");
						setTextColor(0x00);
						delay(1500);
					}
					else {
						gotoxy(15,15);
						setTextColor(0x02);
						printf("回答正確");
						delay(500);
						gotoxy(15,17);
						printf("遊戲正式開始");
						setTextColor(0x00);
						delay(1500);
					}
				}
				else {
					gotoxy(15,15);
					setTextColor(0x02);
					printf("回答正確");
					setTextColor(0x00);
					delay(2000);	
				}
			}
			else if(i==1) {
				setTextColor(0x30); 
				gotoxy(24, 10); printf("  ");
				setTextColor(0x00);
				gotoxy(15,10); printf("有多少個");
				gotoxy(27,10); printf("進入了");
				gotoxy(15,15);		
				printf("Ans: ");
				scanf("%d", &ans);
				if(ans != totalIn && j != 0) {
					if(again[2] == 1) {
						clrscr();
						again[2] = 0;
						gotoxy(20, 10);
						setTextColor(0xE0);
						printf("捲  土  重  來");
						setTextColor(0x00);
						gotoxy(24, 12);
						printf("各關卡中有一次免死金牌");
						delay(2000);
					}
					else {
						gotoxy(15,15);
						setTextColor(0x04);
						printf("正解為： %d", totalIn);
						setTextColor(0x00);
						delay(1000);
						return j;
					}
				}
				else if(j == 0) {
					if(ans != totalIn) {
						gotoxy(15,15);
						setTextColor(0x04);
						printf("正解為： %d", totalIn);
						delay(500);
						gotoxy(15,17);
						printf("遊戲正式開始");
						setTextColor(0x00);
						delay(1500);
					}
					else {
						gotoxy(15,15);
						setTextColor(0x02);
						printf("回答正確");
						delay(500);
						gotoxy(15,17);
						printf("遊戲正式開始");
						setTextColor(0x00);
						delay(1500);
					}
				}
				else {
					gotoxy(15,15);
					setTextColor(0x02);
					printf("回答正確");
					setTextColor(0x00);
					delay(2000);	
				}
			}
			else {
				setTextColor(0x30); 
				gotoxy(24, 10); printf("  ");
				setTextColor(0x00);
				gotoxy(15,10); printf("有多少個");
				gotoxy(27,10); printf("離開了");
				gotoxy(15,15);		
				printf("Ans: ");
				scanf("%d", &ans);
				if(ans != totalOut && j != 0) {
					if(again[2] == 1) {
						clrscr();
						again[2] = 0;
						gotoxy(20, 10);
						setTextColor(0xE0);
						printf("捲  土  重  來");
						setTextColor(0x00);
						gotoxy(24, 12);
						printf("各關卡中有一次免死金牌");
						delay(2000);
					}
					else {
						gotoxy(15,15);
						setTextColor(0x04);
						printf("正解為： %d", totalOut);
						setTextColor(0x00);
						delay(1000);
						return j;
					}
				}
				else if(j==0) {
					if(ans != totalOut) {
						gotoxy(15,15);
						setTextColor(0x04);
						printf("正解為： %d", totalOut);
						delay(500);
						gotoxy(15,17);
						printf("遊戲正式開始");
						setTextColor(0x00);
						delay(1500);
					}
					else {
						gotoxy(15,15);
						setTextColor(0x02);
						printf("回答正確");
						delay(500);
						gotoxy(15,17);
						printf("遊戲正式開始");
						setTextColor(0x00);
						delay(1500);
					}
				}
				else {
					gotoxy(15,15);
					setTextColor(0x02);
					printf("回答正確");
					setTextColor(0x00);
					delay(2000);	
				}
			}
		}
		return j;
	}
}

int Episode_b1() {
	//規則說明
	clrscr();
	gotoxy(1,1);
	printf("英文拼字\a");
	delay(1000);
	char *s[] = {"左側畫面會有隨機字母掉落，右側畫面為玩家輸入區域",
				"在字母掉落途中，玩家可利用右上方暫存區作筆記",
				"待字母掉落至底部，暫存區將會關閉輸入模式，玩家需於答案區鍵入答案",
				"若回答正確，則播放下一題題目",
				"若回答錯誤，則遊戲結束，完成的單詞越多，步數扣得越少",
				"總共有三個不同主題的關卡，每一個關卡有十個題目",
				"全對者步數將變為 原始步數取 log 後再乘以原始步數 "};
	cout_y = 4, cout_x = 3;
	int i, j;
	for(j=0; j<7; j++) {
		gotoxy(cout_x, cout_y);
		for(i=0; i<strlen(s[j]); i++) {
			printf("%c", s[j][i]);
			delay(50);
		}
		cout_y += 2;
	}
	delay(500); gotoxy(3,19); 
	if(chance) {
		setTextColor(0xE0);
		printf("及  時  止  損\n\n\a");
		setTextColor(0x00);
		char *s1 = "你有機會可以選擇不要遊玩，是否仍要進入？ (Y/N)";
		for(i=0; i<strlen(s1); i++) {
			printf("%c", s1[i]);
			delay(50);
		}
		char c;
		do {
			c = getch();
		} while(toupper(c) != 'Y' && toupper(c) != 'N');
		if(toupper(c)=='N') return 0;
	}
	played += 1;
	gotoxy(3,21); delay(2000);
	printf("Press Enter to Start\a");
	
	char ch;
	do {
		ch = getch();
	} while(ch != '\r');
	if(ch == '\r') {
		gotoxy(3,21);  setTextColor(0x20 | 0x07);
		printf("     遊    戲    開    始     \a");
		setTextColor(0x00); delay(1000); clrscr();
		
		char *a1[]={"ape", "deer", "wolf", "turtle", "monkey", "elephant", "goat", "chicken", "rabbit", "dinosaur"};
		char *a2[]={"coconut", "tomato", "cherry", "peach", "guava", "mango", "grape", "strawberry", "watermelon", "avocado"};
		char *a3[]={"bank", "campus", "studio", "bookstore", "museum", "hospital", "prison", "library", "restaurant", "supermarket"};
		char b[25][5]; //輸出的陣列 
		int i, j, x, y, countx, county;
		char ch; //暫存區 
		char c[20]; //答案字串 
		int sum = 0;
		srand((unsigned) time(NULL));
		HideCursor(); 
		int T;
		for(T=0; T<3; T++) {
			if(T==0) {
				gotoxy(10,10); printf("第一關：動物"); delay(1000); clrscr();
			} 
			else if(T==1) {
				gotoxy(10,10); printf("第二關：水果"); delay(1000); clrscr();
			}
			else if(T==2) {
				gotoxy(10,10); printf("第三關：場所"); delay(1000); clrscr();
			}
			for(i=0; i<10; i++) {
				countx = 0; county = 0;
				gotoxy(1,25); puts("-------------------------");
				gotoxy(38, 2); puts("移動中時的文字暫存區：");
				//清空隨機輸出矩陣
				for(y=0; y<5; y++)
					for(x=0; x<25; x++)
						b[x][y] = ' ';
				if(T==0) {
					for(j=0; j<strlen(a1[i]); j++) {
						do {
							x = rand() % 20 + 3;
							y = rand() % 5;
						} while(b[x][y] != ' ' || b[x-1][y] != ' ' || b[x+1][y] != ' ' || b[x][y-1] != ' ' || b[x][y+1] != ' ' || b[x-2][y] != ' ' || b[x+2][y] != ' ' ); //間隔拉大 
						b[x][y] = a1[i][j];
					}
				}
				else if(T==1) {
					for(j=0; j<strlen(a2[i]); j++) {
						do {
							x = rand() % 20 + 3;
							y = rand() % 5;
						} while(b[x][y] != ' ' || b[x-1][y] != ' ' || b[x+1][y] != ' ' || b[x][y-1] != ' ' || b[x][y+1] != ' ' || b[x-2][y] != ' ' || b[x+2][y] != ' ' ); //間隔拉大 
						b[x][y] = a2[i][j];
					}
				}
				else if(T==2) {
					for(j=0; j<strlen(a3[i]); j++) {
						do {
							x = rand() % 20 + 3;
							y = rand() % 5;
						} while(b[x][y] != ' ' || b[x-1][y] != ' ' || b[x+1][y] != ' ' || b[x][y-1] != ' ' || b[x][y+1] != ' ' || b[x-2][y] != ' ' || b[x+2][y] != ' ' ); //間隔拉大 
						b[x][y] = a3[i][j];
					}
				}	
				for (j=3; j<25; j++) {
					//移動
					gotoxy(1, j);
					if(j<7) {
						for(y=7-j; y<5; y++) {
							for(x=0; x<25; x++)
								printf("%c", b[x][y]);
							printf("\n");
						}
					}
					else if(j>20) {                            
						for(y=0; y<25-j; y++) {
							for(x=0; x<25; x++)
								printf("%c", b[x][y]);
							printf("\n");
						}
					}
					else {
						for(y=0; y<5; y++) {
							for(x=0; x<25; x++)
								printf("%c", b[x][y]);
							printf("\n");
						}
					}
					delay(275);
					if(j<21) {
						gotoxy(1, j);
						for(y=0; y<5; y++)
							puts("                         ");
					}
					else {
						gotoxy(1, 20);
						for(y=0; y<5; y++)
							puts("                         ");
					}
					//暫存區 
					if (kbhit()) {
						ch = getch();
						if(ch == '\b') {
							countx--;
							gotoxy(40+countx, 4+county);
							printf(" ");
						}
						else if(ch == '\r') {
							countx = 0;
							county++;
						}
						else {
							gotoxy(40+countx, 4+county);
							printf("%c", ch);
							countx++;
						}
					}
				}
				if(hint_b1 == 1) {
					gotoxy(40, 12);
					printf("提示字首");
					delay(33); 
					gotoxy(44, 14);
					printf("字首：%c", a1[i][0]);
					delay(233);
				}
				gotoxy(40, 10); printf("答案： "); scanf("%s", c); clrscr();
				//判斷對錯 
				if(T==0) if (strcmp(a1[i], c) != 0) {
					if(again[3] == 1) {
						again[3] = 0;
						gotoxy(20, 10);
						setTextColor(0xE0);
						printf("捲  土  重  來");
						setTextColor(0x00);
						gotoxy(24, 12);
						printf("各關卡中有一次免死金牌");
						delay(2000);
						again[3] == 0;
						clrscr();
					}
					else {
						gotoxy(20, 10);
						setTextColor(0x0C);	
						printf("正確答案：%s", a1[i]);
						gotoxy(20, 12);
						setTextColor(0x00);
						printf("玩家輸入：%s", c);											
						gotoxy(20, 15);							
						printf("Press any key to continue");
						getch();
						return sum;
					}
				}
				else if(T==1) if (strcmp(a2[i], c) != 0) {
					if(again[3] == 1) {
						again[3] = 0;
						gotoxy(20, 10);
						setTextColor(0xE0);
						printf("捲  土  重  來");
						setTextColor(0x00);
						gotoxy(24, 12);
						printf("各關卡中有一次免死金牌");
						delay(2000);
						clrscr();
					}
					else {
						gotoxy(20, 10);
						setTextColor(0x0C);	
						printf("正確答案：%s", a1[i]);
						gotoxy(20, 12);
						setTextColor(0x00);
						printf("玩家輸入：%s", c);											
						gotoxy(20, 15);					
						printf("Press any key to continue");
						getch();
						return sum;
					}
				}
				else if(T==2) if (strcmp(a3[i], c) != 0) {
					if(again[3] == 1) {
						again[3] = 0;
						gotoxy(20, 10);
						setTextColor(0xE0);
						printf("捲  土  重  來");
						setTextColor(0x00);
						gotoxy(24, 12);
						printf("各關卡中有一次免死金牌");
						delay(2000);
						clrscr();
					}
					else {
						gotoxy(20, 10);
						setTextColor(0x0C);
						printf("正確答案：%s", a1[i]);
						gotoxy(20, 12);
						setTextColor(0x00);
						printf("玩家輸入：%s", c);											
						gotoxy(20, 15);							
						printf("Press any key to continue");
						getch();
						return sum;
					}
				}
				sum++;
			}
		}
		return sum;
	}
} 

void sth() {
	HideCursor();
	char su[19][48];
	int check[10] = {0};
	int i, j, k;
	FILE *fp = fopen("sudoku.txt", "r");
    for(i=0; i<19; i++) 
       	for(j=0; j<48; j++) 
			fscanf(fp, "%c", &su[i][j]);
	fclose(fp);
	//初始題目 
	char out[19][48] = {0x00};
	srand((unsigned) time(NULL));
	for(i=0; i<19; i++) 
		for(j=0; j<48; j++)
			if(su[i][j] == '+' || su[i][j] == '-')
				out[i][j] = su[i][j];
	for(k=0; k<ans_sth; k++) {
		int SU;
		do {
			i = rand() % 9;
			i = 1 + 2 * i;
			j = rand() % 9;
			j = 3 + 5 * j;
			SU = su[i][j] - '0';
		} while(out[i][j] != 0x00 || check[SU] == 5);
		out[i][j] = su[i][j];
		check[SU] += 1;
	}
	int note[82][10] = {0};
	/*for(i=1; i<82; i++) {  //1582行 
		for(j=0; j<10; j++) {
			int m = i / 9;
			int n = i - 10 * m;
			m = 3 + 5 * m;
			n = 2 + 2 * n;
			if(out[m-1][n] == 0x00) {
				
			}
		}
	} */ 
	//規則說明 
	clrscr();
	gotoxy(1,1);
	printf("數獨\a");
	delay(1000);
	char *s[] = {"將空格分別填入數字 1 ~ 9",
				"在每排、每列及每個小的九方格中，一個數字只能出現一次",
				"若回答正確，答案將會顯示在格中",
				"若回答錯誤，則生命減一",
				"請善用生命猜格子",
				"當生命歸零，則遊戲結束，玩家步數 -30",
				"完成可以挑選獎勵"};
	cout_y = 4, cout_x = 3;
	for(j=0; j<7; j++) {
		gotoxy(cout_x, cout_y);
		for(i=0; i<strlen(s[j]); i++) {
			printf("%c", s[j][i]);
			delay(50);
		}
		cout_y += 2;
	}
	delay(2000); gotoxy(3,19);  
	printf("Press Enter to Start\a");
	char c;
	do {
		c = getch();	
	} while(c != '\r');
	if(c=='\r') {
		gotoxy(3,19);  setTextColor(0x20 | 0x07);
		printf("     遊    戲    開    始     \a");
		setTextColor(0x00); delay(1000); clrscr();
		//印圖 
		for(i=0; i<19; i++) {
	       	for(j=0; j<48; j++) {
	     		if(out[i][j] == '+') {
	       			setTextColor(0x70);
	       			printf(" ");
	       			setTextColor(0x00);       			
				}
				else if(out[i][j] == '-') {
	       			setTextColor(0x80);
	       			printf(" ");
	       			setTextColor(0x00);       			
				}
	       		else if(out[i][j] == 0x00) printf(" ");
	       		else printf("%c", out[i][j]);
			}
			printf("\n");
		}
		int x=3, y=2;
		int life = 10;
		while(1) {
			//移動格子閃爍 
			gotoxy(55, 10); printf("Life : %02d", life);
			gotoxy(x, y); setTextColor(0x20 | 0x07);
			if(out[y-1][x] == 0x00) printf("   "); 
			else printf(" %c ", out[y-1][x]); delay(88);
			gotoxy(x, y); setTextColor(0x00);
			if(out[y-1][x] == 0x00) printf("   "); 
			else printf(" %c ", out[y-1][x]); delay(88);
			/*//空白格子筆記 猶豫要不要做  1509行 
			gotoxy(55, 15); setTextColor(0xD0); printf("N O T E"); setTextColor(0x00);
			gotoxy(55, 17); for(i=1; i<4; i++) printf("%d ", note[][i]);
			gotoxy(55, 18); for(i=4; i<7; i++) printf("%d ", note[][i]);
			gotoxy(55, 19); for(i=7; i<10; i++) printf("%d ", note[][i]);*/
			if(kbhit()) {
				char c = getch();
				if(c==72 && y>=4) y-=2; //up
				else if(c==72 && y==2) y+=16;
				else if(c==80 && y<=16) y+=2; //down
				else if(c==80 && y==18) y-=16;
				else if(c==75 && x>=8) x-=5; //left
				else if(c==75 && x==3) x+=40;
				else if(c==77 && x<=38) x+=5; //right
				else if(c==77 && x==43) x-=40;
				else if(c>='1' && c<='9') {
					if(out[y-1][x] == 0x00) {
						if(c == su[y-1][x]) {
							out[y-1][x] = c;
							//印地圖 
							gotoxy(1, 1);
							for(i=0; i<19; i++) {
						       	for(j=0; j<48; j++) {
						     		if(out[i][j] == '+') {
						       			setTextColor(0x70);
						       			printf(" ");
						       			setTextColor(0x00);       			
									}
									else if(out[i][j] == '-') {
						       			setTextColor(0x80);
						       			printf(" ");
						       			setTextColor(0x00);       			
									}
						       		else if(out[i][j] == 0x00) printf(" ");
						       		else printf("%c", out[i][j]);
								}
								printf("\n");
							}
						}
						else {
							life--;
							gotoxy(55, 10); 
							setTextColor(0x04);
							printf("Life : %02d", life);
							setTextColor(0x00);
							delay(235);
							if(life == 0) {
								t-=30;
								clrscr();
								break;
							}
						}
					} //判斷空 end
				} //判斷是否數字 
	 		} //kbhit end
	 		int check = 0;
	 		for(i=1; i<19; i+=2)
				for(j=3; j<48; j+=5)
					if(out[i][j] == 0x00) {
						check = 1;
						break;
					}
			if(!check) {
				clrscr();
				gotoxy(4, 4);
				char c = 92; //反斜線的 ASCII 
				printf("/(ΦωΦ)/ Congratulations %c(ΦωΦ)%c\n\n\n\n請選擇獎勵：\n\n\n", c, c);
				printf("	A. 後顧無憂\n\n"); //步數+100 
				printf("	B. 及時止損\n\n"); //可以再一次選擇跳脫關卡 
				printf("	C. 金剛護體\n\n"); //闖關失敗不減少步數 
				printf("	D. 捲土重來\n\n"); //闖關有一次失敗但可以繼續的機會 
				printf("	E. 迴光返照\n\n"); //當第一次步數=0 +20步數 //未做
				if (life > 7) printf("	F.天選之人"); //小孩子才做選擇 
				c = getch();
				if(toupper(c) == 'A') {
					clrscr();
					gotoxy(20, 10);
					setTextColor(0xE0);
					printf("後  顧  無  憂");
					Achieve[1] = 1;
					setTextColor(0x00);
					gotoxy(24, 12);
					printf("步數增加 100");
					t+=100;
					delay(2000);
				}
				else if(toupper(c) == 'B') {
					Achieve[2] = 1;
					t+=60;
					chance = 1;
				}
				else if(toupper(c) == 'C') {
					Achieve[3] = 1;
					t+=50;
					min = 1;
				}
				else if(toupper(c) == 'D') {
					Achieve[4] = 1;
					t+=40;
					again[1] = 1, again[2] = 1, again[3] = 1;
				}
				else if(toupper(c) == 'E') {
					Achieve[5] = 1;
					t+=30;
					no_die = 1;
				}
				else if(life > 7 && toupper(c) == 'F') {
					clrscr();
					gotoxy(20, 10);
					setTextColor(0xE0);
					printf("天  選  之  人");
					Achieve[6] = 1;
					setTextColor(0x00);
					gotoxy(24, 12);
					printf("小孩子才做選擇");
					t+=100; chance = 1; min = 1; no_die = 1; 
					again[1] = 1, again[2] = 1, again[3] = 1;
					delay(2000);
				} 
				else {
					clrscr();
					gotoxy(20, 10);
					setTextColor(0xE0);
					printf("交  臂  失  之");
					Achieve[7] = 1;
					setTextColor(0x00);
					gotoxy(24, 12);
					printf("沒有任何數據改變");
					Achieve[7] = 1;
					delay(2000);
				}
				break;
			}
		}
	}
}
