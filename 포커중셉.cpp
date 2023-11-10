// 7포커
// 날짜 : 2016-12-06

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct trump  // 카드 구조체
{
	char pat;
	int num;
} Trump;

void Initialization(Trump[]);  // 카드 초기화 함수
void Shuffle(Trump[]);  // 카드 섞기 함수
void Divide(Trump[], Trump[], Trump[], int);  // 카드 나누기 함수

int main(void)
{
	Trump card[52];  //  전체카드  
	Trump player[7];  //  플레이어의 카드
	Trump computer1[7];  //  컴퓨터의 카드
	int playtree, comptree;  // 족보 변수
	int choice;  // 선택 변수

	int i;  // 반복문 변수

	printf("Poker Game! \n");

	for(;;)  // 실행중
	{
		printf("\n\n///////////////////////////////////////////////////////////////////////////\n");

		for(choice=0;(choice<1)||(choice>2);)  // 입력 1.시작 2.종료
		{
		    printf("Main Menu / 1.start 2.exit \n: ");
		    scanf("%d", &choice);
		}
		if(choice==2)
		{
			break;
		}

		printf("\nInitialization\n");  // 카드를 초기화한다.
		Initialization(card);
		/* for(i=0;i<=51;i++)  // 확인 작업
		{
			printf(" %c", card[i].pat);
			printf("%d ", card[i].num);
			if(i%13==12)
			{
				printf("\n");
			}
		} */

		printf("\nShuffle the cards\n");  // 카드를 섞는다.
		Shuffle(card);
		/* for(i=0;i<=51;i++)  // 확인 작업
		{
			printf(" %c", card[i].pat);
			printf("%d ", card[i].num);
			if(i%13==12)
			{
				printf("\n");
			}
		} */

		printf("\nDivide cards \n");  // 카드를 나눈다.
		for(i=0;i<=6;i++)
		{
			Divide(card, player, computer1, i);
		}

		printf("\nCompare the card \n\n");  // 카드를 비교한다.
		printf("palyer: ");
		for(i=0;i<=6;i++)
		{
			printf(" %c", player[i].pat);
			printf("%d ", player[i].num);
		}
		printf("\ncomputer: ");
		for(i=0;i<=6;i++)
		{
			printf(" %c", computer1[i].pat);
			printf("%d ", computer1[i].num);
		}

		printf("\n");
		getchar();
	}

	return 0;
}

void Initialization(Trump card[])  // 카드 초기화 함수 정의
{
	int cnt=0, i;

	for(i=1;cnt<=12;cnt++, i++)  // 스페이드
	{
		card[cnt].pat = 'S';
		card[cnt].num = i;
	}

	for(i=1;cnt<=25;cnt++, i++)  // 다이아
	{
		card[cnt].pat = 'D';
		card[cnt].num = i;
	}

	for(i=1;cnt<=38;cnt++, i++)  // 클로버
	{
		card[cnt].pat = 'C';
		card[cnt].num = i;
	}
	
	for(i=1;cnt<=51;cnt++, i++)  // 하트
	{
		card[cnt].pat = 'H';
		card[cnt].num = i;
	}

	return;
}

void Shuffle(Trump card[])  // 카드 섞기 함수 정의
{
	Trump temp;  // 임시 저장 변수
	int i, j;  // 인덱스 변수
	int cnt, cntby;  // 횟수 변수

	srand((int)time(NULL));

	cntby = (rand()%100+1)*100;  // 100~10000 난수값 저장  

	/* printf("cntby = %d \n", cntby); */  // 확인 작업

	for(cnt=0;cnt<=cntby;cnt++)  // 섞기
	{
		do
		{
		    i = rand()%52;
		    j = rand()%52;
		} while(i==j);

		temp = card[i];
		card[i] = card[j];
		card[j] = temp;
	}

	return;
}

void Divide(Trump card[], Trump player[], Trump computer1[], int i)  // 카드 나누기 함수 정의
{
	int j;
	j=i;
	i *= 2;
	player[j] = card[i];
	computer1[j] = card[i+1];
}

