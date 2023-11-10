

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <windows.h>

#include <conio.h>

#include <wchar.h>

#include <locale.h>

#include <string.h>

 

enum { UP=72, DOWN=80, RIGHT=77, LEFT=75, OKAY=32, ENTER=13 };

 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

 

void gotoxy(int x, int y)

{

	COORD Pos; Pos.X=x<<1; Pos.Y=y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}

 

void setColor(WORD back, WORD text)

{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text|(back<<4));

}

 

void implement();

 

int map[10][10], head[40], back[40];

 

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "Korean"); implement();

	return 0;

}

 

void implement()

{

	int width[10]={0, 3, 6, 12, 15, 18, 24, 27};  // 3 6 12 15 18 24 27

	int heigh[10]={0, 15, 13, 11, 9, 7, 5};  // 15 13 11 9 7 5

	int i, j, k, n, m, temp, M, N;

	int xPos, yPos, key;

	setColor(15,0); for(i=0;i<80;i++) for(j=0;j<25;j++) printf(" "); gotoxy(0,0);

	

	for(j=1, k=1;j<=6;j++) for(i=1;i<=7;i++)

	{

		if(k==22) k++; if(k==37) i+=5; 

		map[i][j]=k++;

	}

	

	for(j=1, k=1;j<=6;j++) for(i=1;i<=7;i++)

	{

		if(i==1 && j==6) i=6; 

		gotoxy(width[i],heigh[j]); printf("%d", map[i][j]);

	} xPos=1; yPos=1; gotoxy(width[xPos],heigh[yPos]);

	

	for(;;) if(kbhit())

	{

		key=getch();

		

		if(key==224)

		{

			key=getch();

			

			if(key==UP && ((xPos<=5 && yPos<5) || (xPos>=6 && yPos<6))) gotoxy(width[xPos],heigh[++yPos]);

			if(key==DOWN && yPos>1) gotoxy(width[xPos],heigh[--yPos]);

			if(key==RIGHT && xPos<7) gotoxy(width[++xPos],heigh[yPos]);

			if(key==LEFT && xPos>1 && !(xPos==6 && yPos==6)) gotoxy(width[--xPos],heigh[yPos]);

		}

		if(key==OKAY)

		{

			if(head[map[xPos][yPos]]==0)

			{

				head[map[xPos][yPos]]=1;

				gotoxy(width[xPos],heigh[yPos]); setColor(15,12); printf("%d", map[xPos][yPos]);

			}

			else

			{

				head[map[xPos][yPos]]=0;

				gotoxy(width[xPos],heigh[yPos]); setColor(15,0); printf("%d", map[xPos][yPos]);

			}

		}

		if(key==ENTER)

		{

			srand((unsigned int)time(NULL));

			for(i=1, n=0, k=1;i<=38;i++) if(head[i]==1)

			{

				n++; back[k++]=i;

			} for(i=1;i<=38;i++) if(head[i]==0) 

			{ if(i==22) continue; back[k++]=i; }

			for(i=1;i<=1000;i++)

			{

				M=rand()%n+1; N=rand()%n+1;

				temp=back[M]; back[M]=back[N]; back[N]=temp;

				M=rand()%(37-n)+n+1; N=rand()%(37-n)+n+1;

				temp=back[M]; back[M]=back[N]; back[N]=temp;

			}

			

			// gotoxy(0,24); for(i=1;i<=n;i++) printf("%d ", back[i]);

			

			setColor(15,12);

			for(i=1, k=1;(k-1)*7+i<=n;i++)

			{

				gotoxy(width[i],heigh[k]); printf("  "); 

				gotoxy(width[i],heigh[k]); printf("%d", back[(k-1)*7+i]);

				if(i%7==0) { k++; i=0; }

			}

			

			// °æ°è¼± 

			

			setColor(15,0);

			for(;(k-1)*7+i<=35;i++)

			{

				// if((k-1)*7+i==22) continue;

				gotoxy(width[i],heigh[k]); printf("  "); 

				gotoxy(width[i],heigh[k]); printf("%d", back[(k-1)*7+i]);

				/*

				if(back[(k-1)*7+i]==22)

				{

					gotoxy(width[i],heigh[k]); printf("  "); 

					gotoxy(width[i],heigh[k]); printf("%d", 38);

				}*/

				if(i%7==0) { k++; i=0; }

			}

			gotoxy(width[6],heigh[6]); printf("  "); gotoxy(width[6],heigh[6]); printf("%d", back[36]);

			gotoxy(width[7],heigh[6]); printf("  "); gotoxy(width[7],heigh[6]); printf("%d", back[37]);

			

			break; 

		}

	}

	setColor(15,12); gotoxy(0,0);

}

 

 

 

 
