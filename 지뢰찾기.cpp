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

	const int xLimit, yLimit;  // �ִ� ��ǥ 

	int InnerPart[40][25];  // ���ڰ��� 0, 1, 2, 3, 4, 5, 6, 7, 8 // ���� -1 

	int OutterPart[40][25];  // 0 ���� // 1 �ܺ� // 2 ǥ�� 

	int xPos, yPos;  // ���� ��ǥ 

	int NoCheckNum;  // Ȯ������ ���� ĭ�� �� // ���ڼ��� ������ �������� 

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

 

//******************** �����Լ� ********************//

int main()

{

	setlocale(LC_ALL, "Korean");

	MainMenu();

	

	return 0;

}

 

//******************** ȭ�� �ʱ�ȭ ********************//

void ScreenInit()

{

	int i, j;

	setColor(0,15); 

	for(i=0;i<80;i++) for(j=0;j<25;j++) { gotoxy(i,j); printf(" "); } 

	gotoxy(0,0);

}

 

//******************** ���θ޴� ********************//

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

				if(yPos==11) { Start(); break; }  // ���� ���� 

				else Quit();  // ���� 

			}

		}

	}

}

 

//******************** ���ӽ����� ���� ********************//

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

			case '1': Game(9, 9, 10); break; // �ʱ� 

			case '2': Game(16, 16, 40); break; // �߱� 

			case '3': Game(30, 16, 99); break; // ���

		}

	}

}

 

//******************** ���� ********************//

void Quit()

{

	int i, j;

	

	setColor(0,15); for(i=0;i<80;i++) for(j=0;j<25;j++) printf(" ");

	exit(0);

}

 

//******************** ���ӽ����� ********************//

void Game(int x, int y, int mineNum)

{

	Map map={x,y,};

	int i, j, k, m, n;  // �ݺ��� ���� 

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

	

	for(i=0;i<x;i++) for(j=0;j<y;j++)  // ����ȭ�� �ʱ�ȭ 

	{

		setColor(0,2); gotoxy(i*2,j); wprintf(L"%wc", 0x25A0); 

		// setColor(0,15); gotoxy(i*2,j+25); printf("%d", map.InnerPart[i][j]); // InnerPart ���� 

		map.OutterPart[i][j]=1; // gotoxy(i*2,j+50); printf("%d", map.OutterPart[i][j]); // OutterPart ���� 

		map.NoCheckNum++; 

	} map.xPos=0; map.yPos=0; gotoxy(map.xPos,map.yPos); setColor(0,10); wprintf(L"%wc", 0x25A0);

	

	for(;;) if(kbhit())  // ���� 0 ���� 

	{

		key=getch(); if(key==27) break;

		if(key==224)

		{

			key=getch();

				

			if(key==UP && map.yPos>0)  // ���� 

			{ PreHandling(&map); map.yPos--; PostHandling(&map); }

			else if(key==DOWN && map.yPos<y-1)  // �Ʒ��� 

			{ PreHandling(&map); map.yPos++; PostHandling(&map); }

			else if(key==RIGHT && map.xPos<x-1)  // ������ 

			{ PreHandling(&map); map.xPos++; PostHandling(&map); }

			else if(key==LEFT && map.xPos>0)  // ���� 

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

 

//******************** ��ǥ�̵��� ���� ó�� ********************//

void PreHandling(Map *map)

{

	setColor(0,2);

	

	if(map->OutterPart[map->xPos][map->yPos]==0)  // Ȯ�ε� �� 

	{

		gotoxy(map->xPos<<1,map->yPos);

		wprintf(L"%wc", 0xFF10+map->InnerPart[map->xPos][map->yPos]);

	}

	else if(map->OutterPart[map->xPos][map->yPos]==1)  // Ȯ�ε��� ���� �� 

	{

		gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25A0);

	}

	else if(map->OutterPart[map->xPos][map->yPos]==2)  // ���� ǥ�õ� �� 

	{

		gotoxy(map->xPos<<1,map->yPos); wprintf(L"%wc", 0x25C6);

	}

}

 

//******************** ��ǥ�̵��� ���� ó�� ********************//

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

 

//******************** �ش���ǥ Ȯ�� ********************//

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

		else  // -1 ���� 

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

 

//******************** ���ڼ��� 0 �̸� �ڵ� ���� ********************//

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

 

//******************** ���� ǥ�� ********************//

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

 

// 9 9 10 : ����ã�� �ʱ� ���� 

// 16 16 40 : ����ã�� �߱� ���� 

// 30 16 99 : ����ã�� ��� ���� 


