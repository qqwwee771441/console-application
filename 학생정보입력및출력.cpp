/* 2020-05-22
 * �л� ���� �Է� �� ��� ���α׷�
 * ���Ŀ� const Ű���� �߰��� �� 
 */

#include <stdio.h>
#define STUDENT_NUMBER 3 // �л��� 

typedef struct student // �л� ����ü 
{
    char name[40];  // �̸� 
    char major[40]; // ���� 
    int year, month, day;   // �⵵, ���, ���� (�������)
    int leap, area, gender; // ����, ����, ���� 
} Student;

void printStudentInfo(Student*); // �л����� ����Լ� 
int ctoi(char); // ����->���� 

/******************** Main �Լ� ********************/
int main()
{
	Student student[STUDENT_NUMBER];
	char registNumStr[20]; // �ֹε�Ϲ�ȣ ���� ���ڿ� 
   	
   	printf("Input the impormation of %d student.\n", STUDENT_NUMBER);
	
	/******************** �л����� �Է� ********************/
    for(int i=0;i<STUDENT_NUMBER;i++)
    {
        printf("----------------------------------------\n");
        printf("Name: ");  scanf("%s", student[i].name);
        printf("Major: "); scanf("%s", student[i].major); 
   		printf("Registration Number: "); 
		scanf("%s", registNumStr); // 0000000000000 ���·� �Է� 
		
		int k = ctoi(registNumStr[6]); // �ֹε�Ϲ�ȣ ���ڸ� ù��° 
		
		/******************** �⵵ �Ǵ� ********************/
	   	if(k==1 or k==2 or k==5 or k==6) student[i].year = 1900;
	   	else if(k==0 or k==9) 			 student[i].year = 1800;
		else 							 student[i].year = 2000;
		
		/******************** ������� �ϼ� ********************/
		student[i].year += ctoi(registNumStr[0])*10+ctoi(registNumStr[1]);
		student[i].month = ctoi(registNumStr[2])*10+ctoi(registNumStr[3]);
		student[i].day   = ctoi(registNumStr[4])*10+ctoi(registNumStr[5]);
       	
       	/******************** ���� �Ǵ� ********************/
       	int year = student[i].year;
       	
		if((year%4==0 && year%100!=0) || year%400==0) student[i].leap = 1;
		else 										  student[i].leap = 0;

		/******************** ������� �Ǵ� ********************/
		if(k==5 or k==6 or k==7 or k==8) student[i].area = -1; // �ܱ� 
		else 							 student[i].area = 1;  // �ѱ� 
		
		/******************** ���� �Ǵ� ********************/
		if(k==1 or k==3 or k==5 or k==7 or k==9) student[i].gender = 1; // ���� 
		else 									 student[i].gender = 2; // ���� 
		
		/******************** �л����� ��� ********************/
		printStudentInfo(&student[i]);
	}
	
	/******************** ��� �л����� ��� ********************/
	printf("========================================\n");
	printf("Print the impormation of All student.\n");
	printf("----------------------------------------\n");
	for(int i=0;i<STUDENT_NUMBER;i++)
	{
		printStudentInfo(&student[i]); // ����Լ� ȣ�� 
	}
	
   	return 0; // �� 
}

/******************** �Լ� ���ǵ� ********************/

void printStudentInfo(Student* student) // �л����� ����Լ�
{
	printf("%s ", student->name);
	printf("%s ", student->major);
	printf("%d %d %d ", student->year, student->month, student->day);
	if(student->leap == 1) printf("<Leap_Year> ");
	else 				   printf("<Not Leap Year> ");
	if(student->area == 1) printf("<Internal> ");
	else 				   printf("<Foreign> ");
	if(student->gender == 1) printf("<Male> ");
	else 					 printf("<Female> ");
	printf("\n");
}

int ctoi(char ch) // ����->����
{
	switch(ch)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	}
}

