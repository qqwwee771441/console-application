#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "NameCard.h"

int main() {
	List list;
	NameCard* pcard;
	const char* compName;
	const char* changePhone;
	
	ListInit(&list);
	
	pcard = MakeNameCard("abc", "123");
	LInsert(&list, pcard);
	pcard = MakeNameCard("def", "456");
	LInsert(&list, pcard);
	pcard = MakeNameCard("ghi", "789");
	LInsert(&list, pcard);
	
	compName = "abc";
	if(LFirst(&list, &pcard)) {
		if(!NameCompare(pcard, compName))
			ShowNameCardInfo(pcard);
		else
			while(LNext(&list, &pcard))
				if(!NameCompare(pcard, compName)) {
					ShowNameCardInfo(pcard);
					break;
				}
	}
	
	compName = "def";
	changePhone = "000";
	if(LFirst(&list, &pcard)) {
		if(!NameCompare(pcard, compName))
			ChangePhoneNum(pcard, changePhone);
		else
			while(LNext(&list, &pcard))
				if(!NameCompare(pcard, compName)) {
					ChangePhoneNum(pcard, changePhone);
					break;
				}
	}
	
	compName = "ghi";
	if(LFirst(&list, &pcard)) {
		if(!NameCompare(pcard, compName)) {
			pcard = LRemove(&list);
			free(pcard);
		}
		else
			while(LNext(&list, &pcard))
				if(!NameCompare(pcard, compName)) {
					pcard = LRemove(&list);
					free(pcard);
					break;
				}
	}
	
	printf("Num Of Data: %d \n", LCount(&list));
	
	if(LFirst(&list, &pcard)) {
		ShowNameCardInfo(pcard);
		
		while(LNext(&list, &pcard))
			ShowNameCardInfo(pcard);
	}
	
	return 0;
}

