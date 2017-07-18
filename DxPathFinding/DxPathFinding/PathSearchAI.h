#pragma once
/*
 * class PathSearchAI
 * 김성철
 *
 * 이 클래스는 경로를 찾는 AI 방법의 기본 클래스이다.
 * 이 클래스에서 파생된 클래스는 1. 거리우선탐색법인 DFS 와 2. A* 탐색법인 AStar이다.
 */
#include "Cell.h"
#include "Map.h"
#include "Point.h"
#include <list>
#include <queue>
using namespace std;
typedef std::priority_queue<Cell> WaySelectionTool;
class PathSearchAI
{
protected:
	//플레이어가 움직일 수 있는 방향
	IntPoint DIR[8];
	//인접노드의 거리
	double	 DIST[8];
	//인접노드중 최소비용 노드 추출
	WaySelectionTool whereShouldIGo;
public:
	PathSearchAI(void);
	~PathSearchAI(void);
	virtual bool searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition) = 0;
	void clear();
};

