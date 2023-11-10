#include <stdio.h>
#include "Point.h"

void SetPointPos(Point* ppos, const int xPos, const int yPos) {
	ppos->xPos = xPos;
	ppos->yPos = yPos;
}

void ShowPointPos(const Point* ppos) {
	printf("(%d, %d) \n", ppos->xPos, ppos->yPos);
}

int PointComp(const Point* pos1, const Point* pos2) {
	if(pos1->xPos == pos2->xPos && pos1->yPos == pos2->yPos) return 0;
	else if(pos1->xPos == pos2->xPos) return 1;
	else if(pos1->yPos == pos2->yPos) return 2;
	else return -1;
}

