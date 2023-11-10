// ��Ʈ���� 

 

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <windows.h>

#include <conio.h>

#include <wchar.h>

#include <locale.h>

#include <string.h>

 

#define LENGTH 20

#define BREADTH 10

 

enum { UP=72, DOWN=80, RIGHT=77, LEFT=75, OKAY=32, HELP='r', WALL=-1 };

enum { RED_BLUCK=1, ORANGE_BLUCK, YELLOW_BLUCK, GREEN_BLUCK, AZURE_BLUCK, BLUE_BLUCK, PURPLE_BLUCK };

 

typedef struct play

{

	int map[30][25];  // �� 

	int bluck[4];  // ����(7)

	int hold;  // ��� // ���� 

	int time;  // �����ϴ� �ð� 

} Play;

 

void gotoxy(int x, int y)

{

	COORD Pos; Pos.X=x<<1; Pos.Y=y;

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

void DrawBluck(Play *play, int bluck, int xPos, int yPos, int shape);

void EraseBluck(Play *play, int bluck, int xPos, int yPos, int shape);

void EraseLine(Play *play);

void RedControl(Play *play);

void OrangeControl(Play *play);

void YellowControl(Play *play);

void GreenControl(Play *play);

void AzureControl(Play *play);

void BlueControl(Play *play);

void PurpleControl(Play *play);

int LoseJudgment(int (*map)[25]);

 

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

	for(i=0;i<40;i++) for(j=0;j<25;j++) { gotoxy(i,j); printf("  "); } 

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

		gotoxy(17,9); setColor(0,14); printf("Tetris");

		gotoxy(17,11); setColor(0,15); printf("1. Start"); gotoxy(17,12); printf("2. Quit");

		xPos=23; yPos=11; gotoxy(xPos,yPos); wprintf(L"%wc", 0x25C0); 

		

		for(;;) if(kbhit())

		{

			key=getch(); if(key==27) Quit();

			if(key==224)

			{

				key=getch();

				

				if(key==UP && yPos>11) 

				{ gotoxy(xPos,yPos--); printf("  "); gotoxy(xPos,yPos); wprintf(L"%wc", 0x25C0); }

				else if(key==DOWN && yPos<12) 

				{ gotoxy(xPos,yPos++); printf("  "); gotoxy(xPos,yPos); wprintf(L"%wc", 0x25C0); }

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

 

//******************** ���ӽ��� ********************//

void Start()  // �¿���Ʈ�� // �����̽��� // ȸ��'r' 

{

	Play play={0,};

	int i, j;

	int key;

	

	ScreenInit(); printf("Begin Speed/Recommend=50 or 500: "); scanf("%d", &play.time);

	

	ScreenInit(); srand((unsigned int)time(NULL));

	

	setColor(0,8); for(i=6;i<16;i++) for(j=0;j<4;j++) 

	{ gotoxy(i,j); wprintf(L"%wc", 0x25A1); }

	setColor(0,15); for(i=6;i<16;i++) for(j=4;j<24;j++) 

	{ gotoxy(i,j); wprintf(L"%wc", 0x25A1); } 

	setColor(0,3); for(j=0;j<25;j++) 

	{ 

		gotoxy(5,j); wprintf(L"%wc", 0x25A0); gotoxy(16,j); wprintf(L"%wc", 0x25A0); 

		play.map[5][j]=WALL; play.map[16][j]=WALL;

	}

	for(i=5;i<17;i++) { gotoxy(i,24); wprintf(L"%wc", 0x25A0); play.map[i][24]=WALL; }

	gotoxy(1,0); printf("Hold"); gotoxy(18,0); printf("Next");

	

	// s3 ���� // s2 ���� // s1 ���� // 

	play.bluck[3]=rand()%7+1; play.bluck[2]=rand()%7+1; play.bluck[1]=rand()%7+1;

	

	for(;;)

	{

		// s1 �̵� // s2 �̵� // s3 �̵� // s3 ���� 

		play.bluck[0]=play.bluck[1]; play.bluck[1]=play.bluck[2];

		play.bluck[2]=play.bluck[3]; play.bluck[3]=rand()%7+1; 

		

		setColor(0,15);

		for(i=18;i<=20;i++) for(j=1;j<=14;j++) { gotoxy(i,j); printf("  "); }

		DrawBluck(&play, play.bluck[3], 18, 10, 0);

		DrawBluck(&play, play.bluck[2], 18, 6, 0);

		DrawBluck(&play, play.bluck[1], 18, 2, 0);

		

		// ���� Ȯ�� 

		for(i=26;i<36;i++) for(j=0;j<24;j++) { gotoxy(i,j); printf("%d", play.map[i-20][j]); } 

		gotoxy(i,j); printf("%d %d %d %d", play.bluck[0], play.bluck[1], play.bluck[2], play.bluck[3]); 

		// s0 0.5�� �������� ���� // �ε��� �Ǵ� 

		// �¿� ����Ű ��Ʈ�� // �����̽��� // R Ȧ��Ű 

		switch(gotoxy(0,24), printf("%d", play.bluck[0]), play.bluck[0])  // ���� Ȯ�� 

		{

			case RED_BLUCK: RedControl(&play); EraseLine(&play); break;

			case ORANGE_BLUCK: OrangeControl(&play); break;

			case YELLOW_BLUCK: YellowControl(&play); break;

			case GREEN_BLUCK: GreenControl(&play); break;

			case AZURE_BLUCK: AzureControl(&play); break;

			case BLUE_BLUCK: BlueControl(&play); break;

			case PURPLE_BLUCK: PurpleControl(&play); break;

		} EraseLine(&play); 

		if(LoseJudgment(play.map)==1)

		{

			setColor(0,12); gotoxy(9,12); printf("Failed.."); 

			for(;;) if(kbhit()) { key=getch(); if(key==OKAY) break; } return;

		}

		// Sleep(10000); // ���� Ȯ�� 

		// play.bluck[3]=rand()%7+1; 

	}

}

 

//******************** ���� ********************//

void Quit()

{

	int i, j;

	setColor(0,15); for(i=0;i<80;i++) for(j=0;j<25;j++) printf("  ");

	exit(0);

}

 

//******************** �� �׸��� ********************//

void DrawBluck(Play *play, int bluck, int xPos, int yPos, int shape)

{

	switch(bluck)

	{

		case RED_BLUCK:

			setColor(0,12);

			if(shape==0)

			{

				gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

		 		gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A0);

		 		

		 		play->map[xPos+1][yPos]=RED_BLUCK; play->map[xPos][yPos+1]=RED_BLUCK;

	    		play->map[xPos+1][yPos+1]=RED_BLUCK; play->map[xPos][yPos+2]=RED_BLUCK;

	    	}

	    	else if(shape==1)

			{ 

				gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0);

		 		gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A0);

		 		

		 		play->map[xPos][yPos]=RED_BLUCK; play->map[xPos+1][yPos]=RED_BLUCK;

	    		play->map[xPos+1][yPos+1]=RED_BLUCK; play->map[xPos+2][yPos+1]=RED_BLUCK;

			}

			break;

		case ORANGE_BLUCK:  // ������� ��ü 

			setColor(0,15); 

			if(shape==0)

			{

				gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=ORANGE_BLUCK; play->map[xPos][yPos+1]=ORANGE_BLUCK;

	    		play->map[xPos][yPos+2]=ORANGE_BLUCK; play->map[xPos+1][yPos+2]=ORANGE_BLUCK;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=ORANGE_BLUCK; play->map[xPos+1][yPos]=ORANGE_BLUCK;

	    		play->map[xPos+2][yPos]=ORANGE_BLUCK; play->map[xPos][yPos+1]=ORANGE_BLUCK;

			}

			else if(shape==2)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=ORANGE_BLUCK; play->map[xPos+1][yPos]=ORANGE_BLUCK;

	    		play->map[xPos+1][yPos+1]=ORANGE_BLUCK; play->map[xPos+1][yPos+2]=ORANGE_BLUCK;

			}

			else if(shape==3)

	    	{

	    		gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos+2][yPos]=ORANGE_BLUCK; play->map[xPos][yPos+1]=ORANGE_BLUCK;

	    		play->map[xPos+1][yPos+1]=ORANGE_BLUCK; play->map[xPos+2][yPos+1]=ORANGE_BLUCK;

			}

			break;

		case YELLOW_BLUCK:

			setColor(0,14); 

			gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0);

			gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0);

			

			play->map[xPos][yPos]=YELLOW_BLUCK; play->map[xPos+1][yPos]=YELLOW_BLUCK;

	    	play->map[xPos][yPos+1]=YELLOW_BLUCK; play->map[xPos+1][yPos+1]=YELLOW_BLUCK;

			break;

		case GREEN_BLUCK:

			setColor(0,10); 

			if(shape==0)

			{

				gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=GREEN_BLUCK; play->map[xPos][yPos+1]=GREEN_BLUCK;

	    		play->map[xPos+1][yPos+1]=GREEN_BLUCK; play->map[xPos+1][yPos+2]=GREEN_BLUCK;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos+1][yPos]=GREEN_BLUCK; play->map[xPos+2][yPos]=GREEN_BLUCK;

	    		play->map[xPos][yPos+1]=GREEN_BLUCK; play->map[xPos+1][yPos+1]=GREEN_BLUCK;

			}

			break;

		case AZURE_BLUCK:

			setColor(0,11); 

			if(shape==0)

			{

				gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+3); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=AZURE_BLUCK; play->map[xPos][yPos+1]=AZURE_BLUCK;

	    		play->map[xPos][yPos+2]=AZURE_BLUCK; play->map[xPos][yPos+3]=AZURE_BLUCK;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos-1,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos-1][yPos]=AZURE_BLUCK; play->map[xPos][yPos]=AZURE_BLUCK;

	    		play->map[xPos+1][yPos]=AZURE_BLUCK; play->map[xPos+2][yPos]=AZURE_BLUCK;

			}

			break;

		case BLUE_BLUCK:

			setColor(0,9); 

	    	if(shape==0)

			{

				gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos+1][yPos]=BLUE_BLUCK; play->map[xPos+1][yPos+1]=BLUE_BLUCK;

	    		play->map[xPos][yPos+2]=BLUE_BLUCK; play->map[xPos+1][yPos+2]=BLUE_BLUCK;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=BLUE_BLUCK; play->map[xPos][yPos+1]=BLUE_BLUCK;

	    		play->map[xPos+1][yPos+1]=BLUE_BLUCK; play->map[xPos+2][yPos+1]=BLUE_BLUCK;

			}

			else if(shape==2)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=BLUE_BLUCK; play->map[xPos+1][yPos]=BLUE_BLUCK;

	    		play->map[xPos][yPos+1]=BLUE_BLUCK; play->map[xPos][yPos+2]=BLUE_BLUCK;

			}

			else if(shape==3)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=BLUE_BLUCK; play->map[xPos+1][yPos]=BLUE_BLUCK;

	    		play->map[xPos+2][yPos]=BLUE_BLUCK; play->map[xPos+2][yPos+1]=BLUE_BLUCK;

			}

			break;

		case PURPLE_BLUCK:

			setColor(0,13); 

	    	if(shape==0)

			{

				gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0); 

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos+1][yPos]=PURPLE_BLUCK; play->map[xPos][yPos+1]=PURPLE_BLUCK;

	    		play->map[xPos+1][yPos+1]=PURPLE_BLUCK; play->map[xPos+2][yPos+1]=PURPLE_BLUCK;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=PURPLE_BLUCK; play->map[xPos][yPos+1]=PURPLE_BLUCK;

	    		play->map[xPos+1][yPos+1]=PURPLE_BLUCK; play->map[xPos][yPos+2]=PURPLE_BLUCK;

			}

			else if(shape==2)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos][yPos]=PURPLE_BLUCK; play->map[xPos+1][yPos]=PURPLE_BLUCK;

	    		play->map[xPos+2][yPos]=PURPLE_BLUCK; play->map[xPos+1][yPos+1]=PURPLE_BLUCK;

			}

			else if(shape==3)

	    	{

	    		gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A0); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A0);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A0); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A0);

				

				play->map[xPos+1][yPos]=PURPLE_BLUCK; play->map[xPos][yPos+1]=PURPLE_BLUCK;

	    		play->map[xPos+1][yPos+1]=PURPLE_BLUCK; play->map[xPos+1][yPos+2]=PURPLE_BLUCK;

			}

			break;

	}

}

 

//******************** �� ����� ********************//

void EraseBluck(Play *play, int bluck, int xPos, int yPos, int shape)

{

	int i, j; 

	

	setColor(0,15);

	

	switch(bluck)

	{

		case RED_BLUCK:

			if(shape==0)

			{ 

				gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

		 		gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A1);

		 		

		 		play->map[xPos+1][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos][yPos+2]=0;

			}

			if(shape==1)

			{ 

				gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1);

		 		gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A1);

		 		

		 		play->map[xPos][yPos]=0; play->map[xPos+1][yPos]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos+2][yPos+1]=0;

			}

			break;

		case ORANGE_BLUCK:  // ������� ��ü 

			if(shape==0)

			{

				gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos][yPos+2]=0; play->map[xPos+1][yPos+2]=0;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos+1][yPos]=0;

	    		play->map[xPos+2][yPos]=0; play->map[xPos][yPos+1]=0;

			}else if(shape==2)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos+1][yPos]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos+1][yPos+2]=0;

			}

			else if(shape==3)

	    	{

	    		gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos+2][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos+2][yPos+1]=0;

			}

			break;

		case YELLOW_BLUCK:

			gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1);

			gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1);

			

			play->map[xPos][yPos]=0; play->map[xPos+1][yPos]=0;

	    	play->map[xPos][yPos+1]=0; play->map[xPos+1][yPos+1]=0;

			break;

		case GREEN_BLUCK:

			if(shape==0)

			{

				gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos+1][yPos+2]=0;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos+1][yPos]=0; play->map[xPos+2][yPos]=0;

	    		play->map[xPos][yPos+1]=0; play->map[xPos+1][yPos+1]=0;

			}

			break;

		case AZURE_BLUCK: 

			if(shape==0)

			{

				gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+3); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos][yPos+2]=0; play->map[xPos][yPos+3]=0;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos-1,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos-1][yPos]=0; play->map[xPos][yPos]=0;

	    		play->map[xPos+1][yPos]=0; play->map[xPos+2][yPos]=0;

			}

			break;

		case BLUE_BLUCK: 

			if(shape==0)

			{

				gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos+1][yPos]=0; play->map[xPos+1][yPos+1]=0;

	    		play->map[xPos][yPos+2]=0; play->map[xPos+1][yPos+2]=0;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos+2][yPos+1]=0;

			}

			else if(shape==2)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos+1][yPos]=0;

	    		play->map[xPos][yPos+1]=0; play->map[xPos][yPos+2]=0;

			}

			else if(shape==3)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos+1][yPos]=0;

	    		play->map[xPos+2][yPos]=0; play->map[xPos+2][yPos+1]=0;

			}

			break;

		case PURPLE_BLUCK:

			if(shape==0)

			{

				gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1); 

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+2,yPos+1); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos+1][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos+2][yPos+1]=0;

	    	}

	    	else if(shape==1)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+2); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos][yPos+2]=0;

			}

			else if(shape==2)

	    	{

	    		gotoxy(xPos,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+2,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos][yPos]=0; play->map[xPos+1][yPos]=0;

	    		play->map[xPos+2][yPos]=0; play->map[xPos+1][yPos+1]=0;

			}

			else if(shape==3)

	    	{

	    		gotoxy(xPos+1,yPos); wprintf(L"%wc", 0x25A1); gotoxy(xPos,yPos+1); wprintf(L"%wc", 0x25A1);

				gotoxy(xPos+1,yPos+1); wprintf(L"%wc", 0x25A1); gotoxy(xPos+1,yPos+2); wprintf(L"%wc", 0x25A1);

				

				play->map[xPos+1][yPos]=0; play->map[xPos][yPos+1]=0;

	    		play->map[xPos+1][yPos+1]=0; play->map[xPos+1][yPos+2]=0;

			}

			break;

	}

	

	setColor(0,8); for(i=6;i<16;i++) for(j=0;j<4;j++) if(play->map[i][j]==0)

	{ gotoxy(i,j); wprintf(L"%wc", 0x25A1); }

}

 

//******************** �� ����� ********************//

void EraseLine(Play *play)

{

	int i, j, k;  // �ݺ��� ���� // k: �������� ���� 

	int line[4], c;  // line: �������� ��, c: ������ 

	int l;  // �ݺ��� ���� 

	

	for(j=4, k=0, c=0;j<24;j++)

	{

		for(i=6, c=0;i<16;i++) if(play->map[i][j]>0) c++;

		if(c==10) line[k++]=j;

	}

	if(k>0)

	{

		for(j=0;j<k;j++) for(i=6;i<16;i++) play->map[i][line[j]]=0;

		setColor(0,15); 

		for(j=0;j<k;j++) for(i=6;i<16;i++) { gotoxy(i,line[j]); wprintf(L"%wc", 0x25A0); } Sleep(play->time>>2);

		for(j=0;j<k;j++) for(i=6;i<16;i++) { gotoxy(i,line[j]); wprintf(L"%wc", 0x25A1); } Sleep(play->time>>2);

		for(j=0;j<k;j++) for(i=6;i<16;i++) { gotoxy(i,line[j]); wprintf(L"%wc", 0x25A0); } Sleep(play->time>>2);

		for(j=0;j<k;j++) for(i=6;i<16;i++) { gotoxy(i,line[j]); wprintf(L"%wc", 0x25A1); } Sleep(play->time>>2);

		

		for(j=0;j<k;j++) for(i=6;i<16;i++) 

		{ 

			for(l=line[j];l>0;l--)

			{

				play->map[i][l]=play->map[i][l-1]; 

				gotoxy(i,l-1); setColor(0,15); wprintf(L"%wc", 0x25A1);

				

				if(play->map[i][l-1]==0) continue;

				switch(play->map[i][l-1])

				{

					case RED_BLUCK: setColor(0,12); break;

					case ORANGE_BLUCK: setColor(0,15); break;

					case YELLOW_BLUCK: setColor(0,14); break;

					case GREEN_BLUCK: setColor(0,10); break;

					case AZURE_BLUCK: setColor(0,11); break;

					case BLUE_BLUCK: setColor(0,9); break;

					case PURPLE_BLUCK: setColor(0,13); break;

				}

				gotoxy(i,l); wprintf(L"%wc", 0x25A0); 

				play->map[i][l-1]=0;

			}

		} 

	}

}

 

//******************** ���� �� �����ϱ� ********************//

void RedControl(Play *play)

{

	int shape=0;

	int xPos=10, yPos=0;  // 6~15, 4~23

	int key; 

	

	int c;  // ���� Ȯ�� ���� 

	int i;  // �ݺ��� ���� 

	

	DrawBluck(play, RED_BLUCK, xPos, yPos, shape);

	

	for(;;)

	{

		if(gotoxy(18,24), 

		printf("%d %d %d %d %d %d", c++, kbhit(), play->map[xPos][yPos+3], play->map[xPos+1][yPos+2], play->map[10][5],

		kbhit()), kbhit())

		{

			KEY:

			

			key=getch();

			

			//******************** ����Ű ********************//

			if(key==224)  

			{

				key=getch();

				

				if(key==RIGHT && 

				((shape==0 && play->map[xPos+2][yPos]==0 && play->map[xPos+2][yPos+1]==0 && play->map[xPos+1][yPos+2]==0)

				|| (shape==1 && play->map[xPos+2][yPos]==0 && play->map[xPos+3][yPos+1]==0)))

				{	 

					EraseBluck(play, RED_BLUCK, xPos++, yPos, shape); 

					DrawBluck(play, RED_BLUCK, xPos, yPos, shape);

				}

				else if(key==LEFT && 

				((shape==0 && play->map[xPos][yPos]==0 && play->map[xPos-1][yPos+1]==0 && play->map[xPos-1][yPos+2]==0) 

				|| (shape==1 && play->map[xPos-1][yPos]==0 && play->map[xPos][yPos+1]==0)))

				{	 

					EraseBluck(play, RED_BLUCK, xPos--, yPos, shape); 

					DrawBluck(play, RED_BLUCK, xPos, yPos, shape);

				}

				else if(key==DOWN && 

				((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+2]==0) 

				|| (shape==1 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0))) 

				{	 

					EraseBluck(play, RED_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, RED_BLUCK, xPos, yPos, shape);

				}

			}

			

			//******************** ��� ���� ********************//

			if(key==OKAY)

			{

				for(;;) 

				if((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+2]==0)

				|| (shape==1 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0))

				{

					EraseBluck(play, RED_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, RED_BLUCK, xPos, yPos, shape);

				}

				else break;

				break;

			}

			

			//******************** ȸ�� ********************//

			if(key==HELP)

			{

				if(shape==0)

				{

					if(play->map[xPos][yPos]==0 && play->map[xPos+2][yPos+1]==0)

					{

						EraseBluck(play, RED_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, RED_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==1)

				{

					if(play->map[xPos][yPos+1]==0 && play->map[xPos][yPos+2]==0)

					{

						EraseBluck(play, RED_BLUCK, xPos, yPos, shape--);

						DrawBluck(play, RED_BLUCK, xPos, yPos, shape);

					}

				}

			}

		}

		

		//******************** �ڵ� ���� ********************//

		else if((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+2]==0)

		|| (shape==1 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0))

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			EraseBluck(play, RED_BLUCK, xPos, yPos++, shape);

			DrawBluck(play, RED_BLUCK, xPos, yPos, shape);

		}

		

		//******************** �ٴ� ********************//

		else

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			break;

		}

	}

}

 

//******************** ��Ȳ(->���) �� �����ϱ� ********************//

void OrangeControl(Play *play)

{

	int shape=0;

	int xPos=10, yPos=0;  // 6~15, 4~23

	int key; 

	

	int c;  // ���� Ȯ�� ���� 

	int i;  // �ݺ��� ���� 

	

	DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

	

	for(;;)

	{

		if(gotoxy(18,24), 

		printf("%d %d %d %d %d %d", c++, kbhit(), play->map[xPos][yPos+3], play->map[xPos+1][yPos+2], play->map[10][5],

		kbhit()), kbhit())

		{

			KEY:

			

			key=getch();

			

			//******************** ����Ű ********************//

			if(key==224)  

			{

				key=getch();

				

				if(key==RIGHT && 

				((shape==0 && play->map[xPos+1][yPos]==0 && play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+2]==0)

				|| (shape==1 && play->map[xPos+3][yPos]==0 && play->map[xPos+1][yPos+1]==0)

				|| (shape==2 && play->map[xPos+2][yPos]==0 && play->map[xPos+2][yPos+1]==0 && play->map[xPos+2][yPos+2]==0) 

				|| (shape==3 && play->map[xPos+3][yPos]==0 && play->map[xPos+3][yPos+1]==0) ) )

				{	 

					EraseBluck(play, ORANGE_BLUCK, xPos++, yPos, shape); 

					DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

				}

				else if(key==LEFT && 

				((shape==0 && play->map[xPos-1][yPos]==0 && play->map[xPos-1][yPos+1]==0 && play->map[xPos-1][yPos+2]==0)

				|| (shape==1 && play->map[xPos-1][yPos]==0 && play->map[xPos-1][yPos+1]==0)

				|| (shape==2 && play->map[xPos-1][yPos]==0 && play->map[xPos][yPos+1]==0 && play->map[xPos][yPos+2]==0) 

				|| (shape==3 && play->map[xPos+1][yPos]==0 && play->map[xPos-1][yPos+1]==0) ) )

				{	 

					EraseBluck(play, ORANGE_BLUCK, xPos--, yPos, shape); 

					DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

				}

				else if(key==DOWN && 

				((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+3]==0)

				|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+1]==0)

				|| (shape==2 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+3]==0) 

				|| (shape==3 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0))) 

				{	 

					EraseBluck(play, ORANGE_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

				}

			}

			

			//******************** ��� ���� ********************//

			if(key==OKAY)

			{

				for(;;) 

				if((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+3]==0)

				|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+1]==0)

				|| (shape==2 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+3]==0)

				|| (shape==3 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0) )

				{

					EraseBluck(play, ORANGE_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

				}

				else break;

				break;

			}

			

			//******************** ȸ�� ********************//

			if(key==HELP)

			{

				if(shape==0)

				{

					if(play->map[xPos+1][yPos]==0 && play->map[xPos+2][yPos]==0)

					{

						EraseBluck(play, ORANGE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==1)

				{

					if(play->map[xPos+1][yPos+1]==0 && play->map[xPos+1][yPos+2]==0)

					{

						EraseBluck(play, ORANGE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==2)

				{

					if(play->map[xPos][yPos+1]==0 && play->map[xPos+2][yPos]==0 && play->map[xPos+2][yPos+1]==0)

					{

						EraseBluck(play, ORANGE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==3)

				{

					if(play->map[xPos][yPos]==0 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0)

					{

						EraseBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

						DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape=0);

					}

				}

			}

		}

		

		//******************** �ڵ� ���� ********************//

		else if((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+3]==0)

		|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+1]==0)

		|| (shape==2 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+3]==0)

		|| (shape==3 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0) )

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			EraseBluck(play, ORANGE_BLUCK, xPos, yPos++, shape);

			DrawBluck(play, ORANGE_BLUCK, xPos, yPos, shape);

		}

		

		//******************** �ٴ� ********************//

		else

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			break;

		}

	}

}

 

//******************** ��� �� �����ϱ� ********************//

void YellowControl(Play *play)

{

	int shape=0;

	int xPos=10, yPos=0;  // 6~15, 4~23

	int key; 

	

	int c;  // ���� Ȯ�� ���� 

	int i;  // �ݺ��� ���� 

	

	DrawBluck(play, YELLOW_BLUCK, xPos, yPos, shape);

	

	for(;;)

	{

		if(gotoxy(18,24), 

		printf("%d %d %d %d %d %d", c++, kbhit(), play->map[xPos][yPos+3], play->map[xPos+1][yPos+2], play->map[10][5],

		kbhit()), kbhit())

		{

			KEY:

			

			key=getch();

			

			//******************** ����Ű ********************//

			if(key==224)  

			{

				key=getch();

				

				if(key==RIGHT && play->map[xPos+2][yPos]==0 && play->map[xPos+2][yPos+1]==0)

				{	 

					EraseBluck(play, YELLOW_BLUCK, xPos++, yPos, shape); 

					DrawBluck(play, YELLOW_BLUCK, xPos, yPos, shape);

				}

				else if(key==LEFT && play->map[xPos-1][yPos]==0 && play->map[xPos-1][yPos+1]==0)

				{	 

					EraseBluck(play, YELLOW_BLUCK, xPos--, yPos, shape); 

					DrawBluck(play, YELLOW_BLUCK, xPos, yPos, shape);

				}

				else if(key==DOWN && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0) 

				{	 

					EraseBluck(play, YELLOW_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, YELLOW_BLUCK, xPos, yPos, shape);

				}

			}

			

			//******************** ��� ���� ********************//

			if(key==OKAY)

			{

				for(;;) if(play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0)

				{

					EraseBluck(play, YELLOW_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, YELLOW_BLUCK, xPos, yPos, shape);

				}

				else break;

				break;

			}

			

		}

		

		//******************** �ڵ� ���� ********************//

		else if(play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0)

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			EraseBluck(play, YELLOW_BLUCK, xPos, yPos++, shape);

			DrawBluck(play, YELLOW_BLUCK, xPos, yPos, shape);

		}

		

		//******************** �ٴ� ********************//

		else

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			break;

		}

	}

}

 

//******************** �ʷ� �� �����ϱ� ********************//

void GreenControl(Play *play)

{

	int shape=0;

	int xPos=10, yPos=0;  // 6~15, 4~23

	int key; 

	

	int c;  // ���� Ȯ�� ���� 

	int i;  // �ݺ��� ���� 

	

	DrawBluck(play, GREEN_BLUCK, xPos, yPos, shape);

	

	for(;;)

	{

		if(gotoxy(18,24), 

		printf("%d %d %d %d %d %d", c++, kbhit(), play->map[xPos][yPos+3], play->map[xPos+1][yPos+2], play->map[10][5],

		kbhit()), kbhit())

		{

			KEY:

			

			key=getch();

			

			//******************** ����Ű ********************//

			if(key==224)  

			{

				key=getch();

				

				if(key==RIGHT && 

				((shape==0 && play->map[xPos+1][yPos]==0 && play->map[xPos+2][yPos+1]==0 && play->map[xPos+2][yPos+2]==0)

				|| (shape==1 && play->map[xPos+3][yPos]==0 && play->map[xPos+2][yPos+1]==0)))

				{	 

					EraseBluck(play, GREEN_BLUCK, xPos++, yPos, shape); 

					DrawBluck(play, GREEN_BLUCK, xPos, yPos, shape);

				}

				else if(key==LEFT && 

				((shape==0 && play->map[xPos-1][yPos]==0 && play->map[xPos-1][yPos+1]==0 && play->map[xPos][yPos+2]==0) 

				|| (shape==1 && play->map[xPos][yPos]==0 && play->map[xPos-1][yPos+1]==0)))

				{	 

					EraseBluck(play, GREEN_BLUCK, xPos--, yPos, shape); 

					DrawBluck(play, GREEN_BLUCK, xPos, yPos, shape);

				}

				else if(key==DOWN && 

				((shape==0 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+3]==0) 

				|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+1]==0))) 

				{	 

					EraseBluck(play, GREEN_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, GREEN_BLUCK, xPos, yPos, shape);

				}

			}

			

			//******************** ��� ���� ********************//

			if(key==OKAY)

			{

				for(;;) 

				if((shape==0 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+3]==0)

				|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+1]==0))

				{

					EraseBluck(play, GREEN_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, GREEN_BLUCK, xPos, yPos, shape);

				}

				else break;

				break;

			}

			

			//******************** ȸ�� ********************//

			if(key==HELP)

			{

				if(shape==0)

				{

					if(play->map[xPos+1][yPos]==0 && play->map[xPos+2][yPos]==0)

					{

						EraseBluck(play, GREEN_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, GREEN_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==1)

				{

					if(play->map[xPos][yPos]==0 && play->map[xPos+1][yPos+2]==0)

					{

						EraseBluck(play, GREEN_BLUCK, xPos, yPos, shape--);

						DrawBluck(play, GREEN_BLUCK, xPos, yPos, shape);

					}

				}

			}

		}

		

		//******************** �ڵ� ���� ********************//

		else if((shape==0 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+3]==0)

		|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+1]==0))

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			EraseBluck(play, GREEN_BLUCK, xPos, yPos++, shape);

			DrawBluck(play, GREEN_BLUCK, xPos, yPos, shape);

		}

		

		//******************** �ٴ� ********************//

		else

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			break;

		}

	}

}

 

//******************** �ϴû� �� �����ϱ� ********************//

void AzureControl(Play *play)

{

	int shape=0;

	int xPos=10, yPos=0;  // 6~15, 4~23

	int key; 

	

	int c;  // ���� Ȯ�� ���� 

	int i;  // �ݺ��� ���� 

	

	DrawBluck(play, AZURE_BLUCK, xPos, yPos, shape);

	

	for(;;)

	{

		if(gotoxy(18,24), 

		printf("%d %d %d %d %d %d", c++, kbhit(), play->map[xPos][yPos+3], play->map[xPos+1][yPos+2], play->map[10][5],

		kbhit()), kbhit())

		{

			KEY:

			

			key=getch();

			

			//******************** ����Ű ********************//

			if(key==224)  

			{

				key=getch();

				

				if(key==RIGHT && 

				((shape==0 && play->map[xPos+1][yPos]==0 && play->map[xPos+1][yPos+1]==0 && 

				play->map[xPos+1][yPos+2]==0 && play->map[xPos+1][yPos+2]==0)

				|| (shape==1 && play->map[xPos+3][yPos]==0)))

				{	 

					EraseBluck(play, AZURE_BLUCK, xPos++, yPos, shape); 

					DrawBluck(play, AZURE_BLUCK, xPos, yPos, shape);

				}

				else if(key==LEFT && 

				((shape==0 && play->map[xPos-1][yPos]==0 && play->map[xPos-1][yPos+1]==0 && 

				play->map[xPos-1][yPos+2]==0 && play->map[xPos-1][yPos+2]==0)

				|| (shape==1 && play->map[xPos-2][yPos]==0)))

				{	 

					EraseBluck(play, AZURE_BLUCK, xPos--, yPos, shape); 

					DrawBluck(play, AZURE_BLUCK, xPos, yPos, shape);

				}

				else if(key==DOWN && 

				((shape==0 && play->map[xPos][yPos+4]==0) 

				|| (shape==1 && play->map[xPos-1][yPos+1]==0 && play->map[xPos][yPos+1]==0 && 

				play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+1]==0))) 

				{	 

					EraseBluck(play, AZURE_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, AZURE_BLUCK, xPos, yPos, shape);

				}

			}

			

			//******************** ��� ���� ********************//

			if(key==OKAY)

			{

				for(;;) 

				if((shape==0 && play->map[xPos][yPos+4]==0)

				|| (shape==1 && play->map[xPos-1][yPos+1]==0 && play->map[xPos][yPos+1]==0 && 

				play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+1]==0))

				{

					EraseBluck(play, AZURE_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, AZURE_BLUCK, xPos, yPos, shape);

				}

				else break;

				break;

			}

			

			//******************** ȸ�� ********************//

			if(key==HELP)

			{

				if(shape==0)

				{

					if(play->map[xPos-1][yPos]==0 && play->map[xPos+1][yPos]==0 && play->map[xPos+2][yPos]==0)

					{

						EraseBluck(play, AZURE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, AZURE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==1)

				{

					if(play->map[xPos][yPos+1]==0 && play->map[xPos][yPos+2]==0 && play->map[xPos][yPos+3]==0)

					{

						EraseBluck(play, AZURE_BLUCK, xPos, yPos, shape--);

						DrawBluck(play, AZURE_BLUCK, xPos, yPos, shape);

					}

				}

			}

		}

		

		//******************** �ڵ� ���� ********************//

		else if((shape==0 && play->map[xPos][yPos+4]==0)

		|| (shape==1 && play->map[xPos-1][yPos+1]==0 && play->map[xPos][yPos+1]==0 && 

		play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+1]==0))

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			EraseBluck(play, AZURE_BLUCK, xPos, yPos++, shape);

			DrawBluck(play, AZURE_BLUCK, xPos, yPos, shape);

		}

		

		//******************** �ٴ� ********************//

		else

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			break;

		}

	}

}

 

//******************** �Ķ� �� �����ϱ� ********************//

void BlueControl(Play *play)

{

	int shape=0;

	int xPos=10, yPos=0;  // 6~15, 4~23

	int key; 

	

	int c;  // ���� Ȯ�� ���� 

	int i;  // �ݺ��� ���� 

	

	DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

	

	for(;;)

	{

		if(gotoxy(18,24), 

		printf("%d %d %d %d %d %d", c++, kbhit(), play->map[xPos][yPos+3], play->map[xPos+1][yPos+2], play->map[10][5],

		kbhit()), kbhit())

		{

			KEY:

			

			key=getch();

			

			//******************** ����Ű ********************//

			if(key==224)  

			{

				key=getch();

				

				if(key==RIGHT && 

				((shape==0 && play->map[xPos+2][yPos]==0 && play->map[xPos+2][yPos+1]==0 && play->map[xPos+2][yPos+2]==0)

				|| (shape==1 && play->map[xPos+1][yPos]==0 && play->map[xPos+3][yPos+1]==0)

				|| (shape==2 && play->map[xPos+2][yPos]==0 && play->map[xPos+1][yPos+1]==0 && play->map[xPos+1][yPos+2]==0) 

				|| (shape==3 && play->map[xPos+3][yPos]==0 && play->map[xPos+3][yPos+1]==0) ) )

				{	 

					EraseBluck(play, BLUE_BLUCK, xPos++, yPos, shape); 

					DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

				}

				else if(key==LEFT && 

				((shape==0 && play->map[xPos][yPos]==0 && play->map[xPos][yPos+1]==0 && play->map[xPos-1][yPos+2]==0)

				|| (shape==1 && play->map[xPos-1][yPos]==0 && play->map[xPos-1][yPos+1]==0)

				|| (shape==2 && play->map[xPos-1][yPos]==0 && play->map[xPos-1][yPos+1]==0 && play->map[xPos-1][yPos+2]==0) 

				|| (shape==3 && play->map[xPos-1][yPos]==0 && play->map[xPos+1][yPos+1]==0) ) )

				{	 

					EraseBluck(play, BLUE_BLUCK, xPos--, yPos, shape); 

					DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

				}

				else if(key==DOWN && 

				((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+3]==0)

				|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0)

				|| (shape==2 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+1]==0) 

				|| (shape==3 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+2]==0))) 

				{	 

					EraseBluck(play, BLUE_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

				}

			}

			

			//******************** ��� ���� ********************//

			if(key==OKAY)

			{

				for(;;) 

				if((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+3]==0)

				|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0)

				|| (shape==2 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+1]==0)

				|| (shape==3 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+2]==0) )

				{

					EraseBluck(play, BLUE_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

				}

				else break;

				break;

			}

			

			//******************** ȸ�� ********************//

			if(key==HELP)

			{

				if(shape==0)

				{

					if(play->map[xPos][yPos]==0 && play->map[xPos][yPos+1]==0 && play->map[xPos+2][yPos+1]==0)

					{

						EraseBluck(play, BLUE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==1)

				{

					if(play->map[xPos+1][yPos]==0 && play->map[xPos][yPos+2]==0)

					{

						EraseBluck(play, BLUE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==2)

				{

					if(play->map[xPos+2][yPos]==0 && play->map[xPos+2][yPos+1]==0)

					{

						EraseBluck(play, BLUE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==3)

				{

					if(play->map[xPos+1][yPos+1]==0 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0)

					{

						EraseBluck(play, BLUE_BLUCK, xPos, yPos, shape);

						DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape=0);

					}

				}

			}

		}

		

		//******************** �ڵ� ���� ********************//

		else if((shape==0 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+3]==0)

		|| (shape==1 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0)

		|| (shape==2 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+1]==0)

		|| (shape==3 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+1]==0 && play->map[xPos+2][yPos+2]==0) )

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			EraseBluck(play, BLUE_BLUCK, xPos, yPos++, shape);

			DrawBluck(play, BLUE_BLUCK, xPos, yPos, shape);

		}

		

		//******************** �ٴ� ********************//

		else

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			break;

		}

	}

}

 

//******************** ���� �� �����ϱ� ********************//

void PurpleControl(Play *play)

{

	int shape=0;

	int xPos=10, yPos=0;  // 6~15, 4~23

	int key; 

	

	int c;  // ���� Ȯ�� ���� 

	int i;  // �ݺ��� ���� 

	

	DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

	

	for(;;)

	{

		if(gotoxy(18,24), 

		printf("%d %d %d %d %d %d", c++, kbhit(), play->map[xPos][yPos+3], play->map[xPos+1][yPos+2], play->map[10][5],

		kbhit()), kbhit())

		{

			KEY:

			

			key=getch();

			

			//******************** ����Ű ********************//

			if(key==224)  

			{

				key=getch();

				

				if(key==RIGHT && 

				((shape==0 && play->map[xPos+2][yPos]==0 && play->map[xPos+3][yPos+1]==0)

				|| (shape==1 && play->map[xPos+1][yPos]==0 && play->map[xPos+2][yPos+1]==0 && play->map[xPos+1][yPos+2]==0)

				|| (shape==2 && play->map[xPos+3][yPos]==0 && play->map[xPos+2][yPos+1]==0) 

				|| (shape==3 && play->map[xPos+2][yPos]==0 && play->map[xPos+2][yPos+1]==0 && play->map[xPos+2][yPos+2]==0)))

				{	 

					EraseBluck(play, PURPLE_BLUCK, xPos++, yPos, shape); 

					DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

				}

				else if(key==LEFT && 

				((shape==0 && play->map[xPos][yPos]==0 && play->map[xPos-1][yPos+1]==0)

				|| (shape==1 && play->map[xPos-1][yPos]==0 && play->map[xPos-1][yPos+1]==0 && play->map[xPos-1][yPos+2]==0)

				|| (shape==2 && play->map[xPos-1][yPos]==0 && play->map[xPos][yPos+1]==0) 

				|| (shape==3 && play->map[xPos][yPos]==0 && play->map[xPos-1][yPos+1]==0 && play->map[xPos][yPos+2]==0) ) )

				{	 

					EraseBluck(play, PURPLE_BLUCK, xPos--, yPos, shape); 

					DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

				}

				else if(key==DOWN && 

				((shape==0 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0)

				|| (shape==1 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+2]==0)

				|| (shape==2 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+1]==0) 

				|| (shape==3 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+3]==0) ) ) 

				{	 

					EraseBluck(play, PURPLE_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

				}

			}

			

			//******************** ��� ���� ********************//

			if(key==OKAY)

			{

				for(;;) 

				if((shape==0 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0)

				|| (shape==1 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+2]==0)

				|| (shape==2 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+1]==0)

				|| (shape==3 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+3]==0) )

				{

					EraseBluck(play, PURPLE_BLUCK, xPos, yPos++, shape);

					DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

				}

				else break;

				break;

			}

			

			//******************** ȸ�� ********************//

			if(key==HELP)

			{

				if(shape==0)

				{

					if(play->map[xPos][yPos]==0 && play->map[xPos][yPos+2]==0)

					{

						EraseBluck(play, PURPLE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==1)

				{

					if(play->map[xPos+1][yPos]==0 && play->map[xPos+2][yPos]==0)

					{

						EraseBluck(play, PURPLE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==2)

				{

					if(play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+2]==0)

					{

						EraseBluck(play, PURPLE_BLUCK, xPos, yPos, shape++);

						DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

					}

				}

				else if(shape==3)

				{

					if(play->map[xPos+2][yPos+1]==0)

					{

						EraseBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

						DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape=0);

					}

				}

			}

		}

		

		//******************** �ڵ� ���� ********************//

		else if((shape==0 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+2]==0)

		|| (shape==1 && play->map[xPos][yPos+3]==0 && play->map[xPos+1][yPos+2]==0)

		|| (shape==2 && play->map[xPos][yPos+1]==0 && play->map[xPos+1][yPos+2]==0 && play->map[xPos+2][yPos+1]==0)

		|| (shape==3 && play->map[xPos][yPos+2]==0 && play->map[xPos+1][yPos+3]==0) )

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			EraseBluck(play, PURPLE_BLUCK, xPos, yPos++, shape);

			DrawBluck(play, PURPLE_BLUCK, xPos, yPos, shape);

		}

		

		//******************** �ٴ� ********************//

		else

		{

			for(i=0;i<play->time;i++) 

			{

				Sleep(1); if(kbhit()) goto KEY;

			}

			break;

		}

	}

}

 

int LoseJudgment(int (*map)[25])  // 3�� 6, 15 

{

	int i, c;

	

	for(i=6, c=0;i<16;i++) if(map[i][3]>0) { c++; break; }

	if(c==1) return 1;

	return 0;

}

 
