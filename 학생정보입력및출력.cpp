/* 2020-05-22
 * 학생 정보 입력 및 출력 프로그램
 * 이후에 const 키워드 추가할 것 
 */

#include <stdio.h>
#define STUDENT_NUMBER 3 // 학생수 

typedef struct student // 학생 구조체 
{
    char name[40];  // 이름 
    char major[40]; // 전공 
    int year, month, day;   // 년도, 몇월, 몇일 (생년월일)
    int leap, area, gender; // 윤년, 지역, 성별 
} Student;

void printStudentInfo(Student*); // 학생정보 출력함수 
int ctoi(char); // 문자->정수 

/******************** Main 함수 ********************/
int main()
{
	Student student[STUDENT_NUMBER];
	char registNumStr[20]; // 주민등록번호 저장 문자열 
   	
   	printf("Input the impormation of %d student.\n", STUDENT_NUMBER);
	
	/******************** 학생정보 입력 ********************/
    for(int i=0;i<STUDENT_NUMBER;i++)
    {
        printf("----------------------------------------\n");
        printf("Name: ");  scanf("%s", student[i].name);
        printf("Major: "); scanf("%s", student[i].major); 
   		printf("Registration Number: "); 
		scanf("%s", registNumStr); // 0000000000000 형태로 입력 
		
		int k = ctoi(registNumStr[6]); // 주민등록번호 뒷자리 첫번째 
		
		/******************** 년도 판단 ********************/
	   	if(k==1 or k==2 or k==5 or k==6) student[i].year = 1900;
	   	else if(k==0 or k==9) 			 student[i].year = 1800;
		else 							 student[i].year = 2000;
		
		/******************** 생년월일 완성 ********************/
		student[i].year += ctoi(registNumStr[0])*10+ctoi(registNumStr[1]);
		student[i].month = ctoi(registNumStr[2])*10+ctoi(registNumStr[3]);
		student[i].day   = ctoi(registNumStr[4])*10+ctoi(registNumStr[5]);
       	
       	/******************** 윤년 판단 ********************/
       	int year = student[i].year;
       	
		if((year%4==0 && year%100!=0) || year%400==0) student[i].leap = 1;
		else 										  student[i].leap = 0;

		/******************** 출생지역 판단 ********************/
		if(k==5 or k==6 or k==7 or k==8) student[i].area = -1; // 외국 
		else 							 student[i].area = 1;  // 한국 
		
		/******************** 성별 판단 ********************/
		if(k==1 or k==3 or k==5 or k==7 or k==9) student[i].gender = 1; // 남자 
		else 									 student[i].gender = 2; // 여자 
		
		/******************** 학생정보 출력 ********************/
		printStudentInfo(&student[i]);
	}
	
	/******************** 모든 학생정보 출력 ********************/
	printf("========================================\n");
	printf("Print the impormation of All student.\n");
	printf("----------------------------------------\n");
	for(int i=0;i<STUDENT_NUMBER;i++)
	{
		printStudentInfo(&student[i]); // 출력함수 호출 
	}
	
   	return 0; // 끝 
}

/******************** 함수 정의들 ********************/

void printStudentInfo(Student* student) // 학생정보 출력함수
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

int ctoi(char ch) // 문자->정수
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

