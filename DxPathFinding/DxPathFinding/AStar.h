#pragma once
/*
 * class AStar
 * �輺ö
 *
 * AStar �˰����� ��Ÿ����. 
 * AStar = �Ÿ��켱Ž���� + �޸���ƽ�̴�
 * �� ����� COST = G + H�� G �� START���� ������������ �Ÿ��̰� H�� ������ġ���� GOAL������ �����Ÿ��̴�.
 * �� COST�� ������ ���� ������ ��带 �����Ѵ�.
 */
#include "pathsearchai.h"

/*
 * ����ġ ��� ���
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
