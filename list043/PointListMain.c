#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"
#include "Point.h"

int WhoIsPrecede(Point* pos1, Point* pos2) {
	if(pos1->xPos < pos2->xPos) return 0;
	else if(pos1->xPos == pos2->xPos) {
		if(pos1->yPos < pos2->yPos) return 0;
		else return 1;
	}
	else return 1;
}

int main() {
	List list;
	Point compPos;
	Point* ppos;
	
	ListInit(&list);
	SetSortRule(&list, WhoIsPrecede);
	
	/* Store 4 Data */
	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 1);
	LInsert(&list, ppos);
	
	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 2);
	LInsert(&list, ppos);
	
	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 1);
	LInsert(&list, ppos);
	
	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 2);
	LInsert(&list, ppos);
	
	/* Print All Datas */
	printf("Data Number: %d \n", LCount(&list));
	
	if(LFirst(&list, &ppos)) {
		ShowPointPos(ppos);
		
		while(LNext(&list, &ppos))
			ShowPointPos(ppos);
	} printf("\n");
	
	/* Delete All Datas whose xPos == 2 */
	compPos.xPos = 2;
	compPos.yPos = 0;
	
	if(LFirst(&list, &ppos)) {
		if(PointComp(ppos, &compPos) == 1) {
			ppos = LRemove(&list);
			free(ppos);
		}
		
		while(LNext(&list, &ppos)) {
			if(PointComp(ppos, &compPos) == 1) {
				ppos = LRemove(&list);
				free(ppos);
			}
		}
	}
	
	/* Print All Datas */
	printf("Data Number: %d \n", LCount(&list));
	
	if(LFirst(&list, &ppos)) {
		ShowPointPos(ppos);
		
		while(LNext(&list, &ppos))
			ShowPointPos(ppos);
	} printf("\n");
	
	return 0;
}

