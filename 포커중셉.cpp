// 7��Ŀ
// ��¥ : 2016-12-06

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct trump  // ī�� ����ü
{
	char pat;
	int num;
} Trump;

void Initialization(Trump[]);  // ī�� �ʱ�ȭ �Լ�
void Shuffle(Trump[]);  // ī�� ���� �Լ�
void Divide(Trump[], Trump[], Trump[], int);  // ī�� ������ �Լ�

int main(void)
{
	Trump card[52];  //  ��üī��  
	Trump player[7];  //  �÷��̾��� ī��
	Trump computer1[7];  //  ��ǻ���� ī��
	int playtree, comptree;  // ���� ����
	int choice;  // ���� ����

	int i;  // �ݺ��� ����

	printf("Poker Game! \n");

	for(;;)  // ������
	{
		printf("\n\n///////////////////////////////////////////////////////////////////////////\n");

		for(choice=0;(choice<1)||(choice>2);)  // �Է� 1.���� 2.����
		{
		    printf("Main Menu / 1.start 2.exit \n: ");
		    scanf("%d", &choice);
		}
		if(choice==2)
		{
			break;
		}

		printf("\nInitialization\n");  // ī�带 �ʱ�ȭ�Ѵ�.
		Initialization(card);
		/* for(i=0;i<=51;i++)  // Ȯ�� �۾�
		{
			printf(" %c", card[i].pat);
			printf("%d ", card[i].num);
			if(i%13==12)
			{
				printf("\n");
			}
		} */

		printf("\nShuffle the cards\n");  // ī�带 ���´�.
		Shuffle(card);
		/* for(i=0;i<=51;i++)  // Ȯ�� �۾�
		{
			printf(" %c", card[i].pat);
			printf("%d ", card[i].num);
			if(i%13==12)
			{
				printf("\n");
			}
		} */

		printf("\nDivide cards \n");  // ī�带 ������.
		for(i=0;i<=6;i++)
		{
			Divide(card, player, computer1, i);
		}

		printf("\nCompare the card \n\n");  // ī�带 ���Ѵ�.
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

void Initialization(Trump card[])  // ī�� �ʱ�ȭ �Լ� ����
{
	int cnt=0, i;

	for(i=1;cnt<=12;cnt++, i++)  // �����̵�
	{
		card[cnt].pat = 'S';
		card[cnt].num = i;
	}

	for(i=1;cnt<=25;cnt++, i++)  // ���̾�
	{
		card[cnt].pat = 'D';
		card[cnt].num = i;
	}

	for(i=1;cnt<=38;cnt++, i++)  // Ŭ�ι�
	{
		card[cnt].pat = 'C';
		card[cnt].num = i;
	}
	
	for(i=1;cnt<=51;cnt++, i++)  // ��Ʈ
	{
		card[cnt].pat = 'H';
		card[cnt].num = i;
	}

	return;
}

void Shuffle(Trump card[])  // ī�� ���� �Լ� ����
{
	Trump temp;  // �ӽ� ���� ����
	int i, j;  // �ε��� ����
	int cnt, cntby;  // Ƚ�� ����

	srand((int)time(NULL));

	cntby = (rand()%100+1)*100;  // 100~10000 ������ ����  

	/* printf("cntby = %d \n", cntby); */  // Ȯ�� �۾�

	for(cnt=0;cnt<=cntby;cnt++)  // ����
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

void Divide(Trump card[], Trump player[], Trump computer1[], int i)  // ī�� ������ �Լ� ����
{
	int j;
	j=i;
	i *= 2;
	player[j] = card[i];
	computer1[j] = card[i+1];
}

