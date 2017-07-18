#include "PathSearchAI.h"

#define N	0
#define E	1
#define S	2
#define W	3
#define NE	4
#define SE	5
#define SW	6
#define NW	7


PathSearchAI::PathSearchAI(void)
{
	//플레이어가 갈 수 있는 방향
	DIR[0] = IntPoint(0, -1); //N
	DIR[1] = IntPoint(1,  0); //E
	DIR[2] = IntPoint(0,  1); //S
	DIR[3] = IntPoint(-1, 0); //W
	DIR[4] = IntPoint(1,  1); //NE
	DIR[5] = IntPoint(1, -1); //SE
	DIR[6] = IntPoint(-1,-1); //SW
	DIR[7] = IntPoint(-1, 1); //NW

	DIST[0] = 1;
	DIST[1] = 1;
	DIST[2] = 1;
	DIST[3] = 1;
	DIST[4] = 1.414f;
	DIST[5] = 1.414f;
	DIST[6] = 1.414f;
	DIST[7] = 1.414f;
}

PathSearchAI::~PathSearchAI(void)
{
}

void PathSearchAI::clearClosedList()
{
	//closedList.clear();
}
void PathSearchAI::clearOpenList()
{
	//openList.clear();
}