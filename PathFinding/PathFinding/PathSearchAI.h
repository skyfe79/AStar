#pragma once
#include "Cell.h"
#include "Map.h"
#include "Point.h"
#include <list>
#include <queue>
using namespace std;
typedef std::priority_queue<Cell> WaySelectionTool;
//typedef std::list<Cell> OpenList;
//typedef std::list<Cell> ClosedList;
class PathSearchAI
{
protected:
	//플레이어가 움직일 수 있는 방향
	IntPoint DIR[8];
	double	 DIST[8];
	WaySelectionTool whereShouldIGo;
	//OpenList	openList;
	//ClosedList	closedList;
	void clearClosedList();
	void clearOpenList();
public:
	PathSearchAI(void);
	~PathSearchAI(void);
	virtual bool searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition) = 0;
};

