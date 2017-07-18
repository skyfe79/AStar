#pragma once
/*
 * class PathSearchAI
 * �輺ö
 *
 * �� Ŭ������ ��θ� ã�� AI ����� �⺻ Ŭ�����̴�.
 * �� Ŭ�������� �Ļ��� Ŭ������ 1. �Ÿ��켱Ž������ DFS �� 2. A* Ž������ AStar�̴�.
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
	//�÷��̾ ������ �� �ִ� ����
	IntPoint DIR[8];
	//��������� �Ÿ�
	double	 DIST[8];
	//��������� �ּҺ�� ��� ����
	WaySelectionTool whereShouldIGo;
public:
	PathSearchAI(void);
	~PathSearchAI(void);
	virtual bool searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition) = 0;
	void clear();
};

