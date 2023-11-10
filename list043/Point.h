#ifndef __POINT_H__
#define __POINT_H__

typedef struct _point {
	int xPos;
	int yPos;
} Point;

void SetPointPos(Point* ppos, const int xPos, const int yPos);
void ShowPointPos(const Point* ppos);
int PointComp(const Point* pos1, const Point* pos2);

#endif

