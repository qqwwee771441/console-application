#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define ESC 27
#define ARROW 224
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define SPACE 32

#define MAX_X 80
#define MAX_Y 25
#define MIDDLE -10

enum { black, _blue, _green, _azure, _red, _purple, _yellow, _white,
_black, blue, green, azure, red, purple, yellow, white };

enum { bound=-2, empty=-1 };

/******************** Ŀ�� Ŭ���� ********************/
class Cursor {
	private:
		COORD Pos; // ��ġ ��ǥ 
		WORD text, back; // ���ڻ�, ���� 
	public:
		Cursor(): text(white), back(black) { Pos.X=0; Pos.Y=0; }
		void operator()(const int move) // ��ĭ�̵� 
		{
			switch(move)
			{
			case UP:
				(*this)(Pos.X, Pos.Y-1);
				break;
			case DOWN:
				(*this)(Pos.X, Pos.Y+1);
				break;
			case RIGHT:
				(*this)(Pos.X+2, Pos.Y);
				break;
			case LEFT:
				(*this)(Pos.X-2, Pos.Y);
				break;
			case MIDDLE:
				(*this)(MAX_X/2, MAX_Y/2);
				break;
			}
		}
		void operator()(const short x, const short y) // ��ǥ�̵� 
		{
			Pos.X=x; Pos.Y=y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		}
		void color(const WORD t) // ���ڻ� ���� 
		{
			text=t;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text|(back<<4));
		}
		void color(const WORD t, const WORD b) // ���ڻ�, ���� ���� 
		{
			text=t; back=b;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text|(back<<4));
		}
		void operator++(int) // ��� ��������  ȭ�� �ʱ�ȭ 
		{
			color(white, white);	
			for(int i=0;i<MAX_X;i++) for(int j=0;j<MAX_Y;j++)
			{
				(*this)(i,j); putchar(' ');
			}
		}
		short getX() { return Pos.X; }
		short getY() { return Pos.Y; }
}; Cursor cursor; // Ŀ�� ��ü ���� 

/******************** ������ Ŭ���� ********************/
class Board {
	private:
		int map[17][17]; // 15*15, 0�� 16�� ��� 
		int step; // ��� �����ߴ°�
		// Ȧ��: ���������� �� ����� �� 
		// ¦��: ���������� �� ����� �� 
		int xPos, yPos; // ���� Ŀ�� �� ��ǥ 
	public:
		Board() : step(0)
		{
			for(int i=0;i<=16;i++) // ���: -1
			{
				map[0][i]=bound; map[16][i]=bound;
				map[i][0]=bound; map[i][16]=bound;
			}
			for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) map[i][j]=empty; // �����: 0 
		}
		void display(){
			cursor.color(_black);
			for(int y=2;y<=14;y++) for(int x=2;x<=14;x++)
			{
				move(x,y); wprintf(L"%wc", 0x254B); printf(" "); // ???
			}
			move(1,15); wprintf(L"%wc", 0x250F); printf(" ");
			move(1,1); wprintf(L"%wc", 0x2517); printf(" ");
			move(15,15); wprintf(L"%wc", 0x2513); printf(" ");
			move(15,1); wprintf(L"%wc", 0x251B); printf(" ");
			for(int i=2;i<=14;i++)
			{
				move(1,i); wprintf(L"%wc", 0x2523); printf(" ");
				move(15,i); wprintf(L"%wc", 0x252B); printf(" ");
				move(i,15); wprintf(L"%wc", 0x2533); printf(" ");
				move(i,1); wprintf(L"%wc", 0x253B); printf(" ");
			}
		}
		void move(int x, int y)
		{
			xPos=x; yPos=y;
			cursor(22+xPos*2,19-yPos);
		}
		void move(const int m) // ��ĭ�̵� 
		{
			switch(m)
			{
			case UP:
				if(yPos<15) move(xPos,yPos+1);
				break;
			case DOWN:
				if(yPos>1) move(xPos,yPos-1);
				break;
			case RIGHT:
				if(xPos<15) move(xPos+1,yPos);
				break;
			case LEFT:
				if(xPos>1) move(xPos-1,yPos);
				break;
			}
		}
		void put()
		{
			if(step%2==0 && map[xPos][yPos]==empty) // ����� ������ �� ���� 
			{
				map[xPos][yPos]=black; // ��: 1 
				wprintf(L"%wc", 0x25CF);
				step++;
			}
			if(step%2==1 && map[xPos][yPos]==empty) // �氡�� ������ �� ���� 
			{
				map[xPos][yPos]=white; // ��: 2 
				wprintf(L"%wc", 0x25CB);
				step++;
			}
		}
		int getX() const { return xPos; }
		int getY() const { return yPos; }
		bool okay() 
		{
			if((map[xPos][yPos]==empty 
			&& threes()<=1 && fours()<=1
			&& !Is6()) || (Is5())) return true;
			else return false; 
		}
		void printMap()
		{
			cursor(0,25); cursor.color(black);
			for(int y=16;y>=0;y--) 
			{
				for(int x=0;x<=16;x++) printf("%2d ", map[x][y]);
				printf("\n");
			}
		}
		/******************** 33�Ǵ� ********************/
		int threes()
		{
			if(map[xPos][yPos]==empty)
			{
				int count=0;
				map[xPos][yPos]=black;
				/******************** 1 ********************/
				for(int y=yPos+2;y>=yPos;y--) // ������
				{
					if(map[xPos][y]==black && map[xPos][y-1]==black && map[xPos][y-2]==black 
					&& map[xPos][y+1]==empty && map[xPos][y-3]==empty
					&& (map[xPos][y+2]==empty || map[xPos][y-4]==empty)
					&& (map[xPos][y+2]!=black && map[xPos][y-4]!=black)) count++;
				}
				for(int x=xPos-2;x<=xPos;x++) // ������
				{
					if(map[x][yPos]==black && map[x+1][yPos]==black && map[x+2][yPos]==black 
					&& map[x-1][yPos]==empty && map[x+3][yPos]==empty
					&& (map[x-2][yPos]==empty || map[x+4][yPos]==empty)
					&& (map[x-2][yPos]!=black && map[x+4][yPos]!=black)) count++;
				}
				for(int x=xPos-2, y=yPos-2;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y+1]==black && map[x+2][y+2]==black 
					&& map[x-1][y-1]==empty && map[x+3][y+3]==empty
					&& (map[x-2][y-2]==empty || map[x+4][y+4]==empty)
					&& (map[x-2][y-2]!=black && map[x+4][y+4]!=black)) count++;
				}
				for(int x=xPos-2, y=yPos+2;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y-1]==black && map[x+2][y-2]==black 
					&& map[x-1][y+1]==empty && map[x+3][y-3]==empty
					&& (map[x-2][y+2]==empty || map[x+4][y-4]==empty)
					&& (map[x-2][y+2]!=black && map[x+4][y-4]!=black)) count++;
				}
				/******************** 2 ********************/
				for(int y=yPos+3;y>=yPos;y--) // ������
				{
					if(map[xPos][y+1]==empty && map[xPos][y]==black && map[xPos][y-1]==black 
					&& map[xPos][y-2]==empty && map[xPos][y-3]==black && map[xPos][y-4]==empty) count++;
				}
				for(int x=xPos-3;x<=xPos;x++) // ������
				{
					if(map[x-1][yPos]==empty && map[x][yPos]==black && map[x+1][yPos]==black 
					&& map[x+2][yPos]==empty && map[x+3][yPos]==black && map[x+4][yPos]==empty) count++;
				}
				for(int x=xPos-3, y=yPos-3;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x-1][y-1]==empty && map[x][y]==black && map[x+1][y+1]==black 
					&& map[x+2][y+2]==empty && map[x+3][y+3]==black && map[x+4][y+4]==empty) count++;
				}
				for(int x=xPos-3, y=yPos+3;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x-1][y+1]==empty && map[x][y]==black && map[x+1][y-1]==black 
					&& map[x+2][y-2]==empty && map[x+3][y-3]==black && map[x+4][y-4]==empty) count++;
				}
				/******************** 3 ********************/
				for(int y=yPos+3;y>=yPos;y--) // ������
				{
					if(map[xPos][y+1]==empty && map[xPos][y]==black && map[xPos][y-1]==empty 
					&& map[xPos][y-2]==black && map[xPos][y-3]==black && map[xPos][y-4]==empty) count++;
				}
				for(int x=xPos-3;x<=xPos;x++) // ������
				{
					if(map[x-1][yPos]==empty && map[x][yPos]==black && map[x+1][yPos]==empty 
					&& map[x+2][yPos]==black && map[x+3][yPos]==black && map[x+4][yPos]==empty) count++;
				}
				for(int x=xPos-3, y=yPos-3;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x-1][y-1]==empty && map[x][y]==black && map[x+1][y+1]==empty 
					&& map[x+2][y+2]==black && map[x+3][y+3]==black && map[x+4][y+4]==empty) count++;
				}
				for(int x=xPos-3, y=yPos+3;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x-1][y+1]==empty && map[x][y]==black && map[x+1][y-1]==empty 
					&& map[x+2][y-2]==black && map[x+3][y-3]==black && map[x+4][y-4]==empty) count++;
				}
				
				map[xPos][yPos]=empty;
				return count;
			}
			return 10;
		}
		/******************** 44�Ǵ� ********************/
		int fours()
		{
			if(map[xPos][yPos]==empty)
			{
				int count=0;
				map[xPos][yPos]=black;
				int a=0, b=0, c=0, d=0;
				/******************** 1 ********************/
				if(a==0) for(int y=yPos+3;y>=yPos;y--) // ������
				{
					if(map[xPos][y]==black && map[xPos][y-1]==black && map[xPos][y-2]==black 
					&& map[xPos][y-3]==black
					&& (map[xPos][y+1]==empty || map[xPos][y-4]==empty)) { count++; a++; break; }
				}
				if(b==0) for(int x=xPos-3;x<=xPos;x++) // ������
				{
					if(map[x][yPos]==black && map[x+1][yPos]==black && map[x+2][yPos]==black 
					&& map[x+3][yPos]==black
					&& (map[x-1][yPos]==empty || map[x+4][yPos]==empty)) { count++; b++; break; }
				}
				if(c==0) for(int x=xPos-3, y=yPos-3;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y+1]==black && map[x+2][y+2]==black 
					&& map[x+3][y+3]==black
					&& (map[x-1][y-1]==empty || map[x+4][y+4]==empty)) { count++; c++; break; }
				}
				if(d==0) for(int x=xPos-3, y=yPos+3;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y-1]==black && map[x+2][y-2]==black 
					&& map[x+3][y-3]==black
					&& (map[x-1][y+1]==empty || map[x+4][y-4]==empty)) { count++; d++; break; }
				}
				/******************** 2 ********************/
				if(a==0) for(int y=yPos+4;y>=yPos;y--) // ������
				{
					if(map[xPos][y]==black && map[xPos][y-1]==black 
					&& map[xPos][y-2]==black && map[xPos][y-3]==empty && map[xPos][y-4]==black) 
					{ count++; a++; break; }
				}
				if(b==0) for(int x=xPos-4;x<=xPos;x++) // ������
				{
					if(map[x][yPos]==black && map[x+1][yPos]==black 
					&& map[x+2][yPos]==black && map[x+3][yPos]==empty && map[x+4][yPos]==black) 
					{ count++; b++; break; }
				}
				if(c==0) for(int x=xPos-4, y=yPos-4;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y+1]==black 
					&& map[x+2][y+2]==black && map[x+3][y+3]==empty && map[x+4][y+4]==black) 
					{ count++; c++; break; }
				}
				if(d==0) for(int x=xPos-4, y=yPos+4;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y-1]==black 
					&& map[x+2][y-2]==black && map[x+3][y-3]==empty && map[x+4][y-4]==black) 
					{ count++; d++; break; }
				}
				/******************** 3 ********************/
				if(a==0) for(int y=yPos+4;y>=yPos;y--) // ������
				{
					if(map[xPos][y]==black && map[xPos][y-1]==black 
					&& map[xPos][y-2]==empty && map[xPos][y-3]==black && map[xPos][y-4]==black) 
					{ count++; a++; break; }
				}
				if(b==0) for(int x=xPos-4;x<=xPos;x++) // ������
				{
					if(map[x][yPos]==black && map[x+1][yPos]==black 
					&& map[x+2][yPos]==empty && map[x+3][yPos]==black && map[x+4][yPos]==black) 
					{ count++; b++; break; }
				}
				if(c==0) for(int x=xPos-4, y=yPos-4;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y+1]==black 
					&& map[x+2][y+2]==empty && map[x+3][y+3]==black && map[x+4][y+4]==black) 
					{ count++; c++; break; }
				}
				if(d==0) for(int x=xPos-4, y=yPos+4;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y-1]==black 
					&& map[x+2][y-2]==empty && map[x+3][y-3]==black && map[x+4][y-4]==black) 
					{ count++; d++; break; }
				}
				/******************** 4 ********************/
				if(a==0) for(int y=yPos+4;y>=yPos;y--) // ������
				{
					if(map[xPos][y]==black && map[xPos][y-1]==empty 
					&& map[xPos][y-2]==black && map[xPos][y-3]==black && map[xPos][y-4]==black) 
					{ count++; a++; break; }
				}
				if(b==0) for(int x=xPos-4;x<=xPos;x++) // ������
				{
					if(map[x][yPos]==black && map[x+1][yPos]==empty 
					&& map[x+2][yPos]==black && map[x+3][yPos]==black && map[x+4][yPos]==black) 
					{ count++; b++; break; }
				}
				if(c==0) for(int x=xPos-4, y=yPos-4;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y+1]==empty 
					&& map[x+2][y+2]==black && map[x+3][y+3]==black && map[x+4][y+4]==black) 
					{ count++; c++; break; }
				}
				if(d==0) for(int x=xPos-4, y=yPos+4;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y-1]==empty 
					&& map[x+2][y-2]==black && map[x+3][y-3]==black && map[x+4][y-4]==black) 
					{ count++; d++; break; }
				}
				
				map[xPos][yPos]=empty;
				return count;
			}
			return 10;
		}
		bool Is6()
		{
			if(map[xPos][yPos]==empty)
			{
				map[xPos][yPos]==black;
				int count=0;
				for(int y=yPos+5;y>=yPos;y--) // ������
				{
					if(map[xPos][y]==black && map[xPos][y-1]==black &&
					map[xPos][y-2]==black && map[xPos][y-3]==black &&
					map[xPos][y-4]==black && map[xPos][y-5]==black) count++;
				}
				for(int x=xPos-5;x<=xPos;x++) // ������
				{
					if(map[x][yPos]==black && map[x+1][yPos]==black &&
					map[x+2][yPos]==black && map[x+3][yPos]==black &&
					map[x+4][yPos]==black && map[x+5][yPos]==black) count++;
				}
				for(int x=xPos-5, y=yPos-5;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y+1]==black &&
					map[x+2][y+2]==black && map[x+3][y+3]==black &&
					map[x+4][y+4]==black && map[x+5][y+5]==black) count++;
				}
				for(int x=xPos-5, y=yPos+5;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y-1]==black &&
					map[x+2][y-2]==black && map[x+3][y-3]==black &&
					map[x+4][y-4]==black && map[x+5][y-5]) count++;
				}
				map[xPos][yPos]==empty;
				if(count>0) return true;
			}
			return false;
		}
		bool Is5()
		{
			if(map[xPos][yPos]==empty)
			{
				map[xPos][yPos]==black;
				int count=0;
				for(int y=yPos+4;y>=yPos;y--) // ������
				{
					if(map[xPos][y]==black && map[xPos][y-1]==black &&
					map[xPos][y-2]==black && map[xPos][y-3]==black &&
					map[xPos][y-4]==black) return true;
				}
				for(int x=xPos-4;x<=xPos;x++) // ������
				{
					if(map[x][yPos]==black && map[x+1][yPos]==black &&
					map[x+2][yPos]==black && map[x+3][yPos]==black &&
					map[x+4][yPos]==black) return true;
				}
				for(int x=xPos-4, y=yPos-4;x<=xPos && y<=yPos;x++,y++) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y+1]==black &&
					map[x+2][y+2]==black && map[x+3][y+3]==black &&
					map[x+4][y+4]==black) return true;
				}
				for(int x=xPos-4, y=yPos+4;x<=xPos && y>=yPos;x++,y--) // �밢�� 
				{
					if(map[x][y]==black && map[x+1][y-1]==black &&
					map[x+2][y-2]==black && map[x+3][y-3]==black &&
					map[x+4][y-4]==black) return true;
				}
				map[xPos][yPos]==empty;
				if(count>0) return true;
			}
			return false;
		}
};

/******************** �ΰ����� Ŭ���� ********************/
class Computer {
	struct Stone { // ���� 
		int mok; // 4�� 3�� 2�� 
		int type; // �� ���� �Ǵ�
		int xPos, yPos; // �ٽ� ��ǥ 
		int direction; // ���� - ���� ���� �밢1 �밢2 
		
		Stone(int m, int t, int x, int y, int d)
		: mok(m), type(t), xPos(x), yPos(y), direction(d) { }
	};
	Board& board;
	int map[17][17];
	int step;
	int xPos, yPos;
	public:
		Computer(Board& ref) : board(ref), step(0) 
		{
			for(int i=0;i<=16;i++) // ���: -1
			{
				map[0][i]=bound; map[16][i]=bound;
				map[i][0]=bound; map[i][16]=bound;
			}
			for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) map[i][j]=empty; // �����: 0
		}
		int operator()()
		{
			xPos=board.getX();
			yPos=board.getY();
			map[xPos][yPos]=black; step++;
			
			if(Is5(black) == true) // ��(1)�� 5���� ������°�?
			{
				return black;
			} 
			
			/******************** ��� ������? ********************/ /***** �ٽɺκ� *****/
			Stone whiteStone = Is4(white);
			if(whiteStone.mok == 0) whiteStone = Is3(white);
			if(whiteStone.mok == 0) whiteStone = _Is3(white);
			if(whiteStone.mok == 0) whiteStone = Is2(white);
			
			Stone blackStone = Is4(black); int k=rand()%4;
			if(blackStone.mok == 0) blackStone = Is3(black);
			if(blackStone.mok == 0 && k==0) blackStone = _Is3(black);
			if(blackStone.mok == 0) blackStone = Is2(black);
			
			cursor(0,25); cursor.color(black);
			//printf("%d %d %d %d %d", 
			//black4.mok, black4.type, black4.xPos, black4.yPos, black4.direction); // ����� 
			printf("%d %d %d %d %d", blackStone.mok, blackStone.type, 
			blackStone.xPos, blackStone.yPos, blackStone.direction); // ����� 
			cursor(0,26); cursor.color(black);
			printf("%d %d %d %d %d", whiteStone.mok, whiteStone.type, 
			whiteStone.xPos, whiteStone.yPos, whiteStone.direction); // ����� 
			
			if(whiteStone.mok == 4)
			{
				xPos = whiteStone.xPos; 
				yPos = whiteStone.yPos;
			}
			else if(blackStone.mok == 4) // ��밡 4���̸�  
			{
				xPos = blackStone.xPos; 
				yPos = blackStone.yPos;
				/*
				if(black4.type==1) // ����1 
				{
					if(black4.direction==1) // ����1 
					{
						int k = rand()%2; 
						xPos=black4.xPos;
						if(k==0) yPos=black4.yPos+1;
						else yPos=black4.yPos-4;
					}
					if(black4.direction==2) // ����2 
					{
						int k = rand()%2; 
						if(k==0) xPos=black4.xPos-1;
						else xPos=black4.xPos+4;
						yPos=black4.yPos;
					}
					if(black4.direction==3) // ����3 
					{
						int k = rand()%2; 
						if(k==0) 
						{
							xPos=black4.xPos-1;
							yPos=black4.yPos+1;
						}
						else 
						{
							xPos=black4.xPos+4;
							yPos=black4.yPos-4;
						}
					}
					if(black4.direction==4) // ����4 
					{
						int k = rand()%2; 
						if(k==0) 
						{
							xPos=black4.xPos-1;
							yPos=black4.yPos-1;
						}
						else 
						{
							xPos=black4.xPos+4;
							yPos=black4.yPos+4;
						}
					}
				}
				*/
			}
			else if(whiteStone.mok == 3)
			{
				if(whiteStone.type==1) // ����1 
				{
					if(whiteStone.direction==1) // ����1 
					{
						int k = rand()%2; 
						xPos=whiteStone.xPos;
						if(k==0) yPos=whiteStone.yPos+1;
						else yPos=whiteStone.yPos-3;
					}
					if(whiteStone.direction==2) // ����2 
					{
						int k = rand()%2; 
						if(k==0) xPos=whiteStone.xPos-1;
						else xPos=whiteStone.xPos+3;
						yPos=whiteStone.yPos;
					}
					if(whiteStone.direction==3) // ����3 
					{
						int k = rand()%2; 
						if(k==0) 
						{
							xPos=whiteStone.xPos-1;
							yPos=whiteStone.yPos+1;
						}
						else 
						{
							xPos=whiteStone.xPos+3;
							yPos=whiteStone.yPos-3;
						}
					}
					if(whiteStone.direction==4) // ����4 
					{
						int k = rand()%2; 
						if(k==0) 
						{
							xPos=whiteStone.xPos-1;
							yPos=whiteStone.yPos-1;
						}
						else 
						{
							xPos=whiteStone.xPos+3;
							yPos=whiteStone.yPos+3;
						}
					}
				}
				else if(whiteStone.type==2 || whiteStone.type==3)
				{
					xPos=whiteStone.xPos;
					yPos=whiteStone.yPos;
				}
			}
			else if(whiteStone.mok == -3)
			{
				xPos = whiteStone.xPos; 
				yPos = whiteStone.yPos;
			}
			else if(blackStone.mok == 3) // ��밡 3���̸� 
			{
				if(blackStone.type==1) // ����1 
				{
					if(blackStone.direction==1) // ����1 
					{
						int k = rand()%2; 
						xPos=blackStone.xPos;
						if(k==0) yPos=blackStone.yPos+1;
						else yPos=blackStone.yPos-3;
					}
					if(blackStone.direction==2) // ����2 
					{
						int k = rand()%2; 
						if(k==0) xPos=blackStone.xPos-1;
						else xPos=blackStone.xPos+3;
						yPos=blackStone.yPos;
					}
					if(blackStone.direction==3) // ����3 
					{
						int k = rand()%2; 
						if(k==0) 
						{
							xPos=blackStone.xPos-1;
							yPos=blackStone.yPos+1;
						}
						else 
						{
							xPos=blackStone.xPos+3;
							yPos=blackStone.yPos-3;
						}
					}
					if(blackStone.direction==4) // ����4 
					{
						int k = rand()%2; 
						if(k==0) 
						{
							xPos=blackStone.xPos-1;
							yPos=blackStone.yPos-1;
						}
						else 
						{
							xPos=blackStone.xPos+3;
							yPos=blackStone.yPos+3;
						}
					}
				}
				else if(blackStone.type==2 || blackStone.type==3)
				{
					xPos=blackStone.xPos;
					yPos=blackStone.yPos;
				}
			}
			else if(blackStone.mok == -3)
			{
				xPos = blackStone.xPos; 
				yPos = blackStone.yPos;
			}
			else if(whiteStone.mok == 2) // �����Ѵ�.
			{
				xPos = whiteStone.xPos; 
				yPos = whiteStone.yPos;	
			} 
			else if(blackStone.mok == 2)
			{
				xPos = blackStone.xPos; 
				yPos = blackStone.yPos;
			}
			else // ���� ���� 
			{
				for(;;) 
				{
					int x=rand()%5-2; int y=rand()%5-2;
					if(step<10) { x=rand()%3-1; y=rand()%3-1; }
					if(map[xPos+x][yPos+y]==empty) 
					{
						xPos+=x; yPos+=y;
						break;
					}
				}
			}			
			
			/******************** ������ ********************/
			board.move(xPos, yPos);
			board.put();
			map[xPos][yPos]=white; step++;
			
			if(Is5(white) == true) // ��(2)�� 5���� ������°�?
			{
				return white;
			}
			
			return -1;
		}
		
		/******************** �����ΰ�? ********************/
		bool Is5(const int stone) // 1: �浹, 2: �鵹 
		{
			for(int y=yPos+4;y>=yPos;y--) // ������
			{
				if(map[xPos][y]==stone && map[xPos][y-1]==stone &&
				map[xPos][y-2]==stone && map[xPos][y-3]==stone &&
				map[xPos][y-4]==stone) return true;
			}
			for(int x=xPos-4;x<=xPos;x++) // ������
			{
				if(map[x][yPos]==stone && map[x+1][yPos]==stone &&
				map[x+2][yPos]==stone && map[x+3][yPos]==stone &&
				map[x+4][yPos]==stone) return true;
			}
			for(int x=xPos-4, y=yPos-4;x<=xPos && y<=yPos;x++,y++) // �밢�� 
			{
				if(map[x][y]==stone && map[x+1][y+1]==stone &&
				map[x+2][y+2]==stone && map[x+3][y+3]==stone &&
				map[x+4][y+4]==stone) return true;
			}
			for(int x=xPos-4, y=yPos+4;x<=xPos && y>=yPos;x++,y--) // �밢�� 
			{
				if(map[x][y]==stone && map[x+1][y-1]==stone &&
				map[x+2][y-2]==stone && map[x+3][y-3]==stone &&
				map[x+4][y-4]==stone) return true;
			}
			return false;
		}
		
		/******************** ����� �뵵 ����� ********************/
		void printMap()
		{
			cursor(0,25); cursor.color(black);
			for(int y=16;y>=0;y--) 
			{
				for(int x=0;x<=16;x++) printf("%2d ", map[x][y]);
				printf("\n");
			}
		}
		
		/******************** 4���ΰ�? ********************/
		Stone Is4(const int self)
		{
			int xStore = xPos;
			int yStore = yPos;
			
			for(yPos=15;yPos>=1;yPos--) for(xPos=1;xPos<=15;xPos++) /***** ���� *****/
			{
				if(map[xPos][yPos]==empty)
				{
					map[xPos][yPos]=self; 
					bool stone5=Is5(self);
					map[xPos][yPos]=empty;
					if(stone5==true)
					{
						Stone stone4(4,0,xPos,yPos,0);
						xPos = xStore; yPos = yStore;
						return stone4;
					}
					map[xPos][yPos]=empty;
				}
			}
			xPos = xStore; yPos = yStore;
			/*
			for(int y=14;y>=5;y--) for(int x=1;x<=15;x++) // ����1 ����1 
			{
				if(map[x][y]==self && map[x][y-1]==self
				&& map[x][y-2]==self && map[x][y-3]==self
				&& map[x][y+1]==empty && map[x][y-4]==empty)
				{
					return Stone(4,1,x,y,1);
				}
			}
			for(int y=15;y>=1;y--) for(int x=2;x<=11;x++) // ����1 ����2
			{
				if(map[x][y]==self && map[x+1][y]==self
				&& map[x+2][y]==self && map[x+3][y]==self
				&& map[x-1][y]==empty && map[x+4][y]==empty)
				{
					return Stone(4,1,x,y,2);
				}
			}
			for(int y=14;y>=5;y--) for(int x=2;x<=11;x++) // ����1 ����3
			{
				if(map[x][y]==self && map[x+1][y-1]==self
				&& map[x+2][y-2]==self && map[x+3][y-3]==self
				&& map[x-1][y+1]==empty && map[x+4][y-4]==empty)
				{
					return Stone(4,1,x,y,3);
				}
			}
			for(int y=2;y<=11;y++) for(int x=2;x<=11;x++) // ����1 ����4
			{
				if(map[x][y]==self && map[x+1][y+1]==self
				&& map[x+2][y+2]==self && map[x+3][y+3]==self
				&& map[x-1][y-1]==empty && map[x+4][y+4]==empty)
				{
					return Stone(4,1,x,y,4);
				}
			}
			*/
			
			return Stone(0,0,0,0,0);
		}
		/******************** 3���ΰ�? ********************/
		Stone Is3(const int self)
		{
			/******************** ����1 ********************/
			for(int y=14;y>=4;y--) for(int x=1;x<=15;x++) // ����1 ����1 
			{
				if(map[x][y]==self && map[x][y-1]==self
				&& map[x][y-2]==self && map[x][y+1]==empty && map[x][y-3]==empty)
				{
					return Stone(3,1,x,y,1);
				}
			}
			for(int y=15;y>=1;y--) for(int x=2;x<=12;x++) // ����1 ����2
			{
				if(map[x][y]==self && map[x+1][y]==self
				&& map[x+2][y]==self && map[x-1][y]==empty && map[x+3][y]==empty)
				{
					return Stone(3,1,x,y,2);
				}
			}
			for(int y=14;y>=4;y--) for(int x=2;x<=12;x++) // ����1 ����3
			{
				if(map[x][y]==self && map[x+1][y-1]==self
				&& map[x+2][y-2]==self && map[x-1][y+1]==empty && map[x+3][y-3]==empty)
				{
					return Stone(3,1,x,y,3);
				}
			}
			for(int y=2;y<=12;y++) for(int x=2;x<=12;x++) // ����1 ����4
			{
				if(map[x][y]==self && map[x+1][y+1]==self
				&& map[x+2][y+2]==self && map[x-1][y-1]==empty && map[x+3][y+3]==empty)
				{
					return Stone(3,1,x,y,4);
				}
			}
			/******************** ����2 ********************/
			for(int y=14;y>=5;y--) for(int x=1;x<=15;x++) // ����2 ����1 
			{
				if(map[x][y]==self && map[x][y-1]==self
				&& map[x][y-2]==empty && map[x][y-3]==self
				&& map[x][y+1]==empty && map[x][y-4]==empty)
				{
					return Stone(3,2,x,y-2,1);
				}
			}
			for(int y=15;y>=1;y--) for(int x=2;x<=11;x++) // ����2 ����2
			{
				if(map[x][y]==self && map[x+1][y]==self
				&& map[x+2][y]==empty && map[x+3][y]==self
				&& map[x-1][y]==empty && map[x+4][y]==empty)
				{
					return Stone(3,2,x+2,y,2);
				}
			}
			for(int y=14;y>=5;y--) for(int x=2;x<=11;x++) // ����2 ����3
			{
				if(map[x][y]==self && map[x+1][y-1]==self
				&& map[x+2][y-2]==empty && map[x+3][y-3]==self
				&& map[x-1][y+1]==empty && map[x+4][y-4]==empty)
				{
					return Stone(3,2,x+2,y-2,3);
				}
			}
			for(int y=2;y<=11;y++) for(int x=2;x<=11;x++) // ����2 ����4
			{
				if(map[x][y]==self && map[x+1][y+1]==self
				&& map[x+2][y+2]==empty && map[x+3][y+3]==self
				&& map[x-1][y-1]==empty && map[x+4][y+4]==empty)
				{
					return Stone(3,2,x+2,y+2,4);
				}
			}
			/******************** ����3 ********************/
			for(int y=14;y>=5;y--) for(int x=1;x<=15;x++) // ����3 ����1 
			{
				if(map[x][y]==self && map[x][y-1]==empty
				&& map[x][y-2]==self && map[x][y-3]==self
				&& map[x][y+1]==empty && map[x][y-4]==empty)
				{
					return Stone(3,3,x,y-1,1);
				}
			}
			for(int y=15;y>=1;y--) for(int x=2;x<=11;x++) // ����3 ����2
			{
				if(map[x][y]==self && map[x+1][y]==empty
				&& map[x+2][y]==self && map[x+3][y]==self
				&& map[x-1][y]==empty && map[x+4][y]==empty)
				{
					return Stone(3,3,x+1,y,2);
				}
			}
			for(int y=14;y>=5;y--) for(int x=2;x<=11;x++) // ����3 ����3
			{
				if(map[x][y]==self && map[x+1][y-1]==empty
				&& map[x+2][y-2]==self && map[x+3][y-3]==self
				&& map[x-1][y+1]==empty && map[x+4][y-4]==empty)
				{
					return Stone(3,3,x+1,y-1,3);
				}
			}
			for(int y=2;y<=11;y++) for(int x=2;x<=11;x++) // ����3 ����4
			{
				if(map[x][y]==self && map[x+1][y+1]==empty
				&& map[x+2][y+2]==self && map[x+3][y+3]==self
				&& map[x-1][y-1]==empty && map[x+4][y+4]==empty)
				{
					return Stone(3,3,x+1,y+1,4);
				}
			}
			return Stone(0,0,0,0,0);
		}
		/******************** ���� 3���ΰ�? ********************/
		Stone _Is3(const int self)
		{
			int k=rand()%2;
			if(k==0)
			{
				int xStore = xPos;
				int yStore = yPos;
			
				for(yPos=15;yPos>=1;yPos--) for(xPos=1;xPos<=15;xPos++) /***** ���� *****/
				{
					int c=rand()%2;
					if(c==0) continue;
					
					if(map[xPos][yPos]==empty)
					{
						map[xPos][yPos]=self; 
						Stone stone4=Is4(self);
						map[xPos][yPos]=empty;
						if(stone4.mok == 4)
						{
							Stone stone3(-3,0,xPos,yPos,0);
							xPos = xStore; yPos = yStore;
							return stone3;
						}
					}
				}
				xPos = xStore; yPos = yStore;
			}
			return Stone(0,0,0,0,0);
		}
		/******************** 2���ΰ�? ********************/
		Stone Is2(const int self)
		{
			/******************** ����1 ********************/
			for(int y=14;y>=3;y--) for(int x=1;x<=15;x++) // ����1 ����1 
			{
				if(map[x][y]==self && map[x][y-1]==self
				&& map[x][y+1]==empty && map[x][y-2]==empty)
				{
					int k=rand()%2;
					if((k==0 && y!=14) || (y==3)) return Stone(2,1,x,y+1,1);
					else return Stone(2,1,x,y-2,1);
				}
			}
			for(int y=15;y>=1;y--) for(int x=2;x<=13;x++) // ����1 ����2
			{
				if(map[x][y]==self && map[x+1][y]==self
				&& map[x-1][y]==empty && map[x+2][y]==empty)
				{
					int k=rand()%2;
					if((k==0 && x!=2) || (x==13)) return Stone(2,1,x-1,y,1);
					else return Stone(2,1,x+2,y,1);
				}
			}
			for(int y=14;y>=3;y--) for(int x=2;x<=13;x++) // ����1 ����3
			{
				if(map[x][y]==self && map[x+1][y-1]==self
				&& map[x-1][y+1]==empty && map[x+2][y-2]==empty)
				{
					int k=rand()%2;
					if(k==0 && x!=2 && y!=14) return Stone(2,1,x-1,y+1,1);
					else if(x!=13 && y!=3) return Stone(2,1,x+2,y-2,1);
				}
			}
			for(int y=2;y<=13;y++) for(int x=2;x<=13;x++) // ����1 ����4
			{
				if(map[x][y]==self && map[x+1][y+1]==self
				&& map[x-1][y-1]==empty && map[x+2][y+2]==empty)
				{
					int k=rand()%2;
					if(k==0 && x!=2 && y!=2) return Stone(2,1,x-1,y-1,1);
					else if(x!=13 && y!=13) return Stone(2,1,x+2,y+2,1);
				}
			}
			/******************** ����3 ********************/
			for(int y=14;y>=4;y--) for(int x=1;x<=15;x++) // ����3 ����1 
			{
				if(map[x][y]==self && map[x][y-1]==empty
				&& map[x][y-2]==self && map[x][y+1]==empty && map[x][y-3]==empty)
				{
					return Stone(2,3,x,y-1,1);
				}
			}
			for(int y=15;y>=1;y--) for(int x=2;x<=12;x++) // ����3 ����2
			{
				if(map[x][y]==self && map[x+1][y]==empty
				&& map[x+2][y]==self && map[x-1][y]==empty && map[x+3][y]==empty)
				{
					return Stone(2,3,x+1,y,2);
				}
			}
			for(int y=14;y>=4;y--) for(int x=2;x<=12;x++) // ����3 ����3
			{
				if(map[x][y]==self && map[x+1][y-1]==empty
				&& map[x+2][y-2]==self && map[x-1][y+1]==empty && map[x+3][y-3]==empty)
				{
					return Stone(2,3,x+1,y-1,3);
				}
			}
			for(int y=2;y<=12;y++) for(int x=2;x<=12;x++) // ����3 ����4
			{
				if(map[x][y]==self && map[x+1][y+1]==empty
				&& map[x+2][y+2]==self && map[x-1][y-1]==empty && map[x+3][y+3]==empty)
				{
					return Stone(2,3,x+1,y+1,4);
				}
			}
			
			return Stone(0,0,0,0,0);
		}
};

/******************** �Լ� ����� ********************/
void MainMenu();
void MainMenuDisplay();
void Game();
void Rule();
void Quit();

/******************** Main �Լ� ********************/
int main()
{
	setlocale(LC_ALL, "korean");
	srand((unsigned int)time(NULL));
	MainMenu();
	return 0;
}

/******************** ���θ޴� ********************/
void MainMenu()
{
	MainMenuDisplay();
	
	for(int key;;) if(kbhit())
	{
		key=getch(); if(key==ESC) break;
		
		if(key==ARROW) // ����Ű 
		{
			key=getch();
			switch(key)
			{
			case UP:
				if(cursor.getY() > 10) // ���� 
				{
					cursor(UP); cursor(UP);
				}
				break;
			case DOWN:
				if(cursor.getY() < 14) // �Ʒ��� 
				{
					cursor(DOWN); cursor(DOWN);
				}
				break;
			}
		}
		
		if(key==SPACE) // �����̽� 
		{
			switch(cursor.getY())
			{
			case 10:
				Game(); // �����ϱ� 
				break;
			case 12:
				Rule(); // ��Ģ���� 
				break;
			case 14:
				Quit(); // ������ 
				break;
			}
		}
	}
	cursor++; cursor(0,0); cursor.color(black);
}

/******************** ���θ޴� �����ֱ� ********************/
void MainMenuDisplay()
{
	cursor++; cursor(MIDDLE);
	cursor(UP); cursor(UP); cursor(UP); cursor(UP);
	cursor(LEFT); cursor(LEFT); cursor(LEFT);
	cursor.color(blue); 
	printf("Main Menu");
	cursor(RIGHT);
	cursor(DOWN); cursor(DOWN);
	cursor.color(black);
	printf("1. Game");
	cursor(DOWN); cursor(DOWN);
	printf("2. Rule");
	cursor(DOWN); cursor(DOWN);
	printf("3. Quit");
	cursor(LEFT);
	cursor(UP); cursor(UP); cursor(UP); cursor(UP);
}

/******************** �����ϱ� ********************/ /***** �� ���α׷��� �ٽ� *****/
void Game()
{
	cursor++; cursor.color(black); // ȭ�� �ʱ�ȭ 
	Board board; // ������ ��ü ���� 
	board.display(); // ������ ���̱� 
	board.move(8,8); // Ŀ�� ��ġ 8 8 
	Computer AI(board);
	int victory; // 1�̸� ��� 2�̸� ��� 
	
	cursor.color(black,white);
	for(int key;;) if(kbhit())
	{	
		key=getch(); if(key==ESC) break;
		
		if(key==ARROW) // ����Ű 
		{
			key=getch();
			switch(key)
			{
			case UP: board.move(UP);
				break;
			case DOWN: board.move(DOWN);
				break;
			case RIGHT: board.move(RIGHT);
				break;
			case LEFT: board.move(LEFT);
				break;
			}
		}
		
		if(key==SPACE) // �����̽� 
		{
			if(board.okay()==true) 
			{
				board.put();
				int ai=AI();
				if(ai==-1)
				{
					continue;
				}
				else if(ai==black)
				{
					victory=black; break;
				}
				else if(ai==white)
				{
					victory=white; break;
				}
			}
		}
		
		if(key=='a') AI.printMap();
		if(key=='b') board.printMap();
	}
	
	if(victory==black)
	{
		cursor(0,25); cursor.color(blue);
		printf("Player Victory!");
	}
	else if(victory==white)
	{
		cursor(0,25); cursor.color(red);
		printf("Comptuer AI Victory!");
	}
	getch();
	
	AI.printMap();
	getch();
	board.printMap();
	getch();
	
	cursor(0,25); cursor.color(black,black);
	for(int i=0;i<30;i++) printf(" ");
	
	MainMenuDisplay();
}

/******************** ��Ģ���� ********************/
void Rule()
{
	cursor++; cursor(MIDDLE); cursor(UP); cursor(UP);
	cursor(LEFT); cursor(LEFT); cursor(LEFT);
	cursor.color(black); printf("Renju Rule");
	cursor(DOWN); cursor(DOWN); 
	cursor(LEFT); cursor(LEFT); cursor(LEFT); cursor(LEFT);
	printf("black: First,  33(X) 44(X) 6(X) ");
	cursor(DOWN);
	printf("white: Second, 33(O) 44(O) 6(O) ");
	
	for(int key;;) if(kbhit())
	{
		key=getch(); 
		if(key==ESC || key==SPACE) break;
	}
	MainMenuDisplay();
}

/******************** ������ ********************/
void Quit()
{
	cursor++; cursor(MIDDLE); cursor(LEFT); cursor(LEFT); cursor(LEFT);
	cursor.color(red); printf("Program Quit");
	exit(0);
}

