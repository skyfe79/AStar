#pragma once
#include "pathsearchai.h"

class AStar :
	public PathSearchAI
{
public:
	AStar(void);
	~AStar(void);
	bool searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition);
};
