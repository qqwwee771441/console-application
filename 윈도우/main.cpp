#include <stdio.h>
#include <conio.h>
#include <math.h>

double m[100000];  // ������ ���� 
int c[100000];  // ������ ǥ���� �� ���� ���� 

int main() {
	int n, r;  // �Է¹޴� N�� R 
	int x[100000];  // �Է¹޴� x 
	int y[100000];  // �Է¹޴� y 
	
	int a[100000];  // ������ a 
	int b[100000];  // ������ b 
	
	scanf("%d %d", &n, &r);
	
	/******************** �Է� ********************/
	int minY = 200000000;
	int minIdx;
	for(int i=0; i<n; i++) {
		scanf("%d %d", &(x[i]), &(y[i]));
		if(minY > y[i]) {
			minY = y[i];
			minIdx = i;
		} else if(minY == y[i]) {
			if(x[minIdx] > x[i]) {
				minIdx = i;
			}
		}
	}
	// y = tan(x-a) + b - r/cos
	
	/******************** �������� ********************/
	int first = minIdx;  // minIdx���� �����ؼ� �ٽ� first�� ���ƿ��� �ݺ��� break 
	int priority=1;  // ���� ������ �� 
	int p;  // for���� priority 
	int idx;  // for���� minIdx 
	int num;  // ������ ����
	int rad;  // for���� �񱳼�Ÿ�� 
	/******************** �ϴ� 1�϶��� 2�̻��϶� ���� ********************/
	if(n>1) {
	for(int i=0; ; i++) {
		a[i] = x[minIdx];
		b[i] = y[minIdx];
		
		printf("DEBUG; %d %d , %d \n", a[i], b[i], priority); // DEBUG
		getch();
		
		if(minIdx==first && i!=0) {
			num = i+1;
			break;
		}
		
		rad = 2*M_PI;  // rad�� 0 ~ 2����-�۽Ƿ� 
		p = 9;  // p�� �켱���� 0 ~ 8 
		for(int j=0; j<n; j++) {
			if(j == minIdx)
				continue;
			
			if(priority<=1 && y[j]-b[i]==0 && x[j]-a[i]>0) {		 // 1
				if(p>=1) { p = 1; idx = j; }
			} else if(priority<=2 && y[j]-b[i]>0 && x[j]-a[i]>0) {   // 2
				if(p>=2) { if(rad > atan((double)(y[idx]-b[i])/(double)(x[idx]-a[i]))) {
					p = 2; idx = j; rad = atan((double)(y[idx]-b[i])/(double)(x[idx]-a[i]));
				} }
			} else if(priority<=3 && y[j]-b[i]>0 && x[j]-a[i]==0) {  // 3
				if(p>=3) { p = 3; idx = j; }
			} else if(priority<=4 && y[j]-b[i]>0 && x[j]-a[i]<0) {   // 4
				if(p>=4) { p = 4; idx = j; }
			} else if(priority<=5 && y[j]-b[i]==0 && x[j]-a[i]<0) {  // 5
				if(p>=5) { p = 5; idx = j; }
			} else if(priority<=6 && y[j]-b[i]<0 && x[j]-a[i]<0) {   // 6
				if(p>=6) { p = 6; idx = j; }
			} else if(priority<=7 && y[j]-b[i]<0 && x[j]-a[i]==0) {  // 7
				if(p>=7) { p = 7; idx = j; }
			} else if(priority<=8 && y[j]-b[i]<0 && x[j]-a[i]>0) {   // 8
				// TODO~!!
				if(p>=8) { if(rad > 2*M_PI+atan((double)(y[idx]-b[i])/(double)(x[idx]-a[i]))) {
					p = 8; idx = j; rad = 2*M_PI+atan((double)(y[idx]-b[i])/(double)(x[idx]-a[i]));
				} }
			}
		}
		
		priority = p;
		minIdx = idx;
		if(x[idx]-a[i] == 0) {
			c[i] = idx;
		} else {
			m[i] = (double)(y[idx]-b[i])/(double)(x[idx]-a[i]);  // review later
		}
	}
	} else {
		a[0] = x[minIdx];
		b[0] = y[minIdx];
		num = 1;
	}
	
	for(int i=0; i<num; i++) {
		if(!c[i]) {
			printf("%d %d %lf \n", a[i], b[i], m[i]);
		} else {
			printf("%d %d %lf \n", a[i], b[i], 0);
		}
	}
}

