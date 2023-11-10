#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NameCard.h"

NameCard* MakeNameCard(const char* name, const char* phone) {
	NameCard* newCard = (NameCard*)malloc(sizeof(NameCard));
	
	strcpy(newCard->name, name);
	strcpy(newCard->phone, phone);
	
	return newCard;
}

void ShowNameCardInfo(const NameCard* pcard) {
	printf("Name: %s, Phone: %s \n", pcard->name, pcard->phone);
	return;
}

int NameCompare(const NameCard* pcard, const char* name) {
	return strcmp(pcard->name, name);
}

void ChangePhoneNum(NameCard* pcard, const char* phone) {
	strcpy(pcard->phone, phone);
	return;
}

