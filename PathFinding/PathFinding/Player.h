#pragma once
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
	int getMaxDir();
};

