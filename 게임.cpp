#include <stdio.h>  // printf // scanf

#include <stdlib.h>  // srand((unsigned int)time(NULL)); // rand()

#include <time.h>  // clock_t(long) // clock() // time

#include <windows.h>  // <wincon.h> // GetStdHandle();

#include <conio.h>  // kbhit(); // getch(); // 0 or 224(0xE0) // 72(up,H), 80(down,M), 75(left,K), 77(right,P)

#include <wchar.h>  // wchar_t(unsigned short) // wprintf, wscanf // L" "

#include <locale.h>  // setlocale(LC_ALL, "Korean");

 

void gotoxy(int x, int y)  // 0~79(80), 0~24(25)

{

	COORD Pos;

	Pos.X=x; Pos.Y=y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}

 

void setColor(WORD back, WORD text)  // black(0,8), blue(1,9), green(2,10), azure(3,11), red(4,12), purple(5,13), yellow(6,14), white(7,15)

{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text|(back<<4));

}

 

void Initialization();

void MainMenu();

void Start();

void Option();

void Quit();

void control();

void ball();

void easy();

void normal();

void hard();

 

clock_t start, end;

int key, xPos, yPos, i, j, k;

WORD Bcolor=15, Tcolor=0;

int direction;  // 25B2(up), 25B6(right), 25BC(down), 25C0(left)

int map[80][25];

int xBall, yBall;

int xMemory=15, yMemory=8;

int re[80][25];

 

int main()

{

	setlocale(LC_ALL, "Korean"); 

	srand((unsigned int)time(NULL));

	

	//******************** Game Start ********************//

	gotoxy(2,1); printf("¦£"); for(i=2;i<=37;i++) printf("¦¡"); printf("¦¤");  // 2, 2(1), 72(36), 2(1) // --¦£72¦¤--- // 39

	for(yPos=2;yPos<=21;yPos++)

	{

		xPos=2; gotoxy(xPos, yPos); printf("¦¢"); xPos=76; gotoxy(xPos, yPos); printf("¦¢");  // -¦£20¦¦-- // 11 (?)

	}

	gotoxy(2,22); printf("¦¦"); for(i=2;i<=37;i++) printf("¦¡"); printf("¦¥");  // 2, 2(1), 72(36), 2(1) // --¦¦72¦¥--- // 39

		

	gotoxy(34,11); setColor(0,15); printf("START GAME!"); Sleep(1000);

	gotoxy(34,11); setColor(0,7); printf("START GAME!"); gotoxy(34,10); setColor(0,15); printf("START GAME!"); Sleep(1000);

	gotoxy(34,11); setColor(0,0); printf("START GAME!"); gotoxy(34,10); setColor(0,7); printf("START GAME!"); 

	gotoxy(34,9); setColor(0,15); printf("START GAME!"); Sleep(1000); 

	gotoxy(34,10); setColor(0,0); printf("START GAME!"); gotoxy(34,9); setColor(0,7); printf("START GAME!"); Sleep(1000);

	gotoxy(34,9); setColor(0,12); printf("START GAME!"); Sleep(1000);

	

	for(i=0;i<80;i++) for(j=0;j<25;j++) if(i<4 || i>75 || j<2 || j>21) map[i][j]=-1;

	

	MainMenu();

	

	return 0;

}

 

//******************** Initialization ********************//

void Initialization()

{

	setColor(Bcolor,Tcolor);

	for(xPos=4;xPos<=75;xPos++) for(yPos=2;yPos<=21;yPos++)

	{

		gotoxy(xPos, yPos); printf(" "); map[xPos][yPos]=0;

	}

}

 

//******************** Main Menu ********************//

void MainMenu()

{

	Initialization();

	

	gotoxy(35,9); setColor(Bcolor,12); printf("Main Menu"); 

	gotoxy(35,11); setColor(Bcolor,Tcolor); printf("1.start"); gotoxy(35,12); printf("2.option"); gotoxy(35,13); printf("3.quit");

	

	xPos=45; yPos=11; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25C0);

	

	for(;;) if(kbhit())

	{

		key=getch(); if(key==27) Quit();

		if(key==224)

		{

			key=getch();

			if(key==72 && yPos>11)

			{

				gotoxy(xPos, yPos); printf(" "); gotoxy(xPos,--yPos); wprintf(L"%wc", 0x25C0); 

			}

			else if(key==80 && yPos<13)

			{

				gotoxy(xPos, yPos); printf(" "); gotoxy(xPos,++yPos); wprintf(L"%wc", 0x25C0);

			}

		}

		if(key==32)

		{

			if(yPos==11) Start();

			else if(yPos==12) Option();

			else Quit();

		}

	}

}

 

//******************** start ********************//

void Start()

{

	Initialization();

	for(i=4;i<=74;i+=2) if(i<=26 || (i>=28 && i<=50) || i>=54)

	{

		gotoxy(i,4); printf("¦¡"); gotoxy(i,11); printf("¦¡"); gotoxy(i,13); printf("¦¡"); gotoxy(i,20); printf("¦¡");  

	}

	for(j=4;j<=20;j++) if(j<=11 || j>=13)

	{

		gotoxy(4,j); printf("¦¢"); gotoxy(26,j); printf("¦¢"); gotoxy(28,j); printf("¦¢"); gotoxy(50,j); printf("¦¢");

		gotoxy(52,j); printf("¦¢"); gotoxy(74,j); printf("¦¢");

		if(j==4 || j==13)

		{

			gotoxy(4,j); printf("¦£"); gotoxy(28,j); printf("¦£"); gotoxy(52,j); printf("¦£");

			gotoxy(26,j); printf("¦¤"); gotoxy(50,j); printf("¦¤"); gotoxy(74,j); printf("¦¤");

		}

		if(j==11 || j==20)

		{

			gotoxy(4,j); printf("¦¦"); gotoxy(28,j); printf("¦¦"); gotoxy(52,j); printf("¦¦");

			gotoxy(26,j); printf("¦¥"); gotoxy(50,j); printf("¦¥"); gotoxy(74,j); printf("¦¥");

		}

	}

	gotoxy(14,7); printf("Easy"); gotoxy(37,7); printf("Normal"); gotoxy(62,7); printf("Hard");  // (16,7), (40,7), (64,7)

	gotoxy(13,16); printf("Ready 1"); gotoxy(37,16); printf("Ready 2"); gotoxy(61,16); printf("Ready 3");  // (16,16), (40,16), (64,16)

	

	xPos=xMemory; yPos=yMemory; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2);

	for(;;) if(kbhit())

	{

		key=getch(); if(key==27) break;

		if(key==224)

		{

			key=getch();

			if(key==72 && yPos>8)

			{

				gotoxy(xPos,yPos); printf(" "); yPos-=9; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2);

			}

			else if(key==80 && yPos<17)

			{

				gotoxy(xPos,yPos); printf(" "); yPos+=9; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2);

			}

			else if(key==75 && xPos>15)

			{

				gotoxy(xPos,yPos); printf(" "); xPos-=24; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2);

			}

			else if(key==77 && xPos<63)

			{

				gotoxy(xPos,yPos); printf(" "); xPos+=24; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2);

			}

		}

		if(key==32)  // -1, +1

		{

			if(xPos==15 && yPos==8) { xMemory=15; yMemory=8; easy(); }

			if(xPos==39 && yPos==8) { xMemory=39; yMemory=8; normal(); }

			if(xPos==63 && yPos==8) { xMemory=63; yMemory=8; hard(); }

		}

	}

	MainMenu();

}

 

//******************** option ********************//

void Option()

{

	Initialization();

	gotoxy(37,11); printf("Option");

	

	for(;;) if(kbhit())

	{

		key=getch(); if(key==27) break;

	}

	MainMenu();

}

 

//******************** quit ********************//

void Quit()

{ 

	setColor(0,15);

	for(xPos=0;xPos<=79;xPos++) for(yPos=0;yPos<=24;yPos++)

	{

		gotoxy(xPos, yPos); printf(" ");

	}

	exit(0);

}

 

//******************** control ********************//

void control()

{

	for(;;) if(kbhit())

	{

		key=getch(); if(key==27) Start();

		if(key==224)

		{

			key=getch();

			if(key==72) { direction=1; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2); }

			else if(key==77) { direction=2; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B6); }

			else if(key==80) { direction=3; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25BC); }

			else if(key==75) { direction=4; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25C0); }

			switch(direction)  // 25B2(up), 25B6(right), 25BC(down), 25C0(left)

			{

			case 1: if(map[xPos][yPos-1]==0)

				{ gotoxy(xPos,yPos); printf(" "); gotoxy(xPos,--yPos); wprintf(L"%wc", 0x25B2); } break;

			case 2: if(map[xPos+2][yPos]==0)

				{ gotoxy(xPos++,yPos); printf(" "); gotoxy(++xPos,yPos); wprintf(L"%wc", 0x25B6); } break;

			case 3: if(map[xPos][yPos+1]==0)

				{ gotoxy(xPos,yPos); printf(" "); gotoxy(xPos,++yPos); wprintf(L"%wc", 0x25BC); } break;

			case 4: if(map[xPos-2][yPos]==0)

				{ gotoxy(xPos--,yPos); printf(" "); gotoxy(--xPos,yPos); wprintf(L"%wc", 0x25C0); } break;

			}

		}

		if(key==32)

		{

			switch(direction)

			{

			case 1: if(map[xPos][yPos-1]==1 && map[xPos][yPos-2]==0)

				{ gotoxy(xPos,yPos-1); printf(" "); gotoxy(xPos,yPos-2); wprintf(L"%wc", 0x25A1); 

				map[xPos][yPos-1]=0; map[xPos][yPos-2]=1; } 

				else if(map[xPos][yPos-1]==2) { gotoxy(xPos,yPos); printf(" "); return; } break;  /////////////////////////////////////////////////////////////

			case 2: if(map[xPos+2][yPos]==1 && map[xPos+4][yPos]==0)

				{ gotoxy(xPos+2,yPos); printf(" "); gotoxy(xPos+4,yPos); wprintf(L"%wc", 0x25A1); 

				map[xPos+2][yPos]=0; map[xPos+4][yPos]=1; } 

				else if(map[xPos+2][yPos]==2) { gotoxy(xPos,yPos); printf(" "); return; } break;

			case 3: if(map[xPos][yPos+1]==1 && map[xPos][yPos+2]==0)

				{ gotoxy(xPos,yPos+1); printf(" "); gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A1); 

				map[xPos][yPos+1]=0; map[xPos][yPos+2]=1; } 

				else if(map[xPos][yPos+1]==2) { gotoxy(xPos,yPos); printf(" "); return; } break;

			case 4: if(map[xPos-2][yPos]==1 && map[xPos-4][yPos]==0)

				{ gotoxy(xPos-2,yPos); printf(" "); gotoxy(xPos-4,yPos); wprintf(L"%wc", 0x25A1); 

				map[xPos-2][yPos]=0; map[xPos-4][yPos]=1; } 

				else if(map[xPos-2][yPos]==2) { gotoxy(xPos,yPos); printf(" "); return; } break;

			}

		}

	}

}

 

//******************** ball ********************//

void ball()

{

	map[xBall][yBall]=0;

	for(;;)

	{

		if(kbhit()) { key=getch(); if(key==27) Start(); }

		switch(direction)

		{

		case 1: if(map[xBall][yBall-1]%3==0)  // up 

			{ gotoxy(xBall,yBall); printf(" "); gotoxy(xBall,--yBall); wprintf(L"%wc", 0x25CF); }

			else if(map[xBall][yBall-1]==1)

			{

				if((map[xBall-2][yBall]%3==0 && map[xBall+2][yBall]%3==0) || (map[xBall-2][yBall]==1 && map[xBall+2][yBall]==1)) direction=3;

				else if(map[xBall-2][yBall]==1 && map[xBall+2][yBall]%3==0) direction=2;

				else if(map[xBall-2][yBall]%3==0 && map[xBall+2][yBall]==1) direction=4;

			} break;

		case 2: if(map[xBall+2][yBall]%3==0)  // right

			{ gotoxy(xBall++,yBall); printf(" "); gotoxy(++xBall,yBall); wprintf(L"%wc", 0x25CF); } 

			else if(map[xBall+2][yBall]==1)

			{

				if((map[xBall][yBall-1]%3==0 && map[xBall][yBall+1]%3==0) || (map[xBall][yBall-1]==1 && map[xBall][yBall+1]==1)) direction=4;

				else if(map[xBall][yBall-1]==1 && map[xBall][yBall+1]%3==0) direction=3;

				else if(map[xBall][yBall-1]%3==0 && map[xBall][yBall+1]==1) direction=1;

			} break;

		case 3: if(map[xBall][yBall+1]%3==0)  // down

			{ gotoxy(xBall,yBall); printf(" "); gotoxy(xBall,++yBall); wprintf(L"%wc", 0x25CF); } 

			else if(map[xBall][yBall+1]==1)

			{

				if((map[xBall-2][yBall]%3==0 && map[xBall+2][yBall]%3==0) || (map[xBall-2][yBall]==1 && map[xBall+2][yBall]==1)) direction=1;

				else if(map[xBall-2][yBall]==1 && map[xBall+2][yBall]%3==0) direction=2;

				else if(map[xBall-2][yBall]%3==0 && map[xBall+2][yBall]==1) direction=4;

			} break;

		case 4: if(map[xBall-2][yBall]%3==0)  // left

			{ gotoxy(xBall--,yBall); printf(" "); gotoxy(--xBall,yBall); wprintf(L"%wc", 0x25CF); } 

			else if(map[xBall-2][yBall]==1)

			{

				if((map[xBall][yBall-1]%3==0 && map[xBall][yBall+1]%3==0) || (map[xBall][yBall-1]==1 && map[xBall][yBall+1]==1)) direction=2;

				else if(map[xBall][yBall-1]==1 && map[xBall][yBall+1]%3==0) direction=3;

				else if(map[xBall][yBall-1]%3==0 && map[xBall][yBall+1]==1) direction=1;

			} break;

		}

		if(map[xBall][yBall]==3)  // star

		{

			gotoxy(37,11); return;

		}

		Sleep(100);

	}

}

 

//******************** easy ********************//

void easy()

{

	Initialization();  

	for(xPos=4;xPos<=75;xPos+=2) for(yPos=2;yPos<=21;yPos++)  // square

	{

		if(xPos<16 || xPos>62 || yPos<5 || yPos>18) 

		{

			gotoxy(xPos, yPos); wprintf(L"%wc", 0x25A1); map[xPos][yPos]=1;

		}

		else if(rand()%3==0) 

		{

			gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); map[xPos][yPos]=1;

		}

	}

	for(;;)  // ball

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x25CF); map[xPos][yPos]=2; xBall=xPos; yBall=yPos; break; }

	}

	for(;;)  // star

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x2605); map[xPos][yPos]=3; break; }

	} 

	for(;;)  // player

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2); break; }

	} direction=1; 

	control(); ball(); setColor(0,10); printf("Clear!"); getch();  Start();

}

 

//******************** normal ********************//

void normal()

{

	Initialization();  

	for(xPos=4;xPos<=75;xPos+=2) for(yPos=2;yPos<=21;yPos++)  // square

	{

		if(xPos<12 || xPos>66 || yPos<4 || yPos>19) // 16 62 5 18

		{

			gotoxy(xPos, yPos); wprintf(L"%wc", 0x25A1); map[xPos][yPos]=1;

		}

		else if(rand()%3==0 || rand()%11==0)  // 3

		{

			gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); map[xPos][yPos]=1;

		}

	}

	for(;;)  // ball

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x25CF); map[xPos][yPos]=2; xBall=xPos; yBall=yPos; break; }

	}

	for(i=1;i<=2;i++) for(;;)  // star

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x2605); map[xPos][yPos]=3; break; }

	} 

	for(;;)  // player

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2); break; }

	} direction=1; 

	control(); for(i=1;i<=2;i++) ball(); setColor(0,10); printf("Clear!"); getch(); Start();

}

 

//******************** hard ********************//

void hard()

{

	Initialization();  

	for(xPos=4;xPos<=75;xPos+=2) for(yPos=2;yPos<=21;yPos++)  // square

	{

		if(xPos<8 || xPos>70 || yPos<3 || yPos>20)  // 16 62 5 18

		{

			gotoxy(xPos, yPos); wprintf(L"%wc", 0x25A1); map[xPos][yPos]=1;

		}

		else if(rand()%3==0 || rand()%7==0)  // 3

		{

			gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); map[xPos][yPos]=1;

		}

	}

	for(;;)  // ball

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x25CF); map[xPos][yPos]=2; xBall=xPos; yBall=yPos; break; }

	}

	for(i=1;i<=3;i++) for(;;)  // star

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x2605); map[xPos][yPos]=3; break; }

	} 

	for(;;)  // player

	{

		xPos=rand()%80; yPos=rand()%25; 

		if(map[xPos][yPos]==0 && xPos%2==0) { gotoxy(xPos,yPos); wprintf(L"%wc", 0x25B2); break; }

	} direction=1; 

	control(); for(i=1;i<=3;i++) ball(); setColor(0,10); printf("Clear!"); getch(); Start();

}

