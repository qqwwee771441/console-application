#include <iostream>

using namespace std;

class Sudocu {
	private:
		int map[9][9][10];
	public:
		Sudocu() {
			for(int i=0;i<9;i++)
				for(int j=0;j<9;j++)
					for(int k=0;k<10;k++)
						map[i][j][k] = 0;
		}
		void putNumber(int row, int col, int num) {
			for(int i=0;i<9;i++){ // 세로줄 
				map[i][col][num] = -1;
			}
			for(int j=0;j<9;j++){ // 가로줄 
				map[row][j][num] = -1;
			}
			// 같은 칸 
			if(row<3 && col<3) fillBlock(0,3,0,3,num);
			else if(row<3 && (col>=3 && col<6)) fillBlock(0,3,3,6,num);
			else if(row<3 && (col>=6)) fillBlock(0,3,6,9,num);
			else if((row>=3 && row<6) && col<3) fillBlock(3,6,0,3,num);
			else if((row>=3 && row<6) && (col>=3 && col<6)) fillBlock(3,6,3,6,num);
			else if((row>=3 && row<6) && (col>=6)) fillBlock(3,6,6,9,num);
			else if(row>=6 && col<3) fillBlock(6,9,0,3,num);
			else if(row>=6 && (col>=3 && col<6)) fillBlock(6,9,3,6,num);
			else if(row>=6 && (col>=6)) fillBlock(6,9,6,9,num);
			// 자신
			for(int k=0;k<10;k++) map[row][col][k] = -1;
			map[row][col][num] = 1; // 값 넣기 
			map[row][col][0] = num;
		}
		void fillBlock(int i, int I, int j, int J, int num) {
			for(;i<I;i++) for(;j<J;j++) map[i][j][num] = -1;
		}
		void putEven(int row, int col) {
			map[row][col][1] = -1;
			map[row][col][3] = -1;
			map[row][col][5] = -1;
			map[row][col][7] = -1;
			map[row][col][9] = -1;
		}
		void putOdd(int row, int col) {
			map[row][col][2] = -1;
			map[row][col][4] = -1;
			map[row][col][6] = -1;
			map[row][col][8] = -1;
		}
		void calcAll() {
			calcEach();
			calcRow();
			calcCol();
			calcAllBlock();
		}
		void calcEach() {
			for(int i=0;i<9;i++) for(int j=0;j<9;j++) {
				if(map[i][j][0] > 0) continue;
				int count = 0;
				int num;
				for(int k=1;k<=9;k++) {
					if(map[i][j][k] == 0) num = k;
					else count++;
				}
				if(count == 8) putNumber(i,j,num);
			}
		}
		void calcRow() {
			for(int num=1;num<=9;num++){
				for(int i=0;i<9;i++) {
					int count = 0;
					int row, col;
					int c=0;
					for(int j=0;j<9;j++) {
						if(map[i][j][num] == -1) count++;
						else if(map[i][j][num] == 0) {
							row = i; col = j; c = 1;
						}
					}
					if(count==8 && c==1) putNumber(row, col, num);
				}
			}
		}
		void calcCol() {
			for(int num=1;num<=9;num++){
				for(int j=0;j<9;j++) {
					int count = 0;
					int row, col;
					int c=0;
					for(int i=0;i<9;i++) {
						if(map[i][j][num] == -1) count++;
						else if(map[i][j][num] == 0) {
							row = i; col = j; c = 1;
						}
					}
					if(count==8 && c==1) putNumber(row, col, num);
				}
			}
		}
		void calcAllBlock() {
			calcBlock(0,3,0,3); calcBlock(0,3,3,6); calcBlock(0,3,6,9);
			calcBlock(3,6,0,3); calcBlock(3,6,3,6); calcBlock(3,6,6,9);
			calcBlock(6,9,0,3); calcBlock(6,9,3,6); calcBlock(6,9,6,9);
		}
		void calcBlock(int i, int I, int j, int J) {
			for(int num=1;num<=9;num++) {
				int count = 0;
				int row, col;
				int c=0;
				for(;i<I;i++) for(;j<J;j++) {
					if(map[i][j][num] == -1) count++;
					else if(map[i][j][num] == 0) {
						row = i; col = j; c = 1;
					}
				}
				if(count==8 && c==1) putNumber(row, col, num);
			}
		}
		void printMap() {
			for(int i=0;i<9;i++) {
				for(int j=0;j<9;j++) {
					for(int k=1;k<=9;k++) {
						if(map[i][j][k] == -1) cout<<"X";
						else if(map[i][j][k] == 0) cout<<"-";
						else if(map[i][j][k] == 1) cout<<"O";
					}
					cout<<" ";
				}
				cout<<endl;
			}
		}
		bool Num1IsMinus1(int row, int col) {
			if(map[row][col][1] == -1) return true;
			return false;
		}
		void printNumber() {
			for(int i=0;i<9;i++) {
				for(int j=0;j<9;j++) {
					cout<<map[i][j][0];
				}
				cout<<endl;
			}
		}
};

int main() {
	Sudocu sudocu;
	
	// 검은색 짝수 0 1 2 | 3 4 5 | 6 7 8
	sudocu.putEven(0,4); sudocu.putEven(0,6);
	
	sudocu.putEven(1,0); sudocu.putEven(1,7);
	
	sudocu.putEven(2,1); sudocu.putEven(2,2); sudocu.putEven(2,4);
	
	sudocu.putEven(3,1); sudocu.putEven(3,6);
	
	sudocu.putEven(4,2); sudocu.putEven(4,3); sudocu.putEven(4,4);
	
	sudocu.putEven(5,0); sudocu.putEven(5,3); sudocu.putEven(5,4);
	sudocu.putEven(5,8);
	
	sudocu.putEven(6,1); sudocu.putEven(6,3); sudocu.putEven(6,5);
	sudocu.putEven(6,7);
	
	sudocu.putEven(7,1); sudocu.putEven(7,3); sudocu.putEven(7,5);
	
	sudocu.putEven(8,0); sudocu.putEven(8,2); sudocu.putEven(8,6);
	sudocu.putEven(8,7);
	
	// 흰색 홀수
	for(int i=0;i<9;i++) for(int j=0;j<9;j++) {
		if(sudocu.Num1IsMinus1(i,j) == true) continue;
		sudocu.putOdd(i,j);
	}
	
	/*for(int i=0;i<9;i++) {
		for(int j=0;j<9;j++) {
			if(sudocu.Num1IsMinus1(i,j) == true) 
				cout<<"E";
			else cout<<"O";
		}
		cout<<endl;
	}*/
	
	// 값 넣기 
	sudocu.putNumber(0,5,2); sudocu.putNumber(0,7,6);
	
	sudocu.putNumber(1,2,9); sudocu.putNumber(1,3,3); 
	sudocu.putNumber(1,5,6); sudocu.putNumber(1,6,8);
	
	sudocu.putNumber(2,0,8); sudocu.putNumber(2,5,9);
	
	sudocu.putNumber(3,0,7); sudocu.putNumber(3,2,4);
	sudocu.putNumber(3,7,3); sudocu.putNumber(3,8,2);
	
	sudocu.putNumber(4,0,1); sudocu.putNumber(4,8,4);
	
	sudocu.putNumber(5,2,5); sudocu.putNumber(5,5,7);
	
	sudocu.putNumber(6,2,7); sudocu.putNumber(6,8,3);
	
	sudocu.putNumber(7,0,5); sudocu.putNumber(7,2,3);
	sudocu.putNumber(7,7,1); sudocu.putNumber(7,8,6);
	
	for(int select;;) {
		cout<<"(1, 0): ";
		cin>>select;
		if(select == 1) {
			sudocu.printMap();
			sudocu.printNumber();
		}
		else if(select == 2) {
			int row, col, num;
			cout<<"row col num: ";
			cin>>row>>col>>num;
			sudocu.putNumber(row,col,num);
		}
		else break;
		sudocu.calcAll();
	}
	return 0;
}

