#pragma once
/*
 * class DFS
 * �輺ö
 *
 * �Ÿ��켱Ž���� AI
 * �� ����� COST = G �� G �� START���� ������������ �Ÿ��̴�.
 * �� �Ÿ����� ������ ���� ������ ��带 �����Ѵ�.
 */
#include "pathsearchai.h"
class DFS : public PathSearchAI
{
public:
	DFS(void);
	~DFS(void);
	bool searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition);
};
