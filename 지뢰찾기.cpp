#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <windows.h>

#include <conio.h>

#include <wchar.h>

#include <locale.h>

 

enum { UP=72, DOWN=80, RIGHT=77, LEFT=75, MINE=-1, OKAY=32, HELP='r' };

 

typedef struct map

{

	const int xLimit, yLimit;  // 최대 좌표 

	int InnerPart[40][25];  // 지뢰개수 0, 1, 2, 3, 4, 5, 6, 7, 8 // 지뢰 -1 

	int OutterPart[40][25];  // 0 내부 // 1 외부 // 2 표시 

	int xPos, yPos;  // 현재 좌표 

	int NoCheckNum;  // 확인하지 않은 칸의 수 // 지뢰수와 같으면 게임종료 

} Map;

 

void gotoxy(int x, int y)

{

	COORD Pos; Pos.X=x; Pos.Y=y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}

 

void setColor(WORD back, WORD text)

{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text|(back<<4));

}

 

void ScreenInit();

void MainMenu();

void Start();

void Quit();

void Game(int mineNum, int x, int y);

void PreHandling(Map *map);

void PostHandling(Map *map);

int Check(Map *map);

void ConnectCheck(Map *map, int i, int j);

void MineSign(Map *map);

 

//******************** 메인함수 ********************//

int main()

{

	setlocale(LC_ALL, "Korean");

	MainMenu();

	

	return 0;

}

 

//******************** 화면 초기화 ********************//

void ScreenInit()

{

	int i, j;

	setColor(0,15); 

	for(i=0;i<80;i++) for(j=0;j<25;j++) { gotoxy(i,j); printf(" "); } 

	gotoxy(0,0);

}

 

//******************** 메인메뉴 ********************//

void MainMenu()

{

	int key;

	int xPos, yPos;

	

	for(;;)

	{

		ScreenInit();

		gotoxy(35,9); setColor(0,11); printf("Mine Search");

		gotoxy(35,11); setColor(0,15); printf("1. Start"); gotoxy(35,12); printf("2. Quit");

		xPos=44; yPos=11; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25C0); 

		

		for(;;) if(kbhit())

		{

			key=getch(); if(key==27) Quit();

			if(key==224)

			{

				key=getch();

				

				if(key==UP && yPos>11) 

				{ gotoxy(xPos,yPos--); printf(" "); gotoxy(xPos,yPos); wprintf(L"%wc", 0x25C0); }

				else if(key==DOWN && yPos<12) 

				{ gotoxy(xPos,yPos++); printf(" "); gotoxy(xPos,yPos); wprintf(L"%wc", 0x25C0); }

				else continue;

			}

			if(key==OKAY)

			{

				if(yPos==11) { Start(); break; }  // 게임 시작 

				else Quit();  // 종료 

			}

		}

	}

}

 

//******************** 게임시작전 세팅 ********************//

void Start()

{

	char level; // int x, y, mineNum;

	

	for(;;)

	{

		ScreenInit(); level=NULL;

		for(;(level<'1' || level>'3') && level!=27;) { printf("<Level Select 1, 2, 3>"); level=getch(); } 

		/*

		do { printf("Input Length and Breadth: "); scanf("%d %d", &x, &y); } while(x<1 || y<1 || x>40 || y>25);

		do { printf("Input Mine Number: "); scanf("%d", &mineNum); } while(mineNum<1 || mineNum>x*y);

		*/

		if(level==27) break;

		switch(level)

		{

			case '1': Game(9, 9, 10); break; // 초급 

			case '2': Game(16, 16, 40); break; // 중급 

			case '3': Game(30, 16, 99); break; // 고급

		}

	}

}

 

//******************** 종료 ********************//

void Quit()

{

	int i, j;

	

	setColor(0,15); for(i=0;i<80;i++) for(j=0;j<25;j++) printf(" ");

	exit(0);

}

 

//******************** 게임실행중 ********************//

void Game(int x, int y, int mineNum)

{

	Map map={x,y,};

	int i, j, k, m, n;  // 반복문 변수 

	int key;

	

	ScreenInit();

	srand((unsigned int)time(NULL));

	

	for(k=0;k<mineNum;)

	{

		i=rand()%x; j=rand()%y; 

		if(map.InnerPart[i][j]!=MINE) 

		{ 

			map.InnerPart[i][j]=MINE; 

			for(m=(i>0?i-1:i);m<=(i<39?i+1:i);m++) for(n=(j>0?j-1:j);n<=(j<24?j+1:j);n++) 

			if(map.InnerPart[m][n]!=MINE) map.InnerPart[m][n]++; k++; 

		}

	}

	

	for(i=0;i<x;i++) for(j=0;j<y;j++)  // 게임화면 초기화 

	{

		setColor(0,2); gotoxy(i*2,j); wprintf(L"%wc", 0x25A0); 

		// setColor(0,15); gotoxy(i*2,j+25); printf("%d", map.InnerPart[i][j]); // InnerPart 검토 

		map.OutterPart[i][j]=1; // gotoxy(i*2,j+50); printf("%d", map.OutterPart[i][j]); // OutterPart 검토 

		map.NoCheckNum++; 

	} map.xPos=0; map.yPos=0; gotoxy(map.xPos,map.yPos); setColor(0,10); wprintf(L"%wc", 0x25A0);

	

	for(;;) if(kbhit())  // 배경색 0 고정 

	{

		key=getch(); if(key==27) break;

		if(key==224)

		{

			key=getch();

				

			if(key==UP && map.yPos>0)  // 위쪽 

			{ PreHandling(&map); map.yPos--; PostHandling(&map); }

			else if(key==DOWN && map.yPos<y-1)  // 아래쪽 

			{ PreHandling(&map); map.yPos++; PostHandling(&map); }

			else if(key==RIGHT && map.xPos<x-1)  // 오른쪽 

			{ PreHandling(&map); map.xPos++; PostHandling(&map); }

			else if(key==LEFT && map.xPos>0)  // 왼쪽 

			{ PreHandling(&map); map.xPos--; PostHandling(&map); }

			else continue;

		}

		else if(key==OKAY)

		{

			if(Check(&map)==1)

			{

				gotoxy(35,11); setColor(0,12); printf("Failed...");

				for(;;) if(kbhit()) { key=getch(); if(key==OKAY) break; } break;

			}

			if(map.NoCheckNum==mineNum)

			{

				setColor(0,11);

			    for(map.xPos=0;map.xPos<map.xLimit;map.xPos++)

				for(map.yPos=0;map.yPos<map.yLimit;map.yPos++) 

				if(map.InnerPart[map.xPos][map.yPos]==MINE)

				{

					gotoxy(map.xPos<<1,map.yPos); wprintf(L"%wc", 0x25A0);

				} getch();

				gotoxy(35,11); printf("Success!!"); 

				for(;;) if(kbhit()) { key=getch(); if(key==OKAY) break; } break;

			}

		}

		else if(key==HELP)

		{

			MineSign(&map); 

		}

		else continue;

	}

}

 

//******************** 좌표이동전 글자 처리 ********************//

void PreHandling(Map *map)

{

	setColor(0,2);

	

	if(map->OutterPart[map->xPos][map->yPos]==0)  // 확인된 것 

	{

		gotoxy(map->xPos<<1,map->yPos);

		wprintf(L"%wc", 0xFF10+map->InnerPart[map->xPos][map->yPos]);

	}

	else if(map->OutterPart[map->xPos][map->yPos]==1)  // 확인되지 않은 것 

	{

		gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25A0);

	}

	else if(map->OutterPart[map->xPos][map->yPos]==2)  // 지뢰 표시된 것 

	{

		gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25C6);

	}

}

 

//******************** 좌표이동후 글자 처리 ********************//

void PostHandling(Map *map)

{

	setColor(0,10);

	

	if(map->OutterPart[map->xPos][map->yPos]==0)

	{

		gotoxy(map->xPos<<1,map->yPos);

		wprintf(L"%wc", 0xFF10+map->InnerPart[map->xPos][map->yPos]);

	}

	else if(map->OutterPart[map->xPos][map->yPos]==1)

	{

		gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25A0);

	}

	else if(map->OutterPart[map->xPos][map->yPos]==2)

	{

		gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25C6);

	}

}

 

//******************** 해당좌표 확인 ********************//

int Check(Map *map)

{

	setColor(0,10);

	if(map->OutterPart[map->xPos][map->yPos]==1)

	{

		if(map->InnerPart[map->xPos][map->yPos]>=1 && map->InnerPart[map->xPos][map->yPos]<=8)

		{

			gotoxy(map->xPos<<1,map->yPos);

			wprintf(L"%wc", 0xFF10+map->InnerPart[map->xPos][map->yPos]);

			map->OutterPart[map->xPos][map->yPos]=0; map->NoCheckNum--;

		}

		else if(map->InnerPart[map->xPos][map->yPos]==0)

		{

			setColor(0,2); ConnectCheck(map, map->xPos, map->yPos);

		}

		else  // -1 지뢰 

		{

			setColor(0,12);

			for(map->xPos=0;map->xPos<map->xLimit;map->xPos++)

			for(map->yPos=0;map->yPos<map->yLimit;map->yPos++) 

			if(map->InnerPart[map->xPos][map->yPos]==MINE)

			{

				gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25A0);

			} getch(); return 1;

		}

	}

	

	return 0;

}

 

//******************** 지뢰수가 0 이면 자동 오픈 ********************//

void ConnectCheck(Map *map, int i, int j)

{

	if(map->OutterPart[i][j]==1 && i>=0 && i<map->xLimit && j>=0 && j<map->yLimit)

	{

		gotoxy(i<<1,j); wprintf(L"%wc", 0xFF10+map->InnerPart[i][j]);

		map->OutterPart[i][j]=0; map->NoCheckNum--;

		if(map->InnerPart[i][j]==0)

		{

			ConnectCheck(map, i+1, j); ConnectCheck(map, i, j+1); 

			ConnectCheck(map, i-1, j); ConnectCheck(map, i, j-1);

			ConnectCheck(map, i+1, j+1); ConnectCheck(map, i-1, j+1);

			ConnectCheck(map, i-1, j-1); ConnectCheck(map, i+1, j-1);

		}

	}

}

 

//******************** 지뢰 표시 ********************//

void MineSign(Map *map)

{

	setColor(0,10);

	if(map->OutterPart[map->xPos][map->yPos]==1)

	{

		gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25C6);

		map->OutterPart[map->xPos][map->yPos]=2;

	}

	else if(map->OutterPart[map->xPos][map->yPos]==2)

	{

		gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25A0);

		map->OutterPart[map->xPos][map->yPos]=1;

	}

}

 

// 9 9 10 : 지뢰찾기 초급 기준 

// 16 16 40 : 지뢰찾기 중급 기준 

// 30 16 99 : 지뢰찾기 고급 기준 


