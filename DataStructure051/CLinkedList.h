#include "Employee.h"

#ifndef __C_LINKED_LIST_H__
#define __C_LINKED_LIST_H__

#define TRUE  1
#define FALSE 0

typedef Employee Data;

typedef struct _node {
	Data data;
	struct _node * next;
} Node;

typedef struct _CLL {
	Node* tail;
	Node* cur;
	Node* before;
	int numOfData;
} CList;

typedef CList List;



#endif

