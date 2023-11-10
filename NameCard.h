#ifndef __NAME_CARD_H__
#define __NAME_CARD_H__

#define NAME_LEN 30
#define PHONE_LEN 30

typedef struct __namecard {
	char name[NAME_LEN];
	char phone[PHONE_LEN];
} NameCard;

NameCard* MakeNameCard(const char* name, const char* phone);
void ShowNameCardInfo(const NameCard* pcard);
int NameCompare(const NameCard* pcard, const char* name);
void ChangePhoneNum(NameCard* pcard, const char* phone);

#endif

