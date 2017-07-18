#pragma once
/*
 * class AStar
 * 김성철
 *
 * AStar 알고리즘을 나타낸다. 
 * AStar = 거리우선탐색법 + 휴리스틱이다
 * 이 방법은 COST = G + H로 G 는 START에서 현재점까지의 거리이고 H는 현재위치에서 GOAL까지의 추정거리이다.
 * 이 COST을 가지고 다음 진행할 노드를 선택한다.
 */
#include "pathsearchai.h"

/*
 * 추정치 계산 방법
 * DIAGONAL
 * MANHATTAN
 * EUCLIDEAN
 */
enum HEURISTIC_METHOD { DIAGONAL, MANHATTAN, EUCLIDEAN };
class AStar :
	public PathSearchAI
{
private:
	HEURISTIC_METHOD hm;
public:
	AStar(HEURISTIC_METHOD h = MANHATTAN);
	~AStar(void);
	void setHeuristicMethod(HEURISTIC_METHOD h);
	bool searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition);
};
