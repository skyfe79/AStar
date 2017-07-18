#pragma once
/*
 * class Player
 * 김성철
 *
 * 이 클래스는 AI를 이용하여 맵을 탐색하는 플레이어를 나타낸다.
 * 탐색후 route 멤버에 경로의 좌표가 보관된다.
 */
#include "Map.h"
#include "PathSearchAI.h"
#include "Point.h"
#include <list>
class Player
{
private:
	Map*	ptrMap;
	PathSearchAI* ptrPathSearchAI;
	int		maxDir;
	std::list<IntPoint> route;
public:
	Player(void);
	Player(PathSearchAI* ai, int maxDir = 4);
	Player(const Player& player);
	~Player(void);
	void goesIntoTheMap(Map* m);
	bool searchPath(void);
	int  getMaxDir();
	void setMaxDir(int maxDir);
	void setAi(PathSearchAI* Ai);
};

