#pragma once
/*
 * class DFS
 * 김성철
 *
 * 거리우선탐색법 AI
 * 이 방법은 COST = G 로 G 는 START에서 현재점까지의 거리이다.
 * 이 거리만을 가지고 다음 진행할 노드를 선택한다.
 */
#include "pathsearchai.h"
class DFS : public PathSearchAI
{
public:
	DFS(void);
	~DFS(void);
	bool searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition);
};
