/*
 * Baking System Ver 0.1
 * 작성자: 최광진
 * 내 용: OOP 단계별 프로젝트의 기본 틀 구성 
 */

#include <iostream>
#include <cstring>
#define NAME_LEN 20

using namespace std;

enum { MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

typedef struct {
	int accID;    // 계좌번호 
	int balance;  // 잔  액 
	char cusName[NAME_LEN];  // 고객이름 
} Account;

void ShowMenu();        // 메뉴출력 
void MakeAccount();     // 계좌개설을 위한 함수 
void DepositMoney();    // 입  금 
void WithdrawMoney();   // 출  금 
void ShowAllAccInfo();  // 잔액조회 

Account accArr[100];  // Account 저장을 위한 배열 
int accNum = 0;       // 저장된 Account 수 

int main() {
	int choice;
	
	while(true) {
		ShowMenu();
		cout<<"선택: ";
		cin>>choice;
		cout<<endl;
		
		switch(choice) {
			case MAKE:
				MakeAccount();
				break;
			case DEPOSIT:
				DepositMoney();
				break;
			case WITHDRAW:
				WithdrawMoney();
				break;
			case INQUIRE:
				ShowAllAccInfo();
				break;
			case EXIT:
				return 0;
			default:
				cout<<"Illegal selection.."<<endl;
		}
	}
	
	return 0;
}

void ShowMenu() {
	cout<<"-----Menu-----"<<endl;
	cout<<"1. 계좌개설"<<endl;
	cout<<"2. 입 금"<<endl;
	cout<<"3. 출 금"<<endl;
	cout<<"4. 계좌정보 전체 출력"<<endl;
	cout<<"5. 프로그램 종료"<<endl;
}

void MakeAccount() {
	int id;
	char name[NAME_LEN];
	int balance;
	
	cout<<"[계좌개설]"<<endl;
	cout<<"게좌ID: "; cin>>id;
	cout<<"이 름: ";  cin>>name;
	cout<<"입금액: "; cin>>balance;
	cout<<endl;
	
	accArr[accNum].accID = id;
	strcpy(accArr[accNum].cusName, name);
	accArr[accNum].balance = balance;
	accNum++;
}

void DepositMoney() {
	int id;
	int money;
	
	cout<<"[입  금]"<<endl;
	cout<<"계좌ID: "; cin>>id;
	cout<<"입금액: "; cin>>money;
	
	for(int i=0; i<accNum; i++) {
		if(accArr[i].accID == id) {
			accArr[i].balance += money;
			cout<<"입금완료"<<endl<<endl;
			return;
		}
	}
	cout<<"유효하지 않은 ID 입니다."<<endl<<endl;
}

void WithdrawMoney() {
	int id;
	int money;
	
	cout<<"[출  금]"<<endl;
	cout<<"계좌ID: "; cin>>id;
	cout<<"출금액: "; cin>>money;
	
	for(int i=0; i<accNum; i++) {
		if(accArr[i].accID == id) {
			if(accArr[i].balance < money) {
				cout<<"잔액부족"<<endl<<endl;
				return;
			}
			accArr[i].balance -= money;
			cout<<"출금완료"<<endl<<endl;
			return;
		}
	}
	cout<<"유효하지 않은 ID 입니다."<<endl<<endl;
}

void ShowAllAccInfo() {
	for(int i=0; i<accNum; i++) {
		cout<<"계좌ID: "<<accArr[i].accID<<endl;
		cout<<"이 름: "<<accArr[i].cusName<<endl;
		cout<<"잔 액: "<<accArr[i].balance<<endl<<endl;
	}
}

